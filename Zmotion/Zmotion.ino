
#include <EEPROM.h>

#define POT  0  // Poti
#define DN   7  // PD7
#define UP   6  // PD6
#define DIR  8  // PB0
#define STEP 9  // PB1
#define EN   10 // PB2

#define DELAYTIME  10000
#define DELAYSETUP 800

char setupmode = 0;
bool eepromwrite = HIGH;
unsigned int LL = 0xFFFF, UL = 0xFFFF;
unsigned int count = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  EEPROM.get(1, LL);
  EEPROM.get(3, UL);
  
  if (LL == 0xFFFF && UL == 0xFFFF)
  {
    LL = 50;
    UL = 2000;
    EEPROM.put(1, LL);
    EEPROM.put(3, UL);
  }

  analogReference(DEFAULT);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DN, INPUT_PULLUP);
  pinMode(DIR, OUTPUT);
  digitalWrite(STEP, HIGH);
  pinMode(STEP, OUTPUT);
  digitalWrite(EN, LOW);
  pinMode(EN, OUTPUT);

  if (digitalRead(DN) == LOW)
  {
    setupmode = 1;
    Serial.println(F("Setup mode low speed"));
  }
  else if (digitalRead(UP) == LOW)
  {
    setupmode = 2;
    Serial.println(F("Setup mode high speed"));
  }
  else
    Serial.println(F("Normal mode"));
  
  while (digitalRead(UP) == LOW || digitalRead(DN) == LOW);
  delay(100);

  Serial.print(F("LL:"));
  Serial.print(LL);
  Serial.print(F(" UL:"));
  Serial.println(UL);
}

void StepPuls (unsigned int delaytime)
{
  digitalWrite(STEP, LOW);
  delayMicroseconds(delaytime);
  digitalWrite(STEP, HIGH);
  delayMicroseconds(delaytime);
}

void loop() {
  // put your main code here, to run repeatedly:
  static unsigned long start;
  int adc = map(analogRead(POT), 0, 1023, LL, UL);
  
  if (digitalRead(UP) == LOW)
  {
    // Up motion
    digitalWrite(EN, HIGH);
    digitalWrite(DIR, HIGH);
    start = millis();
    StepPuls(adc);
    
    switch (setupmode)
    {
      default:
        break;
      
      case 1:
        count += 80;
        
        if (count > DELAYSETUP)
        {
          count = 0;
          eepromwrite = LOW;
          
          if (--UL < 1)
            UL = 1;
        }
        break;
      
      case 2:
        if (++count > DELAYSETUP)
        {
          count = 0;
          eepromwrite = LOW;
          
          if (--LL < 1)
            LL = 1;
        }
        break;
    }
  }
  else if (digitalRead(DN) == LOW)
  {
    // Down motion
    digitalWrite(EN, HIGH);
    digitalWrite(DIR, LOW);
    start = millis();
    StepPuls(adc);
    
    switch (setupmode)
    {
      default:
        break;
      
      case 1:
        count += 80;
        
        if (count > DELAYSETUP)
        {
          count = 0;
          eepromwrite = LOW;
          
          if (++UL > 16383)
            UL = 16383;
        }
        break;
      
      case 2:
        if (++count > DELAYSETUP)
        {
          count = 0;
          eepromwrite = LOW;
          
          if (++LL > 16383)
            LL = 16383;
        }
        break;
    }
  }
  else
  {
    if ((start + DELAYTIME) < millis())
    {
      digitalWrite(EN, LOW);

      if (setupmode != 0 && eepromwrite == LOW)
      {
        eepromwrite = HIGH;
        Serial.print(F("Save to EEPROM LL:"));
        Serial.print(LL);
        Serial.print(F(" UL:"));
        Serial.println(UL);
        EEPROM.put(1, LL);
        EEPROM.put(3, UL);
      }
    }
  }
}

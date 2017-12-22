# Zmotion
Stepper motor drive for the Z axis of my Paulimot F400-GV milling machine.

It based on a Arduino Nano clone, programmed with a simple sketch to generate the step pulses for the stepper.
Now I can move the milling head up and down without any force in my arms :-)

Hardware:
1. Arduino Nano (Clone)
2. Toggle switch for UP, DOWN and STOP. Connected to the Arduino.
3. Poti (10k Ohm) connected to a analog input of the Arduino. It's adjusts the speed of the motion.
4. Stepper driver module. The inputs Step, Direction and Enable are connected to the Arduino.
5. Power supply thats fits to the stepper driver module. In my case 36 VDC with 8 A.
6. Stepper motor with a holding torque of 8 Nm.
7. Monting bracket for mounting the stepper motor at the top of the Z axis.
8. Mechanic junction from the stepper motor to the top end of the Z spindle.
9. Handheld housing for the Arduino, switch and poti.

Software:
Simple contorl loop. If the user press down a button the Arduino enables the stepper dirver and outputs step pulses.
After releasing the button the stepper is enabled for 30 seconds. After that it switched off.
The speed of the stepper pulses are proportional to the analog voltage from the poti.
To get a proper range of speed, it is possible to set minimum and maximum speed. Both values are saved in the EEPROM.

Mechanic:
Adapter plate to mount the stepper. It's a simple sheet of metal.
The double junction between stepper motor shaft and Z spindle and the adapter to connect the junction to the spindel (trapeze thread with OD 25 mm and 5 mm pitch) I have ordered from http://www.maedler.de.
At one half of the nut I have removed the inner thread to fit the junction. I added four screws / theads to tighten the nut after I cut them into two parts. So I can fix the junction to the Z spindle and at the same time I have a adjustment of the junction lenght.

May you like it!

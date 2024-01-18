# LEDs-control-Arduino

Arduino script controlling Neopixel LEDs using an infrared remote.
The Arduino Nano Every faces difficulty in simultaneously constantly changing LED colors 
(like when the rainbow mode is activated) and checking for input from an IR receiver. 
This issue is related to how frequently the Adafruit library utilizes the processor. 

To address this, I have implemented two options for setting the LEDs into rainbow mode. 
The first option involves setting it for a few minutes, while the second option locks it with a while-true loop. 
The loop can only be interrupted by using the reset button, 
conveniently located next to my desk and bed.
While this solution works well for me, I acknowledge that it may not be the most elegant or professional approach to the problem.

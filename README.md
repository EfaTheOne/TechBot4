# TechBot4</br>

## What is it?
The TechBot4 is a ESP32 WROOM 32 N8 based pen testing tool. It acts exactly like the ESP32 'Maruader' by JustCallMeKoKo and preforms the same functions, this is just a clone of the work already done. The device 
will have a 2.0 inch 320x240 pixel display with an EYESPI connector and an added MircoSD card holder. The part is made by Adafruit and is an IPS display having a wide angle of viewing. It will run on 3.7V battery 
power and have 1500mAh, the battery will need a battery management system but it is still a work in progress. It will be navigated by 6 buttons with one in the middle used to select and the four around to 
navigate left, right, up and down. It will also need 1 more button to reset and boot the board and I need to add a switch to turn on and off the board(I could make the switch be connected directly to the battery 
but it risks having a voltage shock every time lowering the life of the TechBot. I could wire the switch a GPIO pin but the battery would be constantly drained. I need to do some more research to find out whats 
best.) I need too find all the parts, design a schematic with proper wiring and be efficent as possible to have the longest battery and component life. The PCB needs to be also designed efficently and could use 
some ground planes which i've recently been learning about. Then the 3D model, I want it to be stylish, fit in mypocket and be durable. My first pick for the type of filement would be PETG but if I aqiure better 
filiment I can use it to make a very durable case. 

## Purpose
I am an avid learner in the IT world and want to know how to use tools to help secure networks and privacy now that AI has such a big influence. I also know that learning these skills using the TechBot4 wil be useful to possibly get an IT or engineering job in the future. The TechBot4 is such a cool project that I have been excited about and is the fourth version of the TechBot series.

## Checked Source Parts:
### PCBA Parts:</br>
IP5306-I2C | LCSC Part#:C488349

ESP32-WROOM-32U-N8 | JLCPCB Part #C529579

KH-CL0.5-H2.0-18PIN | JLCPCB Part #C2797195

XC6220B331MR-G | JLCPCB Part #C86534

CH340C | LCSC Part #C84681

HX TYPE-C 16PIN | LCSC Part #C5178539

JST S2B-PH-K-S(LF)(SN) | LCSC Part #C173752

YIZHI YZA-056-5.0 | LCSC Part #C49108648 | 7x (5x for nav 2x for boot and reset)

C&K PCM12SMTR | LCSC Part #C221841

S8050 | JLCPCB Part #C266592 | 2x

0603WAJ0103T5E | JLCPCB Part #C15401 | 5x

0603WAF1001T5E | JLCPCB Part #C21190 | 2x

0603WAF5101T5E | JLCPCB Part #C23186 | 2x

CL21A106KOQNNNE | JLCPCB Part #C1713 | 4x

CL10B104KA8NNNC | JLCPCB Part #C1590 | 4x

### Separate Parts:</br>
2.0" 320x240 Color IPS TFT Display with microSD Card Breakout - ST7789 EYESPI | https://www.adafruit.com/product/4311
 
EYESPI Cable - 18-pin 50mm long Flex PCB (FPC) A-B Type | https://www.adafruit.com/product/5462

Lithium Ion Polymer Battery - 3.7v 2500mAh | https://www.adafruit.com/product/328

SeedStudio RF Anntena | Already have part

3D Printed Case | Made with PETG for durablitly

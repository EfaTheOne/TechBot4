# TechBot4
Part List
-https://www.adafruit.com/product/4311?srsltid=AfmBOopb0Z9bzDvCusqRwQuAI18eDbWa0XD_RDmqvqr7_hGu1QP7qzMz

-https://jlcpcb.com/partdetail/EspressifSystems-ESP32_WROOM_32N8/C529582

Unchecked Sourced Parts:</br>
-Power Management (ESOP-8), PCBA Number: C181692 1x</br>

(Power Management	IP5306 (ESOP-8)	1	C181692	Battery Charger & 5V Boost (Standard))</br>

-Inductor (1.0uH, CD43, ~2.5A) PCBA Number: C409617 1x</br>

(Inductor	1R0 (1.0µH, CD43, ~2.5A)	1	C409617	Power Inductor for IP5306 (SW Pin))</br>

-Regulator (SOT-223) PCBA Number: C6186 1x</br>

(Regulator	AMS1117-3.3 (SOT-223)	1	C6186	Steps down 5V to 3.3V for ESP32)</br>

-Capacitor (0603, X5R, 10V) PCBA Number: C59461 2x</br>

(Capacitor	22µF (0603, X5R, 10V)	2	C59461	IP5306 Input/Output Filtering))</br>

-Capacitor (0603, X5R, 16V) PCBA Number: C19702 3x</br>

(Capacitor	10µF (0603, X5R, 16V)	3	C19702	AMS1117 In/Out, ESP32 Power)</br>

-Capacitor (0603, X7R, 50V) PCBA Number: C14663 1x</br>

(Capacitor	0.1µF (0603, X7R, 50V)	1	C14663	ESP32 Decoupling / Filter)</br>

-Resistor (0603, 1%, 5.1kΩ) PCBA Number: C23178 2x</br>

(Resistor	5.1kΩ (0603, 1%)	2	C23178	USB-C CC Pin Pull-downs (Required for C-to-C charging))</br>

-Resistor (0603, 1%, 1kΩ) PCBA Number: C21190 1x</br>

(Resistor	1kΩ (0603, 1%)	1	C21190	LED limiting or EN Pull-up (See notes))</br>

-USB C Port (16-Pin, SMD) PCBA Number: C165948 1x</br>

(USB Port	USB Type-C 16-Pin (SMD)	1	C165948	Charging Input (Korean Hroparts))</br>

-JST-PH Connector (Vertical SMD) PCBA Number: C396123 1x</br>

(Connector	JST-PH 2-Pin (Vertical SMD)	1	C396123	Battery Connector)</br>

-ESP32 (ESP32-WROOM-32-N8) PCBA Number: C529582 1x

(ESP32	ESP32-WROOM-32-N8	1	C529582	Microcontroller (User specified))</br>

-Tactile Switch (6x6mm, Through-Hole) PCBA Number: C34260 6x</br>

(Switch	Tactile Switch 6x6mm (Through-Hole)	6	C34260	Navigation & Reset Buttons)</br>

-Resistor (0603, 1%, 10kΩ) PCBA Number: C23177 6x</br>

(Resistor	10kΩ (0603, 1%)	6	C23177	Pull-down Resistors for Buttons)</br>

-FPC Connector for IPS Display (EYESPI-Compatible) PCBA Number: C55234 1x</br>

(FPC Connector	0.5mm Pitch, 40-Pin Bottom Contact, SMD	1	C55234	Adafruit 2.0 inch IPS Display FPC Connection)</br>


# What is it?
The TechBot4 is a ESP32 WROOM 32 N8 based pen testing tool. It acts exactly like the ESP32 'Maruader' by JustCallMeKoKo and preforms the same functions, this is just a clone of the work already done. The device will have a 2.0 inch 320x240 pixel display with an EYESPI connector and an added MircoSD card holder. The part is made by Adafruit and is an IPS display having a wide angle of viewing. It will run on 3.7V battery power and have 1500mAh, the battery will need a battery management system but it is still a work in progress. It will be navigated by 6 buttons with one in the middle used to select and the four around to navigate left, right, up and down. It will also need 1 more button to reset and boot the board and I need to add a switch to turn on and off the board(I could make the switch be connected directly to the battery but it risks having a voltage shock every time lowering the life of the TechBot. I could wire the switch a GPIO pin but the battery would be constantly drained. I need to do some more research to find out whats best.) I need too find all the parts, design a schematic with proper wiring and be efficent as possible to have the longest battery and component life. The PCB needs to be also designed efficently and could use some ground planes which i've recently been learning about. Then the 3D model, I want it to be stylish, fit in mypocket and be durable. My first pick for the type of filement would be PETG but if I aqiure better filiment I can use it to make a very durable case. 

# Purpose
I am an avid learner in the IT world and want to know how to use tools to help secure networks and privacy now that AI has such a big influence. The TechBot4 is such a cool project that I have been excited about and is the fourth version of the TechBot series.



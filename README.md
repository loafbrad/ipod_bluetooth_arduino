# Bluetooth control for iPod based on ATtiny45

Control an AirFly Pro Bluetooth without pressing a button! Most iPod Bluetooth mods require exposing a button to power cycle the Bluetooth or pair a new set of headphones. This project enables users to connect an ATtiny45 GPIO pin to a Bluetooth module and receive commands of UART to perform actions.

Space utilization for Attiny45:



(As of August 4th, 2025)
_______________________________________________
| Storage   |  Available   |  Utilization      |
|-----------|--------------|-------------------|
|  Flash    |   4096 Bytes |  3714 Bytes (90%) |
|  RAM      |   256 Bytes  |  133 Bytes (51%)  |
|-----------|--------------|-------------------|

Sketch uses 3714 bytes (45%) of program storage space. Maximum is 8192 bytes.
Global variables use 149 bytes (29%) of dynamic memory, leaving 363 bytes for local variables. Maximum is 512 bytes.

Currently supported actions on AirFly:
- Pair headphones
- Power on AirFly
- Power off AirFly

Clearing Bluetooth memory on AirFly with side button is not currently supported.

Pre-requisites:
 - Arduino IDE
 - ATTinyCore (https://github.com/SpenceKonde/ATTinyCore)
This core can be installed using the boards manager. The boards manager URL is:


    In "Additional Boards Manager URLs", add: http://drazzy.com/package_drazzy.com_index.json
    In the board manager, search for "ATTinyCore by Spence Konde", install



Compiling and programming:
Select board "ATtiny25/45/85 (No bootloader)"
Tools->Chip: Select ATtiny45
Tools->Programmer: Select programmer of choice.

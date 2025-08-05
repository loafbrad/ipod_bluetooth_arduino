# iPod Classic Bluetooth module control based on ATtiny45

For use with [Rockbox build with Bluetooth support](https://github.com/loafbrad/rockbox).

Tested iPods:

- [ ] ~~iPod 1st/2nd gen~~ (not supported/not attempting)
- [ ] iPod 3rd gen*
- [x] iPod 4th gen/iPod Photo (headphone accessory port)
- [x] iPod 5th gen/iPod Video
- [ ] iPod 6th/7th gen/iPod Classic
- [ ] iPod mini 1st/2nd
- [ ] iPod nano 1st gen
- [x] iPod nano 2nd gen

*iPod 3rd gen serial currently not available on Rockbox unconfirmed.

Control an [AirFly Pro Bluetooth module](https://www.twelvesouth.com/products/airfly) without pressing a button! This project enables users to connect an ATtiny45 GPIO pin to a Bluetooth module and receive commands of UART to perform actions. 

Currently supported actions on AirFly:

- Pair headphones
- Power on AirFly
- Power off AirFly

Clearing Bluetooth memory on AirFly with side button is not currently supported.

# ATtiny45 Pinout Description
(TODO)

# Required Hardware:

- ATtiny45 microcontroller (to install in iPod and connect to AirFly)
- Programmer (Any ISP programmer, example will show Arduino UNO as ISP)

# Pre-requisites:

 - [Arduino IDE](https://www.arduino.cc/en/software/)
 - [ATTinyCore](https://github.com/SpenceKonde/ATTinyCore)

# Setup
## 0. Download Arduino IDE

Download and install the Arduino IDE from the link above. At this time everything has been tested with **Arduino IDE v2.3.4**. Follow instructions in installer.

## 1. Setup Arduino UNO as programmer (skip if you are using a different programmer like AVRISPmkII)



## 2. Install ATtiny board support

- On Linux/Windows: `File->Preferences`. On Mac: `Arduino IDE->Settings...`.
- Find "Additional boards manager URLs" and paste the following: http://drazzy.com/package_drazzy.com_index.json.
- Press "OK".
- Select `Tools->Boards->Boards Manager` and search for `"ATTinyCore by Spence Konde"`. Install the package.

## 3. Select board and chip for project

- Select `Tools->Board->ATtinyCore->ATtiny25/45/85 (No bootloader)`
- Select `Tools->Chip->ATtiny45`
- Make sure the following settings are set:
  - `Clock source: 8MHz internal`
  - `LTO: Enabled`
  - `Save EEPROM: doesn't matter`
  - `millis()/micros(): enabled`
  - `Timer 1 clock: CPU (CPU Frequency)`


## 4. Programming ATtiny45 with Arduino UNO

- `Tools->Programmer->Arduino as ISP`
- Click the `Verify` button in the top left corner of the window to verify the program before it get's programmed to the ATtiny45.
- If there are no program errors, select `upload` and the program will be uploaded to the ATtiny45 via the Arduino UNO.

These steps only cover programming the microcontroller with the firmware provided.

# Misc.

## Space utilization for Attiny45:

(As of August 4th, 2025)

| Storage   |  Available   |  Utilization      |
|-----------|--------------|-------------------|
|  Flash    |   4096 Bytes |  3714 Bytes (90%) |
|  RAM      |   256 Bytes  |  133 Bytes (51%)  |

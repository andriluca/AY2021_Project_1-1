# AY2021_Project_1-1

## Requirements

### Software
1. python 3.7.9
1. PSoC Creator 4.4

### Hardware
1. PSoC 5LP
1. LIS3DH
1. TMP36 (Temperature sensor)
1. 24LC512 (Ext. EEPROM)


## Installation

For a basic installation it's required to run these commands on a prompt.

```[bash]

pip install -r requirements.txt

garden install graph

```

If y\_label on graphs is upside-down change value (y.angle) in line 428 in graphs'init.

## Users Guide

### Graphic User Interface

![GUI Screenshot](/Images/GUI_Screenshot.png)

1. Ports: selects the COM port connected to the device.
1. Connect/Disconnect: toggles the PSoC-GUI communication.
1. Start/Stop Device: toggles data acquisition (N.B if Stop Device is pressed, the eeprom\_index is maintained).
1. Print Data: returns the stored data in a graphical format and automatically saves the session into a [\%H-\%M-\%S]data.csv. Data are stored in directories named as \%F. Once done device is turned off and EXT\_EEPROM is reset.
1. Change Settings: allows to select different configurations according to user request, afterwards resets EXT\_EEPROM to avoid data inconsistencies.
	1. FSR: full scale range that goes from ±2g to ±16g.
	1. ODR: output data rate that can be selected as 1Hz, 10Hz, 25Hz, 50Hz.
	1. Temp. Format: selects the temperature measurement unit.
	1. EEPROM\_Saving: enables/disables EXT\_EEPROM data saving.

### On-Board Controls 

1. On-Board Button: if pressed for more than 1s toggles device state between Start/Stop (same as GUI), if pressed for more than 5s reset the EXT\_EEPROM and then restore the last configuration.

### Feedbacks 

1. On-Board LED: it's toggled among four states.
	1. Period 1s	, DC 0%: device is in a Stop condition (OFF / IDLE).
	1. Period 1s	, DC 50%: device is working and saving data in EXT\_EEPROM.
	1. Period 0.25s	, DC 50%: device is no longer sampling because EXT\_EEPROM is full.
	1. Period 1s	, DC 100%: EXT\_EEPROM is resetting (the pulse duration depends on the n° of pages been written).
1. External LED: switches on when EXT\_EEPROM is being read and data are sent through UART. 



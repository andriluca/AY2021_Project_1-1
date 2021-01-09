# AY2021\_Project\_1-1

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

### Circuit

![Electrical Schematic](./Images/Schematico.png)

### Dependencies

For a basic installation it's required to run these commands on a prompt.

```shell
pip install -r requirements.txt

garden install graph
```

If y\_label on graphs is upside-down change value (y.angle) in line 428 in Graphs' init.

## Users Guide

### Graphic User Interface

![GUI Screenshot](./Images/GUI_Screenshot.png)

| 	| Command                   | Description                                                                                                                                                                                                         |
| --- 	| ---                       | ---                                                                                                                                                                                                                 |
| 1 	| **Ports**              | Selects the COM port to which the device is connected.                                                                                                                                                              |
| 2 	| **Conn./Disconnect**   | Toggles the PSoC-GUI communication.                                                                                                                                                                                 |
| 3 	| **Start/Stop Device**  | Toggles data acquisition (N.B if Stop Device is pressed, the previous acquisitions are still maintained).                                                                                                                          |
| 4 	| **Print Data**         | Returns the stored data in graphical format and automatically saves the session into a *[\%H-\%M-\%S]data.csv*. Data are stored in directories named as *\%F/*. Once done device is turned off and EXT\_EEPROM is reset. |
| 5 	| **Change Settings**    | Allows to select different configurations according to user request, afterwards resets EXT\_EEPROM to avoid data inconsistencies.                                                                                   |
| 6 	| **FSR**                | Full scale range that goes from ±2g to ±16g.                                                                                                                                                                        |
| 7 	| **ODR**                | Output data rate that can be selected as 1Hz, 10Hz, 25Hz, 50Hz.                                                                                                                                                     |
| 8 	| **Temp. Format**       | Selects the temperature measurement unit.                                                                                                                                                                           |
| 9 	| **EEPROM\_Saving**     | Enables/disables EXT\_EEPROM data saving.                                                                                                                                                                           |

### On-Board Controls

1. On-Board Button: if pressed for more than 1s toggles device state between Start/Stop (same as GUI), if pressed for more than 5s reset the EXT\_EEPROM and then restore the last configuration.

### Feedbacks

1. **On-Board LED**: it's toggled among four states.
	1. *Period 1s, DC 0%*: device is in a Stop condition (OFF / IDLE).
	1. *Period 1s, DC 50%*: device is working and saving data in EXT\_EEPROM.
	1. *Period 0.25s, DC 50%*: device is no longer sampling because EXT\_EEPROM is full.
	1. *Period 1s, DC 100%*: EXT\_EEPROM is resetting (the pulse duration depends on the n° of pages been written).
1. **External LED**: switches on when EXT\_EEPROM is being read and data are sent through UART.


## For more technical info

### Datasheets
- ![Datasheet TMP36](./Refs/TMP_DATASHEET.pdf)
- ![Datasheet LIS3DH](./Refs/LIS3DH_DATASHEET.pdf)
- ![Datasheet EEPROM](./Refs/EEPROM_DATASHEET.pdf)


### Application Notes
- ![Application Notes LIS3DH](./Refs/LIS3DH_APPLICATION_NOTES.pdf)
- ![Application Notes EEPROM](./Refs/EEPROM_APPLICATION_NOTES.pdf)

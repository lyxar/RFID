# MFRC522 with ATMega2560

## Introduction
This solution is designed and tested with MFRC522 RFID module and ATMega2560. The program is design as a key authorization program, it could be used to open doors, checking in to work or anything that could require some sort of authorization. 
In this solution an LCD display is used to visually see the result of the program, this can be substituted by using the terminal.

<img src="https://i.imgur.com/o60q8iR.jpg"/>

### Useful links

<a href="https://www.nxp.com/docs/en/data-sheet/MFRC522.pdf">MFRC522 RFID datasheet</a>

## Component list

<ul>
  <li>RFID-RC522 Module</li>
  <li>Arduino Mega2560</li>
  <li>Atmel encoder</li>
  <li>Various wires for connecting</li>
  <li>Optional:</li>
  <ul>
  <li>LCD Display</li>
  <li>Potentiometer</li>
  </ul>
</ul>

<img src="https://i.imgur.com/E6LOxOA.png"/>

## MFRC522 RFID Module
The MFRC522 module is used with the SPI bus in this solution. Where the MFRC522 acts as the slave and the MEGA2560 acts as the master.   
Version number of the specifik module can be found in the VersionReg described in the <a href="https://www.nxp.com/docs/en/data-sheet/MFRC522.pdf">MFRC522 RFID datasheet</a>
<a href="https://github.com/miguelbalboa/rfid/blob/master/src/MFRC522.h?fbclid=IwAR2iSVsBzOX7-jfG59Ga0vNzBbzKeCF6gywc9I_DGTQwayT9-MvHw8BFTec">Version number Source</a>

<a href="https://lastminuteengineers.com/how-rfid-works-rc522-arduino-tutorial/"><img src="https://lastminuteengineers.com/wp-content/uploads/2018/07/RC522-RFID-Reader-Writer-Module-Pinout.jpg"/></a>


## Known bugs
The program sometimes overwrite the previous line when displaying information on the terminal.
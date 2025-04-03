# Offgrid Photovoltaic Management System 
 ### Project contains:
 #### Power and mechanical part:
 - PV panels connection and DIY Ground Mount structure 
 - Installation and wiring of the EASUN inverter
#### Managemenet system part:
- [BMS for lead-acid batteries](#bms-for-lead-acid-batteries) - equalize battery, protect from large charge/discharge currents, montors battery state (temp, voltage)
- [ESP32 Master module](#esp32-master-module) - it communicate with EASUN  converter, BMS, Homa Assistant, Energy Meters and sensor. Supervise all system work propertly.
- [Home Assistant integration](#home-assistant-integration) - integrate ESP Master module with HA for easy and compact managment (local and remote access)
- [Power Tracking module](#power-tracking-module) - it is used to regulate heater power accordingly to avaible energy from PV
  



# Management System diagram:

<a href="docs\PV_management_system_diagram.png"><img src="docs\PV_management_system_diagram.png" alt="System Diagram" style="width:400px"></a>



## BMS for lead-acid batteries
BMS have several tasks:
- Battery Balancer equalizes the state of charge of two series connected 12V batteries. If one of battery is overcharged it discharge it using resistor.
- Bidirectional DC-DC converter - protect battery from too much discharge or charge current
- Battery monitoring - measurment of temperature of each battery and voltage.


## ESP32 Master module

## Home Assistant integration

## Power Tracking module

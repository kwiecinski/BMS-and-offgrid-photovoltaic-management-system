# Offgrid Photovoltaic Management System 
 ### Project contains:
 #### Power and mechanical part
 - PV panels connection and DIY Ground Mount structure 
 - Installation and wiring of the EASUN inverter
#### Managemenet system part
- [Offgrid Photovoltaic Management System](#offgrid-photovoltaic-management-system)
    - [Project contains:](#project-contains)
      - [Power and mechanical part](#power-and-mechanical-part)
      - [Managemenet system part](#managemenet-system-part)
- [Management System diagram:](#management-system-diagram)
  - [BMS for lead-acid batteries](#bms-for-lead-acid-batteries)
  - [ESP32 Master module](#esp32-master-module)
  - [Home Assistant integration](#home-assistant-integration)
  - [Power Tracking module](#power-tracking-module)
  



# Management System diagram:

<a href="docs\PV_management_system_diagram.png"><img src="docs\PV_management_system_diagram.png" alt="System Diagram" style="width:400px"></a>



## BMS for lead-acid batteries
BMS have several tasks:
- Battery Balancer equalizes the state of charge of two series connected 12V batteries. If one of battery is overcharged it discharge it using resistor.
- Bidirectional DC-DC converter - protect battery from too much discharge or charge current
- Battery monitoring


## ESP32 Master module

## Home Assistant integration

## Power Tracking module

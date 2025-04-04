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


## PV panels connection and DIY Ground Mount structure 
Moduły fotowoltaiczne które użyłem do budowy mojej instalacji PV to Trina Solar TSM-245. Są to panele używane które kupiłem za ok 40$

[📄 **Trina Solar TSM-245 datasheet**](docs/datasheets/TSM-PC05_trinasolar.pdf)


<table>
  <tr>
    <td align="center">
      <a href="docs\photos\ground-mount-structure\solar-panel-technical-data.jpg">
        <img src="docs\photos\ground-mount-structure\solar-panel-technical-data.jpg" width="200">
      </a><br />
      <sub>PV module TSM-245 - technical data</sub>
    </td>
    <td align="center">
      <a href="docs\photos\ground-mount-structure\solar-panel-diodes.jpg">
        <img src="docs\photos\ground-mount-structure\solar-panel-diodes.jpg" width="200">
      </a><br />
      <sub>PV module TSM-245 - internal diode wiring</sub>
    </td>
  </tr>
</table>


<table>
  <tr>
    <td align="center">
      <a href="docs\photos\ground-mount-structure\solar-panel-front.jpg">
        <img src="docs\photos\ground-mount-structure\solar-panel-front.jpg" width="200">
      </a><br />
      <sub>PV module TSM-245 - front</sub>
    </td>
    <td align="center">
      <a href="docs\photos\ground-mount-structure\solar-panel-back.jpg">
        <img src="docs\photos\ground-mount-structure\solar-panel-back.jpg" width="200">
      </a><br />
      <sub>PV module TSM-245 - back</sub>
    </td>
  </tr>
</table>



## BMS for lead-acid batteries
BMS have several tasks:
- Battery Balancer equalizes the state of charge of two series connected 12V batteries. If one of battery is overcharged it discharge it using resistor.
- Bidirectional DC-DC converter - protect battery from too much discharge or charge current
- Battery monitoring - measurment of temperature of each battery and voltage.

BMS steruje mikrokontorler AVR64DD28. Aby go zaprogramować niezbędny jest programator obsługujący UPDI.
Ja korzystam z SerialUPDI (jego zmodyfikowaną wersje z możlością programowania HV oraz izolacją znajdziesz tutaj: SerialUPDI link)
Środowisko programowania: MPLAB X IDE v6.20 oraz komilator XC8 v0.00

Do pomiaru napiecia i prądu akumulatorów wykorzystuje INA226 oraz przetwornik ADC wbudowany w mikrokontoler.
INA226 mierzy napięcie całego pakietu czyli akumulatora dolnego (BATT_LOW) oraz górnego (BATT_HIGH). 
Wykonuje również pomiar na rezystorze pomiarowym który odpowiada prądowi całego pakietu. 
INA226 jest dwukierunkowa dlatego jest możliwy pomiar prądu ładowania i rozładowania.
ADC mierzy napięcie tylko BATT_LOW. Różnica napięć z INA226 oraz z ADC daje napięcie BATT_HIGH.

Blanansowanie ogniw jest dokonywane z użyciem rezystorów dużej mocy.
Każdy z rezystorów jest wpięty równolegle do akumulatora i załączany tranzystorem mosfet sterowanym z MCU.
MCU steruje tranzystorami z wykorzystaniem PWM który jest generowany sprzętowo za pomocą Timera TCD. 
Timer obsługuje dwa wyjścia WOA oraz WOB, które sa przypisane do odpowiednich pinów MCU.
TCD mam możliwość generowania




## ESP32 Master module

## Home Assistant integration

## Power Tracking module

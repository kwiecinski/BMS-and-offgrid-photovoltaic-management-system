# Offgrid Photovoltaic Management System 
 ### Project contains:
 #### A. Power and mechanical part:

  1. [ Photovoltaic modules](#1-photovoltaic-modules)  
  2. [ Concrete base mounting](#2-concrete-base-mounting)  
  3. [ Metalworking and welding mounting bases and angle bar](#3-metalworking-and-welding-mounting-bases-and-angle-bar)  
  4. [ Painting mounting base, angle bars and perforated profiles](#4-painting-mounting-base-angle-bars-and-perforated-profiles)  
  5. [ PV mountings to perforated profiles](#5-pv-mountings-to-perforated-profiles)  
  6. [ Assembly of PV installation](#6-assembly-of-pv-installation)  
  7. [ Fully assembled PV installation](#7-fully-assembled-pv-installation)<br>
  8. [ Underground Cable Installation and Connection to the Building](#8-underground-cable-installation-and-connection-to-the-building)
 
B. [EASUN inverter - description, installation schematic and wiring](#easun-inverter---description-installation-and-wiring)
#### C. Managemenet system part:
- [BMS for lead-acid batteries](#bms-for-lead-acid-batteries) - equalize battery, protect from large charge/discharge currents, montors battery state (temp, voltage)
- [ESP32 Master module](#esp32-master-module) - it communicate with EASUN  converter, BMS, Homa Assistant, Energy Meters and sensor. Supervise all system work propertly.
- [Home Assistant integration](#home-assistant-integration) - integrate ESP Master module with HA for easy and compact managment (local and remote access)
- [Power Tracking module](#power-tracking-module) - it is used to regulate heater power accordingly to avaible energy from PV
  



## PV panels connection and DIY Ground Mount structure 

### 1. Photovoltaic modules
The photovoltaic modules I used in my PV installation are Trina Solar TSM-245. These are used panels that I purchased for around $40 each. The installation consists of 8 modules connected in series.

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


The first stage was marking the mounting points for the mouting base structure. The entire construction has eight support points. After digging holes in the ground, they were filled with concrete, and concrete bases with reinforcement were embedded in them. I had plenty of these as production waste from the company where I work. They are typically used for mounting lightning protection masts on flat building roofs.

Inside each base, there is reinforcement and four M16 threads. I modified the bases by drilling holes on the opposite side, and I welded additional reinforcement to the bottom using scrap metal, which helps to improve the structural stability.

Before mounting the structure to the concrete bases, the contact surfaces were coated with a bituminous compound to prevent corrosion.

### 2. Concrete base mounting

<table>
  <tr>
    <td align="center" colspan="2">
      <a href="docs\photos\ground-mount-structure\concrete-fixing-with-reinforcement.jpg">
        <img src="docs\photos\ground-mount-structure\concrete-fixing-with-reinforcement.jpg" width="410">
      </a><br />
      <sub>Concrete base with reinforcement</sub>
    </td>
  </tr>
  <tr>
    <td align="center">
      <a href="docs/photos/ground-mount-structure/concrete_base.jpg">
        <img src="docs/photos/ground-mount-structure/concrete_base.jpg" width="200">
      </a><br />
      <sub>Concrete base with mounting thread</sub>
    </td>
    <td align="center">
      <a href="docs/photos/ground-mount-structure/concreete-with-bitumen.jpg">
        <img src="docs/photos/ground-mount-structure/concreete-with-bitumen.jpg" width="200">
      </a><br />
      <sub>Concrete base with bitumen</sub>
    </td>
  </tr>
</table>
<br>

Visible in the photo below is a set of four steel mounting bases of varying heights, with welded pipes and mounting plates. Each element was made with consideration for uneven ground, that is why there are different pipe lengths. Each base has a bottom plate with holes for M16 bolts, intended for anchoring to a concrete base. On the table next to them lies a long steel angle bar, which was welded from several sections. After welding, the elements were ground down. The photo was taken after the mechanical work was completed, during surface preparation for painting. 
All the steel used for building the PV mouting structure comes from scrap yard.

### 3. Metalworking and welding mounting bases and angle bar
<br>
<table>
  <tr>
    <td align="center" colspan="2">
      <a href="docs\photos\ground-mount-structure\steel-workshop-and-painting-12.jpg">
        <img src="docs\photos\ground-mount-structure\steel-workshop-and-painting-12.jpg" width="410">
      </a><br />
      <sub>Metalworking and welding mounting bases and angle bar</sub>
    </td>
  </tr>
  <tr>
    <td align="center" colspan="2">
      <a href="docs\photos\ground-mount-structure\steel-workshop-and-painting-13.jpg">
        <img src="docs\photos\ground-mount-structure\steel-workshop-and-painting-13.jpg" width="410">
      </a><br />
      <sub>Steel angle bar before painting</sub>
    </td>
  </tr>
    <tr>
    <td align="center" colspan="2">
      <a href="docs\photos\ground-mount-structure\steel-workshop-and-painting-14.jpg">
        <img src="docs\photos\ground-mount-structure\steel-workshop-and-painting-14.jpg" width="410">
      </a><br />
      <sub>Longer mounting base  while painting</sub>
    </td>
  </tr>
</table>

Longer mounting base are responsible for the solar incidence angle which in this case is 40 degrees
### 4. Painting mounting base, angle bars and perforated profiles
<table>
  <tr>
    <td align="center" colspan="2">
      <a href="docs\photos\ground-mount-structure\steel-workshop-and-painting-11.jpg">
        <img s    <td colspan="2" style="text-align: left;">
      <div style="width: 200px;">
        <a href="docs/photos/ground-mount-structure/steel-workshop-and-painting-11.jpg">
          <img src="docs/photos/ground-mount-structure/steel-workshop-and-painting-11.jpg" width="200" style="display: block;">
        </a>
        <div style="text-align: center;">
          <sub>Shorter and longer mounting base after painting</sub>
        </div>
      </div>
    </td>
  </tr>
  <tr>
    <td colspan="2" style="text-align: left;">
      <div style="width: 410px;">
        <a href="docs/photos/ground-mount-structure/steel-workshop-and-painting-10.jpg">
          <img src="docs/photos/ground-mount-structure/steel-workshop-and-painting-10.jpg" width="410" style="display: block;">
        </a>
        <div style="text-align: center;">
          <sub>Shorter mounting base after painting</sub>
        </div>
      </div>
    </td>
  </tr>
  <tr>
    <td colspan="2" style="text-align: left;">
      <div style="width: 410px;">
        <a href="docs/photos/ground-mount-structure/steel-workshop-and-painting-01.jpg">
          <img src="docs/photos/ground-mount-structure/steel-workshop-and-painting-01.jpg" width="410" style="display: block;">
        </a>
        <div style="text-align: center;">
          <sub>Perforated profiles, often used for fixing cable tray systems, <br>turned out to be ideal as internal panel brackets. <br>Since they are galvanized, they must be painted <br>with zinc-compatible paint.</sub>
        </div>
      </div>
    </td>
  </tr>
  <tr>
    <td colspan="2" style="text-align: left;">
      <div style="width: 410px;">
        <a href="docs/photos/ground-mount-structure/steel-workshop-and-painting-02.jpg">
          <img src="docs/photos/ground-mount-structure/steel-workshop-and-painting-02.jpg" width="410" style="display: block;">
        </a>
        <div style="text-align: center;">
          <sub>Longer mounting bases drying after painting</sub>
        </div>
      </div>
    </td>
  </tr>
</table>



### 5. PV Mountings to perforated profiles

<table>
  <tr>
    <td colspan="2" style="text-align: left;">
      <div style="width: 410px;">
        <a href="docs/photos/ground-mount-structure/steel-workshop-and-painting-03.jpg">
          <img src="docs/photos/ground-mount-structure/steel-workshop-and-painting-03.jpg" width="410" style="display: block;">
        </a>
        <div style="text-align: center;">
          <sub>Sheet metal used to prepare panel mounts for perforated profiles</sub>
        </div>
      </div>
    </td>
  </tr>

  <tr>
    <td colspan="2" style="text-align: left;">
      <div style="width: 410px;">
        <a href="docs/photos/ground-mount-structure/steel-workshop-and-painting-04.jpg">
          <img src="docs/photos/ground-mount-structure/steel-workshop-and-painting-04.jpg" width="410" style="display: block;">
        </a>
        <div style="text-align: center;">
          <sub>Panel mounts for perforated profiles before welding and drilling</sub>
        </div>
      </div>
    </td>
  </tr>

  <tr>
    <td colspan="2" style="text-align: left;">
      <div style="width: 410px;">
        <a href="docs/photos/ground-mount-structure/steel-workshop-and-painting-05.jpg">
          <img src="docs/photos/ground-mount-structure/steel-workshop-and-painting-05.jpg" width="410" style="display: block;">
        </a>
        <div style="text-align: center;">
          <sub>Panel mounts for perforated profiles. The central M10 bolt is used to attach to the perforated profile, and the two M8 holes are for screwing PV panels</sub>
        </div>
      </div>
    </td>
  </tr>

  <tr>
    <td colspan="2" style="text-align: left;">
      <div style="width: 410px;">
        <a href="docs/photos/ground-mount-structure/steel-workshop-and-painting-06.jpg">
          <img src="docs/photos/ground-mount-structure/steel-workshop-and-painting-06.jpg" width="410" style="display: block;">
        </a>
        <div style="text-align: center;">
          <sub>Solar panel mounting elements after painting, drying in progress</sub>
        </div>
      </div>
    </td>
  </tr>

  <tr>
    <td colspan="2" style="text-align: left;">
      <div style="width: 410px;">
        <a href="docs/photos/ground-mount-structure/steel-workshop-and-painting-07.jpg">
          <img src="docs/photos/ground-mount-structure/steel-workshop-and-painting-07.jpg" width="410" style="display: block;">
        </a>
        <div style="text-align: center;">
          <sub>Spacer for mounting solar panels to the perforated panels which are on the outer side of mounting structure</sub>
        </div>
      </div>
    </td>
  </tr>

  <tr>
    <td colspan="2" style="text-align: left;">
      <div style="width: 410px;">
        <a href="docs/photos/ground-mount-structure/steel-workshop-and-painting-08.jpg">
          <img src="docs/photos/ground-mount-structure/steel-workshop-and-painting-08.jpg" width="410" style="display: block;">
        </a>
        <div style="text-align: center;">
          <sub>Solar panel mounts for perforated profiles – painted and drying</sub>
        </div>
      </div>
    </td>
  </tr>

  <tr>
    <td colspan="2" style="text-align: left;">
      <div style="width: 410px;">
        <a href="docs/photos/ground-mount-structure/steel-workshop-and-painting-08.jpg">
          <img src="docs/photos/ground-mount-structure/steel-workshop-and-painting-08.jpg" width="410" style="display: block;">
        </a>
        <div style="text-align: center;">
          <sub>Solar panel mounts for perforated profiles</sub>
        </div>
      </div>
    </td>
  </tr>
</table>




### 6. Assembly of PV installation
<table>
  <tr>
    <td colspan="2" style="text-align: left;">
      <div style="width: 410px;">
        <a href="docs/photos/ground-mount-structure/assembly-01.jpg">
          <img src="docs/photos/ground-mount-structure/assembly-01.jpg" width="410" style="display: block;">
        </a>
        <div style="text-align: center;">
          <sub>Shorter mounting bases and angle bar mounted on concrete bases. Thanks to the height difference of the mounting bases, the angle bar remains level</sub>
        </div>
      </div>
    </td>
  </tr>
  <tr>
    <td colspan="2" style="text-align: left;">
      <div style="width: 410px;">
        <a href="docs/photos/ground-mount-structure/assembly-02.jpg">
          <img src="docs/photos/ground-mount-structure/assembly-02.jpg" width="410" style="display: block;">
        </a>
        <div style="text-align: center;">
          <sub>Shorter mounting base mounted on a concrete base. Before installation, the base was coated with a bituminous compound. Stainless steel bolts were used for assembly</sub>
        </div>
      </div>
    </td>
  </tr>
  <tr>
    <td colspan="2" style="text-align: left;">
      <div style="width: 410px;">
        <a href="docs/photos/ground-mount-structure/assembly-03.jpg">
          <img src="docs/photos/ground-mount-structure/assembly-03.jpg" width="410" style="display: block;">
        </a>
        <div style="text-align: center;">
          <sub>Ground mounting structure ready for PV panel installation</sub>
        </div>
      </div>
    </td>
  </tr>
  <tr>
    <td colspan="2" style="text-align: left;">
      <div style="width: 200px;">
        <a href="docs/photos/ground-mount-structure/assembly-04.jpg">
          <img src="docs/photos/ground-mount-structure/assembly-04.jpg" width="200" style="display: block;">
        </a>
        <div style="text-align: center;">
          <sub>Here you can see how the panel mounts are used to connect solar panel with perforated profile</sub>
        </div>
      </div>
    </td>
  </tr>
</table>


### 7. Fully assembled PV installation
<table>
    <tr>
    <td align="center" colspan="2">
      <a href="docs\photos\ground-mount-structure\full-assembled-panel-front.jpg">
        <img src="docs\photos\ground-mount-structure\full-assembled-panel-front.jpg" width="410">
      </a><br />
      <sub>Fully assembled PV installation - front</sub>
    </td>
  </tr>
    </tr>
    <tr>
    <td align="center" colspan="2">
      <a href="docs\photos\ground-mount-structure\full-assembled-panel-back.jpg">
        <img src="docs\photos\ground-mount-structure\full-assembled-panel-back.jpg" width="410">
      </a><br />
      <sub>Fully assembled PV installation - back<sub>
    </td>
  </tr>
</table>

### 8. Underground Cable Installation and Connection to the Building
To connect the panels, I used AsXSn 4x35 cable and additionally laid an AsXSn 4x25 cable. I found these cables at a scrapyard at a good price, which is why I chose this somewhat unconventional option. Additionally, I installed a gel-filled Ethernet twisted pair cable to allow for potential data transmission if needed.

<table>
  <tr>
    <td align="center">
      <a href="docs/photos/ground-mount-structure/cable-routes-02.jpg">
        <img src="docs/photos/ground-mount-structure/cable-routes-02.jpg" width="200">
      </a><br />
      <div style="max-width: 200px; text-align: center;">
        <sub>Underground cable entry to the building</sub>
      </div>
    </td>
  </tr>

  <tr>
    <td align="center" valign="top">
      <a href="docs/photos/ground-mount-structure/cable-routes-05.jpg">
        <img src="docs/photos/ground-mount-structure/cable-routes-05.jpg" width="200">
      </a><br />
      <div style="max-width: 200px; text-align: center;">
        <sub>Cable entry point inside the building</sub>
      </div>
    </td>
    <td align="center" valign="top">
      <a href="docs/photos/ground-mount-structure/cable-routes-06.jpg">
        <img src="docs/photos/ground-mount-structure/cable-routes-06.jpg" width="200">
      </a><br />
      <div style="max-width: 200px; text-align: center;">
        <sub>Close-up of the conduit connection and grounding wire</sub>
      </div>
    </td>
  </tr>
</table>




To connect the AROT 50 (blue) protective pipe with the RL50 pipe (white), I created an adapter using a 3D printer. PETG material was chosen for its weather resistance. The opening in adapter was designed to fit the protective pipe only after heating the adapter. Once cooled, the adapter holds the pipe in place.

<table>
  <tr>
    <td align="center" colspan="2">
      <a href="docs/photos/ground-mount-structure/cable-routes-connector.jpg">
        <img src="docs/photos/ground-mount-structure/cable-routes-connector.jpg" width="210">
      </a><br/>
      <sub>Adapter 3D model</sub>
    </td>
  </tr>

  <tr>
    <td align="center">
      <a href="docs/photos/ground-mount-structure/cable-routes-03.jpg">
        <img src="docs/photos/ground-mount-structure/cable-routes-03.jpg" width="200">
      </a><br/>
      <sub>Adapter after printing</sub>
    </td>
    <td align="center ">
      <a href="docs/photos/ground-mount-structure/cable-routes-04.jpg">
        <img src="docs/photos/ground-mount-structure/cable-routes-04.jpg" width="200">
      </a><br/>
      <sub>Adapter mounted on protective pipe</sub>
    </td>
  </tr>

  <tr>
    <td align="center" colspan="2">
      <a href="docs/photos/ground-mount-structure/cable-routes-08.jpg">
        <img src="docs/photos/ground-mount-structure/cable-routes-08.jpg" width="400">
      </a><br />
      <sub>Junction box inside the building.<br> Visible screw terminals for two cables, twisted pair Ethernet connection, <br>and additional grounding.</sub>
    </td>
  </tr>
    <tr>
    <td align="center" colspan="2">
      <a href="docs/photos/ground-mount-structure/cable-routes-10.jpg">
        <img src="docs/photos/ground-mount-structure/cable-routes-10.jpg" width="400">
      </a><br />
      <sub>Junction box at the PV installation site.</sub>
    </td>
  </tr>
</table>


## EASUN inverter - Description, installation and wiring

[📄 **EASUN ISolar SMG II 4kW datasheet**](docs/ISolar-SMG-II-4KW-WiFi.pdf) <br><br>
The EASUN ISolar SMG II 4kW is an off-grid inverter. It does not have the capability to synchronize with the power grid.

Inverter specifications:
- Input voltage from PV array: 60-500V DC
- Input current from PV array: 15A
- Output voltage: 230V/50Hz
- Battery voltage: 24V
- Battery current: max 100A

In my case, 12 PV were connected, each with a maximum voltage of 37V, resulting in a maximum voltage of approximately 440V.

The maximum current of the PV array is 8A.  
Connected PV array meet the inverter's specifications.

Power Source Priority

| Option       | Description       |
|-----------------|-----------------|
| SOL | The inverter uses solar energy to power the loads. If solar energy is insufficient to meet the load demand, the battery **only supplements** the power. The grid supplies power to the loads only when: Solar energy is unavailable (e.g., at night or during heavy cloud cover). Battery voltage drops to the low-level warning voltage or the threshold set in Program 12.|
| UFI  | Utility will provide power to the loads as first priority. Solar and battery energy will provide power to the loads only when utility power is notavailable.|
| SBU  | The inverter uses solar energy to power the loads. If solar energy is insufficient, the battery provides power to the loads.​ The grid supplies power to the loads only when the battery voltage drops to the low-level warning voltage or the threshold set in Program 12. |
| SUB  | Solar energy is charged first and then power to the loads. If solar energy is not sufficient to power all connected loads, Utility energy will supply power to the loads at the same time. <br>**Attention**: I found that there is an idle power (about 150W) that must be drawn from the grid before parallel operation of the grid + solar energy can occur. This means that if the power consumption is up to 150W, it will not be supplied by solar energy but by the grid. If power consumption is over 150W eg. 500W then 350W will we drawn from solar and still 150W will be drawn from grid.|


Key Differences between SOL and SBU is battery usage:

SOL Mode: The battery assists only when solar energy is insufficient, and the grid is used if both solar and battery cannot meet the load. 

SBU Mode: The battery is used after solar, and the grid is used only when the battery is depleted.​





<a href="electrical/schematic.png">
        <img src="electrical/schematic.png" width="500"></a>


# Management System diagram:

<a href="docs\PV_management_system_diagram.png"><img src="docs\PV_management_system_diagram.png" alt="System Diagram" style="width:400px"></a>


## BMS for lead-acid batteries
BMS have several tasks:
- Battery Balancer equalizes the state of charge of two series connected 12V batteries. If one of battery is overcharged it discharge it using resistor.
- Bidirectional DC-DC converter - protect battery from too much discharge or charge current
- Battery monitoring - measurment of temperature of each battery and voltage.

The BMS is controlled by an AVR64DD28 microcontroller. To program it, you need a programmer that supports UPDI.
I'm using SerialUPDI (a modified version with high-voltage programming capability and galvanic isolation, which you can find here: SerialUPDI link).

To measure battery voltage and current, I use the INA226 sensor along with the built-in ADC of the microcontroller.

The INA226 measures:

- The voltage of the entire battery pack, split into BATT_LOW (bottom battery) and BATT_HIGH (top battery)

- The voltage across a shunt resistor, used to measure the current flowing through the entire pack

Since the INA226 is bidirectional, it allows both charging and discharging current measurements.

The microcontroller’s ADC measures only BATT_LOW voltage.
By subtracting the ADC reading from the INA226’s total voltage reading, I can calculate the BATT_HIGH voltage.

Cell balancing is performed using high-power resistors, each connected in parallel with a battery cell.
Each resistor is switched by a MOSFET, which is controlled by the MCU using PWM.

PWM is hardware-generated using the TCD timer, which controls two outputs: WOA and WOB, each assigned to a specific MCU pin.

The TCD timer is capable of generating...




## ESP32 Master module

## Home Assistant integration

## Power Tracking module

## Windows Guide: OTA upload to ESP32 using FRP and non-default port (not 3232)

### Microsoft KM-TEST Loopback Adapter

Windows has a built-in way to create a virtual network interface.

---

### Installing Loopback Adapter

1. Open `cmd.exe` as **Administrator**

2. Run:
   ```cmd
   hdwwiz.exe
   ```

3. In the wizard:
   - Select: **Install the hardware that I manually select (Advanced)**
   - Choose: **Network adapters**
   - Manufacturer: **Microsoft**
   - Network Adapter: **Microsoft KM-TEST Loopback Adapter**
   - Install

4. Check the interface name:
   ```powershell
   Get-NetAdapter
   ```
   Assume it's e.g. `"Ethernet 4"`

---

###  Assign static IP to the adapter

```powershell
New-NetIPAddress -IPAddress 192.168.123.123 -PrefixLength 24 -InterfaceAlias "Ethernet 4"
```

---

###  Set up port proxy

```cmd
netsh interface portproxy add v4tov4 listenport=3232 listenaddress=192.168.123.123 connectport=30219 connectaddress=95.216.245.98
```

####  Check configuration:

```cmd
netsh interface portproxy show all
```

####  Remove forwarding rule:

```cmd
netsh interface portproxy delete v4tov4 listenport=3232 listenaddress=192.168.123.123
```

---

###  Check if port 3232 is listening

```cmd
netstat -ano | findstr :3232
```

---

### 🧪 Alternative method: `ncat` (from Nmap)

If `portproxy` fails, use `ncat` as a TCP proxy:

```cmd
ncat -l 192.168.123.123 3232 --sh-exec "ncat 95.216.245.98 30219" --keep-open
```

---
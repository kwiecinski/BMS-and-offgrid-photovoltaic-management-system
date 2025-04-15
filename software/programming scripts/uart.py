import serial
import serial.tools.list_ports
import time

TARGET_SN = "A5XK3RJTA"  # Możesz też wpisać fragment np. "VID_0403+PID_6001+..."
BAUDRATE = 9600

def find_target_port():
    ports = serial.tools.list_ports.comports()
    for port in ports:
        if TARGET_SN in port.hwid or TARGET_SN in (port.serial_number or "") or TARGET_SN in port.device:
            return port.device
    return None

def main():
    ser = None
    while True:
        if ser is None or not ser.is_open:
            port = find_target_port()
            if port:
                try:
                    print(f"[INFO] Łączenie z {port}...")
                    ser = serial.Serial(port, BAUDRATE, timeout=1)
                    print("[INFO] Połączono.")
                except serial.SerialException as e:
                    print(f"[ERROR] Nie udało się połączyć: {e}")
                    ser = None
        else:
            try:
                line = ser.readline()
                if line:
                    print("[RX]", line.decode(errors='replace').strip())
            except serial.SerialException:
                print("[WARN] Port utracony.")
                ser = None
        time.sleep(0.5)

if __name__ == "__main__":
    main()

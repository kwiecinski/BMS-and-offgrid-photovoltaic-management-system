import serial.tools.list_ports
import subprocess
import time

# Stałe
TARGET_SN = "5"
HEX_PATH = r"d:\Projekty\BMS-and-offgrid-photovoltaic-management-system\software\Balancer-AVR.X\dist\default\production\Balancer-AVR.X.production.hex"
AVRDUDE_CONF = r"c:\Users\User\avrdude\avrdude-v8.0-windows-x64\avrdude.conf"

def find_com_by_serial(target_sn):
    for port in serial.tools.list_ports.comports():
        if port.serial_number and target_sn in port.serial_number:
            return port.device
    return None

def program_device(com_port):
    command = [
        "avrdude.exe",
        "-C", AVRDUDE_CONF,
        "-p", "AVR64DD28",
        "-c", "serialUPDI",
        "-P", com_port,
        "-x", "rtsdtr=high",
        "-U", f"flash:w:{HEX_PATH}:i"
    ]
    print(f"\n➡️  Programuję urządzenie na porcie {com_port}...\n")
    result = subprocess.run(command)
    return result.returncode == 0

def main():
    print("Tryb batch programming. Wciśnij Ctrl+C aby przerwać.")
    try:
        while True:
            input("\nWciśnij Enter aby zaprogramować ponownie (albo Ctrl+C aby zakończyć)...")
            com_port = find_com_by_serial(TARGET_SN)
            if not com_port:
                print(f"❌ Nie znaleziono portu COM z numerem seryjnym zawierającym '{TARGET_SN}'.")
            else:
                success = program_device(com_port)
                if success:
                    print("✅ Programowanie zakończone sukcesem.")
                else:
                    print("❌ Błąd podczas programowania.")

    except KeyboardInterrupt:
        print("\nPrzerwano przez użytkownika.")

if __name__ == "__main__":
    main()

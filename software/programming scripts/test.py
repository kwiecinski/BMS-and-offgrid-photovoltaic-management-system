import serial
import time

port_name = 'COM30'  # zmień na swój port
baudrate = 9600

with serial.Serial(port=port_name, baudrate=baudrate) as ser:
    try:
        while True:
            # Wysyłaj ciągle 0xFF przez 1s (stan TX w większości wysoki)
            end_time = time.time() + 1
            while time.time() < end_time:
                ser.write(b'\xFF')
            print("TX: wysoki (0xFF)")

            time.sleep(0.1)  # mała przerwa dla stabilizacji

            # Wysyłaj ciągle 0x00 przez 1s (stan TX głównie niski)
            end_time = time.time() + 3
            while time.time() < end_time:
                ser.write(b'\x00')
            print("TX: niski (0x00)")

            time.sleep(0.1)

    except KeyboardInterrupt:
        print("Zatrzymano.")


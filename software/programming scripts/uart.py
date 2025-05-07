import serial
import threading
import sys
import msvcrt  # tylko na Windows

def read_serial(port_name='COM1', baudrate=9600):
    try:
        ser = serial.Serial(port_name, baudrate, timeout=0.1)
        print(f"Połączono z {port_name} @ {baudrate} baud.")
    except serial.SerialException as e:
        print(f"Błąd połączenia: {e}")
        return

    paused = threading.Event()  # jeśli ustawiony: działa normalnie; jeśli cleared — pauza
    paused.set()

    def read_loop():
        try:
            while True:
                if paused.is_set() and ser.in_waiting:
                    data = ser.read(ser.in_waiting)
                    print(data.decode(errors='replace'), end='', flush=True)
        except Exception as e:
            print(f"\nBłąd odczytu: {e}")
        finally:
            ser.close()
            print("\nPort zamknięty.")

    def keyboard_loop():
        print("Naciśnij [P] aby zapauzować, [R] aby wznowić, [Q] aby wyjść.")
        while True:
            if msvcrt.kbhit():
                key = msvcrt.getch().lower()
                if key == b'p':
                    paused.clear()
                    print("\n[Pauza]")
                elif key == b'r':
                    paused.set()
                    print("\n[Wznowiono]")
                elif key == b'q':
                    print("\n[Kończę]")
                    break

    reader = threading.Thread(target=read_loop, daemon=True)
    reader.start()

    try:
        keyboard_loop()
    except KeyboardInterrupt:
        pass
    finally:
        paused.clear()
        ser.close()

if __name__ == "__main__":
    read_serial()

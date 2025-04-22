import serial
import time

# Wybierz port COM do testu:
COM_PORT = "COM17"  # <- zmień na swój port

try:
    ser = serial.Serial(COM_PORT)
    ser.baudrate = 9600  # dowolna prędkość
    ser.timeout = 0.1

    print(f"🔌 Testowanie portu {COM_PORT}... Ctrl+C aby przerwać.")

    state = False

    while True:
        # Ustawienie linii wyjściowych
        ser.setDTR(state)
        ser.setRTS(state)

        print(f"\nUstawienie wyjść na: {'wysoki' if state else 'niski'}")

        # Odczyt linii wejściowych
        print(f"CTS: {ser.getCTS()}")
        print(f"DSR: {ser.getDSR()}")
        print(f"DCD: {ser.getCD()}")
        print(f"RI : {ser.ri if hasattr(ser, 'ri') else 'N/A'}")  # nie wszystkie implementacje obsługują RI

        # RX/TX testowanie można tylko zrobić przez zewnętrzny loopback lub drugi port

        state = not state
        time.sleep(1)

except serial.SerialException as e:
    print(f"Błąd portu: {e}")

except KeyboardInterrupt:
    print("\nZakończono przez użytkownika.")

finally:
    if 'ser' in locals() and ser.is_open:
        ser.close()

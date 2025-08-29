#!/usr/bin/env python3
import pymodbus.client as ModbusClient
from pymodbus import pymodbus_apply_logging_config, ModbusException, FramerType

def run_sync_rtu_client():
    # włącz debugowanie
    pymodbus_apply_logging_config("DEBUG")

    # tworzymy klienta RTU
    client = ModbusClient.ModbusSerialClient(
        port="COM1",
        baudrate=9600,
        bytesize=8,
        parity="N",
        stopbits=1,
        timeout=1,
        framer=FramerType.RTU
    )

    print("Łączenie z urządzeniem Modbus...")
    client.connect()

    try:
        rr = client.read_holding_registers(address=202, count=1, device_id=1)
    except ModbusException as e:
        print(f"Błąd Modbus: {e}")
        client.close()
        return

    if rr.isError():
        print(f"Urządzenie zwróciło błąd: {rr}")
    else:
        print(f"Wynik rejestru 202: {rr.registers[0]}")

    client.close()

if __name__ == "__main__":
    run_sync_rtu_client()

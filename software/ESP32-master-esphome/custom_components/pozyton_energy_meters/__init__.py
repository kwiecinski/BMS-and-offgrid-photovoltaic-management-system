import esphome.codegen as cg
import esphome.config_validation as cv
import esphome.pins as pins
import re
from esphome.components import binary_sensor, sensor, text_sensor, uart
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_CURRENT,
    DEVICE_CLASS_ENERGY,
    DEVICE_CLASS_FREQUENCY,
    DEVICE_CLASS_POWER,
    DEVICE_CLASS_REACTIVE_ENERGY,
    DEVICE_CLASS_REACTIVE_POWER,
    DEVICE_CLASS_VOLTAGE,
    STATE_CLASS_MEASUREMENT,
    STATE_CLASS_TOTAL_INCREASING,
    UNIT_AMPERE,
    UNIT_HERTZ,
    UNIT_KILOWATT_HOURS,
    UNIT_VOLT,
    UNIT_WATT,
)

DEPENDENCIES = ["uart"]
AUTO_LOAD = ["binary_sensor", "sensor", "text_sensor"]
DOMAIN = "pozyton_energy_meters"

CONF_DIRECTION_PIN = "direction_pin"
CONF_METERS = "meters"
CONF_MODEL = "model"
CONF_ADDRESS = "address"
CONF_SENSORS = "sensors"
CONF_DIAGNOSTICS = "diagnostics"
CONF_CONNECTION = "connection"
CONF_LAST_SUCCESS = "last_success"
CONF_COMMUNICATION_ERRORS = "communication_errors"
CONF_BAUD_RATE = "baud_rate"
CONF_RESPONSE_TIMEOUT = "response_timeout"
CONF_UPDATE_INTERVAL = "update_interval"
CONF_METER_NAME = "meter_name"
CONF_DEBUG_FIRST_RESPONSE = "debug_first_response"

pozyton_ns = cg.esphome_ns.namespace("pozyton_energy_meters")
PozytonBus = pozyton_ns.class_("PozytonBus", cg.Component, uart.UARTDevice)
MeterModel = pozyton_ns.enum("MeterModel")
Measurement = pozyton_ns.enum("Measurement")

MODEL_OPTIONS = {"SEAB": MeterModel.METER_SEAB, "EABM": MeterModel.METER_EABM}

MEASUREMENTS = {
    "voltage_l1": ("voltage_l1", "V", DEVICE_CLASS_VOLTAGE, STATE_CLASS_MEASUREMENT, 1),
    "voltage_l2": ("voltage_l2", "V", DEVICE_CLASS_VOLTAGE, STATE_CLASS_MEASUREMENT, 1),
    "voltage_l3": ("voltage_l3", "V", DEVICE_CLASS_VOLTAGE, STATE_CLASS_MEASUREMENT, 1),
    "current_l1": ("current_l1", UNIT_AMPERE, DEVICE_CLASS_CURRENT, STATE_CLASS_MEASUREMENT, 2),
    "current_l2": ("current_l2", UNIT_AMPERE, DEVICE_CLASS_CURRENT, STATE_CLASS_MEASUREMENT, 2),
    "current_l3": ("current_l3", UNIT_AMPERE, DEVICE_CLASS_CURRENT, STATE_CLASS_MEASUREMENT, 2),
    "active_power_l1": ("active_power_l1", UNIT_WATT, DEVICE_CLASS_POWER, STATE_CLASS_MEASUREMENT, 1),
    "active_power_l2": ("active_power_l2", UNIT_WATT, DEVICE_CLASS_POWER, STATE_CLASS_MEASUREMENT, 1),
    "active_power_l3": ("active_power_l3", UNIT_WATT, DEVICE_CLASS_POWER, STATE_CLASS_MEASUREMENT, 1),
    "active_power_total": ("active_power_total", UNIT_WATT, DEVICE_CLASS_POWER, STATE_CLASS_MEASUREMENT, 1),
    "reactive_power_l1": ("reactive_power_l1", "var", DEVICE_CLASS_REACTIVE_POWER, STATE_CLASS_MEASUREMENT, 1),
    "reactive_power_l2": ("reactive_power_l2", "var", DEVICE_CLASS_REACTIVE_POWER, STATE_CLASS_MEASUREMENT, 1),
    "reactive_power_l3": ("reactive_power_l3", "var", DEVICE_CLASS_REACTIVE_POWER, STATE_CLASS_MEASUREMENT, 1),
    "reactive_power_total": ("reactive_power_total", "var", DEVICE_CLASS_REACTIVE_POWER, STATE_CLASS_MEASUREMENT, 1),
    "active_energy_import": ("active_energy_import", UNIT_KILOWATT_HOURS, DEVICE_CLASS_ENERGY, STATE_CLASS_TOTAL_INCREASING, 6),
    "active_energy_export": ("active_energy_export", UNIT_KILOWATT_HOURS, DEVICE_CLASS_ENERGY, STATE_CLASS_TOTAL_INCREASING, 6),
    "reactive_energy_positive": ("reactive_energy_positive", "kvarh", DEVICE_CLASS_REACTIVE_ENERGY, STATE_CLASS_TOTAL_INCREASING, 6),
    "reactive_energy_negative": ("reactive_energy_negative", "kvarh", DEVICE_CLASS_REACTIVE_ENERGY, STATE_CLASS_TOTAL_INCREASING, 6),
    "frequency": ("frequency", UNIT_HERTZ, DEVICE_CLASS_FREQUENCY, STATE_CLASS_MEASUREMENT, 2),
}

SENSOR_SCHEMAS = {}
SENSOR_ENUMS = {}
for key, (enum_name, unit, device_class, state_class, decimals) in MEASUREMENTS.items():
    enum_value = getattr(Measurement, "MEASUREMENT_" + enum_name.upper())
    SENSOR_ENUMS[key] = enum_value
    schema = sensor.sensor_schema(
        unit_of_measurement=unit,
        device_class=device_class,
        state_class=state_class,
        accuracy_decimals=decimals,
    ).extend({cv.GenerateID(): cv.declare_id(sensor.Sensor)})
    SENSOR_SCHEMAS[cv.Optional(key)] = schema


def _diagnostic_sensor_schema():
    return cv.Schema(
        {
            cv.Optional(CONF_CONNECTION): binary_sensor.binary_sensor_schema().extend(
                {cv.GenerateID(): cv.declare_id(binary_sensor.BinarySensor)}
            ),
            cv.Optional(CONF_LAST_SUCCESS): text_sensor.text_sensor_schema().extend(
                {cv.GenerateID(): cv.declare_id(text_sensor.TextSensor)}
            ),
            cv.Optional(CONF_COMMUNICATION_ERRORS): sensor.sensor_schema(
                unit_of_measurement="errors",
                accuracy_decimals=0,
                state_class=STATE_CLASS_MEASUREMENT,
            ).extend({cv.GenerateID(): cv.declare_id(sensor.Sensor)}),
        }
    )


def _validate_meter(config):
    if config[CONF_MODEL] == "EABM":
        for key in ("reactive_power_l1", "reactive_power_l2", "reactive_power_l3"):
            if key in config.get(CONF_SENSORS, {}):
                raise cv.Invalid("EABM supports only reactive_power_total via Q(0)", [CONF_SENSORS, key])
    address_pattern = r"\d{3}\.\d{7}" if config[CONF_MODEL] == "SEAB" else r"\d{3} \d{7}"
    if re.fullmatch(address_pattern, config[CONF_ADDRESS]) is None:
        expected = "ttt.nnnnnnn" if config[CONF_MODEL] == "SEAB" else "nnn nnnnnnn"
        model_name = config[CONF_MODEL]
        raise cv.Invalid(f"{model_name} address must use format {expected}")
    return config


METER_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.Required(CONF_METER_NAME): cv.string,
            cv.Required(CONF_MODEL): cv.enum(MODEL_OPTIONS, upper=True),
            cv.Required(CONF_ADDRESS): cv.string,
            cv.Optional(CONF_UPDATE_INTERVAL, default="10s"): cv.positive_time_period_milliseconds,
            cv.Optional(CONF_SENSORS): cv.Schema(SENSOR_SCHEMAS),
            cv.Optional(CONF_DIAGNOSTICS): _diagnostic_sensor_schema(),
        }
    ),
    _validate_meter,
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(PozytonBus),
        cv.Required(CONF_DIRECTION_PIN): pins.gpio_output_pin_schema,
        cv.Required(CONF_METERS): cv.All(cv.ensure_list(METER_SCHEMA), cv.Length(min=1, max=2)),
        cv.Optional(CONF_BAUD_RATE, default=4800): cv.int_range(min=300, max=19200),
        cv.Optional(CONF_RESPONSE_TIMEOUT, default="500ms"): cv.positive_time_period_milliseconds,
        cv.Optional(CONF_DEBUG_FIRST_RESPONSE, default=False): cv.boolean,
    }
).extend(cv.COMPONENT_SCHEMA).extend(uart.UART_DEVICE_SCHEMA)


def _validate_uart_settings(config):
    return uart.final_validate_device_schema(
        DOMAIN,
        baud_rate=config[CONF_BAUD_RATE],
        require_tx=True,
        require_rx=True,
        data_bits=7,
        parity="EVEN",
        stop_bits=1,
    )(config)


FINAL_VALIDATE_SCHEMA = _validate_uart_settings


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    direction_pin = await cg.gpio_pin_expression(config[CONF_DIRECTION_PIN])
    cg.add(var.set_direction_pin(direction_pin))
    cg.add(var.set_baud_rate(config[CONF_BAUD_RATE]))
    cg.add(var.set_response_timeout(config[CONF_RESPONSE_TIMEOUT]))
    cg.add(var.set_debug_first_response(config[CONF_DEBUG_FIRST_RESPONSE]))

    for meter_index, meter in enumerate(config[CONF_METERS]):
        cg.add(
            var.add_meter(
                meter[CONF_MODEL],
                meter[CONF_METER_NAME],
                meter[CONF_ADDRESS],
                meter[CONF_UPDATE_INTERVAL],
            )
        )
        for key, enum_value in SENSOR_ENUMS.items():
            sensor_config = meter.get(CONF_SENSORS, {}).get(key)
            if sensor_config is None:
                continue
            entity = await sensor.new_sensor(sensor_config)
            cg.add(var.set_sensor(meter_index, enum_value, entity))

        diagnostics = meter.get(CONF_DIAGNOSTICS, {})
        if CONF_CONNECTION in diagnostics:
            entity = await binary_sensor.new_binary_sensor(diagnostics[CONF_CONNECTION])
            cg.add(var.set_connection_sensor(meter_index, entity))
        if CONF_LAST_SUCCESS in diagnostics:
            entity = await text_sensor.new_text_sensor(diagnostics[CONF_LAST_SUCCESS])
            cg.add(var.set_last_success_sensor(meter_index, entity))
        if CONF_COMMUNICATION_ERRORS in diagnostics:
            entity = await sensor.new_sensor(diagnostics[CONF_COMMUNICATION_ERRORS])
            cg.add(var.set_error_counter_sensor(meter_index, entity))

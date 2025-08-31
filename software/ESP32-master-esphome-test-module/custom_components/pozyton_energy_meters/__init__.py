import esphome.config_validation as cv
import esphome.codegen as cg
import esphome.pins as pins

from esphome.components import uart
from esphome.const import CONF_ID, CONF_UPDATE_INTERVAL

CONF_METER_TYPE = "meter_type"
CONF_DIR_PIN = "dir_pin"
CONF_DEBUG = "debug"

pozyton_energy_meters_ns = cg.esphome_ns.namespace("pozyton_energy_meters")
PozytonEnergyMeters = pozyton_energy_meters_ns.class_("PozytonEnergyMeters", cg.PollingComponent, uart.UARTDevice)

MeterType = pozyton_energy_meters_ns.enum("MeterType")

METER_TYPES = {
    "SEAB": MeterType.METER_SEAB,
    "EABM": MeterType.METER_EABM,
}

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(PozytonEnergyMeters),
    cv.Required(CONF_METER_TYPE): cv.enum(METER_TYPES, upper=True),
    cv.Required(CONF_DIR_PIN): pins.gpio_output_pin_schema,
    cv.Optional(CONF_DEBUG, default=False): cv.boolean,
    cv.Optional(CONF_UPDATE_INTERVAL, default="60s"): cv.positive_time_period_milliseconds,
}).extend(uart.UART_DEVICE_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    cg.add(var.set_meter_type(config[CONF_METER_TYPE]))

    dir_pin = await cg.gpio_pin_expression(config[CONF_DIR_PIN])
    cg.add(var.set_dir_pin(dir_pin))

    cg.add(var.set_debug(config[CONF_DEBUG]))
    cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))

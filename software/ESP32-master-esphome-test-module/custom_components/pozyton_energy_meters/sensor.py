import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    CONF_ID,
    UNIT_VOLT,
    DEVICE_CLASS_VOLTAGE,
    STATE_CLASS_MEASUREMENT,
)

from .const import (
    CONF_POZYTON_ID,
    CONF_OBIS,
    pozyton_energy_meters_ns,
)

# Klasa sensora w C++
PozytonOBISSensor = pozyton_energy_meters_ns.class_("PozytonOBISSensor", sensor.Sensor)

CONFIG_SCHEMA = sensor.sensor_schema(
    unit_of_measurement=UNIT_VOLT,
    accuracy_decimals=1,
    device_class=DEVICE_CLASS_VOLTAGE,
    state_class=STATE_CLASS_MEASUREMENT,
).extend({
    cv.GenerateID(CONF_POZYTON_ID): cv.use_id(pozyton_energy_meters_ns.class_("PozytonEnergyMeters")),
    cv.Required(CONF_OBIS): cv.string,
})

async def to_code(config):
    hub = await cg.get_variable(config[CONF_POZYTON_ID])
    var = cg.new_Pvariable(config[CONF_ID], PozytonOBISSensor)  # typ C++ sensora
    await sensor.register_sensor(var, config)
    cg.add(hub.register_sensor(var, config[CONF_OBIS]))

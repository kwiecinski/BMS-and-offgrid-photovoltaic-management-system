import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from . import CONF_POZYTON_ID, CONF_OBIS, pozyton_ns, validate_obis

# Tworzymy klasę sensora w namespace Pozyton
PozytonOBISSensor = pozyton_ns.class_("PozytonOBISSensor", sensor.Sensor)

# Schemat konfiguracji sensora
CONFIG_SCHEMA = cv.All(
    sensor.sensor_schema(
        PozytonOBISSensor,
    ).extend(
        {
            cv.GenerateID(CONF_POZYTON_ID): cv.use_id(PozytonEnergyMeter),
            cv.Required(CONF_OBIS): validate_obis,  # OBIS code validator
        }
    ),
    cv.has_exactly_one_key(CONF_OBIS),
)

# Funkcja tworząca sensor w C++ i rejestrująca go w komponencie
async def to_code(config):
    component = await cg.get_variable(config[CONF_POZYTON_ID])
    var = await sensor.new_sensor(config)

    if CONF_OBIS in config:
        cg.add(var.set_obis(config[CONF_OBIS]))

    cg.add(component.register_sensor(var))

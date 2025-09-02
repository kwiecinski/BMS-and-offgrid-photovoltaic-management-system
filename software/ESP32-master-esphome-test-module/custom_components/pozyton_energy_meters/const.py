import esphome.codegen as cg

# Namespace
pozyton_energy_meters_ns = cg.esphome_ns.namespace("pozyton_energy_meters")

MeterType = pozyton_energy_meters_ns.enum("MeterType")

METER_TYPES = {
    "SEAB": MeterType.METER_SEAB,
    "EABM": MeterType.METER_EABM,
}

CONF_METER_TYPE = "meter_type"
CONF_DIR_PIN = "dir_pin"
CONF_DEBUG = "debug"
CONF_POZYTON_ID = "pozyton_id"
CONF_OBIS = "obis"

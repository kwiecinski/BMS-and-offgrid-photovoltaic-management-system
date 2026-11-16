import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.components import uart
from esphome.const import CONF_ID

DEPENDENCIES = ["uart"]

itron_ns = cg.esphome_ns.namespace("itron")
ItronComponent = itron_ns.class_("ItronComponent", cg.Component)

CONF_UART_ID = "uart_id"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(ItronComponent),
    cv.Required(CONF_UART_ID): cv.use_id(uart.UARTComponent),
})

async def to_code(config):
    uart_component = await cg.get_variable(config[CONF_UART_ID])
    var = cg.new_Pvariable(config[CONF_ID], uart_component)
    await cg.register_component(var, config)


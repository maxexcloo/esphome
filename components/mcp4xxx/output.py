import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output, spi
from esphome.const import CONF_ID

CODEOWNERS = ["@ellsclytn"]
DEPENDENCIES = ["spi"]

mcp4xxx_ns = cg.esphome_ns.namespace("mcp4xxx")
MCP4XXX = mcp4xxx_ns.class_("MCP4XXX", cg.Component, output.FloatOutput, spi.SPIDevice)

CONFIG_SCHEMA = (
    output.FLOAT_OUTPUT_SCHEMA.extend({cv.Required(CONF_ID): cv.declare_id(MCP4XXX)})
    .extend(cv.COMPONENT_SCHEMA)
    .extend(spi.spi_device_schema(cs_pin_required=True))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await output.register_output(var, config)
    await spi.register_spi_device(var, config)

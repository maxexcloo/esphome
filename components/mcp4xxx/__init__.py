import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import spi
from esphome.const import CONF_ID

CODEOWNERS = ["@ellsclytn"]
DEPENDENCIES = ["spi"]
AUTO_LOAD = ["fan"]
MULTI_CONF = True

mcp4xxx_ns = cg.esphome_ns.namespace("mcp4xxx")
MCP4XXX = mcp4xxx_ns.class_("MCP4XXX", cg.Component, spi.SPIDevice)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(MCP4XXX),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(spi.spi_device_schema(cs_pin_required=True))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)

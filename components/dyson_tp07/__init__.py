import esphome.codegen as cg
from esphome.components import uart
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
)

CODEOWNERS = ["@aarongorka"]
DEPENDENCIES = ["uart"]
MULTI_CONF = True

dyson_tp07_ns = cg.esphome_ns.namespace("dyson_tp07")
DysonTP07 = dyson_tp07_ns.class_("DysonTP07", cg.PollingComponent, uart.UARTDevice)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(DysonTP07),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(cv.polling_component_schema("60s"))
    .extend(uart.UART_DEVICE_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

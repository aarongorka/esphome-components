import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_RUNNING,
    ENTITY_CATEGORY_NONE,
)

dyson_tp07_ns = cg.esphome_ns.namespace("dyson_tp07")

DysonTP07 = dyson_tp07_ns.class_("DysonTP07", binary_sensor.BinarySensor, cg.Component)

CONF_IS_ON = "is_on"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.use_id(DysonTP07),
        cv.Optional(CONF_IS_ON): binary_sensor.binary_sensor_schema(
            device_class=DEVICE_CLASS_RUNNING,
            entity_category=ENTITY_CATEGORY_NONE,
        ),
    }
)


async def to_code(config):
    var = await cg.get_variable(config[CONF_ID])

    if is_on_config := config.get(CONF_IS_ON):
        is_on = await binary_sensor.new_binary_sensor(is_on_config)
        cg.add(var.set_is_on_sensor(is_on))

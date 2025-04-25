import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import (
    CONF_HUMIDITY,
    CONF_ID,
    DEVICE_CLASS_DURATION,
    DEVICE_CLASS_HUMIDITY,
    DEVICE_CLASS_TEMPERATURE,
    DEVICE_CLASS_VOLUME_FLOW_RATE,
    ENTITY_CATEGORY_DIAGNOSTIC,
    ICON_TIMER,
    STATE_CLASS_MEASUREMENT,
    STATE_CLASS_TOTAL_INCREASING,
    UNIT_CELSIUS,
    UNIT_EMPTY,
    UNIT_PERCENT,
    UNIT_SECOND,
    CONF_PM_2_5,
    CONF_PM_10_0,
    DEVICE_CLASS_PM25,
    DEVICE_CLASS_PM10,
    UNIT_MICROGRAMS_PER_CUBIC_METER,
)

DEPENDENCIES = ["uart"]

CONF_FLOW_1 = "flow_1"
CONF_FLOW_2 = "flow_2"
CONF_FLOW_3 = "flow_3"
CONF_FLOW_4 = "flow_4"
CONF_TEMPERATURE_1 = "temperature_1"
CONF_TEMPERATURE_2 = "temperature_2"
CONF_TEMPERATURE_3 = "temperature_3"
CONF_SPEED = "speed"
CONF_UPTIME = "uptime"

from . import DysonTP07

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.use_id(DysonTP07),
        cv.Optional(CONF_TEMPERATURE_1): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_TEMPERATURE_2): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_TEMPERATURE_3): sensor.sensor_schema(
            unit_of_measurement=UNIT_CELSIUS,
            accuracy_decimals=2,
            device_class=DEVICE_CLASS_TEMPERATURE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_HUMIDITY): sensor.sensor_schema(
            unit_of_measurement=UNIT_PERCENT,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_HUMIDITY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_FLOW_1): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_VOLUME_FLOW_RATE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_FLOW_2): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_VOLUME_FLOW_RATE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_FLOW_3): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_VOLUME_FLOW_RATE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_FLOW_4): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_VOLUME_FLOW_RATE,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_SPEED): sensor.sensor_schema(
            icon="mdi:fan",
            accuracy_decimals=0,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_UPTIME): sensor.sensor_schema(
            unit_of_measurement=UNIT_SECOND,
            icon=ICON_TIMER,
            accuracy_decimals=0,
            state_class=STATE_CLASS_TOTAL_INCREASING,
            device_class=DEVICE_CLASS_DURATION,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
        ),
        cv.Optional(CONF_PM_2_5): sensor.sensor_schema(
            unit_of_measurement=UNIT_MICROGRAMS_PER_CUBIC_METER,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_PM25,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_PM_10_0): sensor.sensor_schema(
            unit_of_measurement=UNIT_MICROGRAMS_PER_CUBIC_METER,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_PM10,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
    }
)


async def to_code(config):
    var = await cg.get_variable(config[CONF_ID])

    if temperature_1_config := config.get(CONF_TEMPERATURE_1):
        temperature_1 = await sensor.new_sensor(temperature_1_config)
        cg.add(var.set_temperature_1_sensor(temperature_1))
    if temperature_2_config := config.get(CONF_TEMPERATURE_2):
        temperature_2 = await sensor.new_sensor(temperature_2_config)
        cg.add(var.set_temperature_2_sensor(temperature_2))
    if temperature_3_config := config.get(CONF_TEMPERATURE_3):
        temperature_3 = await sensor.new_sensor(temperature_3_config)
        cg.add(var.set_temperature_3_sensor(temperature_3))

    if humidity_config := config.get(CONF_HUMIDITY):
        humidity = await sensor.new_sensor(humidity_config)
        cg.add(var.set_humidity_sensor(humidity))

    if flow_1_config := config.get(CONF_FLOW_1):
        flow_1 = await sensor.new_sensor(flow_1_config)
        cg.add(var.set_flow_1_sensor(flow_1))
    if flow_2_config := config.get(CONF_FLOW_2):
        flow_2 = await sensor.new_sensor(flow_2_config)
        cg.add(var.set_flow_2_sensor(flow_2))
    if flow_3_config := config.get(CONF_FLOW_3):
        flow_3 = await sensor.new_sensor(flow_3_config)
        cg.add(var.set_flow_3_sensor(flow_3))
    if flow_4_config := config.get(CONF_FLOW_4):
        flow_4 = await sensor.new_sensor(flow_4_config)
        cg.add(var.set_flow_4_sensor(flow_4))

    if speed_config := config.get(CONF_SPEED):
        speed = await sensor.new_sensor(speed_config)
        cg.add(var.set_speed_sensor(speed))

    if uptime_config := config.get(CONF_UPTIME):
        uptime = await sensor.new_sensor(uptime_config)
        cg.add(var.set_uptime_sensor(uptime))

    if pm25_config := config.get(CONF_PM_2_5):
        pm25 = await sensor.new_sensor(pm25_config)
        cg.add(var.set_pm25_sensor(pm25))

    if pm10_config := config.get(CONF_PM_10_0):
        pm10 = await sensor.new_sensor(pm10_config)
        cg.add(var.set_pm10_sensor(pm10))

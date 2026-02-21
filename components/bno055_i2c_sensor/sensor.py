import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor
from esphome.const import (
    ICON_EMPTY,
    UNIT_EMPTY,
    CONF_ID,
    STATE_CLASS_MEASUREMENT,
    UNIT_DEGREES,
    UNIT_DEGREE_PER_SECOND,
    ENTITY_CATEGORY_DIAGNOSTIC,
    CONF_TEMPERATURE,
    UNIT_CELSIUS,
    DEVICE_CLASS_TEMPERATURE,
    UNIT_METER_PER_SECOND_SQUARED,
)

DEPENDENCIES = ["i2c"]

CONF_SYS_STATUS = "system_status"
CONF_SYS_ERROR = "system_error"
CONF_GYRO_X = "gyro_x"
CONF_GYRO_Y = "gyro_y"
CONF_GYRO_Z = "gyro_z"
CONF_EULER_YAW = "euler_yaw"
CONF_EULER_PITCH = "euler_pitch"
CONF_EULER_ROLL = "euler_roll"
CONF_CALIBRATION_SYS = "calibration_sys"
CONF_CALIBRATION_GYRO = "calibration_gyro"
CONF_CALIBRATION_ACCEL = "calibration_accel"
CONF_CALIBRATION_MAG = "calibration_mag"
CONF_ACCEL_X = "accel_x"
CONF_ACCEL_Y = "accel_y"
CONF_ACCEL_Z = "accel_z"
CONF_POWER_MODE = "power_mode"

bno055_i2c_sensor_ns = cg.esphome_ns.namespace("bno055_i2c_sensor")
BNO055I2CComponent = bno055_i2c_sensor_ns.class_(
    "BNO055I2CComponent ", cg.PollingComponent, i2c.I2CDevice
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(BNO055I2CComponent),
            cv.Optional(CONF_SYS_STATUS): sensor.sensor_schema(
                BNO055I2CComponent,
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_EMPTY,
                accuracy_decimals=0,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(CONF_SYS_ERROR): sensor.sensor_schema(
                BNO055I2CComponent,
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_EMPTY,
                accuracy_decimals=0,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
            cv.Optional(CONF_GYRO_X): sensor.sensor_schema(
                BNO055I2CComponent,
                unit_of_measurement=UNIT_DEGREE_PER_SECOND,
                icon="mdi:axis-x-rotate-clockwise",
                accuracy_decimals=1,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_GYRO_Y): sensor.sensor_schema(
                BNO055I2CComponent,
                unit_of_measurement=UNIT_DEGREE_PER_SECOND,
                icon="mdi:axis-y-rotate-clockwise",
                accuracy_decimals=1,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_GYRO_Z): sensor.sensor_schema(
                BNO055I2CComponent,
                unit_of_measurement=UNIT_DEGREE_PER_SECOND,
                icon="mdi:axis-z-rotate-clockwise",
                accuracy_decimals=1,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_EULER_YAW): sensor.sensor_schema(
                BNO055I2CComponent,
                unit_of_measurement=UNIT_DEGREES,
                icon="mdi:axis-x-rotate-clockwise",
                accuracy_decimals=2,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_EULER_ROLL): sensor.sensor_schema(
                BNO055I2CComponent,
                unit_of_measurement=UNIT_DEGREES,
                icon="mdi:axis-y-rotate-clockwise",
                accuracy_decimals=2,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_EULER_PITCH): sensor.sensor_schema(
                BNO055I2CComponent,
                unit_of_measurement=UNIT_DEGREES,
                icon="mdi:axis-z-rotate-clockwise",
                accuracy_decimals=2,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_CALIBRATION_SYS): sensor.sensor_schema(
                BNO055I2CComponent,
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_EMPTY,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                accuracy_decimals=0,
            ),
            cv.Optional(CONF_CALIBRATION_GYRO): sensor.sensor_schema(
                BNO055I2CComponent,
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_EMPTY,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                accuracy_decimals=0,
            ),
            cv.Optional(CONF_CALIBRATION_ACCEL): sensor.sensor_schema(
                BNO055I2CComponent,
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_EMPTY,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                accuracy_decimals=0,
            ),
            cv.Optional(CONF_CALIBRATION_MAG): sensor.sensor_schema(
                BNO055I2CComponent,
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_EMPTY,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                accuracy_decimals=0,
            ),
            cv.Optional(CONF_TEMPERATURE): sensor.sensor_schema(
                BNO055I2CComponent,
                unit_of_measurement=UNIT_CELSIUS,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
                accuracy_decimals=0,
            ),
            cv.Optional(CONF_ACCEL_X): sensor.sensor_schema(
                BNO055I2CComponent,
                unit_of_measurement=UNIT_METER_PER_SECOND_SQUARED,
                icon="mdi:axis-x-arrow",
                accuracy_decimals=0,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_ACCEL_Y): sensor.sensor_schema(
                BNO055I2CComponent,
                unit_of_measurement=UNIT_METER_PER_SECOND_SQUARED,
                icon="mdi:axis-y-arrow",
                accuracy_decimals=0,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_ACCEL_Z): sensor.sensor_schema(
                BNO055I2CComponent,
                unit_of_measurement=UNIT_METER_PER_SECOND_SQUARED,
                icon="mdi:axis-z-arrow",
                accuracy_decimals=0,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_POWER_MODE): sensor.sensor_schema(
                BNO055I2CComponent,
                unit_of_measurement=UNIT_EMPTY,
                icon=ICON_EMPTY,
                accuracy_decimals=0,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            ),
        }
    )
    .extend(cv.polling_component_schema("60s"))
    .extend(i2c.i2c_device_schema(0x28))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    if sys_status_config := config.get(CONF_SYS_STATUS):
        sens = await sensor.new_sensor(sys_status_config)
        cg.add(var.set_sys_status_sensor(sens))
    if sys_error_config := config.get(CONF_SYS_ERROR):
        sens = await sensor.new_sensor(sys_error_config)
        cg.add(var.set_sys_error_sensor(sens))

    if gyro_x_config := config.get(CONF_GYRO_X):
        sens = await sensor.new_sensor(gyro_x_config)
        cg.add(var.set_gyro_x_sensor(sens))
    if gyro_y_config := config.get(CONF_GYRO_Y):
        sens = await sensor.new_sensor(gyro_y_config)
        cg.add(var.set_gyro_y_sensor(sens))
    if gyro_z_config := config.get(CONF_GYRO_Z):
        sens = await sensor.new_sensor(gyro_z_config)
        cg.add(var.set_gyro_z_sensor(sens))

    if euler_yaw_config := config.get(CONF_EULER_YAW):
        sens = await sensor.new_sensor(euler_yaw_config)
        cg.add(var.set_euler_yaw_sensor(sens))
    if euler_roll_config := config.get(CONF_EULER_ROLL):
        sens = await sensor.new_sensor(euler_roll_config)
        cg.add(var.set_euler_roll_sensor(sens))
    if euler_pitch_config := config.get(CONF_EULER_PITCH):
        sens = await sensor.new_sensor(euler_pitch_config)
        cg.add(var.set_euler_pitch_sensor(sens))

    if calibration_sys_config := config.get(CONF_CALIBRATION_SYS):
        sens = await sensor.new_sensor(calibration_sys_config)
        cg.add(var.set_calibration_sys_sensor(sens))
    if calibration_gyro_config := config.get(CONF_CALIBRATION_GYRO):
        sens = await sensor.new_sensor(calibration_gyro_config)
        cg.add(var.set_calibration_gyro_sensor(sens))
    if calibration_accel_config := config.get(CONF_CALIBRATION_ACCEL):
        sens = await sensor.new_sensor(calibration_accel_config)
        cg.add(var.set_calibration_accel_sensor(sens))
    if calibration_mag_config := config.get(CONF_CALIBRATION_MAG):
        sens = await sensor.new_sensor(calibration_mag_config)
        cg.add(var.set_calibration_mag_sensor(sens))

    if temperature_config := config.get(CONF_TEMPERATURE):
        sens = await sensor.new_sensor(temperature_config)
        cg.add(var.set_temperature_sensor(sens))

    if accel_x_config := config.get(CONF_ACCEL_X):
        sens = await sensor.new_sensor(accel_x_config)
        cg.add(var.set_accel_x_sensor(sens))
    if accel_y_config := config.get(CONF_ACCEL_Y):
        sens = await sensor.new_sensor(accel_y_config)
        cg.add(var.set_accel_y_sensor(sens))
    if accel_z_config := config.get(CONF_ACCEL_Z):
        sens = await sensor.new_sensor(accel_z_config)
        cg.add(var.set_accel_z_sensor(sens))

    if power_mode_config := config.get(CONF_POWER_MODE):
        sens = await sensor.new_sensor(power_mode_config)
        cg.add(var.set_power_mode_sensor(sens))

#pragma once

#include "esphome/components/i2c/i2c.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"

namespace esphome {
namespace bno055_i2c_sensor {

class BNO055I2CComponent : public sensor::Sensor,
                           public PollingComponent,
                           public i2c::I2CDevice {
public:
  void setup() override;
  void update() override;
  void dump_config() override;

  sensor::Sensor *sys_status_sensor_{nullptr};
  sensor::Sensor *sys_error_sensor_{nullptr};
  sensor::Sensor *gyro_x_sensor_{nullptr};
  sensor::Sensor *gyro_y_sensor_{nullptr};
  sensor::Sensor *gyro_z_sensor_{nullptr};
  sensor::Sensor *euler_yaw_sensor_{nullptr};
  sensor::Sensor *euler_roll_sensor_{nullptr};
  sensor::Sensor *euler_pitch_sensor_{nullptr};
  sensor::Sensor *calibration_sys_sensor_{nullptr};
  sensor::Sensor *calibration_gyro_sensor_{nullptr};
  sensor::Sensor *calibration_accel_sensor_{nullptr};
  sensor::Sensor *calibration_mag_sensor_{nullptr};
  sensor::Sensor *temperature_sensor_{nullptr};
  sensor::Sensor *accel_x_sensor_{nullptr};
  sensor::Sensor *accel_y_sensor_{nullptr};
  sensor::Sensor *accel_z_sensor_{nullptr};
  sensor::Sensor *power_mode_sensor_{nullptr};

  void set_sys_status_sensor(sensor::Sensor *sys_status_sensor) {
    sys_status_sensor_ = sys_status_sensor;
  }
  void set_sys_error_sensor(sensor::Sensor *sys_error_sensor) {
    sys_error_sensor_ = sys_error_sensor;
  }
  void set_gyro_x_sensor(sensor::Sensor *gyro_x_sensor) {
    gyro_x_sensor_ = gyro_x_sensor;
  }
  void set_gyro_y_sensor(sensor::Sensor *gyro_y_sensor) {
    gyro_y_sensor_ = gyro_y_sensor;
  }
  void set_gyro_z_sensor(sensor::Sensor *gyro_z_sensor) {
    gyro_z_sensor_ = gyro_z_sensor;
  }
  void set_euler_yaw_sensor(sensor::Sensor *euler_yaw_sensor) {
    euler_yaw_sensor_ = euler_yaw_sensor;
  }
  void set_euler_roll_sensor(sensor::Sensor *euler_roll_sensor) {
    euler_roll_sensor_ = euler_roll_sensor;
  }
  void set_euler_pitch_sensor(sensor::Sensor *euler_pitch_sensor) {
    euler_pitch_sensor_ = euler_pitch_sensor;
  }
  void set_calibration_sys_sensor(sensor::Sensor *calibration_sys_sensor) {
    calibration_sys_sensor_ = calibration_sys_sensor;
  }
  void set_calibration_gyro_sensor(sensor::Sensor *calibration_gyro_sensor) {
    calibration_gyro_sensor_ = calibration_gyro_sensor;
  }
  void set_calibration_accel_sensor(sensor::Sensor *calibration_accel_sensor) {
    calibration_accel_sensor_ = calibration_accel_sensor;
  }
  void set_calibration_mag_sensor(sensor::Sensor *calibration_mag_sensor) {
    calibration_mag_sensor_ = calibration_mag_sensor;
  }
  void set_temperature_sensor(sensor::Sensor *temperature_sensor) {
    temperature_sensor_ = temperature_sensor;
  }
  void set_accel_x_sensor(sensor::Sensor *accel_x_sensor) {
    accel_x_sensor_ = accel_x_sensor;
  }
  void set_accel_y_sensor(sensor::Sensor *accel_y_sensor) {
    accel_y_sensor_ = accel_y_sensor;
  }
  void set_accel_z_sensor(sensor::Sensor *accel_z_sensor) {
    accel_z_sensor_ = accel_z_sensor;
  }
  void set_power_mode_sensor(sensor::Sensor *power_mode_sensor) {
    power_mode_sensor_ = power_mode_sensor;
  }

protected:
  bool initialised_{false};
};

} // namespace bno055_i2c_sensor
} // namespace esphome

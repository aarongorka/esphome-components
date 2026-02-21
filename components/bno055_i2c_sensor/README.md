# BNO055 absolute position sensor

I think it all pretty much works, but be warned it hasn't seen much use as I haven't gotten back to this project yet.

```yaml
# example configuration:

i2c:
  - id: i2c_a
    sda: GPIO3
    scl: GPIO1

sensor:
  - platform: bno055_i2c_sensor
    id: "my_bno055_i2c_sensor"
    system_status:
      name: "BNO055 System Status"
      id: "my_bno055_system_status"
    system_error:
      name: "BNO055 System Error"
      id: "my_bno055_system_error"
    gyro_x:
      name: "BNO055 Gyro X"
      id: "my_bno055_gyro_x"
    gyro_y:
      name: "BNO055 Gyro Y"
      id: "my_bno055_gyro_y"
    gyro_z:
      name: "BNO055 Gyro Z"
      id: "my_bno055_gyro_z"
    euler_yaw:
      name: "BNO055 Euler Yaw"
      id: "my_bno055_euler_yaw"
    euler_roll:
      name: "BNO055 Euler Roll"
      id: "my_bno055_euler_roll"
    euler_pitch:
      name: "BNO055 Euler Pitch"
      id: "my_bno055_euler_pitch"
    calibration_sys:
      name: "BNO055 Calibration System"
      id: "my_bno055_calibration_sys"
    calibration_gyro:
      name: "BNO055 Calibration Gyroscope"
      id: "my_bno055_calibration_gyro"
    calibration_accel:
      name: "BNO055 Calibration Accelerometer"
      id: "my_bno055_calibration_accel"
    calibration_mag:
      name: "BNO055 Calibration Magnetometer"
      id: "my_bno055_calibration_mag"
    temperature:
      name: "BNO055 Temperature"
      id: "my_bno055_temperature"
    accel_x:
      name: "BNO055 Accel X"
      id: "my_bno055_accel_x"
    accel_y:
      name: "BNO055 Accel Y"
      id: "my_bno055_accel_y"
    accel_z:
      name: "BNO055 Accel Z"
      id: "my_bno055_accel_z"

binary_sensor:
  - platform: gpio
    pin: GPIO7
    name: "BNO055 Interrupt"
    id: "my_bno055_interrupt"

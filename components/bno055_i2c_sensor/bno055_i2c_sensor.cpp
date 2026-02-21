#include "bno055_i2c_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace bno055_i2c_sensor {

static const char *TAG = "bno055_i2c_sensor.sensor";

// https://github.com/kriswiner/ESP32/blob/master/Bosch/BNO055_MS5637.ino

#define BNO055_CHIP_ID 0x00 // should be 0xA0
#define BNO055_ACC_ID 0x01  // should be 0xFB
#define BNO055_MAG_ID 0x02  // should be 0x32
#define BNO055_GYRO_ID 0x03 // should be 0x0F
#define BNO055_SW_REV_ID_LSB 0x04
#define BNO055_SW_REV_ID_MSB 0x05
#define BNO055_BL_REV_ID 0x06
#define BNO055_PAGE_ID 0x07
#define BNO055_ACC_DATA_X_LSB 0x08
#define BNO055_ACC_DATA_X_MSB 0x09
#define BNO055_ACC_DATA_Y_LSB 0x0A
#define BNO055_ACC_DATA_Y_MSB 0x0B
#define BNO055_ACC_DATA_Z_LSB 0x0C
#define BNO055_ACC_DATA_Z_MSB 0x0D
#define BNO055_MAG_DATA_X_LSB 0x0E
#define BNO055_MAG_DATA_X_MSB 0x0F
#define BNO055_MAG_DATA_Y_LSB 0x10
#define BNO055_MAG_DATA_Y_MSB 0x11
#define BNO055_MAG_DATA_Z_LSB 0x12
#define BNO055_MAG_DATA_Z_MSB 0x13
#define BNO055_GYR_DATA_X_LSB 0x14
#define BNO055_GYR_DATA_X_MSB 0x15
#define BNO055_GYR_DATA_Y_LSB 0x16
#define BNO055_GYR_DATA_Y_MSB 0x17
#define BNO055_GYR_DATA_Z_LSB 0x18
#define BNO055_GYR_DATA_Z_MSB 0x19
#define BNO055_EUL_HEADING_LSB 0x1A
#define BNO055_EUL_HEADING_MSB 0x1B
#define BNO055_EUL_ROLL_LSB 0x1C
#define BNO055_EUL_ROLL_MSB 0x1D
#define BNO055_EUL_PITCH_LSB 0x1E
#define BNO055_EUL_PITCH_MSB 0x1F
#define BNO055_QUA_DATA_W_LSB 0x20
#define BNO055_QUA_DATA_W_MSB 0x21
#define BNO055_QUA_DATA_X_LSB 0x22
#define BNO055_QUA_DATA_X_MSB 0x23
#define BNO055_QUA_DATA_Y_LSB 0x24
#define BNO055_QUA_DATA_Y_MSB 0x25
#define BNO055_QUA_DATA_Z_LSB 0x26
#define BNO055_QUA_DATA_Z_MSB 0x27
#define BNO055_LIA_DATA_X_LSB 0x28
#define BNO055_LIA_DATA_X_MSB 0x29
#define BNO055_LIA_DATA_Y_LSB 0x2A
#define BNO055_LIA_DATA_Y_MSB 0x2B
#define BNO055_LIA_DATA_Z_LSB 0x2C
#define BNO055_LIA_DATA_Z_MSB 0x2D
#define BNO055_GRV_DATA_X_LSB 0x2E
#define BNO055_GRV_DATA_X_MSB 0x2F
#define BNO055_GRV_DATA_Y_LSB 0x30
#define BNO055_GRV_DATA_Y_MSB 0x31
#define BNO055_GRV_DATA_Z_LSB 0x32
#define BNO055_GRV_DATA_Z_MSB 0x33
#define BNO055_TEMP 0x34
#define BNO055_CALIB_STAT 0x35
#define BNO055_ST_RESULT 0x36
#define BNO055_INT_STATUS 0x37
#define BNO055_SYS_CLK_STATUS 0x38
#define BNO055_SYS_STATUS 0x39
#define BNO055_SYS_ERR 0x3A
#define BNO055_UNIT_SEL 0x3B
#define BNO055_OPR_MODE 0x3D
#define BNO055_PWR_MODE 0x3E
#define BNO055_SYS_TRIGGER 0x3F
#define BNO055_TEMP_SOURCE 0x40
#define BNO055_AXIS_MAP_CONFIG 0x41
#define BNO055_AXIS_MAP_SIGN 0x42
#define BNO055_ACC_OFFSET_X_LSB 0x55
#define BNO055_ACC_OFFSET_X_MSB 0x56
#define BNO055_ACC_OFFSET_Y_LSB 0x57
#define BNO055_ACC_OFFSET_Y_MSB 0x58
#define BNO055_ACC_OFFSET_Z_LSB 0x59
#define BNO055_ACC_OFFSET_Z_MSB 0x5A
#define BNO055_MAG_OFFSET_X_LSB 0x5B
#define BNO055_MAG_OFFSET_X_MSB 0x5C
#define BNO055_MAG_OFFSET_Y_LSB 0x5D
#define BNO055_MAG_OFFSET_Y_MSB 0x5E
#define BNO055_MAG_OFFSET_Z_LSB 0x5F
#define BNO055_MAG_OFFSET_Z_MSB 0x60
#define BNO055_GYR_OFFSET_X_LSB 0x61
#define BNO055_GYR_OFFSET_X_MSB 0x62
#define BNO055_GYR_OFFSET_Y_LSB 0x63
#define BNO055_GYR_OFFSET_Y_MSB 0x64
#define BNO055_GYR_OFFSET_Z_LSB 0x65
#define BNO055_GYR_OFFSET_Z_MSB 0x66
#define BNO055_ACC_RADIUS_LSB 0x67
#define BNO055_ACC_RADIUS_MSB 0x68
#define BNO055_MAG_RADIUS_LSB 0x69
#define BNO055_MAG_RADIUS_MSB 0x6A
//
// BNO055 Page 1
#define BNO055_PAGE_ID 0x07
#define BNO055_ACC_CONFIG 0x08
#define BNO055_MAG_CONFIG 0x09
#define BNO055_GYRO_CONFIG_0 0x0A
#define BNO055_GYRO_CONFIG_1 0x0B
#define BNO055_ACC_SLEEP_CONFIG 0x0C
#define BNO055_GYR_SLEEP_CONFIG 0x0D
#define BNO055_INT_MSK 0x0F
#define BNO055_INT_EN 0x10
#define BNO055_ACC_AM_THRES 0x11
#define BNO055_ACC_INT_SETTINGS 0x12
#define BNO055_ACC_HG_DURATION 0x13
#define BNO055_ACC_HG_THRESH 0x14
#define BNO055_ACC_NM_THRESH 0x15
#define BNO055_ACC_NM_SET 0x16
#define BNO055_GYR_INT_SETTINGS 0x17
#define BNO055_GYR_HR_X_SET 0x18
#define BNO055_GYR_DUR_X 0x19
#define BNO055_GYR_HR_Y_SET 0x1A
#define BNO055_GYR_DUR_Y 0x1B
#define BNO055_GYR_HR_Z_SET 0x1C
#define BNO055_GYR_DUR_Z 0x1D
#define BNO055_GYR_AM_THRESH 0x1E
#define BNO055_GYR_AM_SET 0x1F

// #define BNO055_ADDRESS 0x29 // or 0x28

enum SystemStatus { // BNO-55 operation modes
  IDLE = 0x00,
  SYS_ERROR,

};

enum OPRMode { // BNO-55 operation modes
  CONFIGMODE = 0x00,
  // Sensor Mode
  ACCONLY,
  MAGONLY,
  GYROONLY,
  ACCMAG,
  ACCGYRO,
  MAGGYRO,
  AMG, // 0x07
       // Fusion Mode
  IMU,
  COMPASS,
  M4G,
  NDOF_FMC_OFF,
  NDOF // 0x0C
};

void BNO055I2CComponent::setup() {
  ESP_LOGCONFIG(TAG, "Starting bno055 setup...");

  this->set_timeout(50000, [this]() {
    this->status_clear_error();

    uint8_t chip_id;
    if (!this->read_byte(BNO055_CHIP_ID, &chip_id) || chip_id != 0xA0) {
      ESP_LOGE(TAG, "Could not query chip ID for BNO055.");
      this->mark_failed();
      return;
    }
    ESP_LOGI(TAG, "BNO055 chip ID: %#04x", chip_id);

    OPRMode mode = NDOF; // specify operation mode for sensors
    if (!this->write_byte(BNO055_OPR_MODE, mode)) {
      ESP_LOGE(TAG, "Could not set operating mode.");
      this->mark_failed();
      return;
    }
    uint8_t operation_mode;
    if (!this->read_byte(BNO055_OPR_MODE, &operation_mode) ||
        operation_mode != 0x0C) {
      ESP_LOGE(TAG,
               "Did not get expected operating mode back, marking as failed.");
      this->mark_failed();
      return;
    }
    ESP_LOGCONFIG(TAG, "BNO055 operation mode: %#04x", operation_mode);

    uint8_t self_test;
    if (!this->read_byte(BNO055_ST_RESULT, &self_test)) {
      ESP_LOGE(TAG, "Could not query self test.");
      this->mark_failed();
      return;
    }
    ESP_LOGCONFIG(TAG, "Self test result: %#04x", self_test);

    initialised_ = true;

    ESP_LOGCONFIG(TAG, "BNO055 init complete.");
  });
}

void BNO055I2CComponent::update() {
  ESP_LOGD(TAG, "Starting BNO055 loop...");

  if (!initialised_) {
    return;
  }

  /*
    TODO:
    https://first-tech-challenge.github.io/SkyStone/com/qualcomm/hardware/bosch/BNO055IMU.html

    Result	Meaning
    0	idle
    1	system error
    2	initializing peripherals
    3	system initialization
    4	executing self-test
    5	sensor fusion algorithm running
    6	system running without fusion algorithms
  */
  this->set_timeout("sys_status", 120, [this]() {
    if (this->sys_status_sensor_ != nullptr) {
      uint8_t sys_status;
      if (!this->read_byte(BNO055_SYS_STATUS, &sys_status)) {
        ESP_LOGE(TAG, "Could not query system status.");
        this->mark_failed();
        return;
      }
      ESP_LOGD(TAG, "System status code: %#04x", sys_status);
      this->sys_status_sensor_->publish_state(sys_status);

      if (this->sys_error_sensor_ != nullptr) {
        if (sys_status == 0x01) {
          ESP_LOGE(TAG, "Sytem status indicates an error, reading code...");

          uint8_t sys_error;
          if (!this->read_byte(BNO055_SYS_ERR, &sys_error)) {
            ESP_LOGE(TAG, "Could not query system error.");
            this->mark_failed();
            return;
          }

          if (sys_error == 0x01)
            ESP_LOGE(TAG, "Peripheral initialization error");
          if (sys_error == 0x02)
            ESP_LOGE(TAG, "System initialization error");
          if (sys_error == 0x03)
            ESP_LOGE(TAG, "Self test result failed");
          if (sys_error == 0x04)
            ESP_LOGE(TAG, "Register map value out of range");
          if (sys_error == 0x05)
            ESP_LOGE(TAG, "Register map address out of range");
          if (sys_error == 0x06)
            ESP_LOGE(TAG, "Register map write error");
          if (sys_error == 0x07)
            ESP_LOGE(
                TAG,
                "BNO low power mode no available for selected operation mode");
          if (sys_error == 0x08)
            ESP_LOGE(TAG, "Accelerometer power mode not available");
          if (sys_error == 0x09)
            ESP_LOGE(TAG, "Fusion algorithm configuration error");
          if (sys_error == 0x0A)
            ESP_LOGE(TAG, "Sensor configuration error");

          this->sys_error_sensor_->publish_state(sys_error);
        } else {
          this->sys_error_sensor_->publish_state(0);
        }
      }
    }
  });

  this->set_timeout("gyro", 50, [this]() {
    if ((this->gyro_x_sensor_ != nullptr) ||
        (this->gyro_y_sensor_ != nullptr) ||
        (this->gyro_z_sensor_ != nullptr)) {
      uint8_t gyroData[6];
      if (!this->read_bytes(BNO055_GYR_DATA_X_LSB, &gyroData[0], 6)) {
        ESP_LOGE(TAG, "Could not query gyro data.");
        this->mark_failed();
        return;
      }
      if (this->gyro_x_sensor_ != nullptr) {
        int16_t gyro_x_int = ((int16_t)gyroData[1] << 8) | gyroData[0];
        float gyro_x = gyro_x_int / 16.;
        ESP_LOGD(TAG, "Gyro x: %f", gyro_x);
        this->gyro_x_sensor_->publish_state(gyro_x);
      }
      if (this->gyro_y_sensor_ != nullptr) {
        int16_t gyro_y_int = ((int16_t)gyroData[3] << 8) | gyroData[2];
        float gyro_y = gyro_y_int / 16.;
        ESP_LOGD(TAG, "Gyro y: %f", gyro_y);
        this->gyro_y_sensor_->publish_state(gyro_y);
      }
      if (this->gyro_z_sensor_ != nullptr) {
        int16_t gyro_z_int = ((int16_t)gyroData[5] << 8) | gyroData[4];
        float gyro_z = gyro_z_int / 16.;
        ESP_LOGD(TAG, "Gyro z: %f", gyro_z);
        this->gyro_z_sensor_->publish_state(gyro_z);
      }
    }

    if ((this->euler_yaw_sensor_ != nullptr) ||
        (this->euler_roll_sensor_ != nullptr) ||
        (this->euler_pitch_sensor_ != nullptr)) {
      uint8_t eulerData[6];
      if (!this->read_bytes(BNO055_EUL_HEADING_LSB, &eulerData[0], 6)) {
        this->mark_failed();
        return;
      }
      if (this->euler_yaw_sensor_ != nullptr) {
        int16_t euler_yaw_int =
            (((int16_t)eulerData[1] << 8) | eulerData[0]) / 16.;
        float euler_yaw = euler_yaw_int / 16.;
        ESP_LOGD(TAG, "Euler yaw: %f", euler_yaw);
        this->euler_yaw_sensor_->publish_state(euler_yaw);
      }
      if (this->euler_roll_sensor_ != nullptr) {
        int16_t euler_roll_int =
            (((int16_t)eulerData[3] << 8) | eulerData[2]) / 16.;
        float euler_roll = euler_roll_int / 16.;
        ESP_LOGD(TAG, "Euler roll: %f", euler_roll);
        this->euler_roll_sensor_->publish_state(euler_roll);
      }
      if (this->euler_pitch_sensor_ != nullptr) {
        int16_t euler_pitch_int =
            (((int16_t)eulerData[5] << 8) | eulerData[4]) / 16.;
        float euler_pitch = euler_pitch_int / 16.;
        ESP_LOGD(TAG, "Euler pitch: %f", euler_pitch);
        this->euler_pitch_sensor_->publish_state(euler_pitch);
      }
    }
  });

  this->set_timeout("calibration", 50, [this]() {
    if ((this->calibration_sys_sensor_ != nullptr) ||
        (this->calibration_gyro_sensor_ != nullptr) ||
        (this->calibration_accel_sensor_ != nullptr) ||
        (this->calibration_mag_sensor_ != nullptr)) {
      uint8_t calibration_data;
      if (!this->read_byte(BNO055_CALIB_STAT, &calibration_data)) {
        ESP_LOGE(TAG, "Could not query calibration data.");
        this->mark_failed();
        return;
      }
      ESP_LOGD(TAG, "Not calibrated = 0, fully calibrated = 3");
      if (this->calibration_sys_sensor_ != nullptr) {
        uint8_t calibration_sys = (0xC0 & calibration_data) >> 6;
        ESP_LOGD(TAG, "System calibration status: %d", calibration_sys);
        this->calibration_sys_sensor_->publish_state(calibration_sys);
      }
      if (this->calibration_gyro_sensor_ != nullptr) {
        uint8_t calibration_gyro = (0x30 & calibration_data) >> 4;
        ESP_LOGD(TAG, "Gyro   calibration status: %d", calibration_gyro);
        this->calibration_gyro_sensor_->publish_state(calibration_gyro);
      }
      if (this->calibration_accel_sensor_ != nullptr) {
        uint8_t calibration_accel = (0x0C & calibration_data) >> 2;
        ESP_LOGD(TAG, "Accel  calibration status: %d", calibration_accel);
        this->calibration_accel_sensor_->publish_state(calibration_accel);
      }
      if (this->calibration_mag_sensor_ != nullptr) {
        uint8_t calibration_mag = (0x03 & calibration_data) >> 0;
        ESP_LOGD(TAG, "Mag    calibration status: %d", calibration_mag);
        this->calibration_mag_sensor_->publish_state(calibration_mag);
      }
    }
  });

  this->set_timeout("temperature", 50, [this]() {
    if (this->temperature_sensor_ != nullptr) {
      uint8_t temperature;
      if (!this->read_byte(BNO055_TEMP, &temperature)) {
        ESP_LOGE(TAG, "Failed to query temperature.", temperature);
        this->mark_failed();
        return;
      }
      ESP_LOGD(TAG, "Temperature: %d", temperature);
      this->temperature_sensor_->publish_state(temperature);
    }
  });

  this->set_timeout("acceleration", 50, [this]() {
    if ((this->accel_x_sensor_ != nullptr) ||
        (this->accel_y_sensor_ != nullptr) ||
        (this->accel_z_sensor_ != nullptr)) {
      uint8_t accelData[6];
      if (!this->read_bytes(BNO055_LIA_DATA_X_LSB, &accelData[0], 6)) {
        ESP_LOGE(TAG, "Could not query linear acceleration data.");
        this->mark_failed();
        return;
      }

      if (this->accel_x_sensor_ != nullptr) {
        int16_t accel_x = ((int16_t)accelData[1] << 8) | accelData[0];
        ESP_LOGD(TAG, "Accel x: %f", accel_x);
        this->accel_x_sensor_->publish_state(accel_x);
      }
      if (this->accel_y_sensor_ != nullptr) {
        int16_t accel_y = ((int16_t)accelData[3] << 8) | accelData[2];
        ESP_LOGD(TAG, "Accel y: %f", accel_y);
        this->accel_y_sensor_->publish_state(accel_y);
      }
      if (this->accel_z_sensor_ != nullptr) {
        int16_t accel_z = ((int16_t)accelData[5] << 8) | accelData[4];
        ESP_LOGD(TAG, "Accel z: %f", accel_z);
        this->accel_z_sensor_->publish_state(accel_z);
      }
    }

    this->set_timeout("power_mode", 50, [this]() {
      if (this->power_mode_sensor_ != nullptr) {
        uint8_t power_mode;
        if (!this->read_byte(BNO055_PWR_MODE, &power_mode)) {
          ESP_LOGE(TAG, "Failed to query power mode.");
          this->mark_failed();
          return;
        }
        ESP_LOGD(TAG, "power_mode: %d", power_mode);
        this->power_mode_sensor_->publish_state(power_mode);
      }
    });
  });

  ESP_LOGD(TAG, "BNO055 loop finished.");
}

void BNO055I2CComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Config dump goes here...");
  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication with BNO055 failed!");
  }
  LOG_I2C_DEVICE(this);
}

} // namespace bno055_i2c_sensor
} // namespace esphome

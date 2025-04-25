#pragma once

#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"
// #include "esphome/components/uart/uart_debugger.h"
#include "esphome/core/component.h"

namespace esphome {
namespace dyson_tp07 {

// extern "C" {
// #include "DysonUart.h"
// }

#define START_BYTE 0x12
#define STOP_BYTE 0x12
#define STUFF_BYTE_1 0xDB
#define STUFF_BYTE_2 0xDE
#define STUFF_BYTE_3 0xDD
#define MAX_FAN_LEVEL 10
#define MIN_FAN_LEVEL 1

typedef struct uart_packet_t {
  uint8_t ptr[256];   // @brief Variable to store uart packet data
  size_t packet_size; // @brief Size of ptr in bytes
  float time; // @brief Time of received packets, seconds from the device start
              // (optional)

} uart_packet_t;

typedef struct Dyson_regs {
  struct Flow_reg_t {
    uint16_t Flow1;
    uint16_t Flow2;
    uint16_t Flow3;
    uint16_t Flow4;
  } Flow_reg;

  uint32_t UpTime_reg;

  struct reg_2_0_4_0 {
    double Temp1;
    double Temp2;
    double Temp3;
    double Humidity;
    double Vent_level;
  } Temp_reg;

  struct reg_2_0_3_0 {
    double Reg1;
    double Reg2;
    double Reg3;
    double Reg4;
    double Reg5;
  } reg_2_0_3_0;

  struct reg_2_0_2_0 {
    uint8_t Reg1;
    uint8_t Reg2;
    uint8_t Reg3;
    uint8_t Reg4;
  } reg_2_0_2_0;

  struct reg_2_0_5_0 {
    uint32_t Reg1;
    uint32_t Reg2;
    uint32_t Reg3;
  } reg_2_0_5_0;

  struct reg_2_0_6_0 {
    uint16_t Reg1;
    uint16_t Reg2;
  } reg_2_0_6_0;

  struct reg_2_0_7_0 {
    double Part_2_5;
    double Part_10;
    double Reg3;
    double Reg4;
    double Reg5;
    double Reg6;
    double Reg7;
    double Reg8;
    double Reg9;
    double Reg10;
    double Reg11;
    double Reg12;
    double Reg13;
  } reg_2_0_7_0;

  struct reg_2_0_8_0 {
    uint8_t Part_2_5_int;
    uint8_t Reg2;
    uint8_t Reg3;
    uint8_t Reg4;
    uint8_t Reg5;
    uint8_t Reg6;
    uint8_t Reg7;
    uint8_t Reg8;
    uint8_t Reg9;
    uint8_t Reg10;
    uint8_t Part_10_int;
    uint8_t Reg12;
  } reg_2_0_8_0;

  struct reg_2_0_9_0 {
    double Reg1;
    double Reg2;
    double Reg3;
    double Reg4;
    double Reg5;
  } reg_2_0_9_0;

  struct reg_2_0_10_0 {
    double Reg1;
    double Reg2;
    double Reg3;
    double Reg4;
    double Reg5;
    double Reg6;
    double Reg7;
  } reg_2_0_10_0;

  struct reg_2_0_12_0 {
    uint8_t Reg1;
    uint8_t Reg2;
    uint8_t Reg3;
    uint8_t Reg4;
  } reg_2_0_12_0;

  struct reg_3_0_1_0 {
    uint32_t Reg1;
    uint32_t Reg2;
  } reg_3_0_1_0;

  struct reg_3_0_5_0 {
    double Reg1;
    double Reg2;
    double Reg3;
    double Reg4;
  } reg_3_0_5_0;

  struct reg_3_0_6_0 {
    double Reg1;
    double Reg2;
    double Reg3;
    double Reg4;
    double Reg5;
  } reg_3_0_6_0;

  struct reg_3_0_7_0 {
    double Reg1;
    double Reg2;
    double Reg3;
    double Reg4;
    double Reg5;
  } reg_3_0_7_0;

  struct reg_3_0_8_0 {
    double Reg1;
    double Reg2;
    double Reg3;
    double Reg4;
  } reg_3_0_8_0;

  struct reg_3_0_9_0 {
    double Reg1;
    double Reg2;
    double Reg3;
    double Reg4;
    double Reg5;
    double Reg6;
  } reg_3_0_9_0;

  struct reg_3_0_10_0 {
    double Reg1;
    double Reg2;
    double Reg3;
    double Reg4;
    double Up_time;
  } reg_3_0_10_0;
} Dyson_regs_t;

class DysonTP07 : public sensor::Sensor,
                  public PollingComponent,
                  public uart::UARTDevice {
public:
  void setup() override;
  void update() override;
  void loop() override;
  void dump_config() override;
  void printDysonRegisters(const Dyson_regs_t *dyson_reg);

  sensor::Sensor *temperature_1_sensor_{nullptr};
  sensor::Sensor *temperature_2_sensor_{nullptr};
  sensor::Sensor *temperature_3_sensor_{nullptr};
  sensor::Sensor *humidity_sensor_{nullptr};
  sensor::Sensor *flow_1_sensor_{nullptr};
  sensor::Sensor *flow_2_sensor_{nullptr};
  sensor::Sensor *flow_3_sensor_{nullptr};
  sensor::Sensor *flow_4_sensor_{nullptr};
  sensor::Sensor *speed_sensor_{nullptr};
  sensor::Sensor *uptime_sensor_{nullptr};
  sensor::Sensor *pm25_sensor_{nullptr};
  sensor::Sensor *pm10_sensor_{nullptr};
  binary_sensor::BinarySensor *is_on_sensor_{nullptr};

  void set_temperature_1_sensor(sensor::Sensor *temperature_1_sensor) {
    temperature_1_sensor_ = temperature_1_sensor;
  }
  void set_temperature_2_sensor(sensor::Sensor *temperature_2_sensor) {
    temperature_2_sensor_ = temperature_2_sensor;
  }
  void set_temperature_3_sensor(sensor::Sensor *temperature_3_sensor) {
    temperature_3_sensor_ = temperature_3_sensor;
  }
  void set_humidity_sensor(sensor::Sensor *humidity_sensor) {
    humidity_sensor_ = humidity_sensor;
  }
  void set_flow_1_sensor(sensor::Sensor *flow_1_sensor) {
    flow_1_sensor_ = flow_1_sensor;
  }
  void set_flow_2_sensor(sensor::Sensor *flow_2_sensor) {
    flow_2_sensor_ = flow_2_sensor;
  }
  void set_flow_3_sensor(sensor::Sensor *flow_3_sensor) {
    flow_3_sensor_ = flow_3_sensor;
  }
  void set_flow_4_sensor(sensor::Sensor *flow_4_sensor) {
    flow_4_sensor_ = flow_4_sensor;
  }
  void set_speed_sensor(sensor::Sensor *speed_sensor) {
    speed_sensor_ = speed_sensor;
  }
  void set_uptime_sensor(sensor::Sensor *uptime_sensor) {
    uptime_sensor_ = uptime_sensor;
  }
  void set_pm25_sensor(sensor::Sensor *pm25_sensor) {
    pm25_sensor_ = pm25_sensor;
  }
  void set_pm10_sensor(sensor::Sensor *pm10_sensor) {
    pm10_sensor_ = pm10_sensor;
  }
  void set_is_on_sensor(binary_sensor::BinarySensor *is_on_sensor) {
    is_on_sensor_ = is_on_sensor;
  }
  double get_speed_sensor();
  bool get_is_on_sensor();

protected:
  uint8_t ParseUartStream(uint8_t *rx_buf, size_t buf_size);
  uart_packet_t *UnstuffPacket(uart_packet_t *packet);
  uint8_t ParseDysonPacket(uart_packet_t &packet, Dyson_regs_t &regs);

  uint8_t ParseSecondaryRegister(uint8_t reg, const uint8_t *data,
                                 Dyson_regs_t &regs);
  uint8_t ParseTertiaryRegister(uint8_t reg, const uint8_t *data,
                                Dyson_regs_t &regs);
  template <typename T> uint8_t ParseData(const uint8_t *ptr, T &reg);
};

} // namespace dyson_tp07
} // namespace esphome

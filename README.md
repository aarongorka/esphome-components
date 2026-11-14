# ESPHome External Components

Repository for [ESPHome External Components](https://esphome.io/components/external_components).

Usage:

```
external_components:
  - source: github://aarongorka/esphome-components
```

## Dyson TP07 Component

Reads data from the UART debug port. Also included in the example is configuration to use an infrared transmitter to control the fan.

All credit to https://github.com/Alex-Trusk/Dyson_UART_parser for the original code; this just reimplements it for esphome.

![Dyson TP07 component in Home Assistant](./components/dyson_tp07/home_assistant.png)

```yaml
uart:
  - id: my_uart
    rx_pin: GPIO19
    baud_rate: 115200
    parity: NONE
    stop_bits: 1
    data_bits: 8
    rx_buffer_size: 1024

dyson_tp07:
  - id: my_dyson_tp07
    uart_id: my_uart

sensor:
  - platform: dyson_tp07
    temperature_1:
      id: my_dyson_tp07_temperature_1
      name: Dyson TP07 Temperature 1
    temperature_2:
      id: my_dyson_tp07_temperature_2
      name: Dyson TP07 Temperature 2
    temperature_3:
      id: my_dyson_tp07_temperature_3
      name: Dyson TP07 Temperature 3
    humidity:
      id: my_dyson_tp07_humidity
      name: Dyson TP07 Humidity
    flow_1:
      id: my_dyson_tp07_flow_1
      name: Dyson TP07 Flow 1
    flow_2:
      id: my_dyson_tp07_flow_2
      name: Dyson TP07 Flow 2
    flow_3:
      id: my_dyson_tp07_flow_3
      name: Dyson TP07 Flow 3
    flow_4:
      id: my_dyson_tp07_flow_4
      name: Dyson TP07 Flow 4
    speed:
      id: my_dyson_tp07_speed
      name: Dyson TP07 Speed
    uptime:
      id: my_dyson_tp07_uptime
      name: Dyson TP07 Uptime
    pm_2_5:
      id: my_dyson_tp07_pm25
      name: Dyson TP07 PM2.5
    pm_10_0:
      id: my_dyson_tp07_pm10
      name: Dyson TP07 PM10

binary_sensor:
  - platform: dyson_tp07
    is_on:
      id: my_dyson_tp07_is_on
      name: Dyson TP07 On

# Optional supporting configuration...

remote_transmitter:
  - pin: GPIO13
    carrier_duty_percent: 50%

button:
  - platform: template
    name: "Dyson TP07 Power"
    id: my_dyson_tp07_power
    on_press:
      then:
        - remote_transmitter.transmit_pronto:
            data: '0000 006D 0017 0000 0054 001E 001A 001D 001B 001E 001A 001E 001A 001E 001A 001E 001A 0039 001B 001E 001A 001E 001A 003A 001A 001E 001A 001E 001B 001C 001B 001E 001A 001E 001B 001D 001A 001D 001B 0039 001C 0039 001B 0038 001D 0039 001B 0038 001C 0181'
  - platform: template
    name: "Dyson TP07 Fan Higher"
    id: my_dyson_tp07_fan_higher
    on_press:
      then:
        - remote_transmitter.transmit_pronto:
            data: |
              0000 006D 0017 0000 0054 001D 001C 001D 001B 001D 001C 001D 001B 001D 001C 001C 001D 0039 001C 001D 001B 001D 001B 0039 001C 001D 001B 0039 001B 001D 001B 0038 001D 001D 001B 0038 001C 0039 001B 001D 001C 001D 001A 001E 001A 001D
              001C 0038 001B 0181
  - platform: template
    name: "Dyson TP07 Fan Lower"
    id: my_dyson_tp07_fan_lower
    on_press:
      then:
        - remote_transmitter.transmit_pronto:
            data: |
              0000 006D 0017 0000 0054 001D 001C 001D 001C 001D 001C 001D 001C 001D 001C 001D 001B 0038 001C 001D 001C 001D 001C 0039 001B 001D 001C 0039 001C 001D 001C 0039 001C 0039 001C 001C 001D 001D 001C 001D 001C 001D 001C 0039 001C 0039
              001C 0039 001C 0181
  - platform: template
    name: "Dyson TP07 Fan Direction"
    id: my_dyson_tp07_fan_direction
    on_press:
      then:
        - remote_transmitter.transmit_pronto:
            data: |
              0000 006D 0017 0000 0055 001D 001C 001D 001C 001C 001C 001D 001C 001C 001C 001C 001C 0038 001C 001C 001E 001C 001D 0038 001C 0038 001C 001D 001D 001C 001D 001C 001C 001C 001D 0038 001D 001C 001D 001C 001D 0038 001D 0038 001D 001C
              001D 001C 001D 0181
  - platform: template
    name: "Dyson TP07 Fan Oscillate"
    id: my_dyson_tp07_fan_oscillate
    on_press:
      then:
        - remote_transmitter.transmit_pronto:
            data: |
              0000 006D 0017 0000 0053 001E 001A 001D 001B 001E 001A 001D 001B 001D 001B 001D 001B 003A 001A 001D 001B 001D 001B 0039 001B 001E 001A 001D 001B 003A 001A 003A 001A 001D 001B 001E 001A 003A 001A 001E 001A 001D 001B 001D 001B 001E
              001A 003A 001A 0181

switch:
  - platform: template
    name: "Dyson TP07 Power"
    id: my_dyson_tp07_power_switch
    lambda: !lambda 'return id(my_dyson_tp07).get_is_on_sensor();'
    device_class: switch
    turn_on_action:
      then:
        - if:
            condition:
               - lambda: !lambda 'return !id(my_dyson_tp07).get_is_on_sensor();'
            then:
              - button.press: my_dyson_tp07_power
            else:
              - logger.log: "Already powered on, not doing anything."
    turn_off_action:
      then:
        - if:
            condition:
               - lambda: !lambda 'return id(my_dyson_tp07).get_is_on_sensor();'
            then:
              - button.press: my_dyson_tp07_power
            else:
              - logger.log: "Already powered off, not doing anything."


interval:
  - interval: 60s
    id: set_fan_state
    then:
      - lambda: |
          ESP_LOGV("DysonInterval", "Ensuring fan state matches actual state...");
          bool actual = id(my_dyson_tp07).get_is_on_sensor();
          bool reported = id(my_dyson_tp07_fan).state;
          if (actual != reported) {
            ESP_LOGD("DysonInterval", "Repoted state does not match, setting fan state to actual state...");
            auto call = id(my_dyson_tp07_fan).toggle();
            call.perform();
          } else {
            ESP_LOGV("DysonInterval", "Actual state matches reported state, doing nothing.");
          }

fan:
  - platform: template
    name: "Dyson TP07 Fan"
    id: "my_dyson_tp07_fan"
    speed_count: 10
    on_turn_on:
      - if:
          condition:
              - lambda: !lambda 'return !id(my_dyson_tp07).get_is_on_sensor();'
          then:
            - button.press: my_dyson_tp07_power
          else:
            - logger.log: "Already powered on, not doing anything."
    on_turn_off:
      - if:
          condition:
              - lambda: !lambda 'return id(my_dyson_tp07).get_is_on_sensor();'
          then:
            - button.press: my_dyson_tp07_power
          else:
            - logger.log: "Already powered off, not doing anything."
    on_speed_set:
      - lambda: !lambda |-
          auto current = id(my_dyson_tp07).get_speed_sensor();
          auto desired = x;
          auto steps = desired - current;
          if (steps > 0) {
              for (int i = 0; i < steps; i++) {
                id(my_dyson_tp07_fan_higher).press();
                delay(500);
              }
          } else if (steps < 0) {
              for (int i = 0; i < abs(steps); i++) {
                id(my_dyson_tp07_fan_lower).press();
                delay(500);
              }
          }
```


## homeassistant_cover

A `cover` imported from Home Assistant, like the built-in `homeassistant` switch, light and number
platforms. Useful for devices with displays where you want to control covers in your Home Assistant.

> [!WARNING]
> 100% slop coded

(but I have been using it for quite a while with no issues)

```yaml
cover:
  - platform: homeassistant_cover
    name: Garage Door
    entity_id: cover.garage_door
```

State (`open`, `closed`, `opening`, `closing`), `current_position`, `current_tilt_position` and
`supported_features` are imported. Commands are sent as `cover.open_cover`, `cover.close_cover`,
`cover.stop_cover`, `cover.toggle`, `cover.set_cover_position` and `cover.set_cover_tilt_position`.

Built against ESPHome 2026.10.

## lcd_pcf8574_dynamic

`lcd_pcf8574` with runtime-redefinable custom characters.

> [!WARNING]
> 100% slop coded

(but I have been using it for quite a while with no issues)

![Large clock interface using block glyphs](./components/lcd_pcf8574_dynamic/custom_characters_blocks.jpg)
![Weather interface with icons](./components/lcd_pcf8574_dynamic/custom_characters_icons.jpeg)

These are both on the same device (along with a dozen other pages, each with unique custom characters), which would be impossible with the limit of 8 static custom characters in the upstream driver.

```yaml
external_components:
  - source: github://aarongorka/esphome-components
    components: [lcd_pcf8574_dynamic]

display:
  - platform: lcd_pcf8574_dynamic
    dimensions: 16x2
    lambda: |-
      id(lcd).set_custom_char(0, {0x04, 0x0e, 0x1f, 0x04, 0x04, 0x04, 0x04, 0x00});
      it.print("\x08");
```

Additionally, redraws write only character cells that differ from the previous frame. allowing **much faster refresh rates**. At 250ms `update_interval` and a fairly complex display lambda, it's still perfectly responsive on an esp32c3, allowing for an interactive UI (which was _not_ the case with the upstream driver).


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

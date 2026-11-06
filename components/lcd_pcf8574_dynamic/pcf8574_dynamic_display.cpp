#include "pcf8574_dynamic_display.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

namespace esphome::lcd_pcf8574_dynamic {

static const char *const TAG = "lcd_pcf8574_dynamic";

static const uint8_t LCD_DISPLAY_BACKLIGHT_ON = 0x08;
static const uint8_t LCD_DISPLAY_BACKLIGHT_OFF = 0x00;

void PCF8574DynamicLCDDisplay::setup() {
  this->backlight_value_ = LCD_DISPLAY_BACKLIGHT_ON;
  if (!this->write_bytes(this->backlight_value_, nullptr, 0)) {
    this->mark_failed();
    return;
  }

  LCDDisplay::setup();
}
void PCF8574DynamicLCDDisplay::dump_config() {
  ESP_LOGCONFIG(TAG,
                "PCF8574 Dynamic LCD Display:\n"
                "  Columns: %u, Rows: %u",
                this->columns_, this->rows_);
  LOG_I2C_DEVICE(this);
  LOG_UPDATE_INTERVAL(this);
  if (this->is_failed()) {
    ESP_LOGE(TAG, ESP_LOG_MSG_COMM_FAIL);
  }
}
void PCF8574DynamicLCDDisplay::write_n_bits(uint8_t value, uint8_t n) {
  if (n == 4) {
    // Ugly fix: in the super setup() with n == 4 value needs to be shifted left
    value <<= 4;
  }
  uint8_t data = value | this->backlight_value_;  // Set backlight state
  this->write_bytes(data, nullptr, 0);
  // Pulse ENABLE
  this->write_bytes(data | 0x04, nullptr, 0);
  delayMicroseconds(1);  // >450ns
  this->write_bytes(data, nullptr, 0);
  delayMicroseconds(100);  // >37us
}
void PCF8574DynamicLCDDisplay::send(uint8_t value, bool rs) {
  this->write_n_bits((value & 0xF0) | rs, 0);
  this->write_n_bits(((value << 4) & 0xF0) | rs, 0);
}
void PCF8574DynamicLCDDisplay::backlight() {
  this->backlight_value_ = LCD_DISPLAY_BACKLIGHT_ON;
  this->write_bytes(this->backlight_value_, nullptr, 0);
}
void PCF8574DynamicLCDDisplay::no_backlight() {
  this->backlight_value_ = LCD_DISPLAY_BACKLIGHT_OFF;
  this->write_bytes(this->backlight_value_, nullptr, 0);
}
void PCF8574DynamicLCDDisplay::set_custom_char(uint8_t location, const std::vector<uint8_t> &data) {
  if (data.size() != 8) {
    ESP_LOGW(TAG, "Custom char needs exactly 8 rows, got %u", (unsigned) data.size());
    return;
  }
  location &= 0x7;
  this->user_defined_chars_[location] = data;
  uint8_t charmap[8];
  std::copy(data.begin(), data.end(), charmap);
  this->loadchar(location, charmap);
}

}  // namespace esphome::lcd_pcf8574_dynamic

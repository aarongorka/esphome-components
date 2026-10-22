#include "homeassistant_cover.h"
#include "esphome/components/api/api_server.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

#include <cmath>

namespace esphome::homeassistant_cover {

static const char *const TAG = "homeassistant.cover";

// Bits of the Home Assistant CoverEntityFeature attribute
static constexpr uint32_t FEATURE_OPEN = 1;
static constexpr uint32_t FEATURE_CLOSE = 2;
static constexpr uint32_t FEATURE_SET_POSITION = 4;
static constexpr uint32_t FEATURE_STOP = 8;
static constexpr uint32_t FEATURE_SET_TILT_POSITION = 64;

void HomeassistantCover::setup() {
  auto *server = api::global_api_server;
  server->subscribe_home_assistant_state(this->entity_id_, nullptr, [this](StringRef state) { this->on_state_(state); });
  server->subscribe_home_assistant_state(this->entity_id_, "supported_features",
                                         [this](StringRef value) { this->on_features_(value); });
  server->subscribe_home_assistant_state(this->entity_id_, "current_position",
                                         [this](StringRef value) { this->on_position_(value, false); });
  server->subscribe_home_assistant_state(this->entity_id_, "current_tilt_position",
                                         [this](StringRef value) { this->on_position_(value, true); });
}

void HomeassistantCover::dump_config() {
  LOG_COVER("", "Homeassistant Cover", this);
  ESP_LOGCONFIG(TAG, "  Entity ID: '%s'", this->entity_id_);
}

float HomeassistantCover::get_setup_priority() const { return setup_priority::AFTER_CONNECTION; }

void HomeassistantCover::on_state_(StringRef state) {
  ESP_LOGD(TAG, "'%s': Got state '%s'", this->entity_id_, state.c_str());
  if (state == "opening") {
    this->current_operation = cover::COVER_OPERATION_OPENING;
  } else if (state == "closing") {
    this->current_operation = cover::COVER_OPERATION_CLOSING;
  } else if (state == "open" || state == "closed") {
    this->current_operation = cover::COVER_OPERATION_IDLE;
    // A cover without a reported position only has these two states
    if (!this->has_position_) {
      this->position = state == "open" ? cover::COVER_OPEN : cover::COVER_CLOSED;
    }
  } else {
    // unavailable, unknown or anything else: keep what was last known
    ESP_LOGW(TAG, "'%s': Can't use state '%s'", this->entity_id_, state.c_str());
    return;
  }
  this->publish_state(false);
}

void HomeassistantCover::on_position_(StringRef value, bool tilt) {
  auto parsed = parse_number<float>(value.c_str());
  if (!parsed.has_value() || *parsed < 0.0f || *parsed > 100.0f) {
    return;  // "None" while the cover is unavailable or has no such attribute
  }
  const float fraction = *parsed / 100.0f;
  ESP_LOGD(TAG, "'%s': Got %s %.0f%%", this->entity_id_, tilt ? "tilt" : "position", *parsed);
  if (tilt) {
    this->tilt = fraction;
  } else {
    this->has_position_ = true;
    this->position = fraction;
  }
  this->publish_state(false);
}

void HomeassistantCover::on_features_(StringRef value) {
  auto parsed = parse_number<uint32_t>(value.c_str());
  if (!parsed.has_value()) {
    return;
  }
  const uint32_t features = *parsed;
  this->traits_.set_supports_position((features & FEATURE_SET_POSITION) != 0);
  this->traits_.set_supports_tilt((features & FEATURE_SET_TILT_POSITION) != 0);
  this->traits_.set_supports_stop((features & FEATURE_STOP) != 0);
  this->traits_.set_supports_toggle((features & FEATURE_OPEN) != 0 && (features & FEATURE_CLOSE) != 0);
  ESP_LOGD(TAG, "'%s': Got supported features %u", this->entity_id_, (unsigned) features);
}

void HomeassistantCover::send_action_(StringRef service, StringRef key, StringRef value) {
  static constexpr auto ENTITY_ID_KEY = StringRef::from_lit("entity_id");

  api::HomeassistantActionRequest resp;
  resp.service = service;

  resp.data.init(key.empty() ? 1 : 2);
  auto &entity_id_kv = resp.data.emplace_back();
  entity_id_kv.key = ENTITY_ID_KEY;
  entity_id_kv.value = StringRef(this->entity_id_);

  if (!key.empty()) {
    auto &extra_kv = resp.data.emplace_back();
    extra_kv.key = key;
    extra_kv.value = value;
  }

  api::global_api_server->send_homeassistant_action(resp);
}

void HomeassistantCover::control(const cover::CoverCall &call) {
  if (!api::global_api_server->is_connected()) {
    ESP_LOGE(TAG, "No clients connected to API server");
    return;
  }

  static constexpr auto STOP = StringRef::from_lit("cover.stop_cover");
  static constexpr auto TOGGLE = StringRef::from_lit("cover.toggle");
  static constexpr auto OPEN = StringRef::from_lit("cover.open_cover");
  static constexpr auto CLOSE = StringRef::from_lit("cover.close_cover");
  static constexpr auto SET_POSITION = StringRef::from_lit("cover.set_cover_position");
  static constexpr auto SET_TILT = StringRef::from_lit("cover.set_cover_tilt_position");
  static constexpr auto POSITION_KEY = StringRef::from_lit("position");
  static constexpr auto TILT_KEY = StringRef::from_lit("tilt_position");

  if (call.get_stop()) {
    this->send_action_(STOP);
  }
  if (call.get_toggle().has_value()) {
    this->send_action_(TOGGLE);
  }
  if (call.get_position().has_value()) {
    const float pos = *call.get_position();
    if (this->traits_.get_supports_position()) {
      // The buffer only has to outlive the synchronous send
      char buf[8];
      buf_append_printf(buf, sizeof(buf), 0, "%d", (int) lroundf(pos * 100.0f));
      this->send_action_(SET_POSITION, POSITION_KEY, StringRef(buf));
    } else {
      this->send_action_(pos == cover::COVER_OPEN ? OPEN : CLOSE);
    }
  }
  if (call.get_tilt().has_value()) {
    char buf[8];
    buf_append_printf(buf, sizeof(buf), 0, "%d", (int) lroundf(*call.get_tilt() * 100.0f));
    this->send_action_(SET_TILT, TILT_KEY, StringRef(buf));
  }
}

}  // namespace esphome::homeassistant_cover

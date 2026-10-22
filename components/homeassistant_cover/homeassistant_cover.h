#pragma once

#include "esphome/components/cover/cover.h"
#include "esphome/core/component.h"
#include "esphome/core/string_ref.h"

namespace esphome::homeassistant_cover {

/// A cover in Home Assistant: its state and position are imported over the native API,
/// and commands are sent back as cover.* actions.
class HomeassistantCover : public cover::Cover, public Component {
 public:
  void set_entity_id(const char *entity_id) { this->entity_id_ = entity_id; }
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;

  cover::CoverTraits get_traits() override { return this->traits_; }

 protected:
  void control(const cover::CoverCall &call) override;
  void send_action_(StringRef service, StringRef key = StringRef(), StringRef value = StringRef());
  void on_state_(StringRef state);
  void on_position_(StringRef value, bool tilt);
  void on_features_(StringRef value);

  const char *entity_id_{nullptr};
  cover::CoverTraits traits_{};
  bool has_position_{false};
};

}  // namespace esphome::homeassistant_cover

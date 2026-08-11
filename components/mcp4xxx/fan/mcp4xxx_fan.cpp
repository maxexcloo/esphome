#include "mcp4xxx_fan.h"
#include "esphome/core/log.h"

namespace esphome {
namespace mcp4xxx {

static const char *const TAG = "mcp4xxx.fan";

void MCP4XXXFan::setup() {
  ESP_LOGCONFIG(TAG, "Setting up MCP4XXX Fan...");

  this->traits_.set_supported_speed_count(this->speed_count_);
  this->traits_.set_speed(true);

  auto restore = this->restore_state_();
  if (restore.has_value()) {
    this->state = restore->state;
    this->speed = restore->speed;
  }

  if (!this->write_state_(this->state, this->speed)) {
    this->mark_failed();
    return;
  }
  this->publish_state();
}

void MCP4XXXFan::dump_config() {
  ESP_LOGCONFIG(TAG, "MCP4XXX Fan:");
  ESP_LOGCONFIG(TAG, "  Parent: %p", this->parent_);
  ESP_LOGCONFIG(TAG, "  Speed Count: %d", this->speed_count_);
  ESP_LOGCONFIG(TAG, "  Uses TCON register for on/off control");
  if (this->is_failed()) {
    ESP_LOGE(TAG, "MCP4XXX fan interface is unavailable");
  }
}

void MCP4XXXFan::control(const fan::FanCall &call) {
  const bool target_state = call.get_state().value_or(this->state);
  int target_speed = call.get_speed().value_or(this->speed);
  if (target_state && target_speed < 1) {
    target_speed = this->speed_count_;
  }

  if (!this->write_state_(target_state, target_speed)) {
    return;
  }

  this->state = target_state;
  this->speed = target_speed;
  this->publish_state();
}

bool MCP4XXXFan::write_state_(bool state, int speed) {
  if (this->parent_ == nullptr) {
    ESP_LOGE(TAG, "MCP4XXX parent is not configured");
    return false;
  }

  if (!state) {
    return this->parent_->disable_terminals();
  }

  const uint8_t wiper_value = this->speed_level_to_wiper_value(speed);
  if (!this->parent_->write_wiper_value(wiper_value)) {
    ESP_LOGE(TAG, "Failed to set wiper value to %d", wiper_value);
    return false;
  }
  if (!this->parent_->enable_terminals()) {
    ESP_LOGE(TAG, "Failed to enable terminals");
    return false;
  }

  return true;
}

uint8_t MCP4XXXFan::speed_level_to_wiper_value(int speed_level) {
  if (speed_level <= 0) {
    return 0;  // Minimum speed
  }
  if (speed_level >= this->speed_count_) {
    return MCP4XXX_MAX_VALUE;  // Maximum speed
  }

  // Map speed level (1 to speed_count_) to wiper value (1 to 128)
  // We avoid 0 wiper value when speed > 0 to ensure minimum fan speed
  uint8_t wiper_value = static_cast<uint8_t>((speed_level * MCP4XXX_MAX_VALUE) / this->speed_count_);

  // Ensure we have at least some minimum speed when fan is on
  if (wiper_value == 0 && speed_level > 0) {
    wiper_value = 1;
  }

  return wiper_value;
}

}  // namespace mcp4xxx
}  // namespace esphome

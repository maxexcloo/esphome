#include "mcp4xxx_fan.h"
#include "esphome/core/log.h"

namespace esphome {
namespace mcp4xxx {

static const char *const TAG = "mcp4xxx.fan";

void MCP4XXXFan::setup() {
  ESP_LOGCONFIG(TAG, "Setting up MCP4XXX Fan...");

  // Configure fan traits
  this->traits_.set_supported_speed_count(this->speed_count_);
  this->traits_.set_speed(true);

  // Set initial wiper value to minimum and disable terminals (fan off) using parent component
  if (this->parent_ != nullptr) {
    if (!this->parent_->write_wiper_value(0)) {
      ESP_LOGE(TAG, "Failed to initialize wiper position");
      this->mark_failed();
      return;
    }

    // Start with fan off by disconnecting terminals
    if (!this->parent_->disable_terminals()) {
      ESP_LOGE(TAG, "Failed to disable terminals");
      this->mark_failed();
      return;
    }
  }

  this->current_wiper_value_ = 0;
  this->state = false;  // Fan starts off
}

void MCP4XXXFan::dump_config() {
  ESP_LOGCONFIG(TAG, "MCP4XXX Fan:");
  ESP_LOGCONFIG(TAG, "  Parent: %p", this->parent_);
  ESP_LOGCONFIG(TAG, "  Speed Count: %d", this->speed_count_);
  ESP_LOGCONFIG(TAG, "  Uses TCON register for on/off control");
  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication with MCP4XXX failed!");
  }
}

void MCP4XXXFan::control(const fan::FanCall &call) {
  if (call.get_state().has_value()) {
    bool state = *call.get_state();
    ESP_LOGD(TAG, "Setting fan state to %s", state ? "ON" : "OFF");

    // Use TCON register to control terminal connections for on/off
    if (this->parent_ != nullptr) {
      if (state) {
        // Fan on: enable all terminals
        if (!this->parent_->enable_terminals()) {
          ESP_LOGE(TAG, "Failed to enable terminals");
        }
      } else {
        // Fan off: disable all terminals
        if (!this->parent_->disable_terminals()) {
          ESP_LOGE(TAG, "Failed to disable terminals");
        }
      }
    }

    this->state = state;
  }

  if (call.get_speed().has_value()) {
    int speed_level = *call.get_speed();
    ESP_LOGD(TAG, "Setting fan speed to level %d", speed_level);

    uint8_t wiper_value = this->speed_level_to_wiper_value(speed_level);

    if (this->parent_ != nullptr && this->parent_->write_wiper_value(wiper_value)) {
      this->current_wiper_value_ = wiper_value;
      this->speed = speed_level;
      ESP_LOGD(TAG, "Set wiper value to %d for speed level %d", wiper_value, speed_level);
    } else {
      ESP_LOGE(TAG, "Failed to set wiper value to %d", wiper_value);
    }
  }

  this->publish_state();
}

void MCP4XXXFan::write_state_() {
  // This method is called internally when we need to update the physical state
  // Most of the work is done in control() method
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

#pragma once

#include "esphome/components/fan/fan.h"
#include "esphome/core/component.h"
#include "../mcp4xxx.h"

namespace esphome {
namespace mcp4xxx {

class MCP4XXXFan : public fan::Fan, public Component {
 public:
  MCP4XXXFan(int speed_count) : speed_count_(speed_count) {}

  void setup() override;
  void dump_config() override;
  void set_parent(MCP4XXX *parent) { this->parent_ = parent; }

  fan::FanTraits get_traits() override { return this->traits_; }

 protected:
  void control(const fan::FanCall &call) override;
  bool write_state_(bool state, int speed);

  uint8_t speed_level_to_wiper_value(int speed_level);

  MCP4XXX *parent_{nullptr};
  int speed_count_;
  fan::FanTraits traits_;
};

}  // namespace mcp4xxx
}  // namespace esphome

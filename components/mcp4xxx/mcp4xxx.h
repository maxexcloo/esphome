#pragma once

#include "esphome/components/output/float_output.h"
#include "esphome/components/spi/spi.h"
#include "esphome/core/component.h"

namespace esphome {
namespace mcp4xxx {

class MCP4XXX : public Component,
                public output::FloatOutput,
                public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW,
                                      spi::CLOCK_PHASE_LEADING, spi::DATA_RATE_200KHZ> {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE; }

 protected:
  void write_state(float state) override;

 private:
  void disable_terminals();
  void enable_terminals();
  void write_register(uint8_t address, uint8_t value);
  void write_wiper_value(uint8_t value);
};

}  // namespace mcp4xxx
}  // namespace esphome

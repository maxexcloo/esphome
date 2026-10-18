#include "mcp4xxx.h"
#include <algorithm>
#include "esphome/core/log.h"

namespace esphome {
namespace mcp4xxx {

static const char *const TAG = "mcp4xxx";

// Maximum wiper value (7-bit: 0-128, 129 steps).
static constexpr uint8_t MCP4XXX_MAX_VALUE = 128;
static constexpr uint8_t MCP4XXX_TCON_ADDRESS = 0x04;
// Microchip DS22060B, register 4-2: retain R0HW (bit 3) when disconnecting
// terminals; clearing it forces the wiper onto terminal B.
static constexpr uint8_t MCP4XXX_TERMINALS_CONNECTED = 0xFF;
static constexpr uint8_t MCP4XXX_TERMINALS_DISCONNECTED = 0xF8;
static constexpr uint8_t MCP4XXX_WIPER0_ADDRESS = 0x00;

void MCP4XXX::setup() {
  ESP_LOGCONFIG(TAG, "Setting up MCP4XXX...");

  this->spi_setup();
  if (!this->spi_is_ready()) {
    ESP_LOGE(TAG, "SPI interface is unavailable");
    this->mark_failed();
    return;
  }

  this->write_wiper_value(0);
  this->disable_terminals();
}

void MCP4XXX::dump_config() {
  ESP_LOGCONFIG(TAG, "MCP4XXX Digital Potentiometer:");
  LOG_PIN("  CS Pin: ", this->cs_);
  if (this->is_failed()) {
    ESP_LOGE(TAG, "MCP4XXX SPI interface is unavailable");
  }
}

void MCP4XXX::write_state(float state) {
  if (this->is_failed()) {
    return;
  }
  if (state <= 0.0f) {
    this->disable_terminals();
    return;
  }

  // Keep at least one wiper step while on; update it before connecting terminals.
  const uint8_t wiper_value = std::max<uint8_t>(1, static_cast<uint8_t>(state * MCP4XXX_MAX_VALUE));
  this->write_wiper_value(wiper_value);
  this->enable_terminals();
}

void MCP4XXX::disable_terminals() { this->write_register(MCP4XXX_TCON_ADDRESS, MCP4XXX_TERMINALS_DISCONNECTED); }

void MCP4XXX::enable_terminals() { this->write_register(MCP4XXX_TCON_ADDRESS, MCP4XXX_TERMINALS_CONNECTED); }

void MCP4XXX::write_register(uint8_t address, uint8_t value) {
  this->enable();
  // AD3..AD0 occupy bits 7..4; write-command and upper data bits are zero.
  this->write_byte(address << 4);
  this->write_byte(value);
  this->disable();

  ESP_LOGVV(TAG, "Wrote register: address=0x%02X, data=0x%02X", address, value);
}

void MCP4XXX::write_wiper_value(uint8_t value) { this->write_register(MCP4XXX_WIPER0_ADDRESS, value); }

}  // namespace mcp4xxx
}  // namespace esphome

#pragma once

#include <cmath>
#include <cstring>

#include "esphome/components/i2c/i2c.h"
#include "esphome/core/log.h"

namespace mini_scale {

static constexpr char TAG[] = "mini_scale";
static constexpr uint8_t CALIBRATION_FACTOR_REGISTER = 0x40;
static constexpr uint8_t TARE_REGISTER = 0x50;
static constexpr uint8_t WEIGHT_REGISTER = 0x10;

inline float read_weight(esphome::i2c::I2CDevice *device) {
  uint8_t data[sizeof(float)];
  if (device->read_register(WEIGHT_REGISTER, data, sizeof(data)) !=
      esphome::i2c::ERROR_OK) {
    return NAN;
  }

  float weight;
  std::memcpy(&weight, data, sizeof(weight));
  return weight;
}

inline bool tare(esphome::i2c::I2CDevice *device, const char *name) {
  const uint8_t command = 1;
  if (device->write_register(TARE_REGISTER, &command, sizeof(command)) !=
      esphome::i2c::ERROR_OK) {
    ESP_LOGE(TAG, "%s tare failed", name);
    return false;
  }

  ESP_LOGI(TAG, "%s tared", name);
  return true;
}

inline bool calibrate(esphome::i2c::I2CDevice *device, const char *name,
                      float reference_weight) {
  if (!std::isfinite(reference_weight) || reference_weight <= 0.0f) {
    ESP_LOGE(TAG, "%s calibration weight is invalid", name);
    return false;
  }

  const float measured_weight = read_weight(device);
  if (!std::isfinite(measured_weight)) {
    ESP_LOGE(TAG, "%s weight read failed during calibration", name);
    return false;
  }

  if (std::fabs(measured_weight) < 0.05f) {
    ESP_LOGE(TAG, "%s calibration requires a known weight on the scale", name);
    return false;
  }

  uint8_t data[sizeof(float)];
  if (device->read_register(CALIBRATION_FACTOR_REGISTER, data, sizeof(data)) !=
      esphome::i2c::ERROR_OK) {
    ESP_LOGE(TAG, "%s calibration factor read failed", name);
    return false;
  }

  float current_factor;
  std::memcpy(&current_factor, data, sizeof(current_factor));
  if (!std::isfinite(current_factor) || std::fabs(current_factor) < 0.05f) {
    ESP_LOGE(TAG, "%s current calibration factor is invalid", name);
    return false;
  }

  const float calibrated_factor =
      current_factor * measured_weight / reference_weight;
  std::memcpy(data, &calibrated_factor, sizeof(calibrated_factor));
  if (device->write_register(CALIBRATION_FACTOR_REGISTER, data, sizeof(data)) !=
      esphome::i2c::ERROR_OK) {
    ESP_LOGE(TAG, "%s calibration factor write failed", name);
    return false;
  }

  ESP_LOGI(TAG, "%s calibrated with %.1f g (factor %.3f)", name,
           reference_weight, calibrated_factor);
  return true;
}

}  // namespace mini_scale

#!/usr/bin/env bash
set -euo pipefail

config_log=$(mktemp)
trap 'rm -f "$config_log"' EXIT
if ! esphome config ./*.yaml >"$config_log"; then
  cat "$config_log"
  exit 1
fi

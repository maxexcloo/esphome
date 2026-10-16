#!/usr/bin/env bash
set -euo pipefail

config_log=$(mktemp)
trap 'rm -f "$config_log"' EXIT
for config_file in *.yaml; do
  if [ "$config_file" = "secrets.yaml" ]; then
    continue
  fi
  if ! esphome config "$config_file" >"$config_log"; then
    cat "$config_log"
    exit 1
  fi
done

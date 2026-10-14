#!/usr/bin/env bash
set -euo pipefail

updatecli manifest validate --config .updatecli.d --disable-templating --strict
ruff check --extend-select I components
ruff format --check components
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

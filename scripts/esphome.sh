#!/bin/sh
# Run ESPHome with secrets.yaml written from fnox for this command only; an existing file (as in CI) is used as is.
set -eu
cd "$(dirname "$0")/.."
if [ ! -e secrets.yaml ]; then
  trap 'rm -f secrets.yaml' EXIT
  trap 'exit 130' INT TERM
  (umask 077 && fnox export --format json | jq .secrets >secrets.yaml)
fi
esphome "$@"

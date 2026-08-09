# ESPHome

Device configurations for the homelab ESPHome devices.

## Layout

- `components/` — custom ESPHome components.
- `packages/` — shared configuration packages.
- `*.yaml` — per-device configurations.

## Secrets

`secrets.yaml` requires these keys:

- `api_encryption_key`
- `ota_password`
- `wifi_password`
- `wifi_ssid`

## Conventions

See `AGENTS.md`.

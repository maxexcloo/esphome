# ESPHome

Device configurations for the homelab ESPHome devices.

## Layout

- `packages/` — shared configuration packages.
- `components/` — custom ESPHome components.
- `*.yaml` — per-device configurations.

## Secrets

`secrets.yaml` requires these keys:

- `wifi_ssid`
- `wifi_password`
- `api_encryption_key`
- `ota_password`

## Conventions

See `AGENTS.md`.

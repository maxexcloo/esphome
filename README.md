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

## Development

Install the pinned tools and run all checks with Mise:

```shell
mise install
mise run check
```

Format Python components with `mise run fmt`.

## Licence

AGPL-3.0 - see [LICENSE](LICENSE).

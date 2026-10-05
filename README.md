# ESPHome

Device configurations for the homelab ESPHome devices.

## Conventions

See `AGENTS.md`.

## Dependencies

Remote ESPHome packages and components are pinned to commit hashes. The custom
manager in `renovate.json` matches `github://` references in root device YAML files
and proposes new hashes from each repository's `main` branch. Enable the Renovate
GitHub app for this repository to receive update PRs; updates are not automerged.

## Development

Create `secrets.yaml` with the keys listed below, then install the pinned tools
and run all checks with Mise:

```shell
mise install
mise run check
```

Format Python components with `mise run fmt`.

Compile affected devices after changing hardware, frameworks, external components,
or lambdas:

```shell
mise exec -- esphome compile bedroom-fan.yaml
```

CI discovers root `*.yaml` files, excluding `secrets.yaml`, and validates and
compiles every device. These checks do not upload firmware or test physical devices.

## Layout

- `components/` — custom ESPHome components.
- `packages/` — shared configuration packages.
- `*.yaml` — per-device configurations.

## Licence

AGPL-3.0 - see [LICENSE](LICENSE).

## OTA

Native OTA updates use the API encryption key. Biltong Box and Hallway Front Door
Intercom retain password OTA until their firmware reaches ESPHome 2026.9 or later;
then remove their local `ota` overrides to inherit encryption from `base`.
Apollo and desk packages also retain upstream browser OTA, which is separate from
native OTA encryption.

## Secrets

`secrets.yaml` requires these keys:

- `api_encryption_key`
- `ota_password` — Biltong Box and Hallway Front Door Intercom only
- `wifi_password`
- `wifi_ssid`

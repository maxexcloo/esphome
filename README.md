# ESPHome

Device configurations for the homelab ESPHome devices.

## Conventions

See `AGENTS.md`.

## Dependencies

Remote ESPHome packages and components are pinned to commit hashes. Local
Updatecli policies track their upstream branches and keep the ESPHome interpreter
on Python 3.14. Review proposed changes before applying them.

## Development

Install the [shared Mise configuration](https://github.com/maxexcloo/dotfiles#shared-tools--tasks)
before running local Mise tasks.

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

Pull requests validate root `*.yaml` files, excluding `secrets.yaml`. Compile
changed devices locally before uploading firmware; configuration checks do not test physical devices.

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

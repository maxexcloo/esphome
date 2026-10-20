# ESPHome

Configurations for the ESPHome devices in my homelab.

## Conventions

See `AGENTS.md`.

## Development

Install the [shared Mise configuration](https://github.com/maxexcloo/dotfiles#shared-tools--tasks)
before running local Mise tasks.

Create `secrets.yaml` with the keys listed below, then install the pinned tools
and run all checks with Mise:

```shell
mise install
mise run check
```

Format files and Python components with `mise run fmt`.

Compile affected devices after changing hardware, frameworks, external components,
or lambdas:

```shell
mise exec -- esphome compile bedroom-fan.yaml
```

Pull requests validate the root `*.yaml` files, except `secrets.yaml`, and
compile Bedroom Fan. The checks don't test physical devices, so compile changed
devices locally before uploading firmware.

## Layout

- `components/`: custom ESPHome components.
- `packages/`: shared configuration packages.
- `*.yaml`: per-device configurations.

## Licence

AGPL-3.0 - see [LICENSE](LICENSE).

## OTA

Native OTA updates use the API encryption key. Biltong Box and Hallway Front Door
Intercom keep password OTA until their firmware is on ESPHome 2026.9 or later.
After that, remove their local `ota` overrides so they inherit encryption from
`base`. The Apollo and desk configurations turn off upstream browser OTA because
native OTA encryption doesn't cover it.

## Secrets

`secrets.yaml` requires these keys:

- `api_encryption_key`
- `ota_password` (Biltong Box and Hallway Front Door Intercom only)
- `web_server_password`
- `web_server_username`
- `wifi_password`
- `wifi_ssid`

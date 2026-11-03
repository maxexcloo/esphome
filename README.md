# ESPHome

Configurations for the ESPHome devices in my homelab.

## Conventions

See `AGENTS.md`.

## Development

Install the [shared Mise configuration](https://github.com/maxexcloo/dotfiles#shared-tools--tasks)
before running local Mise tasks.

Install the pinned tools and run all checks with Mise:

```shell
mise install
mise run check
```

Format files and Python components with `mise run fmt`.

Compile affected devices after changing hardware, frameworks, external components,
or lambdas:

```shell
mise run esphome compile bedroom-fan.yaml
```

CI validates every device configuration and compiles Bedroom Fan.

## Layout

- `components/`: custom ESPHome components.
- `packages/`: shared configuration packages.
- `*.yaml`: per-device configurations.

## Secrets

`fnox.toml` maps each `!secret` key to a field of the `ESPHome` item in the
Automation 1Password vault, read through the global fnox `automation` provider.
The `esphome` Mise task writes them to `secrets.yaml` for one ESPHome command and
deletes it afterwards, so run ESPHome through it. The Home Assistant ESPHome
add-on keeps its own `secrets.yaml`, so configurations use `!secret`.

## Licence

AGPL-3.0 - see [LICENSE](LICENSE).

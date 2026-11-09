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

## Secrets

Run ESPHome through `mise run esphome` to load secrets from the `ESPHome` item
in the Automation 1Password vault through the shared fnox `automation` provider.
The Home Assistant ESPHome add-on keeps its own `secrets.yaml`.

## Licence

AGPL-3.0 - see [LICENSE](LICENSE).

# ESPHome

Device configurations for the homelab ESPHome devices.

## Conventions

See `AGENTS.md`.

## Dependencies

Remote ESPHome packages and components are pinned to commit hashes. Local
Updatecli policies track their upstream branches and keep the ESPHome interpreter
on Python 3.14. Review proposed changes before applying them.

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

## Dependency Updates

Mise installs the pinned Updatecli CLI. Run `mise run dependencies:check` locally
to preview updates from `.updatecli.d/`. GitHub authentication uses the existing
`gh` login; credentials stay in the command process.

Review compatibility and major upgrades separately, then apply a selected group:

```sh
mise run dependencies:update --labels group:tools
```

Use the groups declared in the policy, review the Git diff and run the project
checks before committing or deploying. Updatecli changes local files; it does
not create issues, pull requests, commits or deployments. Hosted Renovate is disabled.

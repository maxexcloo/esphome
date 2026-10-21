# ESPHome Repository Conventions

## Device YAML Structure

- Keep device-specific YAML small; reuse packages from `packages/`.
- Put `substitutions` first and `packages` second.
- Put `platform` first in platform entries.
- Preserve hardware pin order, including camera data pins `D0` through `D7`.
- Separate top-level blocks with one blank line.
- Do not add blank lines between entries in the same list.

## Configuration

- Omit values that merely restate ESPHome defaults.
- Follow the naming pattern:
  - filename and `name`: lowercase kebab-case
  - `name_friendly`: title case
- Apollo MSR-2 files keep the factory MAC-suffixed `name` so hostnames and Home
  Assistant devices stay stable; `name_friendly` carries the room.
- Use shared `base`, `diagnostics`, and `web-server` packages when applicable.
- Keep custom ESPHome components in `components/`. Load shared C++ helpers as
  headers through `esphome: includes:`, as `biltong-box.yaml` does with
  `components/mini_scale.h`.
- Document non-obvious hardware requirements, such as pin conflicts, bus
  addresses, or DIP-switch settings, next to the relevant component.

## Security

- Every `web_server` requires authentication; include the shared `web-server`
  package, which sets it, including on top of upstream packages.
- Set `web_server: ota: false` when an upstream package adds browser OTA.

## Validation

- Run `mise run check`, then `mise exec -- esphome compile <device>.yaml` for every
  device affected by the change.
- Check OTA and `web_server` exposure when adding or changing packages.
- Check Home Assistant impact before renaming devices or entities; names derive
  their entity IDs.
- Treat expected board pin warnings separately from configuration or compile
  failures.
- Valid configuration and successful compiles do not prove device behaviour.

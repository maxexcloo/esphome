# ESPHome Repository Conventions

## Device YAML Structure

- Keep device-specific YAML small; reuse packages from `packages/`.
- Put `substitutions` first and `packages` second.
- Sort all remaining top-level component blocks alphabetically.
- Separate top-level blocks with one blank line.
- Do not add blank lines between entries in the same list.

## Key Ordering

- Put `platform` first in platform entries.
- Sort unordered component instances by name, ID or platform as appropriate.
- Preserve hardware pin order, including camera data pins `D0` through `D7`.

## Configuration

- Omit values that merely restate ESPHome defaults.
- Follow the naming pattern:
  - filename and `name`: lowercase kebab-case
  - `name_friendly`: title case
- Use shared `base`, `diagnostics`, and `web-server` packages when applicable.
- Document non-obvious hardware requirements, such as pin conflicts, bus
  addresses, or DIP-switch settings, next to the relevant component.

## Validation

- Run `esphome config <device>.yaml`.
- Run a full `esphome compile <device>.yaml` when changing hardware,
  frameworks, external components, or lambdas.
- Treat expected board pin warnings separately from configuration or compile
  failures.

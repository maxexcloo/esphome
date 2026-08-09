# ESPHome Repository Conventions

## Device YAML structure

- Keep device-specific YAML small; reuse packages from `packages/`.
- Put `substitutions` first and `packages` second.
- Sort all remaining top-level component blocks alphabetically.
- Separate top-level blocks with one blank line.
- Do not add blank lines between entries in the same list.

## Key ordering

- Put `platform` first in platform entries.
- After `platform`, sort single-line keys alphabetically.
- Put multiline keys after all single-line keys, also alphabetically.
- Apply these rules recursively to nested mappings.
- Sort substitutions, packages, component instances, sensors, and similar
  unordered entries by name, ID, or platform as appropriate.

## Meaningful order

- Preserve list order when it affects hardware or behaviour.
- Examples include camera data pins (`D0` through `D7`), automation actions,
  calibration points, and priority-based rules.
- Add a short comment when a required order may look unsorted.

## Configuration

- Omit values that merely restate ESPHome defaults.
- Sort unordered peer headings, lists, and table rows alphabetically. Preserve
  narrative, procedural, dependency, interface, priority, and chronological order.
- Follow the naming pattern:
  - filename and `name`: lowercase kebab-case
  - `name_friendly`: title case
- Use shared `base`, `diagnostics`, and `web_server` packages when applicable.
- Document non-obvious hardware requirements, such as pin conflicts, bus
  addresses, or DIP-switch settings, next to the relevant component.
- Preserve `LICENSE` and its legal text; never relicense without explicit approval.
- Use Australian English throughout authored prose and every project-owned name,
  including identifiers, configuration keys, environment variables, paths, CLI
  commands, and options. Update every producer and consumer together; preserve only
  externally defined names and terminology.

## Validation

- Run `esphome config <device>.yaml`.
- Run a full `esphome compile <device>.yaml` when changing hardware,
  frameworks, external components, or lambdas.
- Treat expected board pin warnings separately from configuration or compile
  failures.

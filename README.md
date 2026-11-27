<p align="center">
    <img src=".github/logo.png" alt="Fossil Test Logo" width="500"/>
</p>

# ***Fossil Test by Fossil Logic***

**Fossil Test** is a unit testing framework from **Fossil Logic** designed for C and C++ projects that require precision, clarity, and control. It focuses on producing reliable, easy-to-understand test results while supporting detailed verification of logic, memory behavior, and system correctness. The framework is well-suited for low-level components, performance-critical code, and environments where predictable behavior matters.

With Fossil Test, developers can build clean, structured tests that fit naturally into existing workflows. Whether you're validating core algorithms, exercising system interfaces, or ensuring API stability, Fossil Test provides a straightforward and dependable approach to testing.

---

## Key Features

| Feature | Description |
|---------|-------------|
| **Command-Line Interface (CLI)** | Run suites, filter/sort/shuffle cases, show results, and export reports for local use and CI/CD. |
| **Traceable Test Metadata** | Test cases carry structured metadata to support clear, reproducible results. |
| **Multiple Testing Styles** | Fits TDD, BDD-style given/when/then helpers, and structured suite/case organization. |
| **Mocking (Fossil Mock)** | Record calls, verify arguments and order, and stub behavior for isolated tests. |
| **Benchmarking (Fossil Mark)** | Measure iteration times and basic stats to spot slow paths. |
| **Sanity Kit** | Portable helpers for process, files, env, and related command-oriented checks. |
| **Flexible Output** | Show modes such as `list`, `tree`, `graph`, and `json`, plus color `enable` / `disable` / `auto`. Prefer `json` with `--verbose ci` in CI. |
| **Tag-Based Filtering** | Run or show subsets of tests by name, suite, tag, or result. |
| **Timeouts** | Configurable per-run timeout (default 60s) with platform-specific enforcement. |
| **Mutation Testing (Fossil Mutate)** | In-memory mutation cases, operators, discovery helpers, and result recording (execution remains the test runner’s job). |
| **Objective-C & Objective-C++ (macOS)** | Compatible with Objective-C / Objective-C++ test sources on macOS. |

---

## Command-Line

The Fossil Test CLI is invoked as `maip` (options and commands as below). Use `help`, `--help`, `help <command>`, or `<command> --help` for details.

### Global options

| Option | Description |
|--------|-------------|
| `--version`, `-v` | Show version information. |
| `--help`, `-h` | Show main usage help. |

### Commands

| Command | Description | Flags / options |
|---------|-------------|-----------------|
| `help` | Global or command-specific help. | `help <command>`, `<command> --help` |
| `run` | Execute tests. | `--fail-fast`, `--only <test>`, `--skip <test>`, `--repeat <count>` |
| `filter` | Filter which tests are considered. | `--test-name <name>`, `--suite-name <name>`, `--tag <tag>`, `--help`, `--options` |
| `sort` | Sort tests. | `--by <criteria>`, `--order <asc\desc>`, `--help`, `--options` |
| `shuffle` | Shuffle tests. | `--seed <seed>`, `--count <count>`, `--by <criteria>`, `--help`, `--options` |
| `show` | Show test cases / results. | `--test-name <name>`, `--suite-name <name>`, `--tag <tag>`, `--result <pass\fail\timeout\skipped\unexpected>`, `--verbose <plain\ci>`, `--mode <list\tree\graph\json>` |
| `color` | Color output. | `enable`, `disable`, `auto` |
| `info` | Environment / runner diagnostics. | `--os`, `--arch`, `--memory`, `--endian`, `--self` |
| `report` | Export results for CI or files. | `--format <json\fson\yaml\csv>`, `--destination <file\stdout>` |
| `timeout=<sec>` | Command/test timeout in seconds (default: 60). | — |

> **Notes:** There is no separate `--host` or theme command. Host/OS details are available via `info`. On Windows, a timed-out test may stop the remainder of the run so the process is not left in an inconsistent state after forced thread termination.

---

## ***Prerequisites***

- **Meson** `1.10.0` or newer — see the [Meson getting started guide](https://mesonbuild.com/Getting-meson.html).

---

### Adding the dependency

#### Meson git wrap

Place a wrap file under `subprojects` (for example `fossil-test.wrap`):

```ini
[wrap-git]
url = https://github.com/fossillogic/fossil-test.git
revision = v2.0.7

[provide]
dependency_names = fossil-test
```

Then use `dependency('fossil-test')` in your `meson.build`. Prefer the latest release from [Fossil Test Releases](https://github.com/fossillogic/fossil-test/releases).

## Configure build options

```sh
meson setup builddir -Dwith_test=enabled
```

#### Tests double as samples

`fossil-test` tests serve two roles:

- **Unit tests** — validate the framework.
- **Usage samples** — show how to write suites, cases, assumes, mocks, and related APIs.

```bash
meson test -C builddir -v
```

For machine-readable CI output, prefer show/report settings such as `--mode json` and `--verbose ci` where applicable.

---

## ***Contributing and Support***

Contributions, questions, and issue reports are welcome on the [Fossil Test repository](https://github.com/fossillogic/fossil-test). Open an issue for bugs or feature requests, or a pull request for fixes and improvements.

---

## ***Conclusion***

Fossil Test is a portable, zero-external-dependency unit testing framework for C and C++, with optional support for mocking (**Fossil Mock**), benchmarking (**Fossil Mark**), mutation bookkeeping (**Fossil Mutate**), and command-oriented helpers (**Sanity**). It is intended for projects that need clear results, predictable behavior, and a practical CLI for local and CI workflows.

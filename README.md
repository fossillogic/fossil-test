# ***Pizza Test by Fossil Logic***

**Pizza Test** is a smart unit testing framework developed by **Fossil Logic** for C and C++ projects. It offers advanced features designed for systems that demand high traceability, behavioral insight, and truth validation. Pizza Test is particularly well-suited for testing components where deterministic logic, memory integrity, and reasoning transparency are critical.

---

## Key Features

| Feature                            | Description                                                                                                                             |
|------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------|
| **Command-Line Interface (CLI)**   | A robust CLI for executing tests, managing test suites, and generating reports, enabling seamless automation and CI/CD workflows.      |
| **Traceable Test Metadata**        | Each test case carries timestamped, hashed metadata for traceability and reproducibility, ensuring full accountability of test results.|
| **Support for Multiple Testing Styles** | Compatible with Behavior-Driven Development (BDD), Domain-Driven Design (DDD), and Test-Driven Development (TDD) methodologies.   |
| **Mocking Capabilities**           | Advanced mocking tools to simulate complex dependencies and edge conditions, enabling isolated and deterministic testing.              |
| **Benchmarking Tools**             | Integrated benchmarking features to measure runtime performance, identify slow paths, and guide optimization.                         |
| **Sanity Kit for Command Tests**   | A specialized module for validating command-line tools, ensuring consistent behavior across platforms and shell environments.         |
| **Customizable Output Themes**     | Multiple output formats and visual themes (e.g., pizza, catch, doctest) to match your preferred style of feedback.                    |
| **Tag-Based Test Filtering**       | Execute subsets of tests based on custom tags for better test suite organization and faster iteration.                                |
| **Detailed Performance Insights**  | In-depth statistics on execution time, memory usage, and test stability to help improve code performance and reliability.              |
| **Objective-C & Objective-C++ Support (macOS)** | Full compatibility with Objective-C and Objective-C++ projects on macOS, allowing testing of Apple-specific frameworks and apps.  |

## Command-Line

The Pizza Test CLI provides an efficient way to run and manage tests directly from the terminal. Here are the available commands and options:

### Commands and Options

| Command          | Description                                                                                   | Notes                                                                                         |
|-----------------|-----------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------|
| `--version`      | Show version information.                                                                    | Immediately prints the version and exits.                                                     |
| `--dry-run`      | Perform a dry run without executing commands.                                                | Sets `G_PIZZA_DRY_RUN=1` to simulate test execution.                                         |
| `--host`         | Show information about the current host.                                                     | Calls `_show_host()` to print system info.                                                    |
| `--help`         | Show this help message.                                                                      | Calls `_show_help()` to display global usage.                                                |
| `run`            | Execute tests with optional parameters.                                                      | Supports `--fail-fast`, `--only <tests>`, `--skip <tests>`, `--repeat <n>`, `--threads <n>`. |
| `filter`         | Filter tests based on criteria.                                                              | Options: `--test-name`, `--suite-name`, `--tag`; supports multiple values and wildcards.     |
| `sort`           | Sort tests by specified criteria.                                                            | Options: `--by <criteria>`, `--order <asc|desc>`; validated against `VALID_CRITERIA`.       |
| `shuffle`        | Shuffle tests with optional parameters.                                                     | Options: `--seed <value>`, `--count <n>`, `--by <criteria>`.                                 |
| `show`           | Show test cases with optional parameters.                                                   | Options: `--test-name`, `--suite-name`, `--tag`, `--result <fail|pass|all>`, `--mode <list|tree|graph>`, `--verbose <plain|ci|doge>`. Default mode is `list` and verbose is `plain`. |
| `color=<mode>`   | Set color mode (`enable`, `disable`, `auto`).                                                | `auto` enables color only if stdout is a terminal.                                           |
| `config=<file>`  | Specify a configuration file.                                                                | Must be `pizza_test.ini`; other names produce an error.                                      |
| `theme=<name>`   | Set the theme for output.                                                                    | Options: `fossil`, `catch`, `doctest`, `cpputest`, `tap`, `gtest`, `unity`.                 |
| `timeout=<sec>`  | Set the timeout for commands (default: 60 seconds).                                          | Sets `G_PIZZA_TIMEOUT` for all command execution.                                           |

> **Note:** In addition to the `--help` option, Pizza Test CLI supports `--help` and subcommand-specific help commands. You can use `<command> --help` (e.g., `run --help`) to display detailed usage information for any command or subcommand. This provides flexible ways to access documentation directly from the terminal.

---

## ***Prerequisites***

To get started, ensure you have the following installed:

- **Meson Build System**: If you don’t have Meson `1.8.0` or newer installed, follow the installation instructions on the official [Meson website](https://mesonbuild.com/Getting-meson.html).

---

### Adding Dependency

#### Adding via Meson Git Wrap

To add a git-wrap, place a `.wrap` file in `subprojects` with the Git repo URL and revision, then use `dependency('fossil-test')` in `meson.build` so Meson can fetch and build it automatically.

#### Integrate the Dependency:

Add the `fossil-test.wrap` file in your `subprojects` directory and include the following content:

```ini
[wrap-git]
url = https://github.com/fossillogic/fossil-test.git
revision = v1.3.1

[provide]
dependency_names = fossil-test
```

**Note**: For the best experience, always use the latest release of Pizza Test. Visit the [Pizza Test Releases](https://github.com/fossillogic/fossil-test/releases) page for the latest versions.

## Configure Build Options

To configure the build system with testing enabled, use the following command:

```sh
meson setup builddir -Dwith_test=enabled
```

#### Tests Double as Samples

The `fossil-test` project is designed so that **test cases serve two purposes**:

- ✅ **Unit Tests** – validate the framework’s correctness.  
- 📖 **Usage Samples** – demonstrate how to write tests with `fossil-test`.  

This approach keeps the codebase compact and avoids redundant “hello world” style examples.  
Instead, the same code that proves correctness also teaches usage.  

This mirrors the **Meson build system** itself, which tests its own functionality by using Meson to build Meson.  
In the same way, `fossil-test` validates itself by demonstrating real-world usage in its own tests.  

```bash
meson test -C builddir -v
```

Running the test suite gives you both verification and practical examples you can learn from.

---

## ***Contributing and Support***

If you would like to contribute, have questions, or need help, feel free

---

## ***Conclusion***

Pizza Test is a powerful and flexible framework for C and C++ developers, designed to support a wide range of testing methodologies such as BDD, DDD, and TDD. With features like mocking, detailed reporting, and performance tracking, Pizza Test empowers developers to create high-quality software and maintainable test suites. Combined with Pizza Mark and Pizza Mock, it provides a complete suite for testing, optimization, and dependency management. Whether you're building small projects or large-scale applications, Pizza Test is an essential tool to ensure the reliability and performance of your code.

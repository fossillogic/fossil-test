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
| `--dry-run`      | Perform a dry run without executing commands.                                                | Sets an internal dry-run flag to simulate test execution.                                     |
| `--host`         | Show information about the current host.                                                     | Prints system information.                                                                   |
| `--help`         | Show this help message.                                                                      | Displays global usage instructions.                                                          |
| `run`            | Execute tests with optional parameters.                                                      | Supports `--fail-fast`, `--only <tests>`, `--skip <tests>`, `--repeat <n>`, `--threads <n>`. |
| `filter`         | Filter tests based on criteria.                                                              | Options: `--test-name`, `--suite-name`, `--tag`; supports multiple values and wildcards.     |
| `sort`           | Sort tests by specified criteria.                                                            | Options: `--by <criteria>`, `--order <asc/desc>`; validated against built-in criteria.      |
| `shuffle`        | Shuffle tests with optional parameters.                                                     | Options: `--seed <value>`, `--count <n>`, `--by <criteria>`.                                 |
| `show`           | Show test cases with optional parameters.                                                   | Options: `--test-name`, `--suite-name`, `--tag`, `--result <fail/pass/all>`, `--mode <list/tree/graph>`, `--verbose <plain/ci/doge>`. Default mode is `list` and verbose is `plain`. |
| `color=<mode>`   | Set color mode.                                                                               | Options: `enable/disable/auto` (`auto` enables color only if stdout is a terminal).         |
| `config=<file>`  | Specify a configuration file.                                                                | Must be named `pizza_test.ini`; other filenames produce an error.                             |
| `theme=<name>`   | Set the theme for output.                                                                    | Options: `fossil/catch/doctest/cpputest/tap/gtest/unity`.                                   |
| `timeout=<sec>`  | Set the timeout for commands.                                                                | Default is 60 seconds; sets an internal timeout for all command execution.                   |
| `report`         | Export test results for CI integration.                                                     | Supported formats: `json/fson/yaml/csv`.                                                    |
| `watch`          | Continuously run tests on file changes.                                                     | Monitors file system changes and reruns tests automatically.                                 |

> **Note:** In addition to the `--help` option, Pizza Test CLI supports `--help` and subcommand-specific help commands. You can use `<command> --help` (e.g., `run --help`) to display detailed usage information for any command or subcommand. This provides flexible ways to access documentation directly from the terminal.

| Section | Key                   | Description                                                      | Notes / Valid Values                                                                 |
|---------|----------------------|------------------------------------------------------------------|-------------------------------------------------------------------------------------|
| general | theme                 | Set the theme for output.                                        | Options: `fossil`, `catch`, `doctest`, `cpputest`, `tap`, `gtest`, `unity`.        |
| test    | run.fail_fast         | Enable or disable fail-fast mode.                                | `0` = disabled, `1` = enabled.                                                     |
| test    | run.only              | Specify which tests to run.                                      | Comma-separated list of test names; wildcards supported.                            |
| test    | run.repeat            | Repeat test execution multiple times.                             | Integer value, e.g., `1` (default).                                               |
| test    | filter.test_name      | Filter tests by name.                                            | Comma-separated list; wildcards supported.                                         |
| test    | filter.suite_name     | Filter tests by suite name.                                      | Comma-separated list; wildcards supported.                                         |
| test    | filter.tag            | Filter tests by tag.                                             | Must match `VALID_TAGS` or contain wildcard `*`.                                   |
| test    | sort.by               | Sort tests by specified criteria.                                | Must match `VALID_CRITERIA`.                                                      |
| test    | sort.order            | Set sort order.                                                  | Options: `asc`, `desc`.                                                           |
| test    | shuffle.seed          | Seed for shuffling tests.                                        | Any string accepted as seed.                                                      |
| test    | shuffle.count         | Number of tests to shuffle.                                      | Integer value.                                                                    |
| test    | shuffle.by            | Criteria to shuffle by.                                          | Must match `VALID_CRITERIA`.                                                      |
| mock    | …                     | Placeholder for future mock-related INI options.                 | Currently unimplemented.                                                          |
| mark    | …                     | Placeholder for future mark-related INI options.                 | Currently unimplemented.                                                          |
| sanity  | …                     | Placeholder for future sanity-related INI options.               | Currently unimplemented.                                                          |

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

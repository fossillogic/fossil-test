# ***Pizza Test by Fossil Logic***

**Pizza Test** is a comprehensive suite for unit testing, mocking, and benchmarking, developed by **Fossil Logic** to boost the reliability, transparency, and performance of **C** and **C++** software. It is now enhanced with **Truthful Intelligence (TI)** metadata and blockchain-inspired audit trails through **Jellyfish AI**, allowing test cases to be cryptographically hashed, signed, traced, and verified over time.

Supporting methodologies like Behavior-Driven Development (BDD), Domain-Driven Design (DDD), and Test-Driven Development (TDD), it caters to a range of workflows with features such as a robust Command-Line Interface (CLI), intelligent mocking tools, integrated benchmarking, and parallel test execution. With additional capabilities like customizable output themes, tag-based filtering, detailed performance insights, and metadata auditing, **Pizza Test**, alongside **Pizza Mock**, **Pizza Mark**, and **Pizza Sanity Kit**, forms a powerful and verifiable toolkit for building high-integrity software.

---

## 🔑 Key Features

| Feature                            | Description                                                                                                                             |
|------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------|
| **Command-Line Interface (CLI)**   | A robust CLI for executing tests, managing test suites, and generating reports, enabling seamless automation and CI/CD workflows.      |
| **Truthful Intelligence Auditing** | Each test case carries timestamped, hashed metadata for traceability and reproducibility via Jellyfish AI's cryptographic core.         |
| **Support for Multiple Testing Styles** | Compatible with Behavior-Driven Development (BDD), Domain-Driven Design (DDD), and Test-Driven Development (TDD) methodologies.   |
| **Mocking Capabilities**           | Advanced mocking tools to simulate complex dependencies and edge conditions, enabling isolated and deterministic testing.              |
| **Benchmarking Tools**             | Integrated benchmarking features to measure runtime performance, identify slow paths, and guide optimization.                         |
| **Sanity Kit for Command Tests**   | A specialized module for validating command-line tools, ensuring consistent behavior across platforms and shell environments.         |
| **Customizable Output Themes**     | Multiple output formats and visual themes (e.g., pizza, catch, doctest) to match your preferred style of feedback.                    |
| **Tag-Based Test Filtering**       | Execute subsets of tests based on custom tags for better test suite organization and faster iteration.                                |
| **Detailed Performance Insights**  | In-depth statistics on execution time, memory usage, and test stability to help improve code performance and reliability.              |

---

Pizza Test is a first-class citizen of the **Truthful Intelligence** ecosystem, using **Jellyfish AI** as its foundation for test integrity, learning from outcomes over time, and enabling tamper-proof validation across distributed development environments.

---

## ***Prerequisites***

To get started with Pizza Test, ensure you have the following installed:

- **Meson Build System**: If you don’t have Meson installed, follow the installation instructions on the official [Meson website](https://mesonbuild.com/Getting-meson.html).

---

### Adding Pizza Test Dependency

#### Adding Pizza Test Dependency With Meson

1. **Install Meson Build System**:
   Install Meson version `1.3` or newer:
   ```sh
   python -m pip install meson           # To install Meson
   python -m pip install --upgrade meson # To upgrade Meson
   ```

2. **Create a `.wrap` File**:
   Add a `fossil-test.wrap` file in your `subprojects` directory with the following content:

   ```ini
   # ======================
   # Git Wrap package definition
   # ======================
   [wrap-git]
   url = https://github.com/fossillogic/fossil-test.git
   revision = v1.2.6

   [provide]
   fossil-test = fossil_test_dep
   ```

3. **Integrate the Dependency**:
   In your `meson.build` file, integrate Fossil Test by adding the following line:
   ```meson
   dep = dependency('fossil-test')
   ```

---

**Note**: For the best experience, always use the latest release of Pizza Test. Visit the [Pizza Test Releases](https://github.com/pizzalogic/pizza-test/releases) page for the latest versions.

## Pizza Test CLI Usage

The Pizza Test CLI provides an efficient way to run and manage tests directly from the terminal. Here are the available commands and options:

### Commands and Options

| Command                          | Description                                                                                   | Notes                                                                                         |
|-----------------------------------|----------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------|
| `--version`                      | Show version information.                                                                    | Useful for verifying the version of the tool in use.                                          |
| `--dry-run`                      | Perform a dry run without executing commands.                                                | Ideal for verifying test selection criteria before actual execution.                          |
| `--host`                         | Show information about the current host.                                                     | Useful for looking up the system you are running tests on.                                    |
| `--help`                         | Show this help message.                                                                      | Provides a quick reference for all available commands.                                        |
| `run`                            | Execute tests with optional parameters.                                                      | Supports additional options like `--fail-fast` and `--repeat`.                                |
| `filter`                         | Filter tests based on criteria.                                                              | Options include filtering by test name, suite name, or tags.                                  |
| `sort`                           | Sort tests by specified criteria.                                                            | Allows sorting in ascending or descending order.                                              |
| `shuffle`                        | Shuffle tests with optional parameters.                                                      | Includes options for specifying a seed or shuffle criteria.                                   |
| `show`                           | Show test cases with optional parameters.                                                    | Useful for listing and inspecting available test cases.                                       |
| `color=<mode>`                   | Set color mode (`enable`, `disable`, `auto`).                                                | Enhances readability in supported terminals.                                                  |
| `config=<file>`                  | Specify a configuration file (must be `pizza_test.ini`).                                     | Allows loading custom settings for test execution.                                            |
| `theme=<name>`                   | Set the theme (`fossil`, `catch`, `doctest`, etc.).                                         | Customizes the appearance of test output.                                                     |
| `timeout=<seconds>`              | Set the timeout for commands (default: 60 seconds).                                          | Ensures commands do not exceed the specified duration, helping to identify long-running tests.|

> **Note:** In addition to the `--help` option, Pizza Test CLI supports `--help` and subcommand-specific help commands. You can use `<command> --help` (e.g., `run --help`) to display detailed usage information for any command or subcommand. This provides flexible ways to access documentation directly from the terminal.

## Configure Build Options

To configure the build system with testing enabled, use the following command:

```sh
meson setup builddir -Dwith_test=enabled
```

---

## ***Contributing and Support***

If you would like to contribute, have questions, or need help, feel free

---

## ***Conclusion***

Pizza Test is a powerful and flexible framework for C and C++ developers, designed to support a wide range of testing methodologies such as BDD, DDD, and TDD. With features like mocking, detailed reporting, and performance tracking, Pizza Test empowers developers to create high-quality software and maintainable test suites. Combined with Pizza Mark and Pizza Mock, it provides a complete suite for testing, optimization, and dependency management. Whether you're building small projects or large-scale applications, Pizza Test is an essential tool to ensure the reliability and performance of your code.

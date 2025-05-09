# ***Fossil Test by Fossil Logic***

**Fossil Test** is a comprehensive suite for unit testing, mocking, and benchmarking, designed by Fossil Logic to enhance the reliability, clarity, and performance of **C**, **C++**, and **Python** projects. Supporting methodologies like Behavior-Driven Development (BDD), Domain-Driven Design (DDD), and Test-Driven Development (TDD), it caters to diverse workflows with features such as a robust Command-Line Interface (CLI), advanced mocking tools, integrated benchmarking, and parallel test execution. Starting with version 1.1.8, **Jellyfish AI** integration further elevates the developer experience by providing intelligent test coverage analysis, diagnostics, and feedback clarity. With additional capabilities like customizable output themes, tag-based test filtering, and detailed performance insights, **Fossil Test**, alongside **Fossil Mock** and **Fossil Mark**, forms a powerful toolkit for building, testing, and optimizing high-quality, maintainable software.

| Feature                     | Description                                                                                                                             |
|-----------------------------|-----------------------------------------------------------------------------------------------------------------------------------------|
| **Command-Line Interface (CLI)** | A robust CLI for executing tests, managing test suites, and generating reports, enabling seamless automation and integration workflows. |
| **Support for Multiple Testing Styles** | Fully compatible with Behavior-Driven Development (BDD), Domain-Driven Design (DDD), and Test-Driven Development (TDD) methodologies. |
| **Mocking Capabilities** | Advanced mocking tools to simulate complex dependencies, ensuring isolated and precise unit testing. |
| **Benchmarking Tools** | Integrated benchmarking features to measure execution time, identify bottlenecks, and optimize code performance. |
| **Sanity Kit for Command Tests** | A specialized suite for validating command-line tools and scripts, ensuring consistent behavior across environments. |
| **Jellyfish AI Integration** | Intelligent assistant for analyzing test coverage, diagnostics, and improving test clarity (available from v1.1.8 onward). |
| **Parallel Test Execution** | Support for multi-threaded test execution to reduce runtime and improve efficiency. |
| **Customizable Output Themes** | Multiple output themes (e.g., fossil, catch, doctest) to tailor the appearance of test results. |
| **Tag-Based Test Filtering** | Organize and execute tests based on custom tags for better test management. |
| **Detailed Performance Insights** | Comprehensive reporting on test execution times and resource usage to aid in performance optimization. |

---

## ***Prerequisites***

To get started with Fossil Test, ensure you have the following installed:

- **Meson Build System**: If you don’t have Meson installed, follow the installation instructions on the official [Meson website](https://mesonbuild.com/Getting-meson.html).

---

### Adding Fossil Test Dependency

#### Adding Fossil Test Dependency With Meson

1. **Install Meson Build System**:
   Install Meson version `1.3` or newer:
   ```sh
   python -m pip install meson           # To install Meson
   python -m pip install --upgrade meson # To upgrade Meson
   ```

2. **Create a `.wrap` File**:
   Add the `fossil-test.wrap` file in your `subprojects` directory and include the following content:

   ```ini
   # ======================
   # Git Wrap package definition
   # ======================
   [wrap-git]
   url = https://github.com/fossillogic/fossil-test.git
   revision = v1.2.0

   [provide]
   fossil-test = fossil_test_dep
   ```

3. **Integrate the Dependency**:
   In your `meson.build` file, integrate Fossil Test by adding the following line:
   ```ini
   dep = dependency('fossil-test')
   ```

---

**Note**: For the best experience, always use the latest release of Fossil Test. Visit the [Fossil Test Releases](https://github.com/fossillogic/fossil-test/releases) page for the latest versions.

## Fossil Test CLI Usage

The Fossil Test CLI provides an efficient way to run and manage tests directly from the terminal. Here are the available commands and options:

### Commands and Options

| Command                          | Description                                                                                   | Notes                                                                                         |
|----------------------------------|-----------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------|
| `--version`                      | Displays the current version of Fossil Test.                                                  | Useful for verifying the version of the tool in use.                                          |
| `--help`                         | Shows help message with usage instructions.                                                   | Provides a quick reference for all available commands.                                        |
| `--dry-run`                      | Perform a dry run without executing commands.                                                 | Ideal for verifying test selection criteria before actual execution.                          |
| `--host <host>`                  | Specify the host name or address.                                                             | Useful for running tests in a specific environment.                                           |
| `--this`                         | Use the current context.                                                                      | Simplifies execution by leveraging the current configuration.                                 |
| `run`                            | Execute tests with optional parameters.                                                       | Supports additional options like `--fail-fast` and `--repeat`.                               |
| `filter`                         | Filter tests based on criteria.                                                               | Options include filtering by test name, suite name, or tags.                                  |
| `sort`                           | Sort tests by specified criteria.                                                             | Allows sorting in ascending or descending order.                                              |
| `shuffle`                        | Shuffle tests with optional parameters.                                                       | Includes options for specifying a seed or shuffle criteria.                                   |
| `color=<mode>`                   | Set color mode (enable, disable, auto).                                                       | Enhances readability in supported terminals.                                                  |
| `threads=<count>`                | Specify the number of threads to use.                                                         | Useful for parallel test execution.                                                           |
| `theme=<name>`                   | Set the theme (fossil, catch, doctest, etc.).                                                 | Customizes the appearance of test output.                                                     |
| `verbose=<level>`                | Set verbosity level (plain, ci, doge, human).                                                 | Adjusts the level of detail in test output.                                                   |

### Run Command Options
| Option               | Description                                                                                   | Notes                                                                                         |
|----------------------|-----------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------|
| `--fail-fast`        | Stop on the first failure.                                                                    | Useful for quickly identifying and addressing critical issues.                               |
| `--skip`             | Skip tests.                                                                                   | Allows selective exclusion of tests during execution.                                         |
| `--only <test>`      | Run only the specified test.                                                                  | Focuses execution on a single test for debugging or validation purposes.                      |
| `--repeat <count>`   | Repeat the test a specified number of times.                                                  | Useful for stress testing or verifying consistency across multiple runs.                      |
| `--help`             | Show help for the run command.                                                                | Provides detailed usage instructions for the `run` command.                                   |

### Filter Command Options
| Option               | Description                                                                                   | Notes                                                                                         |
|----------------------|-----------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------|
| `--test-name <name>` | Filter by test name.                                                                          | Enables precise targeting of individual tests.                                                |
| `--suite-name <name>`| Filter by suite name.                                                                         | Useful for running all tests within a specific suite.                                         |
| `--tag <tag>`        | Filter by tag.                                                                                | Allows grouping and execution of tests based on custom tags.                                  |
| `--help`             | Show help for the filter command.                                                             | Provides detailed usage instructions for the `filter` command.                                |

### Sort Command Options
| Option               | Description                                                                                   | Notes                                                                                         |
|----------------------|-----------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------|
| `--by <criteria>`    | Sort by specified criteria.                                                                   | Common criteria include execution time, name, or priority.                                    |
| `--order <asc/desc>` | Sort in ascending or descending order.                                                        | Helps organize test execution based on preferred order.                                       |
| `--help`             | Show help for the sort command.                                                               | Provides detailed usage instructions for the `sort` command.                                  |

### Shuffle Command Options
| Option               | Description                                                                                   |
|----------------------|-----------------------------------------------------------------------------------------------|
| `--seed <seed>`      | Specify the seed for shuffling.                                                               |
| `--count <count>`    | Number of items to shuffle.                                                                   |
| `--by <criteria>`    | Shuffle by specified criteria.                                                                |
| `--help`             | Show help for the shuffle command.                                                            |

## Configure Build Options

To configure the build system with testing enabled, use the following command:

```sh
meson setup builddir -Dwith_test=enabled
```

---

## ***Contributing and Support***

If you would like to contribute, have questions, or need help, feel free to open an issue on the [Fossil Test GitHub repository](https://github.com/fossillogic/fossil-test) or consult the [Fossil Logic Docs](https://fossillogic.com/docs).

---

## ***Conclusion***

Fossil Test is a powerful and flexible framework for C and C++ developers, designed to support a wide range of testing methodologies such as BDD, DDD, and TDD. With features like mocking, detailed reporting, and performance tracking, Fossil Test empowers developers to create high-quality software and maintainable test suites. Combined with Fossil Mark and Fossil Mock, it provides a complete suite for testing, optimization, and dependency management. Whether you're building small projects or large-scale applications, Fossil Test is an essential tool to ensure the reliability and performance of your code.

# ***Fossil Test: Unit Testing/Mocking Framework*** - `C, C++`

**Overview:**
Fossil Test is a robust unit testing and mocking framework developed by Fossil Logic. It is designed to facilitate the creation of high-quality test cases for C and C++ projects, promoting software reliability and correctness. The framework supports various development methodologies, including Behavior-Driven Development (BDD), Domain-Driven Design (DDD), and Test-Driven Development (TDD), offering flexibility for diverse development workflows.

In addition to Fossil Test, Fossil Logic also offers two additional frameworks to enhance your development experience:
- **Fossil Mark**: A powerful benchmarking tool that allows developers to measure code performance, identify bottlenecks, and optimize execution time. It offers detailed timing information and reporting.
- **Fossil Mock**: A mocking library enabling developers to simulate the behavior of complex dependencies. By using mock objects, you can write focused unit tests that test isolated components, enhancing test reliability and coverage.

Together, Fossil Test, Fossil Mark, and Fossil Mock provide a comprehensive toolkit for developing, testing, and optimizing high-quality software.

---

**Key Features:**

| Feature                  | Description                                                                                                                                                     |
|--------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **BDD, DDD, and TDD Support** | Supports Behavior-Driven, Domain-Driven, and Test-Driven Development styles, catering to various project methodologies.                                        |
| **Comprehensive Unit Testing** | A full suite of tools for creating, managing, and executing unit tests, ensuring that individual units of code behave as expected.                             |
| **Mocking Capabilities** | Powerful mocking features allow developers to simulate complex dependencies, ensuring focused and reliable unit tests.                                         |
| **Test Case Management** | Organize and manage test cases with features for categorization, prioritization, and tagging, improving test suite maintainability.                             |
| **Detailed Reporting**   | Generates comprehensive reports on test execution, including information on passed, failed, skipped, and timed-out tests, aiding quick issue resolution.      |
| **Performance Tracking** | Measures and reports the performance of each test case, helping developers optimize test execution time and performance.                                         |
| **Assertion Detection**  | Ensures that assertions are properly used in code, enforcing critical conditions and identifying potential areas lacking validation.                             |
| **Command-Line Interface (CLI)** | A powerful CLI for running tests, generating reports, and managing the test suite, supporting automation and integration workflows.                        |
| **Extensible and Configurable** | Highly extensible, allowing developers to customize the framework to their needs, from reporting formats to tool integration.                              |

---

## ***Prerequisites***

To get started with Fossil Test, ensure you have the following installed:

- **Meson Build System**: Fossil Test requires Meson. If you don’t have Meson installed, follow the installation instructions on the official [Meson website](https://mesonbuild.com/Getting-meson.html).

---

### Adding Fossil Test Dependency

To integrate Fossil Test into your project, follow these steps:

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
   revision = v1.0.7

   [provide]
   fossil-test = fossil_test_dep
   fossil-mock = fossil_mock_dep
   fossil-mark = fossil_mark_dep
   ```

3. **Integrate the Dependency**:
   In your `meson.build` file, integrate Fossil Test by adding the following line:
   ```ini
   dep = dependency('fossil-test')
   ```

   **Note**: For the best experience, always use the latest release of Fossil Test. Visit the [Fossil Test Releases](https://github.com/fossillogic/fossil-test/releases) page for the latest versions.

---

## Fossil Test CLI Usage

The Fossil Test CLI provides an efficient way to run and manage tests directly from the terminal. Here are the available commands and options:

### Commands and Options

| Command                         | Description                                                                                   |
|----------------------------------|-----------------------------------------------------------------------------------------------|
| `--version`                      | Displays the current version of the Fossil Test CLI.                                            |
| `--help`                         | Shows help message with usage instructions.                                                   |
| `--tip`                          | Displays a tip or hint related to the CLI usage.                                               |
| `--info`                         | Displays detailed information about the test runner configuration.                             |
| `--author`                       | Shows information about the author of the test runner.                                         |
| `only=<tag>` or `only=<tags>`    | Runs only tests tagged with the specified tag(s). Tags can be comma-separated for multiple tags. |
| `reverse [enable/disable]`       | Enables or disables reverse order of test execution.                                           |
| `repeat=<number>`                | Repeats the test suite a specified number of times.                                            |
| `shuffle [enable/disable]`       | Enables or disables shuffling of test execution order.                                         |
| `verbose [cutback/normal/verbose]` | Sets verbosity level of the output. Options are `cutback`, `normal`, and `verbose`.         |
| `list`                           | Lists all available tests.                                                                    |
| `summary [enable/disable]`       | Enables or disables a summary of test results after execution.                                |
| `color [enable/disable]`         | Enables or disables colored output in the terminal.                                           |
| `sanity [enable/disable]`        | Enables or disables sanity checks before running tests.                                        |

### Example Usage

- Display the version:
  ```sh
  fossil_cli --version
  ```

- Run tests tagged with `unit` and `integration`:
  ```sh
  fossil_cli only=unit,integration
  ```

- Enable reverse order of test execution:
  ```sh
  fossil_cli reverse enable
  ```

- Repeat the test suite 5 times:
  ```sh
  fossil_cli repeat=5
  ```

- Show a summary after execution:
  ```sh
  fossil_cli summary enable
  ```

- Enable colored output:
  ```sh
  fossil_cli color enable
  ```

---

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

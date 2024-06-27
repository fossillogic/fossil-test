# ***Fossil Test: Unit Testing/Mocking Framework*** - `C/C++`

**Overview:**
Fossil Test is a robust unit testing and mocking framework developed by Fossil Logic, designed to facilitate the creation of high-quality test cases across any C or C++ project. The framework supports both Behavior-Driven Development (BDD) and Test-Driven Development (TDD) styles, providing a flexible and comprehensive solution for ensuring software reliability and correctness.

**Key Features:**

| Feature                  | Description                                                                                                                                                     |
|--------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **BDD and TDD Support**  | Allows developers to write tests in both BDD and TDD styles, catering to various development and testing preferences.                                            |
| **Unit Testing**         | Provides a complete suite of tools for writing and executing unit tests, ensuring that individual units of code perform as expected.                             |
| **Mocking Capabilities** | Includes powerful mocking features that enable developers to simulate the behavior of complex dependencies, ensuring focused and reliable unit tests.            |
| **Test Case Management** | Supports organizing and managing test cases efficiently, with features for categorizing, prioritizing, and tagging tests.                                        |
| **Detailed Reporting**   | Generates detailed reports on test execution, including information on passed, failed, skipped, and timed-out tests, helping developers quickly address issues.  |
| **Performance Tracking** | Tracks the performance of each test case with built-in timing information, allowing developers to monitor and optimize test execution time.                      |
| **Assertion Detection**  | Detects whether assertions are used within the code, ensuring that critical conditions are enforced and identifying areas that may lack proper validation.        |
| **Command-Line Interface (CLI)** | Includes a powerful CLI for running tests, generating reports, and managing the test suite from the command line, enhancing automation and integration.  |
| **Extensible and Configurable** | Designed to be extensible and configurable, allowing developers to tailor the framework to their specific needs, from reporting formats to tool integration.|

## ***Prerequisites***

Before getting started, make sure you have the following installed:

- **Meson Build System**: This project relies on Meson. If you don't have Meson installed, visit the official [Meson website](https://mesonbuild.com/Getting-meson.html) for installation instructions.

## Adding Dependency

1. **Install Meson Build System**: Before integrating the dependency, ensure you have Meson `1.2` or newer installed on your host system. You can install it with this command.

   ```sh
   python -m pip install meson           # to install Meson
   python -m pip install --upgrade meson # to upgrade Meson
   ```

2. **Adding Wrap File**: You can add a `.wrap` file by first navigating to the `subprojects` directory and creating `fossil-test.wrap`. Next, copy the definition into the file:

   ```ini
   # ======================
   # Git Wrap package definition
   # ======================
   [wrap-git]
   url = https://github.com/fossillogic/fossil-test.git
   revision = v1.0.1

   [provide]
   fossil-test = fossil_test_dep
   fossil-mock = fossil_mock_dep
   ```

3. **Integrate the New Dependency**: After creating the dependency `.wrap` file, you need to integrate it into your Meson project. This typically involves adding the dependency to your `meson.build` file. Here's an example of how you might do that:

   ```ini
   dep = dependency('fossil-test')
   ```

   This line retrieves the `fossil-test` dependency, allowing you to use it in your project. **Releases Page**: Head over to the [Fossil Test Releases](https://github.com/fossillogic/fossil-test/releases) to find any preferred version of the framework. For the best experience with Fossil Test, it is recommended to always use the latest release.

## Fossil Test CLI Usage

The Fossil Test CLI is a command-line tool designed to help you run and manage your test suite efficiently. Below are the available commands and options:

### Commands and Options

| Command                         | Description                                                                                   |
|---------------------------------|-----------------------------------------------------------------------------------------------|
| `--version`                     | Displays the version of the Fossil Test CLI.                                                  |
| `--help`                        | Shows the help message with usage instructions.                                               |
| `--tip`                         | Provides a tip or hint about using the Fossil Test CLI.                                       |
| `--info`                        | Displays information about the test runner.                                                   |
| `--author`                      | Shows information about the author of the test runner.                                        |
| `only=<tag>` or `only=<tags>`   | Runs only the tests tagged with the specified tag(s). Tags should be comma-separated for multiple tags. |
| `reverse [enable/disable]`      | Enables or disables the reverse order of test execution.                                      |
| `repeat=<number>`               | Repeats the test suite for the specified number of times.                                     |
| `shuffle [enable/disable]`      | Enables or disables the shuffling of test execution order.                                    |
| `verbose [cutback/normal/verbose]` | Sets the verbosity level of the output. Options are `cutback`, `normal`, and `verbose`.     |
| `list`                          | Lists all available tests.                                                                    |
| `summary [enable/disable]`      | Enables or disables the summary of test results after execution.                              |
| `color [enable/disable]`        | Enables or disables colored output in the terminal.                                           |
| `sanity [enable/disable]`       | Enables or disables sanity checks before running the tests.                                   |

### Examples

- Display version information:
  ```sh
  fossil_cli --version
  ```

- Show help message:
  ```sh
  fossil_cli --help
  ```

- Run only tests tagged with "unit" and "integration":
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

- Enable verbose output:
  ```sh
  fossil_cli verbose verbose
  ```

- List all available tests:
  ```sh
  fossil_cli list
  ```

- Enable test result summary:
  ```sh
  fossil_cli summary enable
  ```

- Enable colored output:
  ```sh
  fossil_cli color enable
  ```

Feel free to explore and use the various commands and options to tailor the test runner to your needs. For further assistance, refer to the `--help` command.

## Configure Options

You have options when configuring the build, each serving a different purpose:

- **Running Tests**: To enable running tests, use `-Dwith_test=enabled` when configuring the build.

Example:

```sh
meson setup builddir -Dwith_test=enabled
```

## ***Contributing and Support***

If you're interested in contributing to this project, encounter any issues, have questions, or would like to provide feedback, don't hesitate to open an issue or visit the [Fossil Logic Docs](https://fossillogic.com/docs) for more information.

## ***Conclusion:***

Fossil Test is a comprehensive solution for C and C++ developers aiming to ensure the quality and reliability of their code. By supporting both BDD and TDD, along with powerful mocking, assertion detection, detailed reporting, and a robust CLI, Fossil Test empowers developers to create robust and maintainable test suites. Its flexibility and extensibility make it a valuable tool for projects of any size and complexity, fostering a culture of quality and continuous improvement.

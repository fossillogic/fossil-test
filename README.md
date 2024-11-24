# ***Fossil Test by Fossil Logic***

**Fossil Test** is a comprehensive unit testing, mocking, and benchmarking suite created by Fossil Logic, designed to ensure the reliability and performance of C and C++ projects. With support for multiple development methodologies, including Behavior-Driven Development (BDD), Domain-Driven Design (DDD), and Test-Driven Development (TDD), Fossil Test provides a versatile foundation for crafting high-quality test cases across various workflows.

The Fossil suite consists of three complementary frameworks to streamline the development and testing process:

- **Fossil Test**: The core unit testing framework that enables developers to create, manage, and execute unit tests effectively, ensuring each component functions as expected.
- **Fossil Mock**: A dedicated mocking library that simulates complex dependencies. Using mock objects, developers can isolate and thoroughly test individual components, improving the precision and reliability of test coverage.
- **Fossil Mark**: A benchmarking tool that provides detailed performance insights by measuring execution time, identifying bottlenecks, and offering in-depth reporting to optimize code efficiency.

Together, **Fossil Test**, **Fossil Mock**, and **Fossil Mark** offer a powerful, integrated toolkit for developing, testing, and optimizing robust software, making them an essential asset for developers committed to quality and performance.

---

**Key Features:**

| Feature                  | Description                                                                                                                                                     |
|--------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **BDD, DDD, and TDD Support** | Supports Behavior-Driven, Domain-Driven, and Test-Driven Development styles, catering to various project methodologies.                                        |
| **Comprehensive Unit Testing** | A full suite of tools for creating, managing, and executing unit tests, ensuring that individual units of code behave as expected.                             |
| **Mocking Capabilities** | Powerful mocking features allow developers to simulate complex dependencies, ensuring focused and reliable unit tests.                                         |
| **Performance Tracking** | Measures and reports the performance of each test case, helping developers optimize test execution time and performance.                                         |
| **Command-Line Interface (CLI)** | A powerful CLI for running tests, generating reports, and managing the test suite, supporting automation and integration workflows.                        |

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
   revision = v1.1.4

   [provide]
   fossil-test = fossil_test_dep
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
| `--version`                      | Displays the current version of Fossil Test.                                            |
| `--help`                         | Shows help message with usage instructions.                                                   |
| `--info`                         | Displays detailed information about the test run.                             |
| `reverse [enable/disable]`       | Enables or disables reverse order of test execution.                                           |
| `repeat=<number>`                | Repeats the test suite a specified number of times.                                            |
| `shuffle [enable/disable]`       | Enables or disables shuffling of test execution order.                                         |

### Example Usage

- Display the version:
  ```sh
  fossil_cli --version
  ```

- Enable reverse order of test execution:
  ```sh
  fossil_cli reverse enable
  ```

- Repeat the test suite 5 times:
  ```sh
  fossil_cli repeat=5
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

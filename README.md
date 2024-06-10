# Fossil Test - `C`

Fossil Test is a robust unit testing framework designed to ensure the reliability and correctness of your software. With its user-friendly interface and comprehensive suite of tools, Fossil Test streamlines the process of writing, running, and analyzing tests for your applications. It supports a wide range of programming languages and integrates seamlessly with various development environments, making it an ideal choice for both novice and experienced developers. Fossil Test provides advanced features such as test automation, code coverage analysis, and detailed reporting, enabling you to identify and fix bugs efficiently. Its modular architecture allows for easy extension and customization, catering to the specific needs of your projects. Trust Fossil Test to enhance the quality of your code and boost your productivity.

## Prerequisites

Before getting started, make sure you have the following installed:

- **Meson Build System**: This project relies on Meson. If you don't have Meson installed, visit the official [Meson website](https://mesonbuild.com/Getting-meson.html) for installation instructions.

## Adding dependency

1. **Install Meson Build System**: Before integrating the dependency, ensure you have Meson `1.2` or newer installed on your host system. You can install it with this command.

   ```ini
   python -m pip install meson           # to install Meson
   python -m pip install --upgrade meson # to upgrade Meson
   ```

2. **Adding Wrap File**: You can add a `.wrap`, first go into `subprojects` directory and create `fossil-test.wrap` next copy the defintion into the file:

   ```ini
   # ======================
   # Git Wrap package definition
   # ======================
   [wrap-git]
   url = https://github.com/dreamer-coding-555/fossil-test.git
   revision = v1.0.0

   [provide]
   fossil-test = fossil_test_dep
   fossil-mock = fossil_mock_dep
   ```

3. **Integrate the New Dependency**: After creating the dependency `.wrap` file, you need to integrate it into your Meson project. This typically involves adding the dependency to your `meson.build` file. Here's an example of how you might do that:

   ```ini
   test_dep = dependency('fossil-test') # Fossil Test main framework
   mock_dep = dependency('fossil-mock') # Fossil Test mockup framework
   ```

   This line retrieves the `fossil-test` dependency, allowing you to use it in your project.
   
## Configure Options

You have options when configuring the build, each serving a different purpose:

- **Running Tests**: To enable running tests, use `-Dwith_test=enabled` when configuring the build.

Example:

```python
meson setup builddir -Dwith_test=enabled
```

## Contributing and Support

If you're interested in contributing to this project, encounter any issues, have questions, or would like to provide feedback, don't hesitate to open an issue or visit the [Fossil Logic Docs](https://fossillogic.com/docs) for more information.

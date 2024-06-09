# Project Template - `C`

Welcome to the Project Template repository! This README provides user-friendly instructions for setting up, compiling, testing, and running a project using the Meson build system on Windows, macOS, and Linux systems. Please note that the Meson build system is required for successfully building this project.

## Prerequisites

Before getting started, make sure you have the following installed:

- **Meson Build System**: This project relies on Meson. If you don't have Meson installed, visit the official [Meson website](https://mesonbuild.com/Getting-meson.html) for installation instructions.

## Adding dependency

1. **Install Meson Build System**: Before integrating the dependency, ensure you have Meson `1.2` or newer installed on your host system. You can install it with this command.

   ```ini
   python -m pip install meson           # to install Meson
   python -m pip install --upgrade meson # to upgrade Meson
   ```

2. **Adding Wrap File**: You can add a `.wrap`, first go into `subprojects` directory and create `fscl-<name>-c.wrap` next copy the defintion into the file:

   ```ini
   # ======================
   # Git Wrap package definition
   # ======================
   [wrap-git]
   url = https://github.com/fossil-lib/tscl-<name>-c.git
   revision = v2.4.3

   [provide]
   fscl-<name>-c = fscl_<name>_c_dep
   ```

3. **Integrate the New Dependency**: After creating the dependency `.wrap` file, you need to integrate it into your Meson project. This typically involves adding the dependency to your `meson.build` file. Here's an example of how you might do that:

   ```ini
   dep = dependency('fscl-<name>-c')
   ```

   This line retrieves the `fscl-<name>-c` dependency, allowing you to use it in your project.

## Configure Options

You have options when configuring the build, each serving a different purpose:

- **Running Tests**: To enable running tests, use `-Dwith_test=enabled` when configuring the build.

## Contributing and Support

If you're interested in contributing to this project, encounter any issues, have questions, or would like to provide feedback, don't hesitate to open an issue or visit the [Fossil Logic Docs](https://fossillogic.com/docs) for more information.

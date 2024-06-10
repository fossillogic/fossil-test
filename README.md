# Fossil Test - `C`

Fossil Logic's library stands as a cornerstone within a vast collection of libraries, each a testament to the company's commitment to knowledge and innovation. Serving as a rich repository of resources, Fossil Logic's library embodies the organization's dedication to fostering intellectual growth and development. With a diverse array of materials spanning various disciplines, it serves as a hub for exploration, learning, and collaboration. Whether seeking information for research, inspiration for creativity, or solutions to complex problems, Fossil Logic's library offers a wealth of opportunities for individuals to expand their horizons and deepen their understanding.

## Prerequisites

Before getting started, make sure you have the following installed:

- **Meson Build System**: This project relies on Meson. If you don't have Meson installed, visit the official [Meson website](https://mesonbuild.com/Getting-meson.html) for installation instructions.

## Adding dependency

1. **Install Meson Build System**: Before integrating the dependency, ensure you have Meson `1.2` or newer installed on your host system. You can install it with this command.

   ```ini
   python -m pip install meson           # to install Meson
   python -m pip install --upgrade meson # to upgrade Meson
   ```

2. **Adding Wrap File**: You can add a `.wrap`, first go into `subprojects` directory and create `fossil-test-c.wrap` next copy the defintion into the file:

   ```ini
   # ======================
   # Git Wrap package definition
   # ======================
   [wrap-git]
   url = https://github.com/dreamer-coding-555/fossil-test-c.git
   revision = v1.0.0

   [provide]
   fossil-test-c = fossil_test_c_dep
   ```

3. **Integrate the New Dependency**: After creating the dependency `.wrap` file, you need to integrate it into your Meson project. This typically involves adding the dependency to your `meson.build` file. Here's an example of how you might do that:

   ```ini
   dep = dependency('fossil-test-c')
   ```

   This line retrieves the `fossil-test-c` dependency, allowing you to use it in your project.
   
## Configure Options

You have options when configuring the build, each serving a different purpose:

- **Running Tests**: To enable running tests, use `-Dwith_test=enabled` when configuring the build.

Example:

```python
meson setup builddir -Dwith_test=enabled
```

## Contributing and Support

If you're interested in contributing to this project, encounter any issues, have questions, or would like to provide feedback, don't hesitate to open an issue or visit the [Fossil Logic Docs](https://fossillogic.com/docs) for more information.

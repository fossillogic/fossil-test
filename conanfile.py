from conan import ConanFile
from conan.tools.meson import Meson
from conan.tools.files import copy
import os

class PizzaTestConan(ConanFile):
    name = "pizza_test"
    version = "1.2.7"
    license = "MPL-2.0"
    author = "Fossil Logic <michaelbrockus@gmail.com>"
    url = "https://github.com/fossillogic/fossil-test"
    description = "Unit testing framework for software projects"
    topics = ("testing", "mocking", "framework")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    exports_sources = "code/logic/*", "meson.build"
    generators = "PkgConfigDeps"

    def build(self):
        meson = Meson(self)
        meson.configure()
        meson.build(build_dir="builddir")

    def package(self):
        meson = Meson(self)
        meson.install()
        copy(self, "*.h", src="code/logic/fossil/pizza",
             dst=os.path.join(self.package_folder, "include", "fossil", "pizza"))

    def package_info(self):
        self.cpp_info.libs = ["pizza_test"]
        self.cpp_info.includedirs = ["include"]
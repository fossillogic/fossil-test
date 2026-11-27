from conan import ConanFile
from conan.tools.meson import Meson, MesonToolchain
from conan.tools.layout import basic_layout
from conan.tools.files import copy
import os


class FossilTestConan(ConanFile):
    name = "fossil-test"
    version = "2.0.6"
    package_type = "library"

    # Metadata
    license = "Apache-2.0"
    author = "Michael Gene Brockus (Dreamer) <michaelbrockus@gmail.com>"
    url = "https://github.com/fossillogic/fossil-test"
    homepage = "https://fossillogic.com/"
    description = (
        "Lightweight, portable testing library written in pure C "
        "with zero external dependencies."
    )
    topics = ("c", "testing", "test-framework", "portable", "cross-platform", "fossil-logic", "meson")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False, "true", "false"],
        "fPIC": [True, False],
    }
    default_options = {
        "shared": False,          # matches Meson default_library = static
        "fPIC": True,
    }

    # Export the Meson build system + sources (same layout as the repo)
    exports_sources = (
        "meson.build",
        "meson.options",
        "code/*",
        "LICENSE",
        "README.md",
    )

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def configure(self):
        # Pure C library – drop C++-only settings
        self.settings.rm_safe("compiler.libcxx")
        self.settings.rm_safe("compiler.cppstd")
        # Conan option values may arrive as lowercase strings from CI.
        self.options.shared = str(self.options.shared).lower() == "true"
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        basic_layout(self)

    def generate(self):
        tc = MesonToolchain(self)
        # Align with the project's Meson options
        tc.project_options["default_library"] = "shared" if self.options.shared else "static"
        tc.project_options["with_test"] = "disabled"   # library-only package
        tc.generate()

    def build(self):
        meson = Meson(self)
        meson.configure()
        meson.build()

    def package(self):
        # License
        copy(self, "LICENSE",
             src=self.source_folder,
             dst=os.path.join(self.package_folder, "licenses"))

        # Install library (and any files Meson knows about)
        meson = Meson(self)
        meson.install()

        # Current Meson files do not call install_headers(), so copy
        # the public headers ourselves to preserve fossil/io/ hierarchy.
        copy(self, "*.h",
             src=os.path.join(self.source_folder, "code", "logic", "fossil"),
             dst=os.path.join(self.package_folder, "include", "fossil"),
             keep_path=True)

    def package_info(self):
        self.cpp_info.set_property("pkg_config_name", "fossil-test")

        self.cpp_info.libs = ["fossil_test"]
        self.cpp_info.includedirs = ["include"]

        if self.settings.os in ("Linux", "FreeBSD"):
            self.cpp_info.system_libs.append("m")

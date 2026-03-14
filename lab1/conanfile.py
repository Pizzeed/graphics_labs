import os
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout, CMakeDeps
from conan.tools.build import check_min_cppstd
from conan.tools.files import copy, rmdir


class Lab1Recipe(ConanFile):
    name = "lab1"
    version = "0.0.1"

    settings = "os", "compiler", "build_type", "arch"

    exports_sources = "*"

    options = {
        "shared": [True, False],
    }
    default_options = {
        "shared": True,
    }

    @property
    def _min_cppstd(self):
        return '20'

    def requirements(self):
        self.requires("labs_engine/0.0.1")
        self.requires("imgui/1.89.1")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.cache_variables["BUILD_SHARED_LIBS"] = self.options.shared
        tc.generate()
        copy(self, "*", os.path.join("../", self.source_folder, "assets"), os.path.join(self.build_folder, "assets"))        
        copy(self, "*glfw*", os.path.join(self.dependencies["imgui"].package_folder,
            "res", "bindings"), os.path.join(self.source_folder, "src/c++/bindings"))
        copy(self, "*opengl3*", os.path.join(self.dependencies["imgui"].package_folder,
            "res", "bindings"), os.path.join(self.source_folder, "src/c++/bindings"))


    def validate(self):
        if self.settings.compiler.get_safe("cppstd"):
            check_min_cppstd(self, self._min_cppstd)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
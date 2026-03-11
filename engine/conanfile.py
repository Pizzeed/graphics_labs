import os
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout, CMakeDeps
from conan.tools.build import check_min_cppstd
from conan.tools.files import copy, rmdir


class LabsEngineRecipe(ConanFile):
    name = "labs_engine"
    version = "0.0.1"

    settings = "os", "compiler", "build_type", "arch"

    exports_sources = "*"

    options = {
        "shared": [True, False],
        "standalone": [True, False]
    }
    default_options = {
        "shared": True,
        "standalone": False
    }

    @property
    def _min_cppstd(self):
        return '20'

    def requirements(self):
        self.requires("glfw/3.4")
        self.requires("glm/1.0.1")
        self.requires("imgui/1.91.8")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.cache_variables["BUILD_SHARED_LIBS"] = self.options.shared
        tc.cache_variables["STANDALONE"] = self.options.standalone
        tc.generate()
        copy(self, "*glfw*", os.path.join(self.dependencies["imgui"].package_folder,
            "res", "bindings"), os.path.join(self.source_folder, "bindings"))
        copy(self, "*opengl3*", os.path.join(self.dependencies["imgui"].package_folder,
            "res", "bindings"), os.path.join(self.source_folder, "bindings"))


    def validate(self):
        if self.settings.compiler.get_safe("cppstd"):
            check_min_cppstd(self, self._min_cppstd)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        rmdir(self, os.path.join(self.package_folder, "res"))
        rmdir(self, os.path.join(self.package_folder, "share"))

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "labs_engine")
        self.cpp_info.set_property("cmake_target_name", "labs_engine::labs_engine")
        self.cpp_info.libs = ["labs_engine"]
        self.cpp_info.requires = ["glfw::glfw", "glm::glm", "imgui::imgui"]


    def imports(self):
        self.copy('*.so*', src='lib', dst='bin')

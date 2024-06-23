from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.apple import fix_apple_shared_install_name

class KaiORecipe(ConanFile):
    name = "kai_o"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        #self.requires("sdl/2.30.3")
        self.requires("sdl_image/2.6.3", options={"shared": False})
        self.requires("sdl_ttf/2.22.0", options={"shared": False})
        self.requires("glm/cci.20230113")
        self.tool_requires("emsdk/3.1.50")
        self.tool_requires("cmake/[>=3.25]")

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if self.settings.os == 'Windows':
            self.run(f"cmake --install . --prefix=../../install --config {self.settings.build_type}")
        else:
            self.run(f"cmake --install . --prefix=../../../install --config {self.settings.build_type}")

    def layout(self):
        cmake_layout(self)
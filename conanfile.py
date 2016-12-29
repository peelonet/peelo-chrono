from conans import ConanFile, CMake

class PeeloCPPChronoConan(ConanFile):
    name = "peelocpp_chrono"
    version = "0.1.0"
    settings = "os", "compiler", "build_type", "arch"
    exports = "*"

    def build(self):
        cmake = CMake(self.settings)
        self.run("cmake %s %s" % (self.conanfile_directory, cmake.command_line))
        self.run("cmake --build . %s" % (cmake.build_config,))

    def package(self):
        self.copy("*.hpp", dst="include")
        self.copy("*.lib", dst="lib", src="lib")
        self.copy("*.a", dst="lib", src="lib")

    def package_info(self):
        self.cpp_info.libs = ["peelocpp_chrono"]

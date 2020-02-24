from conans import ConanFile, CMake, tools


class KeywordConanFile(ConanFile):
    name = "keyword"
    version = "0.0.0"
    license = "MIT"
    description = "keyword function arguments for C++"
    url = "https://github.com/alexFickle/keyword"
    settings = "os", "arch", "compiler", "build_type"
    generators = "cmake"
    exports_sources = ("include/*", "test/*", "CMakeLists.txt", "LICENSE")

    build_requires = "gtest/1.8.1@bincrafters/stable"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if not tools.cross_building(self.settings):
            cmake.test(output_on_failure=True)

    def package_id(self):
        self.info.header_only()

    def package(self):
        self.copy("*.hpp", src="include", dst="include")
        self.copy("LICENSE", src=".", dst=".")

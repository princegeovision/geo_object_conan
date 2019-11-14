from conans import ConanFile, CMake, tools


class GeoobjectConan(ConanFile):
    name = "geo_object"
    version = "1.1"
    license = "MIT"
    author = "prince.geovision.tw@gmail.com"
    url = "https://github.com/princegeovision/geo_object_conan"
    description = "Object for simplify or aggregate function input/output"
    topics = ("C", "jansson")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "cmake"

    def source(self):
        self.run("git clone https://github.com/princegeovision/geo_object_conan.git")

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin") # From bin to bin
        self.copy("*.dylib*", dst="bin", src="lib") # From lib to bin

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="geo_object_conan")
        #cmake.configure()
        cmake.build()

        # Explicit way:
        # self.run('cmake %s/hello %s'
        #          % (self.source_folder, cmake.command_line))
        # self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.h", dst="include", src="geo_object")
        self.copy("*geo_object.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["geo_object"]


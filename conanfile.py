#!/usr/bin/python
# -*- coding: UTF-8 -*-

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
        # 我們可以透過基本指令分岔，不同平台的時候使用的步驟。
        # EX: if platform.system() == "Windows":
        cmake = CMake(self)
        # 這個 Build 意謂使用者可以透過 remote 下載 source , 直接build
        # 所以這邊指的目錄名稱是 github 的 folder名稱。
        cmake.configure(source_folder="geo_object_conan")
        cmake.build()
        # Explicit way:
        # self.run('cmake %s/hello %s'
        #          % (self.source_folder, cmake.command_line))
        # self.run("cmake --build . %s" % cmake.build_config)
    def _configure_cmake(self):
        cmake = CMake(self)
        return cmake

    def package(self):
        # keep_path 不能用 true, 目前架構會失敗
        self.copy("*.h", dst="include", keep_path=False)
        self.copy("*geo_object.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
        cmake = self._configure_cmake()

    def package_info(self):
        self.cpp_info.libs = ["geo_object"]
        #self.cpp_info.libs = tools.collect_libs(self)


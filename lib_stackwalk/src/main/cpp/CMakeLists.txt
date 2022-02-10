# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("stackwalk")

get_filename_component(BREAKPAD_SRC_DIR  ${CMAKE_SOURCE_DIR}/breakpad  ABSOLUTE)

# 定义源文件目录下的源文件，虽然这样可以避免写一大堆文件列表，但由于ide支持不够好，因此有新文件增加时需要手动删除生成的.cxx文件夹后再编译
file(GLOB_RECURSE CPP_SOURCES *.c *.cc *.cpp)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        stackwalk

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ${CPP_SOURCES}
#        stackwalk.cpp
#        ${BREAKPAD_SRC_DIR}/src/processor/minidump_stackwalk.cc
        )
include_directories(${BREAKPAD_SRC_DIR}/src/common/android/include)
include_directories(${BREAKPAD_SRC_DIR}/src)
# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        stackwalk

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})
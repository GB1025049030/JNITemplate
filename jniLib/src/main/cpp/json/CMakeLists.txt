# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

project("jnilib")

include_directories(include)
include_directories(include/harmony)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the className of the library.
        jnilib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/js_call_android_jni.cpp
        src/jni_info.cpp
        src/jni_transform.cpp
        src/jni_utils.cpp
        src/harmony/jkit.cpp
        src/test/transform.cpp
        src/native.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the className of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the className of the path variable.
        log-lib

        # Specifies the className of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your t library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the t library.
        jnilib

        # Links the t library to the log library
        # included in the NDK.
        ${log-lib})
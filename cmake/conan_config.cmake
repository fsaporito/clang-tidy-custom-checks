# Download conan.cmake if it doesn't exists
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
        "${CMAKE_BINARY_DIR}/conan.cmake" TLS_VERIFY ON)
endif()

# Include conan.cmake
include(${CMAKE_BINARY_DIR}/conan.cmake)

# Run conan -install
conan_cmake_run(
    CONANFILE
    ${CMAKE_SOURCE_DIR}/conanfile.txt
    BASIC_SETUP
    CMAKE_TARGETS
    BUILD
    missing)

# Include the produced paths for downloaded dependencies
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
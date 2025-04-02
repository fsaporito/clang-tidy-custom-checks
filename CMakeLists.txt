if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)

# Set the project name and language
project(
  clang-tidy-custom-checks
  VERSION 1.0.0
  LANGUAGES C CXX)

# CMake Minimum Version
cmake_minimum_required(VERSION 3.21) # Needed for Preset

# Check Requirements (Languages, Cmake, Compiler)
if(NOT DEFINED CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 11)
endif()

set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CMake modules & includes
set(CMAKE_CUSTOM_MODULES_PATH ${CMAKE_CUSTOM_MODULES_PATH} ${CMAKE_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CUSTOM_MODULES_PATH}")
include(${CMAKE_CUSTOM_MODULES_PATH}/index.cmake)

# Dependency Management
option(ENABLE_CONAN "Enable conan for dependency management" OFF)
option(ENABLE_CPM "Enable CPM for dependency management" ON)

# Set Warnings
create_warnings_list(C_WARNINGS_LIST CXX_WARNINGS_LIST WARNINGS_AS_ERRORS)
message("-- C Warnings: " ${C_WARNINGS_LIST})
message("-- C++ Warnings: " ${CXX_WARNINGS_LIST})

# Set Build Type and Optimization Settings
create_optimization_flags(USE_LTO OPTIMIZATION_SETTINGS)
message("-- Build Type: " ${CMAKE_BUILD_TYPE})
message("-- Optimization Settings: " ${OPTIMIZATION_SETTINGS})

# Configuration Target with all the warnings and optimizations
add_library(ProjectConfiguration INTERFACE)
target_compile_options(
  ProjectConfiguration
  INTERFACE # Optimization Settigs
  ${OPTIMIZATION_SETTINGS}

  # C++ warnings
  $<$<COMPILE_LANGUAGE:CXX>:${CXX_WARNINGS_LIST}>

  # C warnings
  $<$<COMPILE_LANGUAGE:C>:${C_WARNINGS_LIST}>)

# Static Analyzers
message("-- Clang-Tidy Static Analyzer is Active: " ${STATIC_ANALYZER_CLANG_TIDY})
message("-- CPPCHECK Static Analyzer is Active: " ${STATIC_ANALYZER_CPPCHECK})
message("-- IWYU Static Analyzer is Active: " ${STATIC_ANALYZER_IWYU})
message("-- Visual Studio Static Analysis is Active: " ${STATIC_ANALYZER_VISUAL_STUDIO})
enable_static_analysis(STATIC_ANALYZER_CLANG_TIDY STATIC_ANALYZER_CPPCHECK STATIC_ANALYZER_IWYU
  STATIC_ANALYZER_VISUAL_STUDIO)

# Dependencies configuration
if(ENABLE_CONAN AND ENABLE_CPM)
  message(WARNING "Multiple dependency managers enabled. I hope you know what you are doing")
endif()

if(NOT(ENABLE_CONAN OR ENABLE_CPM))
  message(WARNING "No dependency manager configured. I hope you know what you are doing")
endif()

if(ENABLE_CONAN)
  message("-- Using Conan for dependency management")
  include(${CMAKE_CUSTOM_MODULES_PATH}/conan_config.cmake)
endif()

if(ENABLE_CPM)
  message("-- Using CPM for dependency management")
  include(${CMAKE_MODULES_FOLDER}/CPM_dependencies.cmake)
  setup_CPM_dependencies()
endif()

# Source Code
message("Building Src")
add_subdirectory(src)

# Tests
if(ENABLE_TESTING)
  enable_testing()
  message("Building Tests.")
  add_subdirectory(test)
endif()

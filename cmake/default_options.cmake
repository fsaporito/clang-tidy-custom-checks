# CMake Options
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Testing
option(ENABLE_TESTING "Enable unit tests" ON)
option(ENABLE_COVERAGE "Enable Coverage report" OFF)

# Compilation Options
option(USE_LTO "Add LTO optimization to Release build" ON)
option(WARNINGS_AS_ERRORS "treat warnings as errors" OFF)
option(ENABLE_CCACHE "Enable ccache" OFF)

# Static Analyzers
option(STATIC_ANALYZER_CLANG_TIDY "Enable include-what-you-use static analyzer" OFF)
option(STATIC_ANALYZER_CPPCHECK "Enable clang-tidy static analyzer" OFF)
option(STATIC_ANALYZER_IWYU "Enable cppcheck static analyzer" OFF)
option(STATIC_ANALYZER_VISUAL_STUDIO "Enable visual studio static analyzer" OFF)

# Options Set
option(ENABLE_DEV_OPTIONS "Enable static analyzer, ccache, warnings as errors" ON)

if(ENABLE_DEV_OPTIONS)
    message(
        STATUS
        "Developer mode is Active. For production, use `-DENABLE_DEV_OPTIONS:BOOL=OFF`.")
    set(ENABLE_TESTING ON)
    set(USE_LTO ON)
    set(WARNINGS_AS_ERRORS ON)
    set(ENABLE_CCACHE ON)
    set(STATIC_ANALYZER_CLANG_TIDY ON)
    set(STATIC_ANALYZER_CPPCHECK ON)
    set(STATIC_ANALYZER_IWYU ON)
    set(STATIC_ANALYZER_VISUAL_STUDIO ON)
else()
    message(
        STATUS
        "Developer mode is Not Active. For development, use `-DENABLE_DEV_OPTIONS:BOOL=ON`.")
endif()

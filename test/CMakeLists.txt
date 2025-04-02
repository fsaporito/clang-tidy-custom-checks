find_package(Catch2 REQUIRED)

include(CTest)
include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

include_directories(../src)

add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE ProjectConfiguration Catch2::Catch2WithMain fact prime)
message(STATUS "Target TEST created successfully")

# automatically discover tests that are defined in catch based test files you can modify the unittests. Set TEST_PREFIX
# to whatever you want, or use different for different binaries
catch_discover_tests(
    tests
    TEST_PREFIX
    "unittests."
    REPORTER
    XML
    OUTPUT_DIR
    .
    OUTPUT_PREFIX
    "unittests."
    OUTPUT_SUFFIX
    .xml)

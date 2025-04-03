find_package(Catch2 REQUIRED)

include(CTest)
include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

include_directories(../../src)
include_directories(..) # So that we can find the test_utils.hh

set(IllegalVariableNamesTestName "IllegalVariableNamesTest")

add_executable(${IllegalVariableNamesTestName} IllegalVariableNamesTests.cpp)
target_link_libraries(${IllegalVariableNamesTestName} PRIVATE ProjectConfiguration Catch2::Catch2WithMain IllegalVariableNames)
message(STATUS "Target ${IllegalVariableNamesTestName} created successfully")

# automatically discover tests that are defined in catch based test files you can modify the unittests. Set TEST_PREFIX
# to whatever you want, or use different for different binaries
catch_discover_tests(
    ${IllegalVariableNamesTestName}
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

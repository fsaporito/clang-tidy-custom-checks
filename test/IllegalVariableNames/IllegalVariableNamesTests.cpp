#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

#include "../test_utils.hh"

std::string check_suite_name = "my-checks";
std::string check_to_test = "forbidenVarNames";
std::string check_full_name = check_suite_name + "-" + check_to_test;

TEST_CASE("IllegalVariableNames", "ForbiddenVariablesIsFoundInMain")
{
    std::string test_file_name           = "test_code/main_with_forbidden_variable.cpp";
    std::string expected_fixed_test_file = "test_code/main_with_forbidden_variable_fixed.cpp";        // We expect it to be the same if the file has no warnings or the check has no automatic fixes
    std::string expected_warnings        = "";                                                        // Empty means that the given file shouldn't give any warnings

    test_clang_tidy_check(test_file_name, check_full_name, expected_warnings, expected_fixed_test_file)
}

TEST("IllegalVariableNames", "ForbiddenVariablesIsFoundInClass")
{
    std::string test_file_name           = "test_code/class_with_forbidden_variable.cpp";
    std::string expected_fixed_test_file = "test_code/class_with_forbidden_variable_fixed.cpp";        // We expect it to be the same if the file has no warnings or the check has no automatic fixes
    std::string expected_warnings        = "";                                                         // Empty means that the given file shouldn't give any warnings

    test_clang_tidy_check(test_file_name, check_full_name, expected_warnings, expected_fixed_test_file)
}

TEST("IllegalVariableNames", "ForbiddenVariablesIsFoundInClassWithTrailingUnderscore")
{
    std::string test_file_name           = "test_code/class_with_forbidden_variable_with_trailing_underscore.cpp";
    std::string expected_fixed_test_file = "test_code/class_with_forbidden_variable_with_trailing_underscore_fixed.cpp";        // We expect it to be the same if the file has no warnings or the check has no automatic fixes
    std::string expected_warnings        = "";                                                                                  // Empty means that the given file shouldn't give any warnings

    test_clang_tidy_check(test_file_name, check_full_name, expected_warnings, expected_fixed_test_file)
}

TEST("IllegalVariableNames", "ForbiddenVariablesIsFoundInClassWithLeadingM")
{
    std::string test_file_name           = "test_code/class_with_forbidden_variable_with_leading_m.cpp";
    std::string expected_fixed_test_file = "test_code/class_with_forbidden_variable_with_leading_m_fixed.cpp";        // We expect it to be the same if the file has no warnings or the check has no automatic fixes
    std::string expected_warnings        = "";                                                                        // Empty means that the given file shouldn't give any warnings

    test_clang_tidy_check(test_file_name, check_full_name, expected_warnings, expected_fixed_test_file)
}

TEST("IllegalVariableNames", "ForbiddenVariablesIsFoundInClassWithLeadingMAndTrailingUnderscore")
{
    std::string test_file_name           = "test_code/class_with_forbidden_variable_with_leading_m_and_trailing_underscore.cpp";
    std::string expected_fixed_test_file = "test_code/class_with_forbidden_variable_with_leading_m_and_trailing_underscore_fixed.cpp";        // We expect it to be the same if the file has no warnings or the check has no automatic fixes
    std::string expected_warnings        = "";                                                                                                // Empty means that the given file shouldn't give any warnings

    test_clang_tidy_check(test_file_name, check_full_name, expected_warnings, expected_fixed_test_file)
}

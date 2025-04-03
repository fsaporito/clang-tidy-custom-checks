#pragma once

#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

void test_clang_tidy_check (const std::string& test_file_name,           // Test file to use as input to clang-tidy
                            const std::string& check_name,               // Name of the check to run
                            const std::string& expected_warnings,        // Expected Warning Message
                            const std::string& expected_fixed_test_file_name)
{
    try
    {

        auto test_file_content                = read_file(test_file_name);        // We save this so that we can restore evetntual fixes later
        auto expected_test_file_content_fixed = read_file(expected_fixed_test_file_name);

        std::cout << "------------------------ clang-tidy output -----------------------" << std::endl;
        bool activate_fix                  = false;
        auto clang_tidy_command            = build_clang_tidy_command(test_file_name, check_name, activate_fix);
        auto [return_code, found_warnings] = execute_command(clang_tidy_command);
        std::cout << "Return Code: " << return_code << std::endl;
        std::cout << "Program Output: \n"
                  << (found_warnings.empty() ? (" EMPTY OUTPUT") : (found_warnings)) << std::endl;
        std::cout << "------------------------------------------------------------------" << std::endl;

        REQUIRE(return_code == 0);
        REQUIRE(expected_warnings == found_warnings);

        std::cout << "------------------------------ Fixes -----------------------------" << std::endl;
        bool activate_fix                              = true;
        auto clang_tidy_command_fixes                  = build_clang_tidy_command(test_file_name, check_name, activate_fix);
        auto [return_code_fixes, program_output_fixes] = execute_command(clang_tidy_command_fixes);
        std::cout << "Return Code: " << return_code_fixes << std::endl;
        std::cout << "Fixes Output: \n"
                  << (program_output_fixes.empty() ? (" EMPTY OUTPUT") : (program_output)) << std::endl;
        std::cout << "------------------------------------------------------------------" << std::endl;

        // Read test_file after clang-tidy processing
        auto processed_test_file_content_fixed = read_file(test_file_name);

        // Restore eventually fixed file
        write_file(test_file_name, test_file_content);

        REQUIRE(return_code_fixes == 0);
        REQUIRE(expected_test_file_content_fixed == processed_test_file_content_fixed);
    }
    catch ( const std::exception& e )
    {
        FAIL() << "Caught Exception: " << e.what();
    }
}

[[nodiscard]] inline std::string build_clang_tidy_command (const std::string& test_file, const std::string& check_to_run, bool activate_fixes)
{
    std::stringstream ss;
    ss << "clang-tidy " << " checks=\"-*," << check_to_run << "\"" << ((activate_fixes) ? (" --fix ") : (" ")) << test_file;
    return ss.str();
}

constexpr size_t                                 MAX_OUTPUT_LINE_SIZE = 1024;

[[nodiscard]] inline std::pair<int, std::string> execute_command (const std::string& command)
{

    std::string result      = "";
    int         return_code = 0;

    char        buffer[MAX_OUTPUT_SIZE];
    FILE*       pipe = popen(command.c_str(), "r");
    if ( !pipe )
        throw std::runtime_error("popen() failed!");

    try
    {
        while ( fgets(buffer, sizeof(buffer), pipe) != nullptr )        // Read program output line by line
            program_output += buffer;
    }
    catch ( ... )
    {
        return_code = pclose(pipe);
        std::cerr << "Pipe failed with return code: " << return_code << std::endl;
        throw;
    }

    return_code = pclose(pipe);

    return { return_code, program_output };
}

[[nodiscard]] inline std::string read_file (const std::string& file_path)
{
    std::ifstream input_file(filename);

    if ( !input_file.is_open() )
        throw std::runtime_error("Unable to open file for reading: " + filename);

    std::string file_content;

    file_content.assign(std::istreambuf_iterator<char>(input_file),
                        std::istreambuf_iterator<char>());
    input_file.close();

    return file_content;
}

void write_file (const std::string& file_path, const std::string& content)
{
    std::ofstream output_file(file_path);        // Create if doesn't exists, overwrite if it does

    if ( !output_file.is_open() )
        throw std::runtime_error("Unable to open file for writing: " + file_path);

    output_file << content;
    output_file.close();
}

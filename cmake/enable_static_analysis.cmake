include_guard()

function(enable_static_analysis STATIC_ANALYZER_CLANG_TIDY STATIC_ANALYZER_CPPCHECK
    STATIC_ANALYZER_IWYU STATIC_ANALYZER_VISUAL_STUDIO)
    # Clang Tidy
    if(STATIC_ANALYZER_CLANG_TIDY)
        find_program(CLANGTIDY clang-tidy REQUIRED)

        # Clang Tidy not found on Path
        if(NOT CLANGTIDY)
            message(WARNING "Static Analyzer clang-tidy was Requested but cannot be found on path")
        else()
            # Set C++ Clang Tidy
            set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY})

            # Warnings as Errors
            if(WARNINGS_AS_ERRORS)
                list(APPEND CMAKE_CXX_CLANG_TIDY -warnings-as-errors=*)
            endif()

            # Set C Clang Tidy
            set(CMAKE_C_CLANG_TIDY ${CMAKE_CXX_CLANG_TIDY})
        endif()
    endif()

    # CppCheck
    if(STATIC_ANALYZER_CPPCHECK)
        find_program(CPPCHECK cppcheck REQUIRED)

        # CppCheck not found on Path
        if(NOT CPPCHECK)
            message(WARNING "Static Analyzer cppcheck was Requested but cannot be found on path")
        else()
            # Set C++ CppCheck
            set(CMAKE_CXX_CPPCHECK
                ${CPPCHECK}
                --template=${CPPCHECK_TEMPLATE}
                --enable=style,performance,warning,portability
                --inline-suppr

                # We cannot act on a bug/missing feature of cppcheck
                --suppress=internalAstError

                # if a file does not have an internalAstError, we get an unmatchedSuppression error
                --suppress=unmatchedSuppression
                --inconclusive)

            # Warnings as Errors
            if(WARNINGS_AS_ERRORS)
                list(APPEND CMAKE_CXX_CPPCHECK --error-exitcode=2)
            endif()

            # Set C CppCheck
            set(CMAKE_C_CPPCHECK ${CMAKE_CXX_CPPCHECK})
        endif()
    endif()

    # Include-What-You-Use (IWYU)
    if(STATIC_ANALYZER_IWYU)
        find_program(IWYU include-what-you-use iwyu REQUIRED)

        # YWYU not found on Path
        if(NOT IWYU)
            message(WARNING "Static Analyzer iwyu was Requested but cannot be found on path")
        else()
            # Set C++ IWYU
            set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${IWYU})
        endif()
    endif()

    # Static Analysis in Visual Code
    if(STATIC_ANALYZER_VISUAL_STUDIO)
        set(VS_ANALYSIS_RULESET "AllRules.ruleset")

        # Disable Clang-Tidy if not configured
        if(NOT "${CMAKE_CXX_CLANG_TIDY}" STREQUAL "")
            set(_VS_CLANG_TIDY "true")
        else()
            set(_VS_CLANG_TIDY "false")
        endif()

        # Set properties only if we are generating a visual studio project
        if(CMAKE_GENERATOR MATCHES "Visual Studio")
            get_all_targets(_targets_list)

            foreach(target IN LISTS ${_targets_list})
                set_target_properties(
                    ${target}
                    PROPERTIES VS_GLOBAL_EnableMicrosoftCodeAnalysis true
                    VS_GLOBAL_CodeAnalysisRuleSet "${VS_ANALYSIS_RULESET}"
                    VS_GLOBAL_EnableClangTidyCodeAnalysis "${_VS_CLANG_TIDY}")
            endforeach()
        else()
            message(
                STATUS
                "VS static analysis was enabled but we aren't generating a visual studio project. Ignoring ..."
            )
        endif()
    endif()
endfunction()

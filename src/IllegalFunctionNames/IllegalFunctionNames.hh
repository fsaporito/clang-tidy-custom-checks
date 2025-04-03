#pragma once

#include <clang-tidy/ClangTidyCheck.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <string>

namespace clang
{
    namespace tidy
    {
        namespace my_checks
        {

            class IllegalFunctionNamesCheck: public ClangTidyCheck
            {
              public:
                IllegalFunctionNamesCheck(clang::StringRef Name, clang::tidy::ClangTidyContext* Context)
                    : ClangTidyCheck(Name, Context)
                {}

                void registerMatchers(ast_matchers::MatchFinder* Finder) override;
                void check(const ast_matchers::MatchFinder::MatchResult& Result) override;

              private:
                std::string m_check_name = "forbidenFunctionNames";
            };

        }   // namespace my_checks
    }   // namespace tidy
}   // namespace clang

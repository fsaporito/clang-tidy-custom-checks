#include <clang/AST/AST.h>

#include "IllegalFunctionNames/IllegalFunctionNames.hh"

namespace clang
{
    namespace tidy
    {
        namespace my_checks
        {

            void IllegalFunctionNamesCheck::registerMatchers(clang::ast_matchers::MatchFinder* Finder)
            {

                // Match functions and methods specific names
                Finder->addMatcher(
                    clang::ast_matchers::functionDecl(clang::ast_matchers::hasName("function")).bind("function"),
                    this);
            }

            void IllegalFunctionNamesCheck::check(const clang::ast_matchers::MatchFinder::MatchResult& Result)
            {
                if (const FunctionDecl* FD =
                        Result.Nodes.getNodeAs<FunctionDecl>("function"))
                {
                    diag(FD->getLocation(), "Function '%0' is named 'function' which isn't allowed") << FD;
                }
                else if (const FunctionDecl* FD =
                             Result.Nodes.getNodeAs<FunctionDecl>("my_method"))
                {
                    diag(FD->getLocation(), "Function '%0' is named 'my_method' which isn't allowed") << FD;
                }
            }

        }   // namespace my_checks
    }   // namespace tidy
}   // namespace clang

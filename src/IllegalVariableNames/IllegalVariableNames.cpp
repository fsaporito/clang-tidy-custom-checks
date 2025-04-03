#include <clang/AST/AST.h>

#include "IllegalVariableNames/IllegalVariableNames.hh"

namespace clang
{
    namespace tidy
    {
        namespace my_checks
        {

            void IllegalVariableNamesCheck::registerMatchers(clang::ast_matchers::MatchFinder* Finder)
            {

                // For each variable we also don't want leading m_ and trailing _
                // For example for "pippo" we also don't want
                // pippo
                // pippo_
                // m_pippo
                // m_pippo_
                std::string pippo          = "pippo";
                std::string pippo_regex    = "^m_?" + pippo + "(_)?";
                std::string pluto          = "pluto";
                std::string pluto_regex    = "^m_?" + pluto + "(_)?";
                std::string paperino       = "paperino";
                std::string paperino_regex = "^m_?" + paperino + "(_)?";

                // Match variable declarations and field declarations with specific names.
                Finder->addMatcher(
                    clang::ast_matchers::decl(
                        clang::ast_matchers::anyOf(
                            clang::ast_matchers::varDecl(clang::ast_matchers::hasName(pippo)),
                            clang::ast_matchers::fieldDecl(clang::ast_matchers::matchesName(pippo_regex)),
                            clang::ast_matchers::varDecl(clang::ast_matchers::hasName(pluto)),
                            clang::ast_matchers::fieldDecl(clang::ast_matchers::matchesName(pluto_regex)),
                            clang::ast_matchers::varDecl(clang::ast_matchers::hasName(paperino)),
                            clang::ast_matchers::fieldDecl(clang::ast_matchers::matchesName(paperino_regex))))
                        .bind(m_check_name),
                    this);
            }

            void IllegalVariableNamesCheck::check(const clang::ast_matchers::MatchFinder::MatchResult& Result)
            {
                const auto* MatchedDecl = Result.Nodes.getNodeAs<clang::NamedDecl>(m_check_name);
                if (!MatchedDecl)
                    return;

                diag(MatchedDecl->getLocation(),
                     "Variable or field '%0' is excluded by naming convention.")
                    << MatchedDecl->getName();
            }

        }   // namespace my_checks
    }   // namespace tidy
}   // namespace clang

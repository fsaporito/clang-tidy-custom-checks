#include <clang-tidy/ClangTidy.h>
#include <clang-tidy/ClangTidyModule.h>
#include <clang-tidy/ClangTidyModuleRegistry.h>

#include "IllegalFunctionNames/IllegalFunctionNames.hh"
#include "IllegalVariableNames/IllegalVariableNames.hh"


std::string check_suite_name = "my-checks";

class MyChecksPlugin: public clang::tidy::ClangTidyModule
{
  public:
    void addCheckFactories(clang::tidy::ClangTidyCheckFactories& CheckFactories) override
    {
        CheckFactories.registerCheck<clang::tidy::my_checks::IllegalVariableNamesCheck>(check_suite_name + "-forbidden-variable-names");
        CheckFactories.registerCheck<clang::tidy::my_checks::IllegalFunctionNamesCheck>(check_suite_name + "-forbidden-function-names");
    }
};

namespace clang
{
    namespace tidy
    {
        static clang::tidy::ClangTidyModuleRegistry::Add<::MyChecksPlugin> MyChecksPluginInit(check_suite_name, "Custom LLF checks");

        // This anchor is used to force the linker to link in the generated object file and thus register the module.
        volatile int MyChecksPluginAnchorSource = 0;
    }   // namespace tidy
}   // namespace clang

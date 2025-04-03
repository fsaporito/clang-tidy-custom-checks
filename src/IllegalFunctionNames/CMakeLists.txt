set(IllegalFunctionNamesLibName "IllegalFunctionNames")
set(IllegalFunctionNamesLibName "IllegalFunctionNames" PARENT_SCOPE)

add_library(${IllegalFunctionNamesLibName} STATIC IllegalFunctionNames.cpp IllegalFunctionNames.hh)

if(WIN32
   OR MSVC
   OR MSYS
   OR MINGW) # Windows: lib extension
    set_target_properties(${IllegalFunctionNamesLibName} PROPERTIES SUFFIX ".lib")
elseif(UNIX AND NOT (APPLE)) # Linux: so extension
    set_target_properties(${IllegalFunctionNamesLibName} PROPERTIES SUFFIX ".so")
endif()

message(STATUS " - Target ${IllegalFunctionNamesLibName} created successfully")

target_include_directories(${IllegalFunctionNamesLibName} PRIVATE ${CLANG_INCLUDE_DIRS})
target_include_directories(${IllegalFunctionNamesLibName} PRIVATE "/usr/include/clang-tidy")

target_link_libraries(${IllegalFunctionNamesLibName} PUBLIC ProjectConfiguration
    clangTooling
    clangBasic
    clangASTMatchers)

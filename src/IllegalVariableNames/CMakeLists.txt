set(IllegalVariableNamesLibName "IllegalVariableNames")
set(IllegalVariableNamesLibName "IllegalVariableNames" PARENT_SCOPE)

add_library(${IllegalVariableNamesLibName} STATIC IllegalVariableNames.cpp IllegalVariableNames.hh)

if(WIN32
    OR MSVC
    OR MSYS
    OR MINGW) # Windows: lib extension
    set_target_properties(${IllegalVariableNamesLibName} PROPERTIES SUFFIX ".lib")
elseif(UNIX AND NOT(APPLE)) # Linux: so extension
    set_target_properties(${IllegalVariableNamesLibName} PROPERTIES SUFFIX ".so")
endif()

message(STATUS " - Target ${IllegalVariableNamesLibName} created successfully")

target_include_directories(${IllegalVariableNamesLibName} PRIVATE ${CLANG_INCLUDE_DIRS})
target_include_directories(${IllegalVariableNamesLibName} PRIVATE "/usr/include/clang-tidy")

target_link_libraries(${IllegalVariableNamesLibName} PUBLIC ProjectConfiguration
    clangTooling
    clangBasic
    clangASTMatchers)

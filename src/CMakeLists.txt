# Add IllegalVariableNamesCheck
message("Adding Custom Check: IllegalVariableNames")
add_subdirectory(IllegalVariableNames)

# Define Library Name
set(libraryName "CustomClangTidyChecks")
set(libraryName "CustomClangTidyChecks" PARENT_SCOPE)

# Define Library Target
add_library(${libraryName} STATIC CustomClangTidyChecks.cpp)

# Specify Target Extension
if(WIN32
    OR MSVC
    OR MSYS
    OR MINGW) # Windows: lib extension
    set_target_properties(${libraryName} PROPERTIES SUFFIX ".lib")
elseif(UNIX AND NOT(APPLE)) # Linux: so extension
    set_target_properties(${libraryName} PROPERTIES SUFFIX ".so")
endif()

message(STATUS " - Target ${libraryName} created successfully")

target_include_directories(${libraryName} PRIVATE ${CLANG_INCLUDE_DIRS})
target_include_directories(${libraryName} PRIVATE "/usr/include/clang-tidy")

# Link all the custom checks
target_link_libraries(${libraryName} PUBLIC IllegalVariableNames ProjectConfiguration
    clangTooling
    clangBasic
    clangASTMatchers)

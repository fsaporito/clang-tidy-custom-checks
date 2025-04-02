include_guard()

set(CMAKE_MODULES_FOLDER ${CMAKE_CUSTOM_MODULES_PATH})

include(${CMAKE_MODULES_FOLDER}/create_optimization_flags.cmake)
include(${CMAKE_MODULES_FOLDER}/create_warnings_list.cmake)
include(${CMAKE_MODULES_FOLDER}/default_options.cmake)
include(${CMAKE_MODULES_FOLDER}/enable_static_analysis.cmake)

cmake_minimum_required(VERSION 3.0.0)
project(curve-editor VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(wxWidgets)
add_executable(curve-editor source/main.cpp)
target_link_libraries(curve-editor wx::core)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

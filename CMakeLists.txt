cmake_minimum_required(VERSION 3.0.0)
project(file_operation VERSION 0.1.0 LANGUAGES C CXX)

add_executable(file_operation main.cpp)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 17)
include(CPack)

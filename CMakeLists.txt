cmake_minimum_required(VERSION 3.15)

project(storica)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(storica src/main.cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBGIT2 REQUIRED libgit2)

target_link_libraries(storica PRIVATE ${LIBGIT2_LIBRARIES})
target_include_directories(storica PRIVATE ${LIBGIT2_INCLUDE_DIRS})
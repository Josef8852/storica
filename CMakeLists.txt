cmake_minimum_required(VERSION 3.15)
project(storica)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

add_executable(storica src/main.cpp src/reader.cpp src/cache.cpp src/analyzer.cpp)
target_include_directories(storica PRIVATE include)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBGIT2 REQUIRED libgit2)

target_link_libraries(storica PRIVATE 
    ${LIBGIT2_LIBRARIES}
    nlohmann_json::nlohmann_json
)
target_include_directories(storica PRIVATE ${LIBGIT2_INCLUDE_DIRS})
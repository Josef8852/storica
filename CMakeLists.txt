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

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG v6.1.9  
)
 
FetchContent_MakeAvailable(ftxui)
 

add_executable(
storica
src/main.cpp
src/reader.cpp 
src/cache.cpp 
src/analyzer.cpp
src/tui.cpp
)


find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBGIT2 REQUIRED libgit2)

target_link_libraries(storica PRIVATE 
    ${LIBGIT2_LIBRARIES}
    nlohmann_json::nlohmann_json
    ftxui::screen
    ftxui::dom
    ftxui::component
)

target_include_directories(storica PRIVATE include ${LIBGIT2_INCLUDE_DIRS})
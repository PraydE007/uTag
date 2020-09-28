cmake_minimum_required(VERSION 3.18.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/..")

add_compile_options(
    "-std=c++17"
    "-Wall"
    "-Wextra"
    "-Wpedantic"
    "-Werror"
    "-pthread"
)

set(CPPS
    "main.cpp"
)

# GTKmm
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
link_libraries(${GTKMM_LIBRARIES})

add_subdirectory("src")
add_executable(${PROJECT_NAME} ${CPPS})
target_link_libraries(${PROJECT_NAME} "src")
include_directories("src")

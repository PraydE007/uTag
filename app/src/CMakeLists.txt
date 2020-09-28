cmake_minimum_required(VERSION 3.18.2)

project("src")

add_compile_options(
    "-std=c++17"
    "-Wall"
    "-Wextra"
    "-Wpedantic"
    "-Werror"
    "-pthread"
)

set(CPPS
    "Form.cpp"
    "Editor.cpp"
    "TagFile.cpp"
)

# GTKmm
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})
link_libraries(${GTKMM_LIBRARIES})

# message("include_directories \$\{GTKMM_INCLUDE_DIRS\} ${GTKMM_INCLUDE_DIRS}\n\n")
# message("link_directories \$\{GTKMM_LIBRARY_DIRS\} ${GTKMM_LIBRARY_DIRS}\n\n")
# message("link_libraries \$\{GTKMM_LIBRARIES\} ${GTKMM_LIBRARIES}\n\n")

include_directories("../../3dparty/lib1")
link_directories("../../3dparty/lib1")
link_libraries("taglib")

add_library("src" ${CPPS})

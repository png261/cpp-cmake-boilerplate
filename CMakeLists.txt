cmake_minimum_required(VERSION 3.14...3.22)

project(cpp-template-starter LANGUAGES CXX)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        FATAL_ERROR
            "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif()

set(AUTHOR_NAME "")
set(AUTHOR_GITHUB "")
set(AUTHOR_GMAIL "")
set(PROJECT_GITHUB_URL "")
set(PROJECT_SUMMARY "cpp template starter")
set(PROJECT_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(PROJECT_DESCRIPTION "${PROJECT_SOURCE_DIR}/README.md")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(useGoldLinker)

add_subdirectory(external)
add_subdirectory(data)
add_subdirectory(source)
add_subdirectory(packaging)

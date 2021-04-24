cmake_minimum_required(VERSION 3.5)

if(${CMAKE_VERSION} VERSION_LESS 3.5)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(plusblocks  VERSION 1.0
    DESCRIPTION "dwmblocks written in C++"
    LANGUAGES CXX)

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_ASM_COMPILER gcc)
set(CMAKE_LINKER ld)
set(CMAKE_STRIP strip)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." TRUE)

if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
       add_compile_options (-fdiagnostics-color=always)
    endif ()
endif ()

add_compile_options(-Wall)
add_compile_options(-Wextra)
add_compile_options(-Werror=missing-declarations)

add_subdirectory(lib)

add_executable(plusblocks src/main.cpp)

target_link_libraries(plusblocks PRIVATE LibBlock)

# Libraries
add_library(LibBlock
    LibBlock.cpp
    LibBlock.h
    )

target_include_directories(LibBlock PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

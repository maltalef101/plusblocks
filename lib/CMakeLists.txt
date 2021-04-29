# Libraries
add_library(LibBlock
    LibBlock.cpp
    LibBlock.h
    )

target_link_libraries(LibBlock X11)

target_include_directories(LibBlock PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

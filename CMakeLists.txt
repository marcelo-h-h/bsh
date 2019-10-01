cmake_minimum_required (VERSION 3.15)
project (bsh)

set (BSH_VERSION_MAJOR 0)
set (BSH_VERSION_MINOR 0)
set (BSH_VERSION_PATCH 1)

configure_file (include/bsh.h.in include/bsh.h)

add_subdirectory(src)
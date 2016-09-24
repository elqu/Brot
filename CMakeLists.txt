cmake_minimum_required(VERSION 2.8.12)

project(Brot)

set(BROT_VERSION_MAJOR 0)
set(BROT_VERSION_MINOR 1)
set(BROT_VERSION_PATCH 0)

include_directories(include "${PROJECT_BINARY_DIR}/src")

configure_file(ycm_extra_conf.py.in "${PROJECT_SOURCE_DIR}/.ycm_extra_conf.py" @ONLY)

add_subdirectory(src)

cmake_minimum_required(VERSION 2.8)
# Set this to the path, relative or absolute, to the libfxcg root folder
SET(CMAKE_MODULE_PATH ../../)
# No need to touch this
SET(CMAKE_TOOLCHAIN_FILE ${CMAKE_MODULE_PATH}/toolchain/Prizm.cmake)

project(example1)

file(GLOB EXAMPLE1_SRC "src/example1/*.c*")

add_executable(example1 ${EXAMPLE1_SRC})
# [Project name] [Add-in name on-calc] [Unselected image] [Selected image]
makeg3a(example1 "example" "unselected.bmp" "selected.bmp")

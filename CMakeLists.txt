cmake_minimum_required(VERSION 3.29.5)
project(zprobe-cli VERSION "1.0.0" LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64 -O3 -g -Wall -Wextra -Werror -fPIE")
set(CMAKE_C_COMPILER "/usr/bin/gcc")

include_directories(${CMAKE_SOURCE_DIR}/lib/curl)
add_subdirectory(lib)

add_executable(zprobe-cli zprobe.c)
target_link_libraries(zprobe-cli PRIVATE prober misc curl)

set_target_properties(zprobe-cli PROPERTIES INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
set_target_properties(zprobe-cli PROPERTIES BUILD_RPATH ${CMAKE_INSTALL_PREFIX}/bin)

install(TARGETS zprobe-cli DESTINATION bin)
install(TARGETS prober DESTINATION lib)

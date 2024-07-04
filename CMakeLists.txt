cmake_minimum_required(VERSION 3.29.5)
project(zprobe-cli VERSION "1.0.0" LANGUAGES C)
set(C_FLAGGERS "-m64 -O3 -fstack-protector-all -Wall -Wextra -Werror -fPIE")
# set(C_FLAGGERS "-m64 -O3 -g -Wall -Wextra -Werror")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C_FLAGGERS}")
set(CMAKE_C_COMPILER "/usr/bin/gcc")

include(CPack)
include(CTest)
enable_testing()
add_test(NAME "ZPROBE TEST" COMMAND zprobe-cli)

include_directories(${CMAKE_SOURCE_DIR}/lib/curl)
add_subdirectory(lib)

add_executable(zprobe-cli zprobe.c)
target_link_libraries(zprobe-cli PRIVATE prober misc curl memutils)

set_target_properties(zprobe-cli PROPERTIES INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
set_target_properties(zprobe-cli PROPERTIES BUILD_RPATH ${CMAKE_INSTALL_PREFIX}/bin)

install(TARGETS zprobe-cli DESTINATION bin)
install(TARGETS prober DESTINATION lib)
install(TARGETS memutils DESTINATION lib)

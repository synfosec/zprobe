add_library(prober SHARED probe.c probe.h)
add_library(misc STATIC misc.c misc.h)
add_library(memutils SHARED memutils.c memutils.h)
add_library(curl SHARED IMPORTED)

set_target_properties(curl PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/curl/libcurl.so.4.8.0")

cmake_minimum_required (VERSION 2.6)
project (utf8totex)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -W -Wall -Wextra")
add_definitions (-D_XOPEN_SOURCE=700)

if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE Release)
endif (NOT CMAKE_BUILD_TYPE)
if (CMAKE_BUILD_TYPE MATCHES Debug)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb")
else (CMAKE_BUILD_TYPE MATCHES Debug)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -DNDEBUG")
endif (CMAKE_BUILD_TYPE MATCHES Debug)

include_directories(include)

add_library (utf8totex src/from_char.c src/from_str.c src/fputs.c src/get_utf8_char.c)
add_executable (utf8totex-bin exe/utf8totex.c)
set_target_properties (utf8totex-bin PROPERTIES OUTPUT_NAME utf8totex)
target_link_libraries (utf8totex-bin utf8totex)

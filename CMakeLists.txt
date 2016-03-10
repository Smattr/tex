cmake_minimum_required (VERSION 2.6)
project (tex)

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

add_library (tex src/tex_from_char.c src/tex_from_str.c src/tex_fputs.c src/get_utf8_char.c)
add_executable (to_tex src/to_tex.c)
target_link_libraries (to_tex tex)

cmake_minimum_required (VERSION 2.6)
project (glPrimitives)
find_package (OpenGL)
find_package (GLUT)
set(CMAKE_VERBOSE_MAKEFILE ON)
if(UNIX)
include_directories(/usr/include)
endif()

add_executable (gp main.cpp)
target_link_libraries (gp ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})


cmake_minimum_required (VERSION 2.6)
project (Lighting)
find_package (OpenGL)
find_package (GLUT)
include_directories(../../MathGL)

add_executable (light main.cpp)
    
target_link_libraries (light ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})


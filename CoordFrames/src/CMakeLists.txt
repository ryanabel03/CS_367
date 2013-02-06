cmake_minimum_required (VERSION 2.6)
project (CoordFrames)
find_package (OpenGL)
find_package (GLUT)

add_executable (cf main.cpp)
target_link_libraries (cf ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})


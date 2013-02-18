cmake_minimum_required (VERSION 2.6)
project (Animation)
find_package (OpenGL)
find_package (GLUT)
include_directories (../../MathGL)

add_executable (anim animation.cc
     Cylinder.cc Cylinder.h
        Model.cc Model.h Wheel.cc Wheel.h Arm.h Arm.cpp)
target_link_libraries (anim ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})

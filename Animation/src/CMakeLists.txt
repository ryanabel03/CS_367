cmake_minimum_required (VERSION 2.6)
project (Animation)
find_package (OpenGL)
find_package (GLUT)

if(NOT GLUT_FOUND)
if(WIN32)
FIND_LIBRARY (GLUT_LIBRARIES
    NAMES glut32
    PATHS ${OPENGL_LIB_DIRECTORY})
endif(WIN32)
endif(NOT GLUT_FOUND)

include_directories (../../MathGL)

add_executable (anim animation.cc
     Cylinder.cc Cylinder.h
        Model.cc Model.h Wheel.cc Wheel.h Arm.h Arm.cpp)
target_link_libraries (anim ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})

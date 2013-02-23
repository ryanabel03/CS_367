cmake_minimum_required (VERSION 2.6)
project (CoordFrames)
find_package (OpenGL REQUIRED)
find_package (GLUT)
if(NOT GLUT_FOUND)
if(WIN32)
FIND_LIBRARY (GLUT_LIBRARIES
    NAMES glut32
    PATHS ${OPENGL_LIB_DIRECTORY})
endif(WIN32)
endif(NOT GLUT_FOUND)
include_directories(../../MathGL)
add_executable (cf main.cpp CoordFrame.h CoordFrame.cpp 
Transformation.h Translation.h Translation.cpp
Rotation.h Rotation.cpp)
    
target_link_libraries (cf ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})


cmake_minimum_required (VERSION 2.6)
project (CoordFrames)
find_package (OpenGL)
find_package (GLUT)
include_directories(../../MathGL)

add_executable (cf main.cpp CoordFrame.h CoordFrame.cpp 
Transformation.h Translation.h Translation.cpp
Rotation.h Rotation.cpp)
    
target_link_libraries (cf ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})


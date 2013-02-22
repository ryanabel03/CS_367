cmake_minimum_required (VERSION 2.6)
project (Lighting)
find_package (OpenGL)
find_package (GLUT)
if(NOT GLUT_FOUND)
if(WIN32)
FIND_LIBRARY (GLUT_LIBRARIES
    NAMES glut32
    PATHS ${OPENGL_LIB_DIRECTORY})
endif(WIN32)
endif(NOT GLUT_FOUND)

include_directories(../../MathGL)

add_executable (light main.cpp)
    
target_link_libraries (light ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})


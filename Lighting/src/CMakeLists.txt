cmake_minimum_required (VERSION 2.6)
project (Lighting)

find_package (OpenGL)
if(UNIX)
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
set(GLUT_glut_LIBRARY "/usr/lib/x86_64-linux-gnu")
set(GLUT_Xmu_LIBRARY "/usr/lib/x86_64-linux-gnu")
set(GLUT_LIBRARIES "-lglut")
else()
find_package (GLUT)
endif()
endif(UNIX)

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


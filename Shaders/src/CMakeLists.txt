cmake_minimum_required (VERSION 2.6)
project (Shaders)
find_package (OpenGL REQUIRED)
find_package (GLUT)
if(NOT GLUT_FOUND)
if(WIN32)
FIND_LIBRARY (GLUT_LIBRARIES
    NAMES glut32
    PATHS ${OPENGL_LIB_DIRECTORY})
endif(WIN32)
endif(NOT GLUT_FOUND)

add_executable (shdr main.cpp Shader.h Shader.cpp)
    
target_link_libraries (shdr ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})


cmake_minimum_required(VERSION 3.7)
project(mxyzptlk_v2)

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
link_directories(${GLUT_LIBRARY_DIR})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)


find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)


set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES base_opengl.c util/Vectors.c util/Vectors.h util/Text.h util/Text.c util/Colors.h util/Colors.c util/Collections.h util/Collections.c res/Splines.c res/Splines.h)
add_executable(mxyzptlk_v2 ${SOURCE_FILES})

target_link_libraries(mxyzptlk_v2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
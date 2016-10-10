cmake_minimum_required(VERSION 3.4)
project(Assignment02)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m64")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework GLUT -framework OpenGL -lglui")

set(SOURCE_FILES main.cpp Line.cpp Line.h Shader.cpp Shader.h  pen.cpp pen.h Bezier.cpp Bezier.h PiecewiseBezier.cpp PiecewiseBezier.h InterpolationCurve.cpp InterpolationCurve.h Tangent.cpp)




#find_package(GLEW REQUIRED)
#if (GLEW_FOUND)
#   include_directories($(GLEW_INCLUDE_DIRS))
#endif()

#find_package(OpenGL)


#find_package(PkgConfig REQUIRED)
#pkg_search_module(GLFW REQUIRED glfw3)
#include_directories(${GLFW_INCLUDE_DIRS})

#pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

#include_directories(${GTK3_INCLUDE_DIRS})
#link_directories(${GTK3_LIBRARY_DIRS})

#add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(Assignment02 ${SOURCE_FILES})
target_link_libraries(Assignment02)
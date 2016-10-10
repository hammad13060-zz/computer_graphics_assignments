#OS X compilation flags
GLM_PATH=/Users/ojaswa/dev/glm/
CPPFLAGS=-Wno-deprecated-declarations -I. -I${GLM_PATH}
LDFLAGS= -framework GLUT -framework OpenGL -lstdc++

#Linux compilation flags
#CPPFLAGS=
#LDFLAGS= -L/usr/X11R6/lib -L/usr/local/lib -lGL -lGLU -lm -lglut -lGLEW -lstdc++

assignment03: main.cpp shader_utils.cpp shader_utils.h gl_utils.h gl_utils.cpp
	clang -o assignment03 main.cpp shader_utils.cpp gl_utils.cpp ${CPPFLAGS} ${LDFLAGS}

 clean:
	-rm -f assignment03

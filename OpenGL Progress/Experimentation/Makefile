OPENGLLIB= -framework OpenGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN1=bin/exp
BIN2=bin/transform
SRCS1=exp.cpp utility/readfile.cpp utility/shader.cpp  Textures/texture.cpp
SRCS2=transform.cpp utility/readfile.cpp utility/shader.cpp  Textures/texture.cpp

INCLUDES=utility/readfile.hpp utility/shader.hpp Textures/texture.hpp

all:  $(BIN2)
$(BIN1): $(SRCS1) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS1) -o $(BIN1) $(LDFLAGS) $(LIBS)
$(BIN2): $(SRCS2) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS2) -o $(BIN2) $(LDFLAGS) $(LIBS)	
clean:
	rm -f *~ *.o $(BIN1) 

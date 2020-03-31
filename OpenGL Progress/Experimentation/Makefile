OPENGLLIB= -framework OpenGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN1=bin/exp

SRCS1=exp.cpp utility/readfile.cpp utility/shader.cpp  Textures/texture.cpp

INCLUDES=utility/readfile.hpp utility/shader.hpp Textures/texture.hpp

all: $(BIN1) 
$(BIN1): $(SRCS1) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS1) -o $(BIN1) $(LDFLAGS) $(LIBS)
	
clean:
	rm -f *~ *.o $(BIN1) 

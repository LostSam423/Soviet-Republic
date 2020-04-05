OPENGLLIB= -framework OpenGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN1=bin/exp
BIN2=bin/transform
BIN3=bin/into3d
SRCS1=exp.cpp utility/readfile.cpp utility/shader.cpp  Textures/texture.cpp
SRCS2=transform.cpp utility/readfile.cpp utility/shader.cpp  Textures/texture.cpp
SRCS3=into3d.cpp utility/readfile.cpp utility/shader.cpp  Textures/texture.cpp

INCLUDES=utility/readfile.hpp utility/shader.hpp Textures/texture.hpp

all: $(BIN1) $(BIN2) $(BIN3)
$(BIN1): $(SRCS1) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS1) -o $(BIN1) $(LDFLAGS) $(LIBS)
$(BIN2): $(SRCS2) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS2) -o $(BIN2) $(LDFLAGS) $(LIBS)
$(BIN3): $(SRCS3) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS3) -o $(BIN3) $(LDFLAGS) $(LIBS)		
clean:
	rm -f *~ *.o $(BIN1) 

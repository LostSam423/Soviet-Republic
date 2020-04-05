OPENGLLIB= -framework OpenGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN1=bin/ring
BIN2=bin/disk
BIN3=bin/f
BIN4=bin/chessboard
SRCS1=ring.cpp utility/readfile.cpp utility/shader.cpp  Textures/texture.cpp
SRCS2=disk.cpp utility/readfile.cpp utility/shader.cpp Textures/texture.cpp
SRCS3=f.cpp utility/readfile.cpp utility/shader.cpp Textures/texture.cpp
SRCS4=chessboard.cpp utility/readfile.cpp utility/shader.cpp Textures/texture.cpp
INCLUDES=utility/readfile.hpp utility/shader.hpp Textures/texture.hpp

all: $(BIN1) $(BIN2) $(BIN3) $(BIN4)
$(BIN1): $(SRCS1) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS1) -o $(BIN1) $(LDFLAGS) $(LIBS)
$(BIN2): $(SRCS2) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS2) -o $(BIN2) $(LDFLAGS) $(LIBS)	
$(BIN3): $(SRCS3) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS3) -o $(BIN3) $(LDFLAGS) $(LIBS)	
$(BIN4): $(SRCS4) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS4) -o $(BIN4) $(LDFLAGS) $(LIBS)	
clean:
	rm -f *~ *.o $(BIN1) 

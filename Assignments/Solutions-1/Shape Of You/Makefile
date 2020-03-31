OPENGLLIB= -framework OpenGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN1=ring
BIN2=disk
BIN3=f
SRCS1=ring.cpp readfile.cpp shader.cpp  
SRCS2=disk.cpp readfile.cpp shader.cpp
SRCS3=f.cpp readfile.cpp shader.cpp
INCLUDES=readfile.hpp shader.hpp

all: $(BIN1) $(BIN2) $(BIN3)
$(BIN1): $(SRCS1) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS1) -o $(BIN1) $(LDFLAGS) $(LIBS)
$(BIN2): $(SRCS2) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS2) -o $(BIN2) $(LDFLAGS) $(LIBS)	
$(BIN3): $(SRCS3) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS3) -o $(BIN3) $(LDFLAGS) $(LIBS)	
clean:
	rm -f *~ *.o $(BIN1) 

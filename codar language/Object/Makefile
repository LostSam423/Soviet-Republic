OPENGLLIB= -framework OpenGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN6=bin/statement

SRC6=statement.cpp utility/readfile.cpp utility/shader.cpp utility/camera.cpp  Textures/texture.cpp utility/skybox.cpp 


all:  $(BIN6)

$(BIN6): $(SRC6) 
	g++ $(CPPFLAGS) $(SRC6) -o $(BIN6) $(LDFLAGS) $(LIBS)
clean:
	rm -f *~ *.o  $(BIN6)

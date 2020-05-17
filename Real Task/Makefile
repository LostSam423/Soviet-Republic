OPENGLLIB= -framework OpenGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN1=bin/earth

SRC1=earth.cpp utility/readfile.cpp utility/shader.cpp utility/camera.cpp  Textures/texture.cpp utility/skybox.cpp 


all:  $(BIN1)

$(BIN1): $(SRC1) 
	g++ $(CPPFLAGS) $(SRC1) -o $(BIN1) $(LDFLAGS) $(LIBS)
clean:
	rm -f *~ *.o  $(BIN1)

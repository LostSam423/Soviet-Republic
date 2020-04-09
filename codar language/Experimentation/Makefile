OPENGLLIB= -framework OpenGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN1=bin/exp
BIN2=bin/transform
BIN3=bin/into3d
BIN4=bin/cameraexp
BIN5=bin/cubemaptest
BIN6=bin/colors
BIN7=bin/lightemup
BIN8=bin/materialistic
BIN9=bin/mapthelights
SRCS1=exp.cpp utility/readfile.cpp utility/shader.cpp  Textures/texture.cpp
SRCS2=transform.cpp utility/readfile.cpp utility/shader.cpp  Textures/texture.cpp
SRCS3=into3d.cpp utility/readfile.cpp utility/shader.cpp  Textures/texture.cpp
SRCS4=cameraexp.cpp utility/readfile.cpp utility/shader.cpp utility/camera.cpp  Textures/texture.cpp
SRCS5=cubemaptest.cpp utility/readfile.cpp utility/shader.cpp utility/camera.cpp  Textures/texture.cpp
SRCS6=colors.cpp utility/readfile.cpp utility/shader.cpp utility/camera.cpp  Textures/texture.cpp
SRCS7=lightemup.cpp utility/readfile.cpp utility/shader.cpp utility/camera.cpp  Textures/texture.cpp
SRCS8=materialistic.cpp utility/readfile.cpp utility/shader.cpp utility/camera.cpp  Textures/texture.cpp
SRCS9=mapthelights.cpp utility/readfile.cpp utility/shader.cpp utility/camera.cpp  Textures/texture.cpp
INCLUDES=utility/readfile.hpp utility/shader.hpp utility/camera.hpp Textures/texture.hpp

all: $(BIN1) $(BIN2) $(BIN3) $(BIN4) $(BIN5) $(BIN6) $(BIN7) $(BIN8) $(BIN9)
$(BIN1): $(SRCS1) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS1) -o $(BIN1) $(LDFLAGS) $(LIBS)
$(BIN2): $(SRCS2) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS2) -o $(BIN2) $(LDFLAGS) $(LIBS)
$(BIN3): $(SRCS3) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS3) -o $(BIN3) $(LDFLAGS) $(LIBS)
	g++ $(CPPFLAGS) $(SRCS2) -o $(BIN2) $(LDFLAGS) $(LIBS)
$(BIN4): $(SRCS4) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS4) -o $(BIN4) $(LDFLAGS) $(LIBS)
$(BIN5): $(SRCS5) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS5) -o $(BIN5) $(LDFLAGS) $(LIBS)	
$(BIN6): $(SRCS6) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS6) -o $(BIN6) $(LDFLAGS) $(LIBS)	
$(BIN7): $(SRCS7) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS7) -o $(BIN7) $(LDFLAGS) $(LIBS)
$(BIN8): $(SRCS8) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS8) -o $(BIN8) $(LDFLAGS) $(LIBS)
$(BIN9): $(SRCS9) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS9) -o $(BIN9) $(LDFLAGS) $(LIBS)
clean:
	rm -f *~ *.o $(BIN1) $(BIN2) $(BIN3) $(BIN4) $(BIN5) $(BIN6) $(BIN7) $(BIN8) $(BIN9)

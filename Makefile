CC=g++
CFLAGS=-std=c++11 -Wall -Wno-deprecated
LDFLAGS=-framework GLUT -framework OpenGL -framework Cocoa
SOURCES=project.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=project

all: $(SOURCES) $(EXECUTABLE)
		$(MAKE) clean

$(EXECUTABLE): $(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
		$(CC) $(CFLAGS) -c $<

clean:
		rm -rf *.o

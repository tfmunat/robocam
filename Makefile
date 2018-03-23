TARGET := main

CXX = g++

SOURCES := ./src/visual.cpp ./src/track.cpp ./src/movement.cpp ./src/main.cpp
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))

SDL_INC=-I/usr/local/include/SDL2
USB_INC=-I/usr/local/include/libusb-1.0

CXXFLAGS := -std=c++11 -g -Wall
CXXFLAGS += -I./include 
CXXFLAGS += $(SDL_INC)
CXXFLAGS += $(USB_INC)

LIBS := -L/usr/local/lib
LIBS += $(shell pkg-config --libs libusb-1.0)
LIBS += $(shell sdl2-config --libs)
LIBS += $(shell pkg-config --libs opencv)

.DEFAULT_TARGET := $(TARGET)
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

help: 
	@echo "usage: ./main red/green/blue/white/black" 
	@echo "usage_2: make run COLOR=red/green/blue/white/black"
	@echo "press 'q' to quit once run"
clean:
	rm -rf *.o *~ main *.dSYM src/*.o

run: $(TARGET)
	./$(TARGET) $(COLOR)

all: clean run

again: clean $(TARGET)

val: $(TARGET)
	valgrind --show-leak-kinds=definite  --leak-check=yes ./$(TARGET) $(COLOR) 

.PHONY: clean run val all again help

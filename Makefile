# Config

local_GSLFLAGS:=$(gsl-config --libs)
local_GSFLAGS:=$(gsl-config --cflags)

# --Make File--

CC = g++
C_FLAGS = -Wall -g -std=c++11
GSL_FLAGS= -lgsl -lgslcblas 

CC_ENGINE = $(wildcard src/engine/*.cpp)
H_ENGINE = $(wildcard src/engine/*.h)
CC_SOURCE = $(wildcard src/*.cpp)
H_SOURCE = $(wildcard src/*.h)

FILE = $(subst src/, , $(CC_SOURCE)) $(subst src/engine/, , $(CC_ENGINE))

BIN = $(addprefix src/bin/,$(FILE:.cpp=.o))


all: bin uti
	
bin: $(BIN)
src/bin/%.o: src/%.cpp src/%.h $(CC_ENGINE) $(H_ENGINE)
	$(CC) $(C_FLAGS) -o $@ -c $< $(GSL_FLAGS)

src/bin/%.o: src/engine/%.cpp src/engine/%.h
	$(CC) $(C_FLAGS) -o $@ -c $< $(GSL_FLAGS)

uti: kamland.cpp $(H_SOURCE) $(H_ENGINE) $(CC_SOURCE) $(CC_ENGINE) $(BIN)
	$(CC) $(C_FLAGS) -o kamland $< $(BIN) $(GSL_FLAGS)

clean:
	rm -f $(BIN) kamland.o

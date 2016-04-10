TARGET = bin/EngineTest

INCLUDE = -I/usr/local/include/SDL2 -I./src/Engine/include

CC = g++
CXXFLAGS = -g -std=c++11 -Wall
LIB = -lSDL2
SRCS = $(shell find ./src -type f -name *.cpp)
OBJS = $(SRCS:%.cpp=%.o)
OSXFW = -framework OpenGL

$(TARGET):$(OBJS)
	$(CC) $(CXXFLAGS) $(LIB) -o $(TARGET) $(OBJS) $(INCLUDE) $(OSXFW)
	$(RM) $(OBJS)

$(OBJS):
	$(CC) -DDEBUG $(CXXFLAGS) $(INCLUDE) -o $@ -c $(@:%.o=%.cpp)

clean:
	$(RM) $(TARGET) $(OBJS)

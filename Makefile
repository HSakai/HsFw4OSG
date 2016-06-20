TARGET = bin/EngineTest

INCLUDE = -I/usr/local/include -I/usr/local/include/SDL2 -I./src/Framework/include
OSG_LIBPATH=/Library/Frameworks
OSG_LDFLAGS = -L$(OSG_LIBPATH)

CC = g++
CXXFLAGS = -g -std=c++11 -Wall
LIB = -L /usr/local/lib -lSDL2
SRCS = $(shell find ./src -type f -name *.cpp)
OBJS = $(SRCS:%.cpp=%.o)
OSG_LIBS = -F /Library/Frameworks -framework osg -framework OpenThreads -framework osgDB -framework osgFX -framework osgGA -framework osgViewer -framework osgUtil
OSXFW=$(OSG_LIBS)

$(TARGET):$(OBJS)
	$(CC) $(CXXFLAGS) $(OSG_LDFLAGS) $(LIB) -o $(TARGET) $(OBJS) $(INCLUDE) $(OSXFW)
	$(RM) $(OBJS)

$(OBJS):
	$(CC) -DDEBUG $(CXXFLAGS) $(INCLUDE) -o $@ -c $(@:%.o=%.cpp)

clean:
	$(RM) $(TARGET) $(OBJS)

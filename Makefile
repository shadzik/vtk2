PREFIX = /usr
bindir = $(PREFIX)/bin
DESTDIR =
SOURCES = vtk2.cpp
OBJECTS = $(SOURCES:%.cpp=%.o)
TARGET = vtk2
CXX	= g++
CXXLD	= $(CXX)
CFLAGS	= -pipe -Wall -W -O2
CXXFLAGS = -pipe -Wall -W -O2
DEL_FILE = rm -f
INSTALL = /usr/bin/install -c

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)
	$(CXXLD) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

clean:
	$(DEL_FILE) $(OBJECTS) $(TARGET)

vtk2.o: vtk2.cpp

install:
	$(INSTALL) $(TARGET) $(DESTDIR)/$(bindir)

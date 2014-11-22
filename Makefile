SHELL = /bin/sh
SRCDIR = src
OBJDIR = obj
# CC = g++
CFLAGS = -std=c++11 -Wall -O2 -I. `pkg-config --cflags gtkmm-3.0`
LDLIBS = -lpthread `pkg-config --libs gtkmm-3.0`
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
EXECUTABLE = quicklaunch

all: $(SOURCES) $(EXECUTABLE)

install: all
	cp $(EXECUTABLE) /usr/bin/
	chmod a+x /usr/bin/$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDLIBS) $(OBJECTS) -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) -g -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJDIR)/*

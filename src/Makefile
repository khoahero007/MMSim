#Compilation
CC = g++
CFLAGS = -c -Wall -std=c++11
LDFLAGS =

#Directory
SRCDIR = src
OBJDIR = obj
BINDIR = bin

#File Source
SOURCES = main.cpp Common.cpp  Test/Test.cpp

#OBJECT AND EXE
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
EXECUTABLE = test

all: $(SRCDIR)/$(SOURCES) $(BINDIR)/$(EXECUTABLE)

$(OBJECTS): 
	

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*
	rm -f $(BINDIR)/*

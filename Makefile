####################################################################################################### 
# 16. Jul. 2020, Editor: Yu-Wei Kao                                                                   #
# 26. Nov. 2018, Editor: Yu-Wei Kao                                                                   #
# References:                                                                                         #
# 1) https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/                      #
# 2) http://mropengate.blogspot.com/2018/01/makefile.html                                             #
# 3) https://stackoverflow.com/questions/5950395/makefile-to-compile-multiple-c-programs              #
# 4) http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/                                     #
# 5) https://www.wooster.edu/_media/files/academics/areas/computer-science/resources/makefile-tut.pdf #
#######################################################################################################
ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs) -lMinuit
ROOTGLIBS     = $(shell root-config --glibs)

CC       := g++ # This is the main compiler
SRCDIR   := src
BUILDDIR := build
TARGET   := bin/hello
OBJ		 := $(BUILDDIR)/hello.o $(BUILDDIR)/main.o
#OBJ		 := $(BUILDDIR)/ctag_reshaping.o $(BUILDDIR)/hello.o

SRCEXT   := cpp
SOURCES  := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS  := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS   := $(shell root-config --cflags) -g -O3 #-Wno-write-strings -D_FILE_OFFSET_BITS=64 -DDROP_CGAL #-Wall -Wextra
LIB      := $(shell root-config --libs) -lMinuit
INC      := -I interface


all: ${TARGET}

build/main.o: src/main.cpp
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/hello.o: interface/hello.cpp interface/hello.h
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

#build/ctag_reshaping.o: interface/ctag_reshaping.cpp
#	@mkdir -p $(BUILDDIR)
#	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

bin/hello: $(OBJ)
	@mkdir -p bin
	@echo "Linking..."
	$(CC) -o $@ $^ $(CFLAGS) $(LIB)

.PHONY: clean

clean:
	@echo " Cleaning..."; 
	$(RM) -r $(BUILDDIR) $(TARGET)

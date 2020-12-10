# Executable names:
EXE = airports
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = graph.o main.o dsets.o database.o DrawGraph.o cs225/HSLAPixel.o #tests/test-database.o cs225/catch/catchmain.o

# Generated files
CLEAN_RM = images/Out.png

# Use the cs225 makefile template:
include cs225.mk

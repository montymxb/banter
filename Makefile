#
# Banter Makefile
# Created 10/19/2018
# Benjamin Friedman
#

# -03 removed, introduced goofy instruction?
CFLAGS+=-Isrc -std=c90 -ansi -fno-common -fshort-enums -pedantic -W -Wall -fno-common -fshort-enums -Wcast-align -Wcast-qual -Wconversion -Wmissing-declarations -Wredundant-decls -Wnested-externs -Wpointer-arith -Wshadow

# detect unix variant
UNAME_S := $(shell uname -s)

# linux check
ifeq ($(UNAME_S), Linux)
	# setup for linux
endif

# darwin (osx) check
# TODO should version check to determine if >= 10.14, where metal is the target renderer
ifeq ($(UNAME_S), Darwin)
	CFLAGS += -framework OpenGL -framework GLUT
endif

EXE=banter
CC=gcc
SRC := $(wildcard src/*.c)
OBJ := ${SRC:src/%.c=build/%.o}
BUILD_DIR=build
SRC_DIR=src

.PHONY: all clean help

# sets it all up
all: prep $(EXE)

prep:
	if [ ! -d build ]; then mkdir $(BUILD_DIR); fi

# builds latria
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(BUILD_DIR)/$(EXE)

# compile all individually
$(OBJ): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

# builds main
#build/main.o: src/main.c
#	$(CC) -c $(CFLAGS) src/main.c -o build/main.o

# cleans the build
clean:
	@- rm -rf *.o $(EXE)
	@- rm -rf build/

help:
	@echo ""
	@echo "::Targets::"
	@echo "make banter"
	@echo "make clean"
	@echo "make help"
	@echo ""

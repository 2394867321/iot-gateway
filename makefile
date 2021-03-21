SRC=$(wildcard *.c)
OBJ:=$(patsubst %.c,%.o,$(SRC))
CC=gcc
TARGET=hello
LIB=
INCLUDE=
RELEASE=release
SYMBOL=debug
DEFS=
CFLAG=-g
$(TARGET):$(OBJ)
	$(CC) $(CFLAG) $(DEFS) $^ -o $@ $(LIB)
$(RELEASE):$(TARGET)
	objcopy --strip-debug $(TARGET) $(TARGET).release
$(DEBUG):$(TARGET)
	objcopy --only-keep-debug $(TARGET) $(TARGET).symbol

.PHONY:
clear:
	rm -rf $(TARGET) $(TARGET).release $(TARGET).symbol

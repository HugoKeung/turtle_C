CFLAGS = `pkg-config sdl2 --cflags` -g -O2 -Wall -Wextra -Wfloat-equal -pedantic -ansi -lm
CS = neillsdl2.h stack.h turtle.h
TARGET = main
SOURCES =  neillsdl2.c stack.c turtle.c $(TARGET).c
LIBS =  `pkg-config sdl2 --libs`
CC = gcc


all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	$(TARGET) 


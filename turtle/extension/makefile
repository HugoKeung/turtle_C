CFLAGS = `pkg-config sdl2 --cflags` -g -O2 -Wall -Wextra -Wfloat-equal -pedantic -ansi -lm
CS = neillsdl2.h stack.h turtle.h auto.h
TARGET = extension
SOURCES =  neillsdl2.c stack.c turtle.c auto.c $(TARGET).c
LIBS =  `pkg-config sdl2 --libs`
CC = gcc


all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	$(TARGET) 


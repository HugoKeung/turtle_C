CFLAGS =  -g -O2  -Wall -Wextra -Wfloat-equal -pedantic -ansi -lm
INCS =  turtle.h
TARGET = main
SOURCES =   turtle.c $(TARGET).c
LIBS =  
CC = gcc


all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	$(TARGET) 


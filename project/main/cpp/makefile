CC = g++
LD = g++

INCDIR = -I/opt/local/include/SDL2
CFLAGS = -g -Wall -c $(INCDIR)
LDFLAGS = -g -Wall -w -lSDL2

all: arduino-serial

SDL_Blank: main.o screen.o serial.o targets.o
	$(LD) $(LDFLAGS) $^ -o $@

screen.o: screen.cpp screen.h
	$(CC) $(CFLAGS) $<

serial.o: serial.cpp serial.h
	$(CC) $(CFLAGS) $<

targets.o: targets.cpp targets.h
	$(CC) $(CFLAGS) $<

clean:
	/bin/rm -f arduino-serial *.o core*

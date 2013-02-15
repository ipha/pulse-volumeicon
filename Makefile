CC=gcc
CFLAGS=-c -Wall `pkg-config --cflags gtk+-2.0 libpulse`
LDFLAGS=`pkg-config --libs gtk+-2.0 libpulse`
SOURCES=pulse-volumeicon.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=pulse-volumeicon

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
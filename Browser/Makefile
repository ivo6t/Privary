CC = gcc
CFLAGS = -Wall -g
GTKFLAGS = $(shell pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0)

.PHONY: all clean gui

all: gui

gui: GUI.o html.o
	$(CC) $(CFLAGS) $(GTKFLAGS) -o gui_browser GUI.o html.o

GUI.o: GUI.c html.h
	$(CC) $(CFLAGS) $(GTKFLAGS) -c GUI.c

html.o: html.c html.h
	$(CC) $(CFLAGS) -c html.c

clean:
	rm -f *.o gui_browser

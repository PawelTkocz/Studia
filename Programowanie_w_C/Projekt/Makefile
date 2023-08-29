CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror $(shell pkg-config gtk+-3.0 --cflags)
LDFLAGS=$(shell pkg-config gtk+-3.0 --libs)
DEPS=kierki_gtk.h kierki_obs.h
NAME=kierki

$(NAME): kierki.o kierki_gtk.o kierki_obs.o
	$(CC) kierki.o kierki_gtk.o kierki_obs.o -o $(NAME) $(LDFLAGS)

kierki.o: kierki.c $(DEPS)
	$(CC) -c $(CFLAGS) kierki.c -o kierki.o

kierki_gtk.o: kierki_gtk.c $(DEPS)
	$(CC) -c $(CFLAGS) kierki_gtk.c -o kierki_gtk.o

kierki_obs.o: kierki_obs.c $(DEPS)
	$(CC) -c $(CFLAGS) kierki_obs.c -o kierki_obs.o

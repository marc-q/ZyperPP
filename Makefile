CC = g++
OBJECTS = src/zyper.cpp
LIBS =
CFLAGS = --std=c++14 -Wall -Wextra -flto -O2
BINDIR = $(DESTDIR)/usr/bin
NAME = zyper

zyper: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBS)

clean:
	rm $(NAME)

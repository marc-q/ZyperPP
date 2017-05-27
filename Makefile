CC = g++
OBJECTS = zyper.cpp
LIBS =
CFLAGS = -Wall -Wextra -O2 --std=c++14
BINDIR = $(DESTDIR)/usr/bin
NAME = zyper

zyper: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBS)

clean:
	rm $(NAME)

CC=gcc
CFLAGS=-Wall
LIBS = -ljson-c -lncurses

.PHONY: clean

all: $(exe)

$(exe): $(src:.c=.o) stdavk.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(exe)

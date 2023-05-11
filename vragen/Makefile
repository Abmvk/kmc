CC=gcc
CFLAGS=-Wall -g
LIBS = -ljson-c

.PHONY: clean

all: $(exe)

$(exe): $(src:.c=.o) stdavk.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(exe)

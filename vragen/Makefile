CC=gcc
CFLAGS=-Wall

.PHONY: clean

all: $(exe)

$(exe): $(src:.c=.o) stdavk.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(exe)

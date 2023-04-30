CC=gcc
CFLAGS=-Wall

.PHONY: clean

all: $(EXE)

$(EXE): $(SRC:.c=.o) stdavk.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXE)

CC=gcc
CFLAGS = -I.
DEPS = rooms.h items.h
OBJ = adventure.o items.o rooms.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

adventure: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)
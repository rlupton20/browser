EXECUTABLE=luna

CC=gcc
GTK_C_FLAGS=`pkg-config --cflags gtk+-3.0`
GTK_LINK_FLAGS=`pkg-config --libs gtk+-3.0`

luna: main.c
	$(CC) $(GTK_C_FLAGS) -o $(EXECUTABLE) main.c $(GTK_LINK_FLAGS)

install:

clean:
	rm -f *.o $(EXECUTABLE)

BINDIR=$(PREFIX)/bin
EXECUTABLE=luna

CC=gcc

GTK_C_FLAGS=`pkg-config --cflags gtk+-3.0`
GTK_LINK_FLAGS=`pkg-config --libs gtk+-3.0`

WEBKIT_C_FLAGS=`pkg-config --cflags webkit2gtk-3.0`
WEBKIT_LINK_FLAGS=`pkg-config --libs webkit2gtk-3.0`

luna: main.c
	$(CC) $(GTK_C_FLAGS) $(WEBKIT_C_FLAGS) -o $(EXECUTABLE) main.c $(GTK_LINK_FLAGS) $(WEBKIT_LINK_FLAGS)

install:
	install -d $(BINDIR)
	install -m 755 $(EXECUTABLE) $(BINDIR)/$(EXECUTABLE)

clean:
	rm -f *.o $(EXECUTABLE)

BINDIR=$(PREFIX)/bin
EXECUTABLE=luna

CC=gcc
C_FLAGS=-g

GUILE_C_FLAGS=`pkg-config --cflags guile-2.0`
GUILE_LINK_FLAGS=`pkg-config --libs guile-2.0`

GTK_C_FLAGS=`pkg-config --cflags gtk+-3.0`
GTK_LINK_FLAGS=`pkg-config --libs gtk+-3.0`

WEBKIT_C_FLAGS=`pkg-config --cflags webkit2gtk-4.0`
WEBKIT_LINK_FLAGS=`pkg-config --libs webkit2gtk-4.0`

LUNA_C_FLAGS = $(GUILE_C_FLAGS) $(GTK_C_FLAGS) $(WEBKIT_C_FLAGS)
LUNA_LINK_FLAGS = $(GUILE_LINK_FLAGS) $(GTK_LINK_FLAGS) $(WEBKIT_LINK_FLAGS)

luna: main.c core.o view.o keyboard.o
	$(CC) $(C_FLAGS) $(LUNA_C_FLAGS) -o $(EXECUTABLE) main.c core.o view.o keyboard.o $(LUNA_LINK_FLAGS)

view.o: view.c
	$(CC) $(C_FLAGS) $(LUNA_C_FLAGS) -o view.o -c view.c 

core.o: core.c
	$(CC) $(C_FLAGS) $(LUNA_C_FLAGS) -o core.o -c core.c 

keyboard.o: keyboard.c
	$(CC) $(C_FLAGS) $(LUNA_C_FLAGS) -o keyboard.o -c keyboard.c 

install:
	install -d $(BINDIR)
	install -m 755 $(EXECUTABLE) $(BINDIR)/$(EXECUTABLE)

clean:
	rm -f *.o $(EXECUTABLE)

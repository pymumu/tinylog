BIN=libtlog.so

CFLAGS +=-O2 -Wall -Wstrict-prototypes -fno-omit-frame-pointer -Wstrict-aliasing -funwind-tables -Wmissing-prototypes -Wshadow -Wextra -Wno-unused-parameter -Wno-implicit-fallthrough

$(BIN): tlog.o
	$(CC) -shared -o $@ $^

install:
	cp $(BIN) /usr/lib64/
	cp tlog.h /usr/include/

clean:
	$(RM) *.o $(BIN)
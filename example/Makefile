OBJS = example.o ../tlog.o
BIN = example
CFLAGS = -g -O0 -I../
LIBS = -lpthread

.PHONY : all

all: $(BIN) 

$(BIN):$(OBJS)
	$(CC) $^ -o $@ $(LIBS)

clean:
	$(RM) $(BIN) $(OBJS)
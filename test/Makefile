OBJS = test.o ../tlog.o

BIN = test
CFLAGS = -Wall -g -O0 -I../
LIBS = -lpthread

.PHONY : all

all: $(BIN) 

$(BIN):$(OBJS)
	$(CC) $^ -o $@ $(LIBS)

clean:
	$(RM) $(BIN) $(OBJS)
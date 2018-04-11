OBJS = test.o tlog.o
BIN = test
CFLAGS = -Wall -g -O0 -I../
LIBS = -lpthread
ROOT_PATH := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
CFLAGS += -I$(ROOT_PATH)../
CFLAGS += -DBASE_FILE_NAME=\"$(notdir $<)\"
VPATH = $(ROOT_PATH) $(ROOT_PATH)../

.PHONY : all

all: $(BIN) 

all: $(BIN) 

$(BIN):$(OBJS)
	$(CC) $^ -o $@ $(LIBS)

clean:
	$(RM) $(BIN) $(OBJS)
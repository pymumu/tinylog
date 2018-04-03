OBJS = example.o tlog.o
BIN = example
CFLAGS = -Wall -g -O0 
LIBS = -lpthread
ROOT_PATH := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
CFLAGS += -I$(ROOT_PATH)../
VPATH = $(ROOT_PATH) $(ROOT_PATH)../
.PHONY : all

all: $(BIN) 

%.o : %.c
	$(CC) $(CFLAGS) -DBASE_FILE_NAME=\"$(notdir $<)\" -c $< -o $@

$(BIN):$(OBJS)
	$(CC) $^ -o $@ $(LIBS)

clean:
	$(RM) $(BIN) $(OBJS)
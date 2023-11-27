OBJS = example.o tlog.o
BIN = example
CFLAGS = -Wall -g -O0 
CXXFLAGS = -Wall -g -O0 
LIBS = -lpthread
ROOT_PATH := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
CFLAGS += -I$(ROOT_PATH)../
CXXFLAGS += -I$(ROOT_PATH)../
VPATH = $(ROOT_PATH) $(ROOT_PATH)../
.PHONY : all

all: $(BIN) 

$(BIN):$(OBJS)
	$(CXX) $^ -o $@ $(LIBS)

clean:
	$(RM) $(BIN) $(OBJS) *.o *.log
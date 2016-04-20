CC=g++
CPPFLAGS=-std=c++11 -O3 -w
BIN=bin
SRC=src/main.cpp
TESTSRC=src/test*.cpp
# added a location for io_lib_wrapper
INC=-I include/ -I /usr/local/include/
LIB=-L /usr/local/lib/
# io_tools for operating on the bams/sams
# LIBS=lstaden-read
EXE=kbf

all: $(EXE) test

# compile phasing code
$(EXE):
	if [ ! -e $(BIN) ]; then mkdir $(BIN); fi
	$(CC) $(CPPFLAGS) $(INC) $(LIB) -o $(BIN)/$@ $(SRC) -lbf

# run tests
test:
	$(CC) $(CPPFLAGS) $(INC) $(LIB) -o $(BIN)/$@ $(TESTSRC) -lbf

clean:
	rm $(BIN)/$(EXE)
	# remove generated test files
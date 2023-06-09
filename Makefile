CFLAGS=-Wall -O0 -g -std=c++11

BUILDDIR = build
OUT = reader
CC = g++
INC = -Iinclude
LIBS = -lstdc++
DIRS=$(BUILDDIR)

OBJS = reader.o scanner.o parser.o allocater.o

%.o: %.cpp
	$(CC) -c $(INC) -o $@ $< $(CFLAGS)

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o $(OUT)

# Make the build directory
$(shell mkdir -p $(DIRS))

lines:
	wc -l *.h *.cpp | grep total

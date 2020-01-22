CC = gcc # compiler
CFLAGS = -Wall # flag to use e.g ggdb, -Wall etc
LDFLAGS = #which libraries to use e.g -lm, -lefence
# object files to include in the program
OBJFILES = src/util.o src/stack.o src/tree.o src/skveez.o main.o
TARGET = run # executable file name

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
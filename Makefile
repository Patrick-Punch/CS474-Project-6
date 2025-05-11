CC = gcc
CFLAGS = -Wall -Wextra -g
AR = ar
ARFLAGS = rcs

OBJS = image.o block.o free.o inode.o
LIB = libvvsfs.a
EXEC = testfs

all: $(EXEC)

$(EXEC): $(LIB) testfs.o
	$(CC) $(CFLAGS) -o $@ testfs.o -L. -lvvsfs

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

test: $(EXEC)
	./$(EXEC)

clean:
	rm -f *.o

pristine: clean
	rm -f $(EXEC) $(LIB) test.img

.PHONY: all test clean pristine
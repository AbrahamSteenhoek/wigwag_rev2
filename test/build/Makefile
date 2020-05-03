CFILES =  ../../Pattern.c ../Test.c ../main.c
OBJFILES = $(CFILES:.c=.o)
OUT = test

CC = gcc
CFLAGS = -Wall -I /mnt/c/Users/abrah/local/include -I ../ -I ../../
LDFLAGS = -L /mnt/c/Users/abrah/local/lib
LDLIBS = -lcunit

default: $(OUT)

$(OUT): $(OBJFILES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJFILES) $(OUT)

refresh: clean $(OUT)
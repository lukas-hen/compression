CC=gcc
CFLAGS=-Wall -O0 -I./include
BUILD = ./build/
DEPS = file.h
OBJ = $(addprefix $(BUILD), file.o huff.o main.o)
COMMAND = main

$(BUILD)%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

install: main
	sudo cp ./main /usr/local/bin/$(COMMAND) && chmod +x /usr/local/bin/$(COMMAND)

uninstall:
	sudo rm /usr/local/bin/$(COMMAND)

clean:
	rm -f $(BUILD)*.o

run:
	./main

.PHONY: clean run install
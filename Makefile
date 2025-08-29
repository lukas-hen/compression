CC=clang
CFLAGS=-Wall -Wextra -Wconversion -Wno-sign-conversion -O2 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -I./include
BUILD = ./build/
DEPS = file.h statistic.h util.h
OBJ = $(addprefix $(BUILD), file.o statistic.o huff_heap.o huff_tree.o huff_stack.o util.o main.o)
COMMAND = shan

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
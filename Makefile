CC=clang

PROG_NAME := compr

SRC_DIR := src
INCLUDE_DIR := include
OBJ_DIR := obj
BIN_DIR := bin
EXE := $(BIN_DIR)/$(PROG_NAME)

SRC := $(wildcard $(SRC_DIR)/*.c)
HEADER := $(wildcard $(INCLUDE_DIR)/*.h)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS := -I./include # -I is a preprocessor flag, not a compiler flag
CFLAGS   := -Wall -Wextra -Wconversion -Wno-sign-conversion -O2 #-fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer 

#LDFLAGS  := -Llib              # -L is a linker flag
LDLIBS   := -lm                # Left empty if no libs are needed

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BIN_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@
	
debug:
	$(CC) $(CPPFLAGS) -g $(SRC_DIR)/*.c -o $@
# Below are just for lazyness, not building.

install: $(BIN_DIR)/$(PROG_NAME)
	sudo cp $(BIN_DIR)/$(PROG_NAME) /usr/local/bin/$(PROG_NAME) && chmod +x /usr/local/bin/$(PROG_NAME)

uninstall:
	sudo rm /usr/local/bin/$(PROG_NAME)

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR) && $(RM) -r debug debug.*

run:
	./main

format:
	clang-format -i --style=file $(SRC) $(HEADER)

.PHONY: all clean run install uninstall format
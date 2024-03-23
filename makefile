# Define variables
SRC_DIR := src
BIN_DIR := bin
MANUAL_DIR := manual

# List of source files
SRCS := $(wildcard $(SRC_DIR)/*.c)

# Define the build target
myshell: $(SRCS)
	gcc -Wall -o $(BIN_DIR)/myshell $(SRCS)

# Rule to copy the user manual to the bin directory
copy_manual:
	cp $(MANUAL_DIR)/readme.md $(BIN_DIR)/

# Define the clean target
clean:
	rm -rf $(BIN_DIR)/*

# Specify phony targets
.PHONY: myshell clean copy_manual

BUILD_DIR := build
SRC_DIR := src
BIN_DIR := bin

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)
OUTS := $(OBJS:%.o=%)

CPPFLAGS := $(INC_FLAGS) -Wall -Werror -g

all: $(OUTS)
	mkdir -p $(BIN_DIR)
	cp $^ $(BIN_DIR)


$(BUILD_DIR)/%: $(BUILD_DIR)/%.o
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR) $(BIN_DIR)

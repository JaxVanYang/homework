BUILD_DIR := build
SRC_DIR := src

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)
OUTS := $(SRCS:%.c=$(BUILD_DIR)/%)

CPPFLAGS := $(INC_FLAGS) -Wall -g

all: $(OUTS)

# Run $(BUILD_DIR)/target
# But you should run `make all` first for unknown reason
%: $(BUILD_DIR)/$(SRC_DIR)/%
	-$^

$(BUILD_DIR)/%: $(BUILD_DIR)/%.o
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

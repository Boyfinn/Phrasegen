CC = gcc

CLI_TARGET = phrasegen
GUI_TARGET = phrasegengtk

CLI_DIR = cli
GUI_DIR = gui
BUILD_DIR = build

GTK_CFLAGS := $(shell pkg-config --cflags gtk+-3.0)
GTK_LIBS   := $(shell pkg-config --libs gtk+-3.0)

INCLUDES = -IEasyArgs
COMMON_FLAGS = -Wall -Wextra -MMD -MP
DEBUG_FLAGS  = -g
RELEASE_FLAGS = -O2
ASSET_PATH ?= res/

CFLAGS ?= $(COMMON_FLAGS) $(DEBUG_FLAGS)
# CFLAGS += -IEasyArgs

CLI_SRCS = $(wildcard $(CLI_DIR)/*.c)
GUI_SRCS = $(wildcard $(GUI_DIR)/*.c)

CLI_OBJS = $(patsubst $(CLI_DIR)/%.c,$(BUILD_DIR)/cli_%.o,$(CLI_SRCS))
GUI_OBJS = $(patsubst $(GUI_DIR)/%.c,$(BUILD_DIR)/gui_%.o,$(GUI_SRCS))

DEPS = $(CLI_OBJS:.o=.d) $(GUI_OBJS:.o=.d)

all: $(BUILD_DIR)/$(CLI_TARGET) $(BUILD_DIR)/$(GUI_TARGET)

release:
	$(MAKE) CFLAGS="$(COMMON_FLAGS) $(RELEASE_FLAGS) -DASSET_PATH='\"$(ASSET_PATH)\"'" all	#ASsets

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/cli_%.o: $(CLI_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/gui_%.o: $(GUI_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(GTK_CFLAGS) -c $< -o $@

$(BUILD_DIR)/res: res | $(BUILD_DIR)
	cp -r res $(BUILD_DIR)/

$(BUILD_DIR)/$(CLI_TARGET): $(CLI_OBJS) $(BUILD_DIR)/res
	$(CC) $(filter %.o, $^) -o $@

$(BUILD_DIR)/$(GUI_TARGET): $(GUI_OBJS)
	$(CC) $^ -o $@ $(GTK_LIBS) -rdynamic

clean:
	rm -rf $(BUILD_DIR)
-include $(DEPS)
.PHONY: all clean release

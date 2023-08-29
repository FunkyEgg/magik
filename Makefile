rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# Dirs
BIN_DIR := bin
SRC_DIR := src
OBJ_DIR := obj
LIB_DIR := lib

# C Stuff
override CFLAGS := -Wall -Wextra -I$(SRC_DIR) -I$(LIB_DIR) -std=c17 -g

# Sources
SOURCES := $(call rwildcard, $(SRC_DIR), *.c)
HEADERS := $(call rwildcard, $(SRC_DIR), *.h)

# Outputs
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

ifeq ($(OS),Windows_NT)
	OUTPUT_BIN := $(BIN_DIR)/magik.exe
else
	OUTPUT_BIN := $(BIN_DIR)/magik
endif

# TomlC99
TOMLC99 := tomlc99
TOMLC99_DIR := $(LIB_DIR)/$(TOMLC99)
TOMLC99_OBJ_DIR := $(OBJ_DIR)/$(TOMLC99)
TOMLC99_SOURCES := $(TOMLC99_DIR)/toml.c
TOMLC99_OBJECTS := $(patsubst $(TOMLC99_DIR)/%.c, $(TOMLC99_OBJ_DIR)/%.o, $(TOMLC99_SOURCES))
OBJECTS += $(TOMLC99_OBJECTS)

# Rules
.PHONY : all
all : dirs $(OUTPUT_BIN)

$(OUTPUT_BIN) : $(OBJECTS)
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TOMLC99_OBJ_DIR)/%.o : $(TOMLC99_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : dirs
dirs : $(BIN_DIR) $(OBJ_DIR) $(TOMLC99_OBJ_DIR)
$(BIN_DIR) $(OBJ_DIR) $(TOMLC99_OBJ_DIR) :
	@mkdir -p $@

.PHONY : run
run : all
	$(OUTPUT_BIN)

.PHONY : clean
clean :
	rm -rf $(BIN_DIR) $(OBJ_DIR)
# Directories
SRC_DIR                 := ./src
INCLUDE_DIR             := ./include
BUILD_INTERMEDIATES_DIR := ./build-intermediates
BUILD_DIR               := ./build

# Target
NAME := toml-c-parser
SRC  := main.c \
        memory/memmove.c memory/memset.c \
        string/strhash.c string/strlen.c string/strcmp.c \
        string/strcpy.c string/strncpy.c string/strdup.c \
        types/variant.c types/array.c types/map.c \
        file_reader.c \
        tokenizer/token.c tokenizer/tokenizer.c tokenizer/newline.c \
        tokenizer/newline.c tokenizer/equal.c tokenizer/dot.c \
        tokenizer/comma.c tokenizer/lbracket.c tokenizer/rbracket.c \
        tokenizer/lbrace.c tokenizer/rbrace.c tokenizer/double_quote.c \
        tokenizer/default.c tokenizer/single_quote.c tokenizer/comment.c \
        parser/parser.c parser/string.c parser/integer.c \
        parser/float.c parser/boolean.c parser/header.c \
        parser/key_value.c parser/key.c parser/value.c \
        toml.c
OBJ  := $(SRC:%.c=%.o)

# Adjustement
LIB_NAME := $(BUILD_DIR)/lib$(NAME).so
NAME := $(BUILD_DIR)/$(NAME)
SRC  := $(addprefix $(SRC_DIR)/, $(SRC))
OBJ  := $(addprefix $(BUILD_INTERMEDIATES_DIR)/, $(OBJ))

# Compiler
CFLAGS   += -std=c99 -Wall -Wextra -Wpedantic
CPPFLAGS += -I$(INCLUDE_DIR)
#LDFLAGS   =
#LDLIBS    =

all: $(NAME)

lib: $(LIB_NAME)

$(LIB_NAME): LDFLAGS += -shared
$(LIB_NAME): CFLAGS += -fPIC
$(LIB_NAME): $(OBJ)
	@echo "Linking..."
	@mkdir -p $(dir $(NAME))
	@$(CC) -o$(LIB_NAME) $^ $(LDFLAGS) $(LDLIBS)

$(NAME): $(OBJ)
	@echo "Linking..."
	@mkdir -p $(dir $@)
	@$(CC) -o$@ $^ $(LDFLAGS) $(LDLIBS)

$(BUILD_INTERMEDIATES_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<..."
	@mkdir -p $(dir $@)
	@$(CC) -c $(CPPFLAGS) $(CFLAGS) -o$@ $<

clean:
	@echo "Removing intermediates files..."
	@rm -rf $(BUILD_INTERMEDIATES_DIR)

fclean: clean
	@echo "Removing executable..."
	@rm -rf $(BUILD_DIR)

re: fclean all

run: all
	@$(NAME)

check: all
	@valgrind --leak-check=yes $(NAME) --no-output

.PHONY: all lib clean fclean re run check

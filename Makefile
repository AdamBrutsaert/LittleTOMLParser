# Directories
SRC_DIR                 := ./src
INCLUDE_DIR             := ./include
BUILD_INTERMEDIATES_DIR := ./build-intermediates
BUILD_DIR               := ./build

# Target
NAME := toml-c-parser
SRC  := main.c \
        utils/my_min_size.c utils/my_memmove.c utils/my_strhash.c \
        utils/my_strlen.c utils/my_strcpy.c utils/my_strcmp.c \
		utils/my_strdup.c \
        map/toml_variant.c map/toml_array.c
OBJ  := $(SRC:%.c=%.o)

# Adjustement
NAME := $(BUILD_DIR)/$(NAME)
SRC  := $(addprefix $(SRC_DIR)/, $(SRC))
OBJ  := $(addprefix $(BUILD_INTERMEDIATES_DIR)/, $(OBJ))

# Compiler
CFLAGS   += -std=c99 -Wall -Wextra -Wpedantic
CPPFLAGS += -I$(INCLUDE_DIR)
#LDFLAGS   =
#LDLIBS    =

all: $(NAME)

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
	@rm -f $(NAME)

re: fclean all

run: all
	@$(NAME)

check: all
	@valgrind --leak-check=yes $(NAME)

.PHONY: all clean fclean re run check
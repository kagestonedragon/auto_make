NAME = auto_make

GCC = gcc
GCC_FLAGS = -Wall -Wextra -Werror

SRC_PATH = sources/
OBJ_PATH = objects/
INC_PATH = includes/

GCC_INLCLUDE = -I $(INC_PATH)

SRC_MISC_PATH = $(SRC_PATH)misc/

SRC_FILES = create_makefile.c list.c make_variables.c read_directories.c read_files.c
SRC_MISC_FILES = strjoin.c

OBJ_CORE = $(addprefix $(OBJ_PATH), $(SRC_FILES:.c=.o))
OBJ_MISC_CORE = $(addprefix $(OBJ_PATH), $(SRC_MISC_FILES:.c=.o))

OBJECTS = $(OBJ_CORE) $(OBJ_MISC_CORE)

all: $(NAME)

$(NAME): $(OBJECTS)
		$(GCC) $(GCC_FLAGS) $(GCC_INCLUDE) -o $(NAME) $(OBJECTS)

objects:
		mkdir $(OBJ_PATH)

objects/%.o: $(SRC_PATH)%.c | objects
		$(GCC) $(GCC_FLAGS) $(GCC_INCLUDE) -c $< -o $@

objects/%.o: $(SRC_MISC_PATH)%.c | objects
		$(GCC) $(GCC_FLAGS) $(GCC_INCLUDE) -c $< -o $@

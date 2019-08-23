NAME = popa

GCC = gcc

GCC_FLAGS = -Wall -Wextra -Werror

AR = ar
AR_FLAGS = rcs

SRC_PATH = .
OBJ_PATH = objects/
INC_PATH = includes/

GCC_INCLUDE = -I $(INC_PATH)

SRC_PATH = ./
SRC_JOPA_PATH = ./jopa/
SRC_JOPA_PIZDA_PATH = ./jopa/pizda/
SRC_MISC_PATH = ./misc/

SRC_FILES = create_makefile.c list.c make_variables.c read_directories.c read_files.c 
SRC_JOPA_FILES = 
SRC_JOPA_PIZDA_FILES = 
SRC_MISC_FILES = strjoin.c 

OBJ__CORE = $(addprefix $(OBJ_PATH), $(SRC_FILES))
OBJ_JOPA_CORE = $(addprefix $(OBJ_PATH), $(SRC_JOPA_FILES))
OBJ_JOPA_PIZDA_CORE = $(addprefix $(OBJ_PATH), $(SRC_JOPA_PIZDA_FILES))
OBJ_MISC_CORE = $(addprefix $(OBJ_PATH), $(SRC_MISC_FILES))

OBJECTS = $(OBJ__CORE) $(OBJ_JOPA_CORE) $(OBJ_JOPA_PIZDA_CORE) $(OBJ_MISC_CORE) 

all: $(NAME)

$(NAME): $(OBJECTS)
		@($(AR) $(AR_FLAGS) $(NAME) $(OBJECTS))
		@(ranlib $(NAME)
		@(echo $(NAME) "was created!")

clean:
		@(/bin/rm -rf $(OBJ_PATH))
		@(echo "All objects files have been deleted!")

fclean: clean
		@(/bin/rm -f $(NAME))
		@(echo $(NAME) "has been deleted!")

re: fclean all

objects:
		@(mkdir $(OBJ_PATH))

objects/%.o: $(SRC_PATH)%.c | objects
		@(GCC) $(GCC_FLAGS) $(GCC_INCLUDE) -c $< -o $@
		@(echo $< "->" $@)

objects/%.o: $(SRC_JOPA_PATH)%.c | objects
		@(GCC) $(GCC_FLAGS) $(GCC_INCLUDE) -c $< -o $@
		@(echo $< "->" $@)

objects/%.o: $(SRC_JOPA_PIZDA_PATH)%.c | objects
		@(GCC) $(GCC_FLAGS) $(GCC_INCLUDE) -c $< -o $@
		@(echo $< "->" $@)

objects/%.o: $(SRC_MISC_PATH)%.c | objects
		@(GCC) $(GCC_FLAGS) $(GCC_INCLUDE) -c $< -o $@
		@(echo $< "->" $@)


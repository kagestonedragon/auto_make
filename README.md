# Auto_make

Auto_make it's easiest way to create your own Makefile.

### How to install


1) Clone repository to the root directory
```
git clone https://github.com/kagestonedragon/auto_make.git ~/auto_make
```

2) Compile
```
make -C ~/auto_make
```

3) Copy Auto_make to your project directory
```
cp ~/auto_make/auto_make <path to the project directory>
```


### How to use

```
./auto_make <output file> -S <sd1> <sd2> ... -I <id1> ...
```
Run auto_make with parameters:
* `<output file>` — name of the output file (`% = EXECUTABLE`, `%.a = LIBRARY`)
* `-S` — recursive search in directrories (only `%.c` files)
* `-I` — search header files in directories (only `%.h` files)

<b>Example</b>
```
./auto_make auto_make -S sources -I includes
```

<p align="center">
  <img src="/pics/console.png" width="1000%" alt="auto_make information"/>
</p>


### Generated Makefile

```makefile
########################################################
#@@@-------------GENERATED BY AUTO_MAKE-------------@@@#
#@@                                                  @@#
#@    https://github.com/kagestonedragon/auto_make    @#
########################################################

NAME = auto_make

GCC = gcc

GCC_FLAGS = -Wall -Wextra -Werror

OBJ_PATH = objects/

INCLUDES_INCLUDE = includes/

SOURCES_PATH = sources/

SOURCES_FILES = create_makefile.c errors.c get_variables.c information.c main.c parsing.c parsing_directories.c parsing_files.c 

OBJ_SOURCES_CORE = $(addprefix $(OBJ_PATH), $(SOURCES_FILES:.c=.o))

OBJECTS = $(OBJ_SOURCES_CORE) 
all: $(NAME)

$(NAME): $(OBJECTS)
		@($(GCC) $(GCC_FLAGS) -o $(NAME) $(OBJECTS))
		@(echo "[0;92m"$(NAME) "was created![0;0m")

clean:
		@(/bin/rm -rf $(OBJ_PATH))
		@(echo "[0;91mAll object files have been deleted![0;0m")

fclean: clean
		@(/bin/rm -f $(NAME))
		@(echo "[0;91m"$(NAME) "has been deleted![0;0m")

re: fclean all

objects:
		@(mkdir $(OBJ_PATH))

objects/%.o: $(SOURCES_PATH)%.c | objects
		@($(GCC) $(GCC_FLAGS) -I $(INCLUDES_INCLUDE) -c $< -o $@)
		@(echo "[0;93m"$< "->" $@"[0;0m")

```

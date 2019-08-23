#include "../includes/auto_make.h"
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

static void         add_flags(FILE *f, char **argv)
{
    fprintf(f, "NAME = %s\n\n", argv[1]);
    fprintf(f, "GCC = gcc\n\n");
    fprintf(f, "GCC_FLAGS = -Wall -Wextra -Werror\n\n");
    fprintf(f, "AR = ar\n");
    fprintf(f, "AR_FLAGS = rcs\n\n");
    fprintf(f, "SRC_PATH = %s\n", argv[3]);
    fprintf(f, "OBJ_PATH = objects/\n");
    fprintf(f, "INC_PATH = %s\n\n", argv[5]);
    fprintf(f, "GCC_INCLUDE = -I $(INC_PATH)\n\n");
}

static void         add_paths(FILE *f, t_list *list)
{
    while (list)
    {
        fprintf(f, "%s_PATH = %s/\n", list->make_data, list->data);
        list = list->next;
    }
    fprintf(f, "\n");
}

static int          source_file(char *name)
{
    int             length;

    length = strlen(name);
    if (name[length - 1] == 'c' && name[length - 2] == '.')
        return (1);
    return (0);
}

static void         find_files(FILE *f, char *path)
{
    DIR             *dir;
    struct dirent   *entry;

    dir = opendir(path);
    while ((entry = readdir(dir)))
    {
        if (entry->d_type == DT_REG && source_file(entry->d_name))
            fprintf(f, "%s ", entry->d_name);
    }
}

static void         add_files(FILE *f, t_list *list)
{
    while (list)
    {
        fprintf(f, "%s_FILES = ", list->make_data);
        find_files(f, list->data);
        fprintf(f, "\n");
        list = list->next;
    }
    fprintf(f, "\n");
}

static void         add_objects(FILE *f, t_list *list)
{
    while (list)
    {
        fprintf(f, "OBJ_%s_CORE = $(addprefix $(OBJ_PATH), $(%s_FILES:.c=.o))\n", &list->make_data[4], list->make_data);
        list = list->next;
    }
    fprintf(f, "\n");
}

static void         add_combined_objects(FILE *f, t_list *list)
{
    fprintf(f, "OBJECTS = ");
    while (list)
    {
        fprintf(f, "$(OBJ_%s_CORE) ", &list->make_data[4]);
        list = list->next;
    }
    fprintf(f, "\n\n");
}

static void         add_main_instructions(FILE *f)
{
    fprintf(f, "all: $(NAME)\n\n");
    fprintf(f, "$(NAME): $(OBJECTS)\n");
    fprintf(f, "\t\t@($(AR) $(AR_FLAGS) $(NAME) $(OBJECTS))\n");
    fprintf(f, "\t\t@(ranlib $(NAME))\n");
    fprintf(f, "\t\t@(echo $(NAME) \"was created!\")\n\n");
    fprintf(f, "clean:\n");
    fprintf(f, "\t\t@(/bin/rm -rf $(OBJ_PATH))\n");
    fprintf(f, "\t\t@(echo \"All objects files have been deleted!\")\n\n");
    fprintf(f, "fclean: clean\n");
    fprintf(f, "\t\t@(/bin/rm -f $(NAME))\n");
    fprintf(f, "\t\t@(echo $(NAME) \"has been deleted!\")\n\n");
    fprintf(f, "re: fclean all\n\n");
    
}

static void         add_create_objects(FILE *f, t_list *list)
{
    fprintf(f, "objects:\n");
    fprintf(f, "\t\t@(mkdir $(OBJ_PATH))\n\n");
    while (list)
    {
        fprintf(f, "objects/%%.o: $(%s_PATH)%%.c | objects\n", list->make_data);
        fprintf(f, "\t\t@($(GCC) $(GCC_FLAGS) $(GCC_INCLUDE) -c $< -o $@)\n");
        fprintf(f, "\t\t@(echo $< \"->\" $@)\n\n");
        list = list->next;
    }
}

void                create_makefile(t_list *list, char **argv)
{
    FILE    *f;

    f = fopen("Makefile", "w");
    add_flags(f, argv);
    add_paths(f, list);
    add_files(f, list);
    add_objects(f, list);
    add_combined_objects(f, list);
    add_main_instructions(f);
    add_create_objects(f, list);
}

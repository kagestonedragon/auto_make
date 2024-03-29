#include "auto_make.h"
#include <fcntl.h>
#include <stdio.h>

static int      add_comment(FILE *f)
{
    fprintf(f, "########################################################\n");
    fprintf(f, "#@@@-------------GENERATED BY AUTO_MAKE-------------@@@#\n");
    fprintf(f, "#@@                                                  @@#\n");
    fprintf(f, "#@    https://github.com/kagestonedragon/auto_make    @#\n");
    fprintf(f, "########################################################\n\n");
    return (0);
}

static int      add_main(FILE *f, t_auto_make *core)
{
    fprintf(f, "NAME = %s\n\n", core->file_name);
    fprintf(f, "GCC = gcc\n\n");
    fprintf(f, "GCC_FLAGS = -Wall -Wextra -Werror\n\n");
    fprintf(f, "OBJ_PATH = objects/\n");
    if (core->file_type == LIBRARY)
    {
        fprintf(f, "\nAR = ar\n");
        fprintf(f, "AR_FLAGS = rcs\n");
    }
    fprintf(f, "\n");
    return (0);
}

static int      add_includes(FILE *f, t_auto_make *core)
{
    t_dir       *temporary_dir;

    temporary_dir = core->includes_folders;
    while (temporary_dir)
    {
        fprintf(f, "%s = %s/\n", temporary_dir->variable, temporary_dir->data);
        temporary_dir = temporary_dir->next;
    }
    fprintf(f, "\n");
    return (0);
}

static int      add_directories(FILE *f, t_auto_make *core)
{
    t_dir       *temporary_dir;

    temporary_dir = core->sources_folders->directories;
    while (temporary_dir)
    {
        fprintf(f, "%s_PATH = %s/\n", temporary_dir->variable, temporary_dir->data);
        temporary_dir = temporary_dir->next;
    }
    fprintf(f, "\n");
    return (0);
}

static int      add_files(FILE *f, t_auto_make *core)
{
    t_dir       *temporary_dir;
    t_list      *temporary_list;

    temporary_dir = core->sources_folders->directories;
    while (temporary_dir)
    {
        fprintf(f, "%s_FILES = ", temporary_dir->variable);
        temporary_list = temporary_dir->files;
        fprintf(f, "\\\n");
        while (temporary_list)
        {
            fprintf(f, "\t\t%s ", temporary_list->data);
            if ((temporary_list = temporary_list->next))
                fprintf(f, "\\\n");
            else
                fprintf(f, "\n");
        }
        temporary_dir = temporary_dir->next;
    }
    fprintf(f, "\n");
    return (0);
}

static int      add_objects(FILE *f, t_auto_make *core)
{
    t_dir       *temporary_dir;

    temporary_dir = core->sources_folders->directories;
    while (temporary_dir)
    {
        fprintf(f, "OBJ_%s_CORE = $(addprefix $(OBJ_PATH), $(%s_FILES:.c=.o))\n", temporary_dir->variable, temporary_dir->variable);
        temporary_dir = temporary_dir->next;
    }
    fprintf(f, "\n");
    return (0);
}

static int      add_combined_objects(FILE *f, t_auto_make *core)
{
    t_dir       *temporary_dir;

    temporary_dir = core->sources_folders->directories;
    fprintf(f, "OBJECTS = ");
    while (temporary_dir)
    {
        fprintf(f, "$(OBJ_%s_CORE) ", temporary_dir->variable);
        temporary_dir = temporary_dir->next;
    }
    fprintf(f, "\n\n");
    return (0);

}

static int      add_main_instruction(FILE *f, t_auto_make *core)
{
    fprintf(f, "all: $(NAME)\n\n");
    fprintf(f, "$(NAME): $(OBJECTS)\n");
    if (core->file_type == LIBRARY)
    {
        fprintf(f, "\t\t@($(AR) $(AR_FLAGS) $(NAME) $(OBJECTS))\n");
        fprintf(f, "\t\t@(ranlib @(NAME))\n");
    }
    else
        fprintf(f, "\t\t@($(GCC) $(GCC_FLAGS) -o $(NAME) $(OBJECTS))\n");
    fprintf(f, "\t\t@(echo \"\033[0;92m\"$(NAME) \"was created!\033[0;0m\")\n\n");
    fprintf(f, "clean:\n");
    fprintf(f, "\t\t@(/bin/rm -rf $(OBJ_PATH))\n");
    fprintf(f, "\t\t@(echo \"\033[0;91mAll object files have been deleted!\033[0;0m\")\n\n");
    fprintf(f, "fclean: clean\n");
    fprintf(f, "\t\t@(/bin/rm -f $(NAME))\n");
    fprintf(f, "\t\t@(echo \"\033[0;91m\"$(NAME) \"has been deleted!\033[0;0m\")\n\n");
    fprintf(f, "re: fclean all\n\n");
    return (0);
}

static int      add_includes_to_objects(FILE *f, t_auto_make *core)
{
    t_dir       *temporary_dir;

    temporary_dir = core->includes_folders;
    while (temporary_dir)
    {
        fprintf(f, "-I $(%s) ", temporary_dir->variable);
        temporary_dir = temporary_dir->next;
    }
    return (0);
}

static int      add_creating_objects(FILE *f, t_auto_make *core)
{
    t_dir       *temporary_dir;

    temporary_dir = core->sources_folders->directories;
    fprintf(f, "objects:\n");
    fprintf(f, "\t\t@(mkdir $(OBJ_PATH))\n\n");
    while (temporary_dir)
    {
        fprintf(f, "objects/%%.o: $(%s_PATH)%%.c | objects\n", temporary_dir->variable);
        fprintf(f, "\t\t@($(GCC) $(GCC_FLAGS) ");
        add_includes_to_objects(f, core);
        fprintf(f, "-c $< -o $@)\n");
        fprintf(f, "\t\t@(echo \"\033[0;93m\"$< \"->\" $@\"\033[0;0m\")\n");
        if ((temporary_dir = temporary_dir->next))
            fprintf(f, "\n");
    }
    return (0);
}

int             create_makefile(t_auto_make *core)
{
    FILE        *f;

    if (!(f = fopen("Makefile", "w")))
        parsing_error(ERROR_MAKEFILE, "Makefile");
    add_comment(f);
    add_main(f, core);
    if (core->includes_folders)
        add_includes(f, core);
    add_directories(f, core);
    add_files(f, core);
    add_objects(f, core);
    add_combined_objects(f, core);
    add_main_instruction(f, core);
    add_creating_objects(f, core);
    return (0);
}

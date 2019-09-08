#include "auto_make.h"
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

static int          get_file_type(char *file_name)
{
    int             length;
    
    length = strlen(file_name);
    if (file_name[length - 1] == 'a' && file_name[length - 2] == '.')
        return (LIBRARY);
    return (EXECUTABLE);
}

static t_dir        *add_include(char *data)
{
    t_dir           *new;

    new = (t_dir *)malloc(sizeof(t_dir));
    new->data = data;
    new->files = NULL;
    new->next = NULL;
    return (new);
}

static t_folders    *add_folder(char *data)
{
    t_folders       *new;

    new = (t_folders *)malloc(sizeof(t_folders));
    new->data = data;
    new->directories = NULL;
    new->next = NULL;
    return (new);
}

static int          is_folder(char *name)
{
    struct stat     sb;

    if (!stat(name, &sb) && S_ISDIR(sb.st_mode))
        return (1);
    parsing_error(ERROR_DIRECTORY, name);
    return (0);
}

static int          parsing_includes(t_auto_make *core, int *i, int argc, char **argv)
{
    t_dir           *temporary;

    if (*i + 1 == argc)
        return (0);
    if (is_folder(argv[*i + 1]))
        core->includes_folders = add_include(argv[*i + 1]);
    temporary = core->includes_folders;
    *i += 2;
    while (*i < argc)
    {
        if (is_folder(argv[*i + 1]))
            temporary->next = add_include(argv[*i]);
        temporary = temporary->next;
        *i += 1;
    }
    return (0);
}

static int          parsing_sources(t_auto_make *core, int argc, char **argv)
{
    int             i;
    t_folders       *temporary;

    if (is_folder(argv[3]))
        core->sources_folders = add_folder(argv[3]);
    temporary = core->sources_folders;
    i = 3;
    while (++i < argc)
    {
        if (argv[i][0] == '-' && argv[i][1] == 'I')
            return (parsing_includes(core, &i, argc, argv));
        else
        {
            if (is_folder(argv[i]))
                temporary->next = add_folder(argv[i]);
            temporary = temporary->next;
        }
    }
    return (0);
}

t_auto_make         *parsing(int argc, char **argv)
{
    t_auto_make     *core;

    core = (t_auto_make *)malloc(sizeof(t_auto_make));
    core->file_type = get_file_type(argv[1]);
    core->file_name = argv[1];
    core->includes_folders = NULL;
    parsing_sources(core, argc, argv);
    return (core);
}

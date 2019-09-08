#include "auto_make.h"
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

static int          is_source_file(char *name)
{
    int             length;

    length = strlen(name);
    if (name[length - 1] == 'c' && name[length - 2] == '.')
        return (1);
    return (0);
}

static t_list       *create_file(char *data)
{
    t_list          *new;

    new = (t_list *)malloc(sizeof(t_list));
    new->data = data;
    new->next = NULL;
    return (new);
}

static t_list      *new_file(t_list *list, char *data)
{
    list->next = (t_list *)malloc(sizeof(t_list));
    list->next->data = data;
    list->next->next = NULL;
    return (list->next);
}

static t_list       *get_files(char *path)
{
    DIR             *dir;
    struct dirent   *entry;
    t_list          *temporary;
    t_list          *list;

    list = NULL;
    dir = opendir(path);
    while ((entry = readdir(dir)))
    {
        if (entry->d_type == DT_REG && is_source_file(entry->d_name))
        {
            if (list)
            {
                temporary->next = new_file(temporary, entry->d_name);
                temporary = temporary->next;
            }
            else
            {
                temporary = create_file(entry->d_name);
                list = temporary;
            }
        }
    }
    return (list);
}

static int          is_header_file(char *name)
{
    int             length;

    length = strlen(name);
    if (name[length - 1] == 'h' && name[length - 2] == '.')
        return (1);
    return (0);
}

static t_list       *get_include_files(char *path)
{
    DIR             *dir;
    struct dirent   *entry;
    t_list          *temporary;
    t_list          *list;

    list = NULL;
    dir = opendir(path);
    while ((entry = readdir(dir)))
    {
        if (entry->d_type == DT_REG && is_header_file(entry->d_name))
        {
            if (list)
            {
                temporary->next = new_file(temporary, entry->d_name);
                temporary = temporary->next;
            }
            else
            {
                temporary = create_file(entry->d_name);
                list = temporary;
            }
        }
    }
    return (list);
}

int                 parsing_files(t_auto_make *core)
{
    t_dir           *temporary;

    temporary = core->sources_folders->directories;
    while (temporary)
    {
        temporary->files = get_files(temporary->data);
        temporary = temporary->next;
    }
    return (0);
}

int                 parsing_include_files(t_auto_make *core)
{
    t_dir           *temporary;

    temporary = core->includes_folders;
    while (temporary)
    {
        temporary->files = get_include_files(temporary->data);
        temporary = temporary->next;
    }
    return (0);
}

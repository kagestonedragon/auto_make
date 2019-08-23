#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../includes/auto_make.h"

void                print_list(t_list *list)
{
    while (list)
    {
        printf("%s\n", list->data);
        printf("%s\n", list->make_data);
        list = list->next;
    }
}

static char         *get_full_path(const char *path, char *d_name)
{
    char            *temporary;
    char            *result;

    temporary = strjoin(path, "/");
    result = strjoin(temporary, d_name);
    free(temporary);
    return (result);
}

void                read_directories(t_list *list, const char *path)
{
    DIR             *dir;
    struct dirent   *entry;
    char            *full_path;

    dir = opendir(path);
    while ((entry = readdir(dir)))
    {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
        {
            full_path = get_full_path(path, entry->d_name);
            new_element(last_element(list), full_path);
            read_directories(list, full_path);
        }
    }
    closedir(dir);
}

int main(int argc, char **argv)
{
    t_list  *directories;

    (void)argc;
    directories = create_list(argv[3]);
    read_directories(directories, argv[3]);
    get_make_variables(directories, argv[3]);
    create_makefile(directories, argv);
    print_list(directories);
    return (0);
}

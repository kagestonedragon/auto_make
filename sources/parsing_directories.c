#include "auto_make.h"
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char                *strjoin(char const *s1, char const *s2)
{
    char            *join_result;
    char            *join_result_begin;
    int             size;

    if (!s1 || !s2)
        return (NULL);
    if (!(size = strlen(s1) + strlen(s2) + 1))
        return (NULL);
    if (!(join_result = (char *)malloc(sizeof(char) * size)))
        return (NULL);
    join_result_begin = join_result;
    while (*s1)
        *join_result++ = *s1++;
    while (*s2)
        *join_result++ = *s2++;
    *join_result = '\0';
    return (join_result_begin);
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

static t_dir        *last_directory(t_dir *dir)
{
    t_dir           *temporary;

    temporary = dir;
    while (temporary->next)
        temporary = temporary->next;
    return (temporary);

}

static t_dir        *new_directory(t_dir *dir, char *data)
{
    dir->next = (t_dir *)malloc(sizeof(t_dir));
    dir->next->files = NULL;
    dir->next->data = data;
    dir->next->next = NULL;
    return (dir->next);
}

static t_dir        *create_directory(char *path)
{
    t_dir          *dir;

    dir = (t_dir *)malloc(sizeof(t_dir));
    dir->data = path;
    dir->files = NULL;
    dir->next = NULL;
    return (dir);
}

static int          get_directories(t_dir *list, const char *path)
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
            new_directory(last_directory(list), full_path);
            get_directories(list, full_path);
        }
    }
    closedir(dir);
    return (0);
}

int                 parsing_directories(t_auto_make *core)
{
    t_folders       *temporary;

    temporary = core->sources_folders;
    while (temporary)
    {
        temporary->directories = create_directory(temporary->data);
        get_directories(temporary->directories, temporary->data);
        temporary = temporary->next;
    }
    return (0);
}


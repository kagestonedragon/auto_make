#include "auto_make.h"
#include <ctype.h>
#include <string.h>

static int      modify_variable(char *data)
{
    int         i;

    i = -1;
    while (data[++i])
    {
        if (data[i] == '/')
            data[i] = '_';
        data[i] = toupper(data[i]);
    }
    return (0);
}

static int      get_include_variables(t_auto_make *core)
{
    t_dir       *temporary_dir;

    temporary_dir = core->includes_folders;
    while (temporary_dir)
    {
        temporary_dir->variable = strjoin(temporary_dir->data, "_INCLUDE");
        modify_variable(temporary_dir->variable);
        temporary_dir = temporary_dir->next;
    }
    return (0);
}

int             get_variables(t_auto_make *core)
{
    t_folders   *temporary;
    t_dir       *temporary_dir;

    temporary = core->sources_folders;
    while (temporary)
    {
        temporary->variable = strdup(temporary->data);
        modify_variable(temporary->variable);
        temporary_dir = temporary->directories;
        while (temporary_dir)
        {
            temporary_dir->variable = strjoin(temporary->variable, &(temporary_dir->data[strlen(temporary->variable)]));
            modify_variable(temporary_dir->variable);
            temporary_dir = temporary_dir->next;
        }
        temporary = temporary->next;
    }
    get_include_variables(core);
    return (0);
}

#include "../includes/auto_make.h"
#include <string.h>
#include <ctype.h>

static void modify_variable(char *make_data)
{
    int     i;

    i = -1;
    while (make_data[++i])
    {
        if (make_data[i] == '/')
            make_data[i] = '_';
        make_data[i] = toupper(make_data[i]);    
    }
}

void        get_make_variables(t_list *list, char *source)
{
    while (list)
    {
        list->make_data = strjoin("SRC", &(list->data[strlen(source)]));
        modify_variable(list->make_data);
        list = list->next;
    }
}

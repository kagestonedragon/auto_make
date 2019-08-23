#include "../includes/auto_make.h"
#include <stdlib.h>
#include <string.h>

t_list      *last_element(t_list *list)
{
    t_list  *_list;

    _list = list;
    while (_list->next)
        _list = _list->next;
    return (_list);
}

t_list      *new_element(t_list *list, char *data)
{
    list->next = (t_list *)malloc(sizeof(t_list));
    list->next->data = data;
    list->next->next = NULL;
    return (list->next);
}

t_list      *create_list(char *data)
{
    t_list  *list;

    list = (t_list *)malloc(sizeof(t_list));
    list->data = data;
    list->next = NULL;
    return (list);
}

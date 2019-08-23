#ifndef AUTO_MAKE_H
# define AUTO_MAKE_H

typedef struct      s_list{
    char            *data;
    char            *make_data;
    struct s_list   *next;
}                   t_list;

typedef struct      s_auto_make{

}

t_list              *create_list(char *data);
t_list              *new_element(t_list *list, char *data);
t_list              *last_element(t_list *list);

void                get_make_variables(t_list *list, char *source);

void                create_makefile(t_list *list, char **argv);

char                *strjoin(char const *s1, char const *s2);

#endif

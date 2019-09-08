#ifndef AUTO_MAKE_H
# define AUTO_MAKE_H

# define LIBRARY            1
# define EXECUTABLE         2

# define ERROR_DIRECTORY    100
# define ERROR_MAKEFILE     200

typedef enum{
    false,
    true
}       t_bool;

typedef struct              s_list{
    char                    *data;
    struct s_list           *next;
}                           t_list;

typedef struct              s_dir{
    char                    *data;
    char                    *variable;
    t_list                  *files;
    struct s_dir            *next;
}                           t_dir;

typedef struct              s_folders{
    char                    *data;
    char                    *variable;
    t_dir                   *directories;
    struct s_folders        *next;
}                           t_folders;

typedef struct              s_auto_make{
    int                     file_type;
    char                    *file_name;
    t_folders               *sources_folders;
    t_dir                   *includes_folders;
}                           t_auto_make;

/* ERROR HANDLING */
int                         initialization_errors(int argc, char **argv);
int                         parsing_error(int error, char *name);

/* PARSING */
t_auto_make                 *parsing(int argc, char **argv);
int                         parsing_directories(t_auto_make *core);
int                         parsing_files(t_auto_make *core);
int                         get_variables(t_auto_make *core);
int                         create_makefile(t_auto_make *core);
int                         parsing_include_files(t_auto_make *core);

/* MISC */
char                        *strjoin(char const *s1, char const *s2);

/* INFORMATION */
int                         get_information(t_auto_make *core);
#endif

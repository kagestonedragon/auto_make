#include "auto_make.h"
#include <stdio.h>

int                 main(int argc, char **argv)
{
    t_auto_make     *core;

    if (initialization_errors(argc, argv))
        return (1);
    core = parsing(argc, argv);
    parsing_directories(core);
    parsing_files(core);
    parsing_include_files(core);
    get_variables(core);
    create_makefile(core);
    get_information(core);
    return (0);
}

#include "auto_make.h"
#include <stdio.h>
#include <stdlib.h>

int         initialization_errors(int argc, char **argv)
{
    if (argc < 4)
    {
        printf("Error!\n");
        return (300);
    }
    if (argv[2][0] != '-' || argv[2][1] != 'S')
    {
        printf("Error!\n");
        return (300);
    }
    if (argv[3][0] == '-')
    {
        printf("Error!\n");
        return (300);
    }
    return (0);
}

int         parsing_error(int error, char *name)
{
    if (error == ERROR_DIRECTORY)
        printf("auto_make: %s: No such file or directory\n", name);
    if (error == ERROR_MAKEFILE)
        printf("auto_make: %s: can't open or create file\n", name);
    exit(0);
    return (0);
}

#include <stdio.h>

int     help(void)
{
    printf("Usage: ./auto_make -O [filename] -S  ... -I ... -L ...\n\n");
    printf("\"-O\" - output file\n");
    printf("\"-S\" - source files (.c)\n");
    printf("\"-I\" - header files (.h)\n");
    printf("\"-L\" - lib files (.a, etc...)\n");
    printf("Example: ./auto_make -O libftprintf.a -S sources misc -I includes -L libft\n");
    return (0);
}

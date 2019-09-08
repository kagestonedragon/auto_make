#include "auto_make.h"
#include <stdio.h>

int                 get_information(t_auto_make *core)
{
    int             i;

    printf("\t\e[97m>-----------AUTO_MAKE------------<\e[0m\n");
    if (core->file_type == LIBRARY)
        printf("\e[96mFILE TYPE:\e[91m %s\n", "LIBRARY");
    else
        printf("\e[96mFILE TYPE: \e[91m%s\n", "EXECUTABLE");
    printf("\e[96mFILE NAME: \e[91m%s\n\n", core->file_name);
    printf("\e[96mSOURCES\e[0m\n");
    i = 0;
    while (core->sources_folders)
    {
        printf("\e[92m%d: %s\e[0m\n", ++i, core->sources_folders->data);
        while (core->sources_folders->directories)
        {
            printf("\t\e[93m%s\e[0m\n", core->sources_folders->directories->data);
            if (!core->sources_folders->directories->files)
                printf("\t\t\e[91m%s\e[0m\n", "EMPTY");
            while (core->sources_folders->directories->files)
            {
                printf("\t\t\e[95m%s\e[0m\n", core->sources_folders->directories->files->data);
                core->sources_folders->directories->files = core->sources_folders->directories->files->next;
            }
            core->sources_folders->directories = core->sources_folders->directories->next;
        }
        core->sources_folders = core->sources_folders->next;
    }
    i = 0;
    if (core->includes_folders)
    {
        printf("\n\e[96mINCLUDES\e[0m\n");
        while (core->includes_folders)
        {
            printf("\e[92m%d: %s\e[0m\n", ++i, core->includes_folders->data);
            if (!core->includes_folders->files)
                printf("\t\e[91m%s\e[0m\n", "EMPTY");
            while (core->includes_folders->files)
            {
                printf("\t\e[95m%s\e[0m\n", core->includes_folders->files->data);
                core->includes_folders->files = core->includes_folders->files->next;
            }
            core->includes_folders = core->includes_folders->next;
        }
    }
    printf("\t\e[97m>-----------AUTO_MAKE------------<\e[0m\n");
    return (0);
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {   // Too few
        printf("Error : Too few arguments\n");
        return 0;
    }
    if (argc > 5) {   // Too many
        printf("Error : Too many arguments\n");
        return 0;
    }

    

    if (check_operation(argv[1]) == e_view) {   // if -v
        if (view_mp3(argv[2]) == e_failure) {
            printf("Error : unable to view the file's content\n");
            return 0;
        }
    } else if (check_operation(argv[1]) == e_edit) { // if -e
       if (edit_mp3(argv[4],argv[2],argv[3]) == e_failure) {
            printf("Error : unable to view the file's content\n");
            return 0;
        }
    } else {
        printf("Error : Unsupported arguments given\n");
        return 0;
    }
}

oper check_operation(char *argv) {
    if (!(strcmp(argv, "-v"))) return e_view;   // if -v
    else if (!(strcmp(argv, "-e"))) return e_edit; // if -e
    else return e_unsupported;
}

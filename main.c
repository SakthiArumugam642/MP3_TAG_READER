/*
Name : Sakthivel A
Date : 15-09-2025
Desc : MP3 Tag Reader and Editor
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {   // Too few
        printf("Error : Too few arguments\nRequired Format\nFor View-> ./a.out -v file_name.mp3\nFor Edit-> ./a.out -e -tag_edit_id new_tag_content file_name.mp3\nTo know more about tag edit IDs try format ./a.out -h\n");
        return 0;
    }
    if (argc > 5) {   // Too many
        printf("Error : Too many arguments\nRequired Format\nFor View-> ./a.out -v file_name.mp3\nFor Edit-> ./a.out -e -tag_edit_id new_tag_content file_name.mp3\nTo know more about tag edit IDs try format ./a.out -h\n");
        return 0;
    }

    

    if (check_operation(argv[1]) == e_view) {   // if -v
        if (view_mp3(argv[2]) == e_failure) {
            printf("Error : unable to view the file's content\nRequired Format ./a.out -v file_name.mp3\n");
            return 0;
        }
    } else if (check_operation(argv[1]) == e_edit) { // if -e
       if (edit_mp3(argv[4],argv[2],argv[3]) == e_failure) {
            printf("Error : unable to edit the file's content\nRequired Format ./a.out -e -tag_edit_id new_tag_content file_name.mp3\n");
            return 0;
        }
    }
     else if (check_operation(argv[1]) == e_help){ // if -h
        for(int i=0;i<6;i++){
            printf("%s -> %s%s\n",helper[i],tag_name[i],TAG[i]); // printing all tagID,tagname,helper tag id for edit
        }
     }
    else {
        printf("Error : Unsupported arguments given\nRequired Format\nFor View-> ./a.out -v file_name.mp3\nFor Edit-> ./a.out -e -tag_edit_id new_tag_content file_name.mp3\nTo know more about tag edit IDs try format ./a.out -h\n");
        return 0;
    }
}

oper check_operation(char *argv) {
    if (!(strcmp(argv, "-v"))) return e_view;   // if -v
    else if (!(strcmp(argv, "-e"))) return e_edit; // if -e
    else if (!(strcmp(argv, "-h"))) return e_help; // if -h
    else return e_unsupported;
}

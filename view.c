#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

static char buffer[1024];
char *TAG[] = {"TIT2","TALB","TCON","TCOM","TPE1","TYER"};
char *helper[] = {"-t","-A","-c","-m","-a","-y"};
char *tag_name[] = {"Title : ","Album : ","Content : ","Composer : ","Artist : ","Year : "};

sts open_mp3_view(FILE **fptr, char *mp3) {
    *fptr = fopen(mp3, "r");  // open in read mode
    if (*fptr) return e_success;
    else return e_failure;
}

sts view_mp3(char *mp3) {
    FILE *fptr;
    if (open_mp3_view(&fptr, mp3) == e_failure) return e_failure;

    fread(buffer, 3, 1, fptr);
    if (strncmp(buffer, "ID3", 3)) {
        printf("Error : Not a MP3 File\n");
        fclose(fptr);
        return e_failure;
    }

    fread(buffer, 7, 1, fptr);   // skip version + flags + size
    read_tag_view(fptr);

    fclose(fptr);
    return e_success;
}

sts read_tag_view(FILE *fptr) {
    while (!feof(fptr)) {
        if (fread(buffer, 4, 1, fptr) != 1) break;

        for (int j = 0; j < 6; j++) {
            if (strncmp(buffer, TAG[j], 4) == 0) {
                int size = get_tag_size_view(fptr);
                fseek(fptr, 2, SEEK_CUR);  // skip flags (2 bytes)
                printf("%s",tag_name[j]);
                fread(buffer, size, 1, fptr);
                print_tag_content(buffer, size);
            }
        }
    }
    return e_success;
}

int get_tag_size_view(FILE *fptr) {
    unsigned char size_buf[4];
    fread(size_buf, 4, 1, fptr);
    int size = (size_buf[0] & 0x7F) << 21|(size_buf[1] & 0x7F) << 14|(size_buf[2] & 0x7F) << 7|(size_buf[3] & 0x7F);
    return size;
}

sts print_tag_content(char *buffer, int size) {
    // Skip the encoding byte
    for (int i = 1; i < size; i++) {
        printf("%c", buffer[i]);
    }
    printf("\n");
    return e_success;
}

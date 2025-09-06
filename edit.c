#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"

static char buffer[1024];   // global buffer
FILE *temp = NULL;          // temp file

// ---- Helper: read raw 4-byte size ----
int get_tag_size_edit(FILE *fptr) {
    unsigned char size_buf[4];
    if (fread(size_buf, 4, 1, fptr) != 1) return -1;
    int size = (size_buf[0] << 24) |
               (size_buf[1] << 16) |
               (size_buf[2] << 8)  |
               (size_buf[3]);
    return size;
}

// ---- Helper: write raw 4-byte size ----
void write_tag_size(FILE *fp, int size) {
    unsigned char size_buf[4];
    size_buf[0] = (size >> 24) & 0xFF;
    size_buf[1] = (size >> 16) & 0xFF;
    size_buf[2] = (size >> 8)  & 0xFF;
    size_buf[3] = size & 0xFF;
    fwrite(size_buf, 4, 1, fp);
}

int get_index(char *helper[], char *tag) {
    for (int i = 0; i < 6; i++) {
        if (strcmp(helper[i], tag) == 0) return i;
    }
    return -1;
}

sts open_mp3_edit(FILE **fptr, char *mp3) {
    *fptr = fopen(mp3, "rb");
    if (!*fptr) return e_failure;

    temp = fopen("temp.mp3", "wb");
    if (!temp) {
        fclose(*fptr);
        return e_failure;
    }
    return e_success;
}

sts edit_mp3(char *mp3, char *tag, char *new_content) {
    FILE *fptr = NULL;
    if (open_mp3_edit(&fptr, mp3) == e_failure) return e_failure;

    // Copy header (10 bytes)
    if (fread(buffer, 10, 1, fptr) != 1) {
        fclose(fptr);
        fclose(temp);
        return e_failure;
    }
    fwrite(buffer, 10, 1, temp);

    if (read_tag_edit(fptr, tag, new_content) == e_failure) {
        fclose(fptr);
        fclose(temp);
        return e_failure;
    }

    fclose(fptr);
    fclose(temp);

    // Replace old file with new one
    remove(mp3);
    rename("temp.mp3", mp3);

    return e_success;
}

sts read_tag_edit(FILE *fptr, char *tag, char *new_content) {
    int ind = get_index(helper, tag);
    if (ind == -1) {
        printf("Error: Invalid tag given\n");
        return e_failure;
    }

    while (fread(buffer, 4, 1, fptr) == 1) {
        buffer[4] = '\0';   // frame ID string

        int size = get_tag_size_edit(fptr);
        if (size < 0) break;

        unsigned char flags[2];
        if (fread(flags, 2, 1, fptr) != 1) break;

        if (strncmp(buffer, TAG[ind], 4) == 0) {
            // Write new frame with new content
            fwrite(buffer, 4, 1, temp);
            write_tag_size(temp, strlen(new_content) + 1); // include encoding
            fwrite(flags, 2, 1, temp);
            fputc(0x00, temp); // encoding byte
            fwrite(new_content, strlen(new_content), 1, temp);

            // Skip old frame data
            fseek(fptr, size, SEEK_CUR);

            printf("Edited Tag: %s\n", TAG[ind]);
}
 else {
            // Copy original frame
            fwrite(buffer, 4, 1, temp);
            write_tag_size(temp, size);
            fwrite(flags, 2, 1, temp);

            fread(buffer, size, 1, fptr);
            fwrite(buffer, size, 1, temp);
        }
    }
    return e_success;
}

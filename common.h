#ifndef COMMON_H
#define COMMON_H

typedef enum { e_view, e_edit, e_unsupported } oper;
typedef enum { e_success, e_failure } sts;

extern char *TAG[];
extern char *helper[];
extern char *tag_name[];

oper check_operation(char *);
sts open_mp3_view(FILE **, char *);
sts open_mp3_edit(FILE **, char *);

sts view_mp3(char *);
sts edit_mp3(char *,char *,char *);

sts read_tag_view(FILE *);
sts read_tag_edit(FILE *,char *,char *);
int get_index(char *[],char *);

void write_tag_size(FILE*,int);
int get_tag_size_view(FILE *);
int get_tag_size_edit(FILE *);
sts print_tag_content(char *, int);

#endif

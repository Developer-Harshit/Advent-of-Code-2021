#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
const char* find_path(int mode);
FILE* get_file(int mode);
char* read_line(FILE* file);
char* read_until(FILE* file ,char terminator);
char* _read_until(FILE* file ,int (*comparator)(int));
void free_line(char* line_data);
#endif
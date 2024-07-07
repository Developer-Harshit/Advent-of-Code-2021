#include "include/utils.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
const char* find_path(int mode){
    return mode == 0 ? "data/test.txt" : "data/input.txt";
}
FILE* get_file(int mode){
    const char* path = find_path(mode);
    return fopen(path, "r");
}
char* read_line(FILE* file){
    return read_until(file,'\n');
}
char* read_until(FILE* file ,char terminator){
    int c;
    int offset = 0;
    int buffer_size = sizeof(char) * 4;
    char* buffer = malloc(buffer_size);
    assert(buffer != NULL);
    while(c = fgetc(file) , c != terminator && c != EOF){
        if (offset == buffer_size - 1){
            buffer_size *=2;
            buffer = realloc(buffer, buffer_size);
            assert(buffer != NULL);
        }
        
        buffer[offset++] = (char)c;
    }
    if(c == EOF && offset == 0){
        free(buffer);
        return NULL;
    }
    if (offset < buffer_size-1) {
        buffer = realloc(buffer,offset +1);
        assert(buffer != NULL);
    }
    buffer[offset] = '\0';
    return buffer;
}

void free_line(char* line_data){
    free(line_data);
}

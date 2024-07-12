#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

const char* find_path(int mode);
FILE* get_file(int mode);
char* read_line(FILE* file);
char* read_until(FILE* file ,char terminator);
char* _read_until(FILE* file ,int (*comparator)(int));
void free_line(char* line_data);



#define array_functions(T) \
    typedef struct { \
        T * buffer; \
        int offset; \
        int size; \
    } Array_##T; \
    extern Array_##T array_##T##_create(); \
    extern void array_##T##_push( Array_##T * arr , T ele); \
    extern void array_##T##_shrink( Array_##T * arr); \
    extern void array_##T##_free( Array_##T * arr);

#define array_functions_impl(T) \
    Array_##T array_##T##_create(){ \
        Array_##T arr = {.buffer = malloc( sizeof( T ) * 4 ),.size = 4,.offset=0}; \
        assert(arr.buffer!=NULL); \
        return arr; \
    } \
    void array_##T##_push( Array_##T * arr , T ele){ \
        if (sizeof( T ) * arr->offset == arr->size - sizeof( T ) ){ \
            arr->size *= 2; \
            arr->buffer = realloc(arr->buffer, arr->size); \
            assert(arr->buffer != NULL); \
        } \
        arr->buffer[arr->offset] = ele; \
        arr->offset++; \
    } \
    void array_##T##_shrink( Array_##T * arr){ \
        if (arr->offset < arr->size-sizeof( T )) { \
            arr->size = sizeof( T ) * (arr->offset + 1); \
            arr->buffer = realloc(arr->buffer, arr->size); \
            assert(arr->buffer != NULL); \
        } \
    } \
    void array_##T##_free( Array_##T * arr){ \
        assert(arr->buffer != NULL); \
        free(arr->buffer); \
    }


#endif
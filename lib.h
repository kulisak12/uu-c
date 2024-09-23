#pragma once

#include <stdbool.h>

char* get_next_token(char** remaining, const char* delim);

typedef struct DynArray DynArray;
struct DynArray {
    int size;
    int capacity;
    int* values;
};

DynArray dynarray_create();
void dynarray_append(DynArray* array, int value);
void dynarray_print(DynArray* array);
bool dynarray_contains(DynArray* array, int value);
DynArray parse_int_list(char* line);
void dynarray_free(DynArray* array);

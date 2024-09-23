#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"

/**
 * @brief Find the next token in a string.
 * @param remaining Pointer to the remaining string to search. Will be modified. Will be set to NULL when no more tokens exist.
 * @param delim The delimiter to search for.
 * @return The next token in the string.
 */
char* get_next_token(char** remaining, const char* delim) {
    if (*remaining == NULL) {
        fprintf(stderr, "String to search is NULL.\n");
        exit(1);
    }
    char* token = *remaining;
    char* delim_pos = strstr(*remaining, delim);
    if (delim_pos == NULL) {
        *remaining = NULL;
        return token;
    }
    *delim_pos = '\0';
    *remaining = delim_pos + strlen(delim);
    return token;
}

DynArray dynarray_create() {
    int* values = malloc(sizeof(int));
    return (DynArray) { 0, 1, values };
}

void dynarray_append(DynArray* array, int value) {
    if (array->size == array->capacity) {
        array->capacity *= 2;
        int* old = array->values;
        int* new = malloc(array->capacity * sizeof(int));
        for (int i = 0; i < array->size; i++) {
            new[i] = old[i];
        }
        array->values = new;
        free(old);
    }
    array->values[array->size] = value;
    array->size++;
}

void dynarray_print(DynArray* array) {
    for (int i = 0; i < array->size; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", array->values[i]);
    }
    printf("\n");
}

bool dynarray_contains(DynArray* array, int value) {
    for (int i = 0; i < array->size; i++) {
        if (array->values[i] == value) {
            return true;
        }
    }
    return false;
}

DynArray parse_int_list(char* line) {
    DynArray list = dynarray_create();
    char* remaining = line;
    while (remaining != NULL) {
        char* token = get_next_token(&remaining, " ");
        if (strlen(token) == 0) {
            continue;
        }
        int value;
        sscanf(token, "%d", &value);
        dynarray_append(&list, value);
    }
    return list;
}

void dynarray_free(DynArray* array) {
    free(array->values);
}

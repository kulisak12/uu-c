#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct DynArray DynArray;
struct DynArray {
    int size;
    int capacity;
    int* values;
};

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

int get_card_points(char* line) {
    int card_id;
    int chars_read;
    sscanf(line, "Card %d: %n", &card_id, &chars_read);
    char* card_description = line + chars_read;
    const char* delim = " | ";
    char* bar_pos = strstr(card_description, delim);
    *bar_pos = '\0';
    DynArray winning_numbers = parse_int_list(card_description);
    DynArray my_numbers = parse_int_list(bar_pos + strlen(delim));
    int num_matches = 0;
    for (int i = 0; i < my_numbers.size; i++) {
        if (dynarray_contains(&winning_numbers, my_numbers.values[i])) {
            num_matches++;
        }
    }
    dynarray_free(&winning_numbers);
    dynarray_free(&my_numbers);
    if (num_matches == 0) {
        return 0;
    }
    int points = 1;
    for (int i = 1; i < num_matches; i++) {
        points *= 2;
    }
    return points;
}

int main(int argc, char* argv[]) {
    char* line = NULL;
    size_t buffer_len = 0;
    int point_sum = 0;
    while (getline(&line, &buffer_len, stdin) != -1) {
        line[strcspn(line, "\n")] = '\0'; // strip newline
        point_sum += get_card_points(line);
    }
    printf("%d\n", point_sum);
    free(line);
    return 0;
}

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"

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

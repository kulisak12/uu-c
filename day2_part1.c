#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"

int MAX_RED = 12;
int MAX_GREEN = 13;
int MAX_BLUE = 14;

bool is_color_possible(int number, char* color) {
    if (strcmp(color, "red") == 0 && number > MAX_RED) {
        return false;
    }
    if (strcmp(color, "green") == 0 && number > MAX_GREEN) {
        return false;
    }
    if (strcmp(color, "blue") == 0 && number > MAX_BLUE) {
        return false;
    }
    return true;
}

// modifies the argument
bool is_set_possible_internal(char* remaining) {
    const char* delim = ", ";
    while (remaining != NULL) {
        char* token = get_next_token(&remaining, delim);
        int number;
        int chars_read;
        sscanf(token, "%d %n", &number, &chars_read);
        char* color = token + chars_read;
        if (!is_color_possible(number, color)) {
            return false;
        }
    }
    return true;
}

bool is_set_possible(char* set_description) {
    char* remaining = malloc(strlen(set_description) + 1);
    strcpy(remaining, set_description);
    bool result = is_set_possible_internal(remaining);
    free(remaining);
    return result;
}

// modifies the argument
bool is_game_possible_internal(char* remaining) {
    const char* delim = "; ";
    while (remaining != NULL) {
        char* token = get_next_token(&remaining, delim);
        if (!is_set_possible(token)) {
            return false;
        }
    }
    return true;
}

bool is_game_possible(char* game_description) {
    char* remaining = malloc(strlen(game_description) + 1);
    strcpy(remaining, game_description);
    bool result = is_game_possible_internal(remaining);
    free(remaining);
    return result;
}

int main(int argc, char* argv[]) {
    char* line = NULL;
    size_t buffer_len = 0;
    int id_sum = 0;
    while (getline(&line, &buffer_len, stdin) != -1) {
        line[strcspn(line, "\n")] = '\0'; // strip newline
        int game_id;
        int chars_read;
        sscanf(line, "Game %d: %n", &game_id, &chars_read);
        char* game_description = line + chars_read;
        if (is_game_possible(game_description)) {
            id_sum += game_id;
        }
    }
    printf("%d\n", id_sum);
    free(line);
    return 0;
}

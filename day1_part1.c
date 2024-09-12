#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

int get_digit(char c) {
    return c - '0';
}

int get_first_digit(char* line) {
    while (*line != '\0') {
        if (is_digit(*line)) {
            return get_digit(*line);
        }
        line++;
    }
    return -1;
}

int get_last_digit(char* line) {
    int last_digit = -1;
    while (*line != '\0') {
        if (is_digit(*line)) {
            last_digit = get_digit(*line);
        }
        line++;
    }
    return last_digit;
}

int extract_value(char* line) {
    int first_digit = get_first_digit(line);
    int last_digit = get_last_digit(line);
    if (first_digit == -1 || last_digit == -1) {
        fprintf(stderr, "Invalid input: %s\n", line);
        exit(1);
    }
    return 10 * first_digit + last_digit;
}

int main(int argc, char* argv[]) {
    char* line = NULL;
    size_t buffer_len = 0;
    int value_sum = 0;
    while (getline(&line, &buffer_len, stdin) != -1) {
        value_sum += extract_value(line);
    }
    printf("%d\n", value_sum);
    free(line);
    return 0;
}

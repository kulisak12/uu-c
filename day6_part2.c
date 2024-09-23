#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"

typedef long long ll;

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

int get_digit(char c) {
    return c - '0';
}

ll combine_digits_on_line(char* line) {
    ll result = 0;
    while (*line != '\0') {
        if (is_digit(*line)) {
            int digit = get_digit(*line);
            result = result * 10 + digit;
        }
        line++;
    }
    return result;
}

typedef struct {
    ll time;
    ll distance;
} InputData;

InputData parse_input() {
    InputData input_data;
    char* line = NULL;
    size_t buffer_len = 0;
    getline(&line, &buffer_len, stdin);
    input_data.time = combine_digits_on_line(line);
    getline(&line, &buffer_len, stdin);
    input_data.distance = combine_digits_on_line(line);
    free(line);
    return input_data;
}

ll calculate_number_of_ways_to_win(ll time, ll distance_to_beat) {
    ll num_ways = 0;
    // omitting press_time = 0 and press_time = time
    for (ll press_time = 1; press_time < time; press_time++) {
        ll distance = press_time * (time - press_time);
        if (distance > distance_to_beat) {
            num_ways++;
        }
    }
    return num_ways;
}

int main(int argc, char* argv[]) {
    InputData input_data = parse_input();
    ll result = calculate_number_of_ways_to_win(input_data.time, input_data.distance);
    printf("%lld\n", result);
    return 0;
}

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"

typedef struct {
    DynArray times;
    DynArray distances;
} InputData;

InputData parse_input() {
    InputData input_data;
    const char* delim = ":";
    char* line = NULL;
    size_t buffer_len = 0;
    getline(&line, &buffer_len, stdin);
    // line[strcspn(line, "\n")] = '\0'; // strip newline
    char* times_str = strstr(line, delim) + strlen(delim);
    input_data.times = parse_int_list(times_str);
    getline(&line, &buffer_len, stdin);
    char* distances_str = strstr(line, delim) + strlen(delim);
    input_data.distances = parse_int_list(distances_str);
    free(line);
    return input_data;
}

int calculate_number_of_ways_to_win(int time, int distance_to_beat) {
    int num_ways = 0;
    // omitting press_time = 0 and press_time = time
    for (int press_time = 1; press_time < time; press_time++) {
        int distance = press_time * (time - press_time);
        if (distance > distance_to_beat) {
            num_ways++;
        }
    }
    return num_ways;
}

int main(int argc, char* argv[]) {
    InputData input_data = parse_input();
    int result = 1;
    for (int i = 0; i < input_data.times.size; i++) {
        int time = input_data.times.values[i];
        int distance = input_data.distances.values[i];
        result *= calculate_number_of_ways_to_win(time, distance);
    }
    dynarray_free(&input_data.times);
    dynarray_free(&input_data.distances);
    printf("%d\n", result);
    return 0;
}

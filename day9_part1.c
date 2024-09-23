#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"

bool write_differences(DynArray seq, int last_index) {
    bool has_nonzero = false;
    for (int i = 0; i < last_index; i++) {
        int difference = seq.values[i + 1] - seq.values[i];
        if (difference != 0) {
            has_nonzero = true;
        }
        seq.values[i] = difference;
    }
    return has_nonzero;
}

int extrapolate_sequence(DynArray seq) {
    int last_index = seq.size - 1;
    while (write_differences(seq, last_index)) {
        last_index--;
    }
    // result is the sum of remaining values
    int sum = 0;
    for (int i = last_index; i < seq.size; i++) {
        sum += seq.values[i];
    }
    return sum;
}

int main(int argc, char* argv[]) {
    char* line = NULL;
    size_t buffer_len = 0;
    int extrapolate_sum = 0;
    while (getline(&line, &buffer_len, stdin) != -1) {
        DynArray sequence = parse_int_list(line);
        extrapolate_sum += extrapolate_sequence(sequence);
        dynarray_free(&sequence);
    }
    printf("%d\n", extrapolate_sum);
    free(line);
    return 0;
}

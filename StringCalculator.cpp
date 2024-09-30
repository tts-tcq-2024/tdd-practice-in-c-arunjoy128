#include "StringCalculator.h"
int add(const char* input) {
    if (strcmp(input, "0") == 0) {
        return 0;
    }
    
    if (contains_only_non_numeric(input)) {
        return 0;
    }

    char delimiter = ',';
    const char* number_start = input;

    // Check for custom delimiter format
    if (input[0] == '/' && input[1] == '/') {
        delimiter = input[2];
        number_start = strchr(input, '\n') + 1;
    }

    char input_copy[100];
    strcpy(input_copy, number_start);

    // Replace newlines and custom delimiter with commas
    for (int i = 0; i < strlen(input_copy); ++i) {
        if (input_copy[i] == '\n' || input_copy[i] == delimiter) {
            input_copy[i] = ',';
        }
    }

    char* token = strtok(input_copy, ",");
    int sum = 0;

    while (token != NULL) {
        int number = atoi(token);
        if (number <= 1000) {
            sum += number;
        }
        token = strtok(NULL, ",");
    }

    return sum;
}

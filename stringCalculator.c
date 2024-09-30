#include <ctype.h>  // for isdigit
#include <string.h> // for strlen
#include "StringCalculator.h"

// Helper function to check if the input contains only non-numeric characters
int contains_only_non_numeric(const char* input) {
    for (int i = 0; i < strlen(input); ++i) {
        if (isdigit(input[i])) {
            return 0; // False, the input contains a number
        }
    }
    return 1; // True, no digits found
}

int add(const char* input) {
    // If the input contains only non-numeric characters, return 0
    if (contains_only_non_numeric(input)) {
        return 0;
    }
    
    // Placeholder for future cases
    return -1;
}

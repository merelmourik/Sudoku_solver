#include "sudoku.h"

void invalid_input() {
    printf("Invalid input, please try again\n");
    exit(1);
}

void validate_input(char *str) {
    if (strlen(str) != 89)
        invalid_input();
    for (int i = 0; str[i] != '\0' ; i++) {
        if (str[i] != '.' && str[i] != ' ' && (str[i] < '1' || str[i] > '9'))
            invalid_input();
        if (i % 10 == 0 && i != 0)
            if (str[i - 1] != ' ')
                invalid_input();
    }
    return ;
}

#include "sudoku.h"

void invalid_input() {
    printf("Invalid input, please try again\n");
    exit(1);
}

void validate_input(char *str) {
    if (strlen(str) != 89)
        invalid_input();
    for (int i = 0; str[i] != '\0' ; i++)
        if (str[i] != '.' && str[i] != ' ' && (str[i] < '1' || str[i] > '9'))
            invalid_input();
}

void create_raster(char *str) {

}

int main(int argc, char **argv) {
    if (argc == 2){
        validate_input(argv[1]);
        create_raster(argv[1]);
    }
    else {
        printf("Please enter one argument\n");
        return (0);     //or exit?
    }
    return (0);
}
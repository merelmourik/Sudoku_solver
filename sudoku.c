#include "sudoku.h"

void invalid_input() {
    printf("Invalid input, please try again\n");
    exit(1);
}

void validate_input(char *str) {
    int j = 0;
    
    if (strlen(str) != 89)      // check amount of characters
        invalid_input();
    for (int i = 0; str[i] != '\0' ; i++)      // check if it are the correct characters
        if (str[i] != '.' && str[i] != ' ' && (str[i] < '1' || str[i] > '9'))
            invalid_input();
    for (int i = 0; str[i - 1] != '\0'; i++)      // check if the spaces are at the correct position
        if ((i) % 9 == 0 && i != 0) {
            if (str[i + j] != ' ')
                invalid_input();
            j++;
        }

    // for (int i = 0; str[i] != '\0'; i++) {
    //     if (i % 9 == 0 && i != 0 && i != 81) {
    //         if (str[i + j] != ' ') {
    //             printf("hier %d %c", i, str[i]);
    //             invalid_input();
    //         }
    //         j++;
    //     }
    //     else {
    //         if (str[i] != '.' && (str[i] < '1' || str[i] > '9') && str[i + j] != ' ') {
    //             printf("%d\n", (i + j));
    //             printf("daar [%d] [%c]", i, str[i]);
    //             invalid_input();
    //         }
    //     }
    // }

    return ;
}

void create_raster(const char *str, Sudoku *sudoku) {
    sudoku->raster = (char*)malloc(sizeof(char) * 90);
    if (sudoku->raster == NULL)
        exit(1);
    sudoku->raster = strdup(str);
    sudoku->raster[89] = '\0';
}

int main(int argc, char **argv) {
    if (argc == 2){
        validate_input(argv[1]);
        Sudoku sudoku;
        create_raster(argv[1], &sudoku);
        printf("%s\n", sudoku.raster);
    }
    else {
        printf("Please enter one argument\n");
        return (0);     //or exit?
    }
    return (0);
}
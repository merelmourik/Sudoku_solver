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

char *make_row(const char *str, int start) {
    char *new = malloc(sizeof(char) * 10);
    if (new == NULL)
        exit(1);
    int i = 0;
    for (int i = 0; i < 9; i++)
        new[i] = str[i + start];
    return (new);
}

void create_raster(const char *str, char **raster) {
    int j = 0;

    for (int i = 0; i < 9; i++) {
        raster[i] = make_row(str, j);
        j += 10;
    }
    return ;
}

// void solve_sudoku(Sudoku *sudoku)
void print_sudoku(char **raster) {
    for (int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++)
            printf("%c ", raster[i][j]);
        printf("\n");
    }
    return ;
}

void free_raster(char **raster) {
    for (int i = 0; i < 9 ; i++)
        free(raster[i]);
}
int main(int argc, char **argv) {
    char **raster;

    if (argc == 2){
        validate_input(argv[1]);
        raster = (char **)malloc(sizeof(char *) * 9);
        if (raster == NULL)
            exit(1);
        create_raster(argv[1], raster);
        print_sudoku(raster);
        // solve_sudoku(&sudoku);
        // printf("%s\n", raster);
    }
    else {
        printf("Please enter one argument\n");
        return (0);     //or exit?
    }
    free_raster(raster);
    system("leaks a.out");
    return (0);
}
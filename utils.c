#include "main.h"

void print_sudoku(char **raster) {
    for (int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++)
            printf("%c ", raster[i][j]);
        printf("\n");
    }
    return ;
}

void free_sudoku(Sudoku *sudoku) {
    for (int i = 0; i < 9 ; i++)
        free(sudoku->raster[i]);
}

void create_raster(const char *str, Sudoku *sudoku) {
    sudoku->raster = (char **)malloc(sizeof(char *) * 9);
    if(!sudoku->raster)
        exit (1);
    int j = 0;

    for (int i = 0; i < 9; i++) {
        sudoku->raster[i] = make_row(str, j);
        j += 10;
    }
    return ;
}

char *make_row(const char *str, int start) {
    char *new = malloc(sizeof(char) * 10);
    if (new == NULL)
        exit(1);
    for (int i = 0; i < 9; i++)
        new[i] = str[i + start];
    return (new);
}

void invalid_input() {
    printf("Invalid input, please try again\n");
    exit(1);
}


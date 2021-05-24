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
    int i = 0;

    for (int y = 0; y < 9; y++) {
        sudoku->raster[y] = make_row(str, i);
        i += 10;
    }
    return ;
}

char *make_row(const char *str, int i) {
    char *new = malloc(sizeof(char) * 10);
    if (new == NULL)
        exit(1);
    for (int x = 0; x < 9; x++)
        new[x] = str[x + i];
    return (new);
}

void invalid_input() {
    printf("Invalid input, please try again\n");
    exit(1);
}


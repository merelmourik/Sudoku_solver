#include "sudoku.h"

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
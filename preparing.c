#include "sudoku.h"

void create_raster(const char *str, Sudoku *sudoku) {
    int j           = 0;
    sudoku->raster  = (char **)malloc(sizeof(char *) * 9);

    if(!sudoku->raster)
        exit (1);
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

int count_empty_boxes(char **raster) {
    int count = 0;

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            if (raster[i][j] == '.')
                count++;
        }
    return count;
}

int get_empty_boxes(Sudoku *sudoku) {
    int count   = count_empty_boxes(sudoku->raster);
    int k       = 0;

    sudoku->empty_box = (int **)malloc(sizeof(int *) * count);
    if (!sudoku->empty_box)
        exit(1);
    for (int i = 0; i < count; i++) {
        sudoku->empty_box[i] = (int *)malloc(sizeof(int) * 2);
        if (!sudoku->empty_box[i])
            exit(1);
    }
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            if (sudoku->raster[y][x] == '.') {
                sudoku->empty_box[k][0] = y;
                sudoku->empty_box[k][1] = x;
                k++;
            }
        }
    }
    return(count);
}
#include "sudoku.h"

int check_the_box(char **raster, int y, int x, int find) {
    find    += 48;
    int j   = y - 3;

    while(j < y) {
        int i = x - 3;
        while (i < x) {
            if (raster[j][i] == find)
                return (-1);
            i++;
        }
        j++;
    }
    return (0);
}

int check_box(char **raster, int y, int x, int find) {
    if (y < 3) {
        if (x < 3)
            return (check_the_box(raster, 3, 3, find));
        if (x > 2 && x < 6)
            return(check_the_box(raster, 3, 6, find));
        else
            return(check_the_box(raster, 3, 9, find));
    }
    else if (y > 2 && y < 6) {
        if (x < 3)
            return (check_the_box(raster, 6, 3, find));
        if (x > 2 && x < 6)
            return(check_the_box(raster, 6, 6, find));
        else
            return(check_the_box(raster, 6, 9, find));
    }
    else if (y > 5 && y < 9){
        if (x < 3)
            return (check_the_box(raster, 9, 3, find));
        if (x > 2 && x < 6)
            return(check_the_box(raster, 9, 6, find));
        else
            return(check_the_box(raster, 9, 9, find));
    }
    return (-1);
}

int check_row(char *row, int find) {
    find += 48;      

    for (int x = 0; x < 9; x++)
        if (row[x] == find)
            return (-1);
    return (0);
}

int check_column(Sudoku *sudoku, int x, int find) {
    find += 48;
    
    for (int y = 0; y < 9; y++) {
        if (sudoku->raster[y][x] == find)
            return (-1);
    }
    return (0);
}

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

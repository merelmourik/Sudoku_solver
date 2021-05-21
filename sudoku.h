#ifndef SUDOKU_H
# define SUDOKU_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Sudoku {
    int     **empty_box;
    char    **raster;
    int     count;
    int     location;
} Sudoku ;

void print_sudoku(char **raster);
void free_sudoku(Sudoku *sudoku);
void create_raster(const char *str, Sudoku *sudoku);
char *make_row(const char *str, int start);
void invalid_input();


#endif

/*
4.129..75 2..3..8.. .7..8...6 ...1.3.62 1.5...4.3 73.6.8... 6...2..3. ..7..1..4 89..651.7
*/
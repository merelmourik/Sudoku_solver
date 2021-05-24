#ifndef SUDOKU_H
# define SUDOKU_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Sudoku {
    int     **empty_box;
    char    **raster;
} Sudoku ;

char    *make_row(const char *str, int start);

int     count_empty_boxes(char **raster);
int     get_empty_boxes(Sudoku *sudoku);
int     check_column(Sudoku *sudoku, int x, int find);
int     check_row(char *row, int find);
int     check_box(char **raster, int y, int x, int find);
int     check_the_box(char **raster, int y, int x, int find);

void    print_sudoku(char **raster);
void    free_sudoku(Sudoku *sudoku);
void    invalid_input();
void    validate_input(char *str);
void    create_raster(const char *str, Sudoku *sudoku);
void    unsolvable_sudoku();

#endif

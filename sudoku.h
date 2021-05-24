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

void print_sudoku(char **raster);
void free_sudoku(Sudoku *sudoku);
void create_raster(const char *str, Sudoku *sudoku);
char *make_row(const char *str, int start);
void invalid_input();
void validate_input(char *str);
int count_empty_boxes(char **raster);
int get_empty_boxes(Sudoku *sudoku);
int check_column(Sudoku *sudoku, int x, int find);
int check_row(char *row, int find);
int check_box(char **raster, int y, int x, int find);
int check_the_box(char **raster, int y, int x, int find);


#endif

//4.129..75 2..3..8.. .7..8...6 ...1.3.62 1.5...4.3 73.6.8... 6...2..3. ..7..1..4 89..651.7
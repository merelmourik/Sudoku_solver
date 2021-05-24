#include "sudoku.h"

void solve_sudoku(Sudoku *sudoku) {
    int count   = get_empty_boxes(sudoku);
    int j       = 1;
    int y       = sudoku->empty_box[0][0];
    int x       = sudoku->empty_box[0][1];

    for (int box = 0; box <= count; box++)
        while (j < 10) {
            if (check_row(sudoku->raster[y], j) == 0)       
                if (check_column(sudoku, x, j) == 0)     
                    if (check_box(sudoku->raster, y, x, j) == 0)
                    {    
                        sudoku->raster[y][x] = j + 48;     
                        if (box == count)    
                            break;
                        j = 1;
                        y = sudoku->empty_box[box][0];     
                        x = sudoku->empty_box[box][1];     
                        break;
                    }
            j++;
            if (j == 10) {
                if (box == 1)
                    return (unsolvable_sudoku());
                box -= 2;    
                sudoku->raster[y][x] = '.';
                y = sudoku->empty_box[box][0];
                x = sudoku->empty_box[box][1]; 
                j = sudoku->raster[y][x] - 48;
                break ;
            }
        }
    print_sudoku(sudoku->raster);
}

int main(int argc, char **argv) {
    system("clear");
    Sudoku *sudoku = malloc(sizeof(Sudoku));
    if (!sudoku)
        return (-1);
    if (argc == 2){
        validate_input(argv[1]);
        create_raster(argv[1], sudoku);
        print_sudoku(sudoku->raster);
        printf("\nPress a key to solve the sudoku\n");
        getchar();
        system("clear");
        solve_sudoku(sudoku);
    }
    else {
       printf("Please enter one argument\n");
       return (0);
    }
    free_sudoku(sudoku);
    return (0);
}

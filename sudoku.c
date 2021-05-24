#include "sudoku.h"

void solve_sudoku(Sudoku *sudoku) {
    int count   = get_empty_boxes(sudoku);
    int box     = 0;
    int j       = 1;
    int y       = sudoku->empty_box[box][0];
    int x       = sudoku->empty_box[box][1];

    while (box <= count) { 
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
                if (box == 0) {
                    printf("If I can't solve this sudoku, no one can!\n");
                    free_sudoku(sudoku);
                    return ;
                }
                box -= 2;    
                sudoku->raster[y][x] = '.';
                y = sudoku->empty_box[box][0];
                x = sudoku->empty_box[box][1]; 
                j = sudoku->raster[y][x] - 48;
                break ;
            }
        }
        box++;
    }
}

int main(int argc, char **argv) {
    system("clear");
    Sudoku *sudoku = malloc(sizeof(Sudoku));
    (void)argc;

    if (!sudoku)
        return (-1);
//    if (argc != 2){
    argv[1] = "...7...9. ..9.3..6. 8..6..432 7....36.. .2..7..5. ..85....7 981..7..6 .4..9.2.. .6...5...";
    validate_input(argv[1]);
    create_raster(argv[1], sudoku);
    print_sudoku(sudoku->raster);
    // //wait for key press and then solve
    solve_sudoku(sudoku);
    printf("\n");
    printf("Press a key to solve the sudoku\n");
    getchar();
    system("clear");
    print_sudoku(sudoku->raster);
//    }
//    else {
//        printf("Please enter one argument\n");
//        return (0);     //or exit?
//    }
    free_sudoku(sudoku);
    // system("leaks a.out");
    return (0);
}
//validating, preparing, solving
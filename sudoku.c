#include "sudoku.h"

void solve_sudoku(Sudoku *sudoku) {
    get_empty_boxes(sudoku);

    int i = 0;
    int j = 1;
    int box = 0;
    int y = sudoku->empty_box[box][0];
    int x = sudoku->empty_box[box][1];
    while (i < sudoku->count) { // zo lang niet alle lege boxes zijn gevonden
        while (j < 10) {
            if (check_row(sudoku->raster[y], j) == 0)       //row check
                if (check_column(sudoku, x, j) == 0)        //column check
                    if (check_box(sudoku->raster, y, x, j) == 0)
                    {      //box check
                        sudoku->raster[y][x] = j + 48;      //filling in the blanc spot
                        if (i == sudoku->count - 1)     //of NULL terminaten
                            break;
                        box++;      //go to the next empty spot
                        j = 1;
                        y = sudoku->empty_box[box][0];      //communicate the x of the empty box
                        x = sudoku->empty_box[box][1];      //communicate the y of the empty box
                        break;
                    }
            j++;
            //796854321 243176985 851239476 137965842 925418763 468723519 614597238 582341697 379682154
            if (j == 10) {
                if (i != 0)
                    i -= 2;
                if (box != 0)
                    box--;      // de oude j moet hier goed worden gereset
                sudoku->raster[y][x] = '.';
                y = sudoku->empty_box[box][0];
                x = sudoku->empty_box[box][1];      //communicate the x of the empty box
                j = sudoku->raster[y][x] - 48;
                break ;
            }
        }
        i++;
    }
}

int main(int argc, char **argv) {
    Sudoku *sudoku = malloc(sizeof(Sudoku));
    (void)argc;

    if (!sudoku)
        return (-1);
//    if (argc != 2){
    argv[1] = "...7...9. ..9.3..6. 8..6..432 7....36.. .2..7..5. ..85....7 981..7..6 .4..9.2.. .6...5...";
            //79....3.. .....69.. 8...3..76 .....5..2 ..54187.. 4..7..... 61..9...8 ..23..... ..9....54
    validate_input(argv[1]);
    create_raster(argv[1], sudoku);
    print_sudoku(sudoku->raster);
    // //wait for key press and then solve
    solve_sudoku(sudoku);
    printf("\n");
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
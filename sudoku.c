#include "sudoku.h"

void validate_input(char *str) {
    if (strlen(str) != 89)
        invalid_input();
    for (int i = 0; str[i] != '\0' ; i++) {
        if (str[i] != '.' && str[i] != ' ' && (str[i] < '1' || str[i] > '9'))
            invalid_input();
        if (i % 10 == 0 && i != 0)
            if (str[i - 1] != ' ')
                invalid_input();
    }
    return ;
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

void get_empty_boxes(Sudoku *sudoku) {
    sudoku->count = count_empty_boxes(sudoku->raster);
    sudoku->empty_box = (int **)malloc(sizeof(int *) * sudoku->count + 1);
    if (!sudoku->empty_box)
        exit(1);
    for (int i = 0; i < sudoku->count; i++) {
        sudoku->empty_box[i] = (int *)malloc(sizeof(int) * 2);
        if (!sudoku->empty_box[i])
            exit(1);
    }
    int k = 0;
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            if (sudoku->raster[y][x] == '.') {
                sudoku->empty_box[k][0] = y;
                sudoku->empty_box[k][1] = x;
                k++;
            }
        }
    }
    sudoku->empty_box[k] = NULL;
}


int check_the_box(char **raster, int y, int x, int find) {
    find += 48;
    int j = y - 3;

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
    find += 48;         //to transfer to character in ascii
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

//https://voorbeginners.info/sudoku-puzzels/makkelijk-1-oplossing.htm
//796854321 243176985 851239476 137965842 925418763 468723519 614597238 582341697 379682154

//bij de 8e gaat hij ongeveer verkeerd j zou 6 moeten zijn
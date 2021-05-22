#include "main.h"

void validate_input(char *str) {
    int j = 0;

    if (strlen(str) != 89)      // check amount of characters
        invalid_input();
    for (int i = 0; str[i] != '\0' ; i++)      // check if it are the correct characters
        if (str[i] != '.' && str[i] != ' ' && (str[i] < '1' || str[i] > '9'))
            invalid_input();
    for (int i = 0; str[i - 1] != '\0'; i++)      // check if the spaces are at the correct position
        if ((i) % 9 == 0 && i != 0) {
            if (str[i + j] != ' ' && i != 81)
                invalid_input();
            j++;
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
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku->raster[i][j] == '.') {
                sudoku->empty_box[k][0] = i;
                sudoku->empty_box[k][1] = j;
                k++;
            }
        }
    }
    sudoku->empty_box[k] = NULL;
}

int check_row(char *row, int find) {
    find += 48;         //to transfer to character in ascii
    for (int i = 0; i < 9; i++) {
        if (row[i] == find)
            return (-1);
    }
    return (0);
}

int check_column(char **raster, int x, int find) {
    find += 48;         //to transfer to character in ascii
    if (x == 0 && find == 1) {
        for (int j = 0; j < 9; j++)
            printf("%s\n", raster[j]);
    }
    for (int i = 0; i < 9; i++) {
        if (raster[x][i] == find)
            return (-1);
    }
    return (0);
}

int check_the_box(char **raster, int x, int y, int find) {
    find += 48;
    int i = x - 3;

    while (i < x) {
        int j = y - 3;
        while (j < y) {
            if (raster[j][i] == find)
                return (-1);
            j++;
        }
        i++;
    }
    return (0);
}

int check_box(char **raster, int x, int y, int find) {
    if (x < 3) {
        if (y < 3)
            return (check_the_box(raster, 3, 3, find));
        if (y > 2 && y < 6)
            return(check_the_box(raster, 6, 3, find));
        else
            return(check_the_box(raster, 9, 3, find));
    }
    if (x > 2 && x < 6) {
        if (y < 3)
            return (check_the_box(raster, 3, 6, find));
        if (y > 2 && y < 6)
            return(check_the_box(raster, 6, 6, find));
        else
            return(check_the_box(raster, 9, 6, find));
    }
    else {
        if (y < 3)
            return (check_the_box(raster, 3, 9, find));
        if (y > 2 && y < 6)
            return(check_the_box(raster, 6, 9, find));
        else
            return(check_the_box(raster, 9, 9, find));
    }
}

void solve_sudoku(Sudoku *sudoku) {
    get_empty_boxes(sudoku);

    int i = 0;
    int j = 1;
    int box = 0;
    int x = sudoku->empty_box[box][0];
    int y = sudoku->empty_box[box][1];
    while (i < sudoku->count) { // zo lang niet alle lege boxes zijn gevonden
        while (j < 10) {
            if (check_row(sudoku->raster[x], j) == 0)       //row check
                if (check_column(sudoku->raster, x, j) == 0)        //column check
                    if (check_box(sudoku->raster, x, y, j) == 0) {      //box check
                        sudoku->raster[x][y] = j + 48;      //filling in the blanc spot
                        if (i == sudoku->count - 1)     //of NULL terminaten
                            break;
                        box++;      //go to the next empty spot
                        j = 1;
                        x = sudoku->empty_box[box][0];      //communicate the x of the empty box
                        y = sudoku->empty_box[box][1];      //communicate the y of the empty box
                        break;
                    }
            j++;
            if (j == 10) {
                if (i != 0)
                    i -= 2;
                if (box != 0)
                    box--;      // de oude j moet hier goed worden gereset
                sudoku->raster[x][y] = '.';
                x = sudoku->empty_box[box][0];      //communicate the x of the empty box
                y = sudoku->empty_box[box][1];
                j = sudoku->raster[x][y] - 48;
                break ;     // er moet ergens een punt worden gezet
            }
        }
        i++;
    }

    /*
    - vind een punt (we gaan van links naar rechts, naar boven naar beneden)
    - zet daar het laagst mogelijke nummer in wat kan
    - check of dat getal in het vierkantje kan
    - check of dat getal in de column can
    - check of dat getal in de rij kan
    - niet check? zet er een getal hoger neer en doe weer de checks
    - allemaal check?
    - onthoud de locatie van waar je was gebleven (en die van die daarvoor?)
    - ga naar de volgende punt en zet daar het volgende oplopende getal is
    - voor de checks weer uit
    - allemaal mooi? continue ->
    - allemaal niet zo mooi? delete waar je was het getal en zet er weer een punt neer
    - ga naar de vorige plek en zet een getal hoger neer
    - doe de checks weer
    - bij het getal 9 aangekomen en het werkt nog steeds niet?
    - go nog een locatie terug en doe daar hetzelfde
    */
}

int main(int argc, char **argv) {
    Sudoku *sudoku = malloc(sizeof(Sudoku));
    (void)argc;

//    if (!sudoku)
//        return (-1);
//    if (argc != 2){
    argv[1] = "79....3.. .....69.. 8...3..76 .....5..2 ..54187.. 4..7..... 61..9...8 ..23..... ..9....54";
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

//825397641 194652873 763418295 612789534 459263187 387145962 231976458 978524316 546831729
//.7......5 .26.5.47. ..38.61.. ..5.....2 ...7.8... 4.....3.. ..29.75.. .87.6.23. 3......9.
//79....3.. .....69.. 8...3..76 .....5..2 ..54187.. 4..7..... 61..9...8 ..23..... ..9....54
//https://voorbeginners.info/sudoku-puzzels/makkelijk-1-oplossing.htm

//bij de 8e gaat hij ongeveer verkeerd j zou 6 moeten zijn
#include "sudoku.h"

void validate_input(char *str) {
    int j = 0;
    
    if (strlen(str) != 89)      // check amount of characters
        invalid_input();
    for (int i = 0; str[i] != '\0' ; i++)      // check if it are the correct characters
        if (str[i] != '.' && str[i] != ' ' && (str[i] < '1' || str[i] > '9'))
            invalid_input();
    for (int i = 0; str[i - 1] != '\0'; i++)      // check if the spaces are at the correct position
        if ((i) % 9 == 0 && i != 0) {
            if (str[i + j] != ' ')
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
    sudoku->empty_box = (int **)malloc(sizeof(int *) * sudoku->count);
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
}

int check_row(char *row, int find) {
    find += 48;         //to transfer to character in ascii
    for (int i = 0; i < 9; i++) {
        if (row[i] == find)
            return (-1);
    }
    return (0);
}

int check_column(char *column, int find) {
    find += 48;         //to transfer to character in ascii
    for (int i = 0; i < 9; i++) {
        if (column[i] == find)
            return (-1);
    }
    return (0);
}

int check_the_box(char **raster, int x, int y, int find) {
    find += 48;
    int i = x + 3;
    int j = y + 3;

    while (x < i) {
        while (y < j) {
            if (raster[x][y] == find)
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
            return (check_the_box(raster, 0, 0, find));
        if (y > 2 && y < 6) 
            return(check_the_box(raster, 3, 0, find));
        else
            return(check_the_box(raster, 6, 0, find));
    }
    if (x > 2 && x < 6) {
        if (y < 3) 
            return (check_the_box(raster, 0, 3, find));
        if (y > 2 && y < 6) 
            return(check_the_box(raster, 3, 3, find));
        else
            return(check_the_box(raster, 6, 3, find));
    }
    else {
        if (y < 3) 
            return (check_the_box(raster, 0, 6, find));
        if (y > 2 && y < 6) 
            return(check_the_box(raster, 3, 6, find));
        else
            return(check_the_box(raster, 6, 6, find));
    }
}

int check_box(Sudoku *sudoku,) {
    // 0 is de x en 1 is de y
    int box = 0;
    int x = sudoku->empty_box[box][0];
    int y = sudoku->empty_box[box][1];
    int i = 0;
    while (i < sudoku->count) { // zo lang niet alle lege boxes zijn gevonden
        for (int j = 1; j < 10; j++;) {
            sudoku->raster[x][y] = j;   // locatie van een lege box
            if (check_row(sudoku->raster[x], j);
                if (check_column(sudoku->raster[y], j));
                    if (check_box(sudoku->raster, x, y, j));
                        break;
            j++;
        }
    }
}

void solve_sudoku(Sudoku *sudoku) {
    get_empty_boxes(sudoku);

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

    if (!sudoku)
        return (-1);
    if (argc == 2){
        validate_input(argv[1]);
        create_raster(argv[1], sudoku);
        print_sudoku(sudoku->raster);
        // //wait for key press and then solve
        solve_sudoku(sudoku);
    }
    else {
        printf("Please enter one argument\n");
        return (0);     //or exit?
    }
    free_sudoku(sudoku);
    // system("leaks a.out");
    return (0);
}
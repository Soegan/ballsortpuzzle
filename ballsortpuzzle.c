#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include "ballsortpuzzle.h"

void string_shuffle(char string[]) {
    int len = strlen(string);
    int j, temp;

    for (int i = len - 1; i > 0; i--) {
        j = rand() % (i + 1);
        temp = string[i];
        string[i] = string[j];
        string[j] = temp;
    }
}

void generator(const int rows, const int columns, char field[rows][columns]) {

    int emptyCol1 = rand() % columns;
    int emptyCol2 = rand() % columns;

    while (emptyCol1 == emptyCol2) {
        emptyCol2 = rand() % columns;
    }

    char symbols[12] = {'+', '*', '@', '^', '&', '$', '#', '%', '-', '=', '!', '?'};

    char string[rows * (columns - 2) + 1];

    int strIndex = 0;

    for (int i = 0; i < columns - 2; i++) {
        for (int j = 0; j < rows; j++) {
            string[strIndex] = symbols[i];
            strIndex++;
        }
    }
    string[strIndex] = '\0';
    string_shuffle(string);
    printf("%s\n", string);

    strIndex = 0;

    
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            if (i == emptyCol1 || i == emptyCol2) {
                field[j][i] = ' ';
                continue;
        }
            field[j][i] = string[strIndex];
            strIndex++;
        }
        
    }

}

void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y) {

    char tmpX;

    if (field[rows - 1][x - 1] == ' ' || field[0][y - 1] != ' ') {
        printf("Cannot use these columns!\n");
        return;
    }

    int rememberRowIndex;

    for (int i = 0; i < rows; i++) {
        if (field[i][x - 1] != ' ') {
            tmpX = field[i][x - 1];
            rememberRowIndex = i;
            break;
        }
    }

    if (field[rows - 1][y - 1] == ' ') {
        field[rows - 1][y - 1] = tmpX;
        field[rememberRowIndex][x - 1] = ' ';
    } else {
        for (int i = rows - 2; i >= 0; i--) {
            if (field[i][y - 1] == ' ' && field[i + 1][y - 1] == tmpX) {
                field[i][y - 1] = tmpX;
                field[rememberRowIndex][x - 1] = ' ';
                break;
            } else if (field[i][y - 1] == ' ' && field[i + 1][y - 1] != tmpX) {
                printf("MUST BE SAME!\n");
                break;
            }
        }
    }
    
}

bool check(const int rows, const int columns, char field[rows][columns]) {

    for (int j = 0; j < columns; j++) {
        char first = field[0][j];

        for (int i = 1; i < rows; i++) {
            if (field[i][j] != first) {
                return false;
            }
        }
    }

    return true;
}

void game_field(const int rows, const int columns, char field[rows][columns]) {
    for (int i = 0; i < rows; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < columns; j++) {
            printf(" %c |", field[i][j]);
        }
        printf("\n");
    }

    printf("  ");
    for (int j = 0; j < columns; j++) {
        printf("--- ");
    }
    printf("\n");

    printf("  ");
    // for (int j = 0; j < columns; j++) {
    //     printf(" %d ", j + 1);
    // }
    printf(" 1");
    for (int j = 1; j < columns; j++) {
        printf("   %d", j + 1);
    }
    printf("\n");
}

void ball_sort_puzzle() {
    int rows = 4;
    int cols = 6;
    char field[rows][cols];
    int x, y;

    srand(time(NULL));

    generator(rows, cols, field);

    game_field(rows, cols, field);

    check(rows, cols, field);
    
    while (!check(rows, cols, field)) {
        printf("Enter what: ");
        scanf("%d", &x);

        printf("Enter where: ");
        scanf("%d", &y);

        if (x > cols || y > rows || x < 1 || y < 1) {
            printf("Cannot use these symbols!\n");
            continue;
        } 
        

        down_possible(rows, cols, field, x, y);

        game_field(rows, cols, field);

    }
    printf("Pobeda, nalivai!\n");
    
}
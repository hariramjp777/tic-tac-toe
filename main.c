#include <stdio.h>
#include "tic_tac_toe.c"
#include <unistd.h>

int main(void) {
    char symbol;
    system("cls");
    do {
        printf("\nEnter your Symbol (X / O): ");
        scanf("\n%c", &symbol);
    } while (symbol != 'X' && symbol != 'O');
    TicTacToe* game = constructTicTacToe(symbol);
    play(game);
    free(game);
}
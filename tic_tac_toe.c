#include <stdio.h>
#include <stdlib.h>
#define BOARD_SIZE 3
#define POS_SIZE 8

typedef char* string;

typedef struct {
    char user;
    char computer;
    char board[BOARD_SIZE][BOARD_SIZE];
    string positions[POS_SIZE][BOARD_SIZE];
    char* user_last_pos;
    char* computer_last_pos;
} TicTacToe;

TicTacToe* constructTicTacToe(char user);

TicTacToe* constructTicTacToe(char user) {
    TicTacToe* game = (TicTacToe*) (malloc(sizeof(TicTacToe)));
    game->user = user;
    game->computer = user == 'X' ? 'O' : 'X';
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            game->board[i][j] = ' ';
        }
    }
    string positions[][BOARD_SIZE] = {
        {"00", "01", "02"},
        {"10", "11", "12"},
        {"20", "21", "22"},
        {"00", "10", "20"},
        {"01", "11", "21"},
        {"02", "12", "22"},
        {"00", "11", "22"},
        {"02", "11", "20"}
    };
    for (int i = 0; i < POS_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            game->positions[i][j] = positions[i][j];
        }
    }
    game->user_last_pos = "";
    game->computer_last_pos = "";
    return game;
}
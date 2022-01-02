#include <stdio.h>
#include <stdlib.h>
#define BOARD_SIZE 3
#define POS_SIZE 8

typedef struct {
    char name;
    char* last_pos;
} Player;

typedef struct {
    Player* user;
    Player* computer;
    char board[BOARD_SIZE][BOARD_SIZE];
    char* positions[POS_SIZE][BOARD_SIZE];
    Player* current;
} TicTacToe;

TicTacToe* constructTicTacToe(char user_name);
void printBoard(TicTacToe* game);

TicTacToe* constructTicTacToe(char user_name) {
    TicTacToe* game = (TicTacToe*) (malloc(sizeof(TicTacToe)));
    if (game == NULL) {
        return NULL;
    }
    game->user = (Player*) (malloc(sizeof(Player)));
    game->computer = (Player*) (malloc(sizeof(Player)));
    if (game->user == NULL || game->computer == NULL) {
        return NULL;
    }
    game->user->name = user_name;
    game->user->last_pos = "";
    game->computer->name = user_name == 'X' ? 'O' : 'X';
    game->computer->last_pos = "";
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            game->board[i][j] = ' ';
        }
    }
    char* positions[][BOARD_SIZE] = {
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
    game->current = game->user; // user first
    return game;
}

void printBoard(TicTacToe* game) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", game->board[i][j]);
        }
        printf("\n");
    }
}
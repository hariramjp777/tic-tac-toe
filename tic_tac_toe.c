#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BOARD_SIZE 3
#define POS_SIZE 8

typedef struct {
    char name;
    char last_pos[3];
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
char* computePosition(TicTacToe* game);
char* winningPosition(char board[][BOARD_SIZE], char* positions[][BOARD_SIZE], Player* player);
char* winningPosition_helper(char board[][BOARD_SIZE], char* positions[][BOARD_SIZE], int i, char name);
int integer(char c);
char character(int x);
void mark(TicTacToe* game, char* pos);
Player* getOpponent(TicTacToe* game);
char* randomPosition(TicTacToe* game);
int gameOver(TicTacToe* game);
int alreadyFilled(TicTacToe* game, char* pos);

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
    game->user->last_pos[0] = '\0';
    game->computer->name = user_name == 'X' ? 'O' : 'X';
    game->computer->last_pos[0] = '\0';
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

void play(TicTacToe* game) {
    char pos[2];
    int is_game_over;
    int count = 0;
    while(1) {
        count += 2;
        system("cls");
        printf("\n");
        printBoard(game);
        printf("\n");
        do {
            printf("> ");
            scanf("%s", pos);
        } while (alreadyFilled(game, pos));
        mark(game, pos);
        if (count < 9) {
            char* magic_pos = computePosition(game);
            mark(game, magic_pos);
            free(magic_pos);
        }
        is_game_over = gameOver(game);
        if (is_game_over == -1) {
            continue;
        }
        else {
            system("cls");
            printf("\n");
            printBoard(game);
            printf("\n");
            if (is_game_over == 0) {
                printf("It's a tie");
            }
            else if (is_game_over == 1) {
                printf("You win the game!");
            }
            else {
                printf("You lost the game!");
            }
            printf("\n");
            break;
        }
    }
}

int alreadyFilled(TicTacToe* game, char* pos) {
    int x = integer(pos[0]);
    int y = integer(pos[1]);
    return game->board[x][y] != ' ';
}

void mark(TicTacToe* game, char* pos) {
    int x = integer(pos[0]);
    int y = integer(pos[1]);
    game->board[x][y] = game->current->name;
    game->current->last_pos[0] = pos[0];
    game->current->last_pos[1] = pos[1];
    game->current->last_pos[2] = pos[2];
    game->current = getOpponent(game);
}

char* computePosition(TicTacToe* game) {
    Player* current_player = game->current;
    Player* opponent_player = getOpponent(game);
    if (strcmp(current_player->last_pos, "") == 0 || strcmp(opponent_player->last_pos, "") == 0) {
        char* magic_pos = randomPosition(game);
        return magic_pos;
    }
    char* winning_pos_current = winningPosition(game->board, game->positions, current_player);
    if (strcmp(winning_pos_current, "") != 0) {
        return winning_pos_current;
    }
    char* winning_pos_opponent = winningPosition(game->board, game->positions, opponent_player);
    if (strcmp(winning_pos_opponent, "") != 0) {
        return winning_pos_opponent;
    }
    char* magic_pos = randomPosition(game);
    return magic_pos;
}

char* randomPosition(TicTacToe* game) {
    int row_index, col_index;
    srand(time(0));
    do {
        row_index = rand() % BOARD_SIZE;
        col_index = rand() % BOARD_SIZE;
    } while (game->board[row_index][col_index] != ' ');
    char* pos = malloc(3 * sizeof(char));
    pos[0] = character(row_index);
    pos[1] = character(col_index);
    pos[2] = '\0';
    return pos;
}

char* winningPosition(char board[][BOARD_SIZE], char* positions[][BOARD_SIZE], Player* player) {
    for (int i = 0; i < POS_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            char* winning_position;
            if (strcmp(positions[i][j], player->last_pos) == 0) {
                winning_position = winningPosition_helper(board, positions, i, player->name);
                if (strcmp(winning_position, "") != 0) {
                    return winning_position;
                }
            }
        }
    }
    return "";
}

char* winningPosition_helper(char board[][BOARD_SIZE], char* positions[][BOARD_SIZE], int i, char name) {
    int count_name = 0, count_space = 0, final_x, final_y;
    char* pos; 
    int x, y;
    for (int j = 0; j < BOARD_SIZE; j++) {
        pos = positions[i][j];
        x = integer(pos[0]);
        y = integer(pos[1]);
        if (board[x][y] == ' ' ) {
            final_x = x;
            final_y = y;
            count_space++;
        }
        else {
            if (board[x][y] == name) {
                count_name++;
            }
        }
    }
    if (count_name == 2 && count_space == 1) {
        char* winning_pos = malloc(3 * sizeof(char));
        winning_pos[0] = character(final_x);
        winning_pos[1] = character(final_y);
        winning_pos[2] = '\0';
        return winning_pos;
    }
    return "";
}

int integer(char c) {
    return (int) c - 48;
}

char character(int x) {
    return x + '0';
}

Player* getOpponent(TicTacToe* game) {
    if (game->current == game->user) {
        return game->computer;
    }
    return game->user;
}

void printBoard(TicTacToe* game) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("[%c] ", game->board[i][j]);
        }
        printf("\n");
    }
}

int gameOver(TicTacToe* game) {
    char current_name;
    char* current_pos;
    int x, y, count; 
    int is_space = 0;
    for (int i = 0; i < POS_SIZE; i++) {
        current_name = '\0';
        count = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            current_pos = game->positions[i][j];
            x = integer(current_pos[0]);
            y = integer(current_pos[1]);
            if (game->board[x][y] == ' ') {
                is_space = 1;
                break;
            }
            if (current_name == '\0') {
                current_name = game->board[x][y];
                count++;
                continue;
            }
            if (current_name != game->board[x][y]) {
                break;
            }
            count++;
        }
        if (count == 3) {
            return current_name == game->user->name ? 1 : 2;
        }
    }
    if (is_space == 1) {
        return -1;
    }
    return 0;
}
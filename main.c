#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void reset_board();
void print_board();
char check_win_conditions();
void player_input();
void computer_input();
void print_winner(char);
int check_free_spaces();

char board[3][3];
char winner = ' ';
int spaces_remaining = 9;
const char PLAYER = 'X';
const char COMPUTER = 'O';

int main() {

    // Seed the computer input with the current time at start of game
    srand(time(0));

    reset_board();

    while (winner == ' ' && spaces_remaining != 0) {
        
        // Players Turn
        print_board();
        player_input();
        winner = check_win_conditions();
        if (winner != ' ' || spaces_remaining == 0) 
            break;
        

        // Computers Turn
        print_board();
        computer_input();
        Sleep(.75 * 1000);
        winner = check_win_conditions();
        if (winner != ' ' || spaces_remaining == 0)
            break;
    }

    print_board();
    print_winner(winner);
    return 0;
}

void reset_board() {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            board[y][x] = ' ';
        }
    }
}

void print_board() {
    system("cls");
    printf("\n %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---");
    printf("\n %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---");
    printf("\n %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

void player_input() {
    int x;
    int y;

    do {
        do {
            printf("Please select a row (#1-3): ");
            scanf("%d", &x);
            x--;
            if (x < 0 || x > 2) 
                printf("The number you selected was outside of the allowable range.\n");
                
        } while (x < 0 || x > 2);

        do {
        printf("Please select a column (#1-3): ");
        scanf("%d", &y);
        y--;
        if (y < 0 || y > 2) 
                printf("The number you selected was outside of the allowable range.\n");

        } while (y < 0 || y > 2);

        if (board[x][y] != ' ')
            printf("There is already a character in that position. Please try again.\n");

    } while (board[x][y] != ' ');
    
    board[x][y] = PLAYER;
    spaces_remaining--;
}

void computer_input() {
    int x;
    int y;

    do {
        x = rand() % 3;
        y = rand() % 3;
    } while(board[x][y] != ' ');

    printf("Computer picks: %d, %d\n", x, y);
    board[x][y] = COMPUTER;
}

int check_free_spaces() {
    int free_spaces = 9;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (board[x][y] != ' ')
                free_spaces--;
        }
    }

    return free_spaces;
}

char check_win_conditions() {

    // Evaluate Row Wins
    for (int i = 0; i < 3; i ++) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
            return board[i][0];
    }

    // Evaluate Column Wins
    for (int i = 0; i < 3; i ++) {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
            return board[0][i];
    }

    // Evaluate Diagonal Wins
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
        return board[0][0];

    if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
        return board[0][2];

    return ' ';
}

void print_winner(char winner) {
    if (winner == PLAYER)
        printf("YOU WIN!");
    else if (winner == COMPUTER)
        printf("COMPUTER WINS!");
    else
        printf("IT'S A TIE!");
}
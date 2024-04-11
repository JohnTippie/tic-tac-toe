#include "main.hpp"

char board[3][3];
char PLAYER = 'X';
char COMPUTER = 'O';
uint8_t spaces_remaining = 9;

int main() {

    // General Setup
    bool running = true;
    char winner = ' ';
    srand(time(NULL));
    get_player_symbols();
    reset_board();

    while (running) {

        while (winner == ' ' && spaces_remaining != 0) {
            
            // Player Turn
            print_board();
            player_input();
            winner = evaluate_win_conditions();
            if (winner != ' ' || spaces_remaining == 0)
                break;

            // Computer Turn
            print_board();
            computer_input();
            Sleep(.75 * 1000);
            winner = evaluate_win_conditions();
            if (winner != ' ' || spaces_remaining != 0)
                break;
        }

        print_board();
        print_winner(winner);

        // running = get_continue();
        if (!running)
            break;
    }

    return EXIT_SUCCESS;
}

void get_player_symbols() {
    char response;

    do {
        std::string input;
        system("cls");
        printf("Would you like to use default symbols? (Y/N)\n");
        printf("Player default: X\n");
        printf("Computer default: O\n");
        std::cin >> input;

        // Validate the user entered only 1 character
        if (input.length() != 1) {
            printf("Invalid selection: Too long. Please only enter 'Y' or 'N'\n");
            Sleep(1.5 * 1000);
        } else
            response = toupper(input[0]);
        
        // Validate the user entered only 'Y' or 'N'
        if (response)
            if (response != 'Y' && response != 'N') {
                printf("Invalid selection: Incorrect Char. Please only enter 'Y' or 'N'\n");
                Sleep(1.5 * 1000);
            }

    } while (response != 'Y' && response != 'N');
    
    if (response == 'N') {
        std::string input;
        
        // Validate the user entered only 1 character
        do {
            system("cls");
            printf("Please note: all symbols must be only one character\n");
            printf("Please enter the Player's symbol: \n");
            std::cin >> input;
        
            if (input.length() != 1) {
                printf("Invalid entry: Entry too long. Please only enter 1 character\n");
                Sleep(1.5 * 1000);
            }
        } while (input.length() != 1);
            PLAYER = input[0];

        do {
            printf("Please enter the Computers's symbol: \n");
            std::cin >> input;
        
            if (input.length() != 1) {
                printf("Invalid entry: Entry too long. Please only enter 1 character\n");
                Sleep(1.5 * 1000);
            }
        } while (input.length() != 1);
            COMPUTER = input[0];
    }
}

void reset_board() {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            board[x][y] = ' ';
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
    uint8_t x;
    uint8_t y = 100;

    // Verify selected space is empty
    do {

        // Select Row and validate it is in an appropriate range
        do {
            int input;
            printf("Please select a row (#1-3): \n");
            std::cin >> input;

            if (!std::cin) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                printf("Invalid entry: Not a number. Please only enter the number 1 through 3\n");
            } 

            if ((input < 1 || input > 3) && x)
                printf("Invalid entry: Out of bounds. Please only enter the number 1 through 3\n");
            
            x = input;
            x--;

        } while(x > 2);

        // Select Column

        do {
            int input;
            printf("Please select a column (#1-3): \n");
            std::cin >> input;

            if (!std::cin) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                printf("Invalid entry: Not a number. Please only enter the number 1 through 3\n");
            } 

            if ((input < 1 || input > 3) && y)
                printf("Invalid entry: Out of bounds. Please only enter the number 1 through 3\n");
            
            y = input;
            y--;
            
        } while(y > 2);
    } while (board[x][y] != ' ');

    board[x][y] = PLAYER;
    spaces_remaining--;
}

char evaluate_win_conditions() {

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

void computer_input() {
    int x;
    int y;

    do {
        x = rand() % 3;
        y = rand() % 3;
    } while(board[x][y] != ' ');

    printf("Computer picks: %d, %d\n", x + 1, y + 1);
    board[x][y] = COMPUTER;
}

void print_winner(char winner) {
    if (winner == PLAYER)
        printf("YOU WIN!\n");
    else if (winner == COMPUTER)
        printf("COMPUTER WINS!\n");
    else
        printf("IT'S A TIE!\n");
}
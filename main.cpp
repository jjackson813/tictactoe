#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void initialize(char board[]) {
    for (int i = 0; i < 9; i++) {
        board[i] = '1' + i;
    }
}

int getMode() {
    int mode;
    cout << "Select game mode (1 or 2):\n";
    cout << "1. One Player\n";
    cout << "2. Two Players\n";
    while (mode != 1 && mode != 2) {
        cin >> mode;
        if (mode != 1 && mode != 2) {
            cout << "Select a valid game mode (1 or 2).\n";
        }
    }
    return mode;
}

void displayBoard(char board[]) {
    cout << "\n";
    for (int i = 0; i < 9; i += 3) {
        cout << " " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << " \n";
        if (i < 6) {
            cout << "---+---+---\n";
        }
    }
    cout << "\n";
}


bool checkWinLine(char board[], char player) {
    for (int i = 0; i < 9; i += 3) {
        if (board[i] == player && board[i + 1] == player && board[i + 2] == player) {
            return true;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (board[i] == player && board[i + 3] == player && board[i + 6] == player) {
            return true;
        }
    }
    return false;
}

bool checkWinDiagonal(char board[], char player) {
    if (board[0] == player && board[4] == player && board[8] == player) {
        return true;
    }
    if (board[2] == player && board[4] == player && board[6] == player) {
        return true;
    }
    return false;
}

bool checkWin(char board[], char player) {
    if (checkWinLine(board, player) || checkWinDiagonal(board, player) == true) {
        return true;
    }
    else {
        return false;
    }
}

int getUserMove(char currentPlayer, char board[]) {
    int move;
    bool invalidMove = true;
    while(invalidMove) {
        cout << "\nPlayer " << currentPlayer << ", please enter your move (1-9): ";
        cin >> move;
        move--; // Adjusting user input to 0-based indexing
        if (move < 0 || move >= 9 || board[move] == 'X' || board[move] == 'O') {
            cout << "\nInvalid move. Please try again.\n";
        }
        else {
            invalidMove = false;
        }
    }    
    return move;
}

int randomMove(char board[]) {
    int move;
    srand(time(NULL));
    do {
        move = rand() % 9;
    } while (board[move] == 'X' || board[move] == 'O');
    return move;
}

int getComputerMove(char board[]) {
    int move;
    move = randomMove(board);
    return move;
}

void updateBoard(char board[], int move, char currentPlayer) {
    if (move >= 0 && move < 9) {
        board[move] = currentPlayer;
    }
    
}

bool checkTie(char board[]) {
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            return false;
        }
    }
    return true;
}

void switchPlayer(char& currentPlayer) {
    if (currentPlayer == 'X') {
        currentPlayer = 'O';
    }
    else {
        currentPlayer = 'X';
    }
}

int getMove(char board[], int mode, char currentPlayer) {
    int move;
    if (mode == 1 && currentPlayer == 'O') {
        move = getComputerMove(board);
        cout << "Computer chose: " << move + 1<< "\n";
    } 
    else {
        move = getUserMove(currentPlayer, board);
    }
    return move;
}

bool gameEnds(char board[], char currentPlayer) {
    if (checkWin(board, currentPlayer)) {
        displayBoard(board);
        cout << "\nPlayer " << currentPlayer << " wins!\n";
        return true;
    }
    if (checkTie(board)) {
        displayBoard(board);
        cout << "\nThe game is a tie.\n";
        return true;
    }

    return false;
}

void play(char board[], int mode) {
    char currentPlayer = 'X';
    int move;
    bool gameOn = true;
    while (gameOn) {
        displayBoard(board);
        move = getMove(board, mode, currentPlayer);
        updateBoard(board, move, currentPlayer);
        if(gameEnds(board, currentPlayer)) {
            gameOn = false;
        }
        else {
            switchPlayer(currentPlayer);
        }
    }
}

void startGame() {
    char board[9];
    initialize(board);
    int gameMode = getMode();
    play(board, gameMode);
}

int main() {
    startGame();
    return 0;
}

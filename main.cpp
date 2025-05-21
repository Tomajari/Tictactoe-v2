#include <iostream>
#include <vector>
#include <limits>    // for std::numeric_limits
#include <string>    // for std::string
using namespace std;

class TicTacToe {
private:
    int size;                        
    vector<vector<char>> board;      
    char currentPlayer;

public:
    TicTacToe(int n) 
      : size(n), board(n, vector<char>(n, ' ')), currentPlayer('X') {}

    void displayBoard() {
        cout << "\nCurrent Board:\n";
        for (int i = 0; i < size; ++i) {
            cout << " ";
            for (int j = 0; j < size; ++j) {
                cout << board[i][j];
                if (j < size - 1) cout << " | ";
            }
            cout << "\n";
            if (i < size - 1) {
                // build a line of dashes of the correct width
                cout << string(size * 4 - 3, '-') << "\n";
            }
        }
        cout << endl;
    }

    bool checkWin() {
        // rows
        for (int i = 0; i < size; ++i) {
            bool win = true;
            for (int j = 0; j < size; ++j)
                if (board[i][j] != currentPlayer) { win = false; break; }
            if (win) return true;
        }
        // columns
        for (int j = 0; j < size; ++j) {
            bool win = true;
            for (int i = 0; i < size; ++i)
                if (board[i][j] != currentPlayer) { win = false; break; }
            if (win) return true;
        }
        // main diagonal
        bool diag1 = true;
        for (int i = 0; i < size; ++i)
            if (board[i][i] != currentPlayer) { diag1 = false; break; }
        if (diag1) return true;
        // anti-diagonal
        bool diag2 = true;
        for (int i = 0; i < size; ++i)
            if (board[i][size - 1 - i] != currentPlayer) { diag2 = false; break; }
        return diag2;
    }

    bool checkDraw() {
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                if (board[i][j] == ' ') return false;
        return true;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    bool takeInput() {
        int position;
        cout << "Player " << currentPlayer 
             << ", choose a position (1-" << size*size << "): ";
        cin >> position;
        if (!cin || position < 1 || position > size*size) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid number! Try again.\n";
            return false;
        }
        int idx = position - 1;
        int row = idx / size;
        int col = idx % size;
        if (board[row][col] != ' ') {
            cout << "That square is already taken! Try again.\n";
            return false;
        }
        board[row][col] = currentPlayer;
        return true;
    }

    void playGame() {
        while (true) {
            displayBoard();
            if (!takeInput()) continue;
            if (checkWin()) {
                displayBoard();
                cout << "Player " << currentPlayer << " wins!\n";
                break;
            }
            if (checkDraw()) {
                displayBoard();
                cout << "It's a draw!\n";
                break;
            }
            switchPlayer();
        }
    }
};

int main() {
    int n;
    cout << "Welcome to Tic-Tac-Toe!\n"
         << "Enter board size (e.g. 3 for 3×3, 5 for 5×5): ";
    cin >> n;
    if (!cin || n < 3) {
        cout << "Invalid size. Using default 3×3 board.\n";
        n = 3;
    }
    TicTacToe game(n);
    game.playGame();
    return 0;
}

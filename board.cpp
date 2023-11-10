#include <iostream>
#include <string>
using namespace std;


struct Board {
    int numberOfMines;
    int xLocation;
    int yLocation;
    char mineBoard[10][15];
    char playerBoard[10][15];
    int currentScore;

    void setBoardSize();
    void setBoard();
    void printBoard();
    void getPlayerInput();
    void uncover(int x, int y);
    void flagging();
};


void Board::setBoardSize() {

}


void Board::setBoard() {
    
}


// needs to be edited to highlight or point to where the cursor is currently located
void Board::printBoard() {
    system("clear");

    string corners[9] = {"┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"};
    int l = 0;

    for (int i = 0; i < 10; ++i) {
        if (i != 0) {
            l = 3;
        }

        cout << corners[l] << "─────";

        for (int j = 1; j < 15; ++j) {
            cout << corners[l+1] << "─────";
        }

        cout << corners[l+2];
        cout << '\n';

        for (int j = 0; j < 15; ++j) {
            cout << "│  " << playerBoard[i][j] << "  ";
        }
        cout << "│" << '\n';
    }

    cout << corners[6] << "─────";
    for (int j = 1; j < 15; ++j) {
            cout << corners[7] << "─────";
        }
    cout << corners[8];

}


void Board::getPlayerInput() {
    char playerInput;
    printBoard();
    cout << "input the direction you want to head. "
            "if you put in multiple characters, "
            "only the first one will be considered.";

    bool validInput = false;
    do {
        cin >> playerInput;

        switch (playerInput) {
        case 'w':
            if (yLocation + 1 >= 10) {
                ++yLocation;
                validInput = true;
            }
            break;

        case 'a':
            if (xLocation - 1 < 0) {
                --xLocation;
                validInput = true;
            }
            break;

        case 's':
            if (yLocation - 1 < 0) {
                --yLocation;
                validInput = true;
            }
            break;

        case 'd':
            if (xLocation + 1 >= 15) {
                ++xLocation;
                validInput = true;
            }
            break;

        case 'o':
            uncover(xLocation, yLocation);
            validInput = true;
            break;

        case 'p':
            flagging();
            validInput = true;
            break;

        default:
            break;
        }
        
        if (!validInput) {
            printBoard();
            cout << "invalid input";
        }

    } while (!validInput);

}


void Board::uncover(int x, int y) {
    if (mineBoard[y][x] == 'B') {
        currentScore -= 100;
        playerBoard[y][x] = '@';
        cout << "You uncovered a mine!";
        return;
    }
    
    int surroundingMineCount = 48;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {

            if (i == 0 && j == 0) {
                continue;
            }

            int neighborX = x + i;
            int neighborY = y + j;

            bool cellOutOfRange = (neighborX < 0 || neighborX >= 15 || neighborY < 0 || neighborY >= 10);
            if (cellOutOfRange) {
                continue;
            }

            if (mineBoard[neighborY][neighborX] == 'B') {
                surroundingMineCount++;
            }
        }
    }

    if (surroundingMineCount != 48) {
        playerBoard[y][x] = char(surroundingMineCount);
        return;
    }

    // recursively uncover the neighboring cells if surroundingMineCount is 0.
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {

            if (i == 0 && j == 0) {
                continue;
            }

            int neighborX = x + i;
            int neighborY = y + j;

            bool cellOutOfRange = (neighborX < 0 || neighborX >= 15 || neighborY < 0 || neighborY >= 10);
                if (cellOutOfRange) {
                    continue;
                }

            uncover(neighborX, neighborY);
        }
    }
}


void Board::flagging() {
    if (playerBoard[yLocation][xLocation] == 'F') {
        playerBoard[yLocation][xLocation] = ' ';
        numberOfMines += 1;
        return;
    }

    playerBoard[yLocation][xLocation] = 'F';
    numberOfMines -= 1;

    if (mineBoard[yLocation][xLocation] == 'B') {
        currentScore += 10;
    } else {
        currentScore -= 100;
    }
}


int main() {
    Board b = {
        50, 3, 3,
        {{'.', '.', '.', '.', 'B', '.', '.', '.', 'B', '.', 'B', '.', '.', '.', '.'},
         {'.', 'B', '.', 'B', 'B', 'B', '.', '.', '.', '.', '.', 'B', '.', '.', 'B'}, 
         {'B', 'B', '.', '.', '.', '.', 'B', '.', 'B', '.', '.', 'B', 'B', '.', 'B'}, 
         {'.', '.', '.', '.', '.', 'B', 'B', 'B', '.', 'B', '.', '.', '.', '.', '.'}, 
         {'.', 'B', '.', '.', '.', '.', '.', 'B', '.', '.', 'B', '.', 'B', '.', '.'}, 
         {'.', '.', 'B', '.', '.', '.', '.', 'B', '.', 'B', 'B', '.', '.', 'B', '.'}, 
         {'B', '.', '.', '.', '.', 'B', '.', 'B', 'B', '.', '.', 'B', '.', 'B', '.'}, 
         {'B', 'B', 'B', '.', '.', '.', 'B', '.', 'B', 'B', '.', '.', 'B', '.', '.'}, 
         {'.', '.', 'B', '.', '.', '.', '.', 'B', '.', '.', 'B', '.', 'B', 'B', '.'}, 
         {'.', '.', '.', 'B', '.', 'B', '.', '.', '.', 'B', '.', '.', '.', '.', '.'}},

        {{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}},
        0
    };

    b.uncover(3, 3);
    b.printBoard();

}

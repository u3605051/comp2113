#include "board.h"
#include "display.h"
#include "colors.h"
#include <iostream>
using namespace std;


struct Board {
    int columns;
    int rows;
    int numberOfMines;
    int xLocation;
    int yLocation;
    char ** mineBoard;
    char ** playerBoard;
    int currentScore;

    void setBoardSize();
    void setBoard();
    void printBoard();
    void getPlayerInput();
    void uncover(int x, int y);
    void flagging();

};

void Board::setBoardSize() {
    cout << "please input the column x row";
    cin >> columns >> rows;

    mineBoard = new char * [rows];
    playerBoard = new char * [rows];
    for (int i = 0; i < rows; ++i) {
        mineBoard[i] = new char [columns];
        playerBoard[i] = new char [columns];
    }
}

Board::~Board() {
    for (int i = 0; i < rows; ++i) {
        delete[] mineBoard[i];
        delete[] playerBoard[i];
    }
    delete[] mineBoard;
    delete[] playerBoard;
}


void Board::setBoard() {
}


// needs to be edited to highlight or point to where the cursor is currently located
void Board::printBoard() {
    char corners[9] = {'┌', '┬', '┐', '├', '┼', '┤', '└', '┴', '┘'};
    int l = 0;

    for (int i = 0; i < rows; ++i) {
        if (i != 0) {
            l = 3;
        }

        cout << corners[l] << "─────";

        for (int j = 1; j < columns; ++j) {
            cout << corners[l+1] << "─────";
        }

        cout << corners[l+2];

        for (int j = 0; j < columns; ++j) {
            cout << "│  " << playerBoard[i][j] << "  │";
        }
    }

    cout << corners[6] << "─────";
    for (int j = 1; j < columns; ++j) {
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
            if (yLocation + 1 >= rows) {
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
            if (xLocation + 1 >= columns) {
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
        playerBoard[yLocation][xLocation] = '@';
        cout << "You uncovered a mine!";
        return;
    }
    
    int surroundingMineCount = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {

            if (i == 0 && j == 0) {
                continue;
            }

            int neighborX = x + i;
            int neighborY = y + j;

            bool cellOutOfRange = (neighborX < 0 || neighborX >= columns || neighborY < 0 || neighborY >= rows);
            if (cellOutOfRange) {
                continue;
            }

            if (mineBoard[neighborY][neighborX] == 'B') {
                surroundingMineCount++;
            }
        }
    }

    if (surroundingMineCount != 0) {
        playerBoard[yLocation][xLocation] = surroundingMineCount;
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

            bool cellOutOfRange = (neighborX < 0 || neighborX >= columns || neighborY < 0 || neighborY >= rows);
                if (cellOutOfRange) {
                    continue;
                }

            uncover(neighborX, neighborY);
        }
    }
}


void Board::flagging() {
    if (playerBoard[yLocation][xLocation] == '▶') {
        playerBoard[yLocation][xLocation] == ' ';
        numberOfMines += 1;
        return;
    }

    playerBoard[yLocation][xLocation] == '▶';
    numberOfMines -= 1;

    if (mineBoard[yLocation][xLocation] == 'B') {
        currentScore += 10;
    } else {
        currentScore -= 100;
    }
}



void runGame(Board b){
    b.setBoard();
}

// Copyright (c) 2025 Nathan Greenfield. All rights reserved

#include "tttgame.h"
#include "tttgameai.h"

TicTacToeGame::TicTacToeGame() {
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            currentState.mBoard[r][c] = GameState::Empty;
}

GameState TicTacToeGame::getBoard() const {
    return currentState;
}

bool TicTacToeGame::setSquareState(unsigned short row, unsigned short col, GameState::SquareState state) {
    if (row < 3 && col < 3 && currentState.mBoard[row][col] == GameState::Empty) {
        currentState.mBoard[row][col] = state;
        return true;
    }
    return false;
}

bool TicTacToeGame::setSquareState(unsigned short square, GameState::SquareState state) {
    if (square >= 1 && square <= 9) {
        unsigned short row = (square - 1) / 3;
        unsigned short col = (square - 1) % 3;
        return setSquareState(row, col, state);
    }
    return false;
}

char TicTacToeGame::getWinner() {
    for (int i = 0; i < 3; ++i) {
        if (currentState.mBoard[i][0] != GameState::Empty && currentState.mBoard[i][0] == currentState.mBoard[i][1] && currentState.mBoard[i][1] == currentState.mBoard[i][2])
            return currentState.mBoard[i][0] == GameState::X ? 'X' : 'O';
        if (currentState.mBoard[0][i] != GameState::Empty && currentState.mBoard[0][i] == currentState.mBoard[1][i] && currentState.mBoard[1][i] == currentState.mBoard[2][i])
            return currentState.mBoard[0][i] == GameState::X ? 'X' : 'O';
    }
    if (currentState.mBoard[0][0] != GameState::Empty && currentState.mBoard[0][0] == currentState.mBoard[1][1] && currentState.mBoard[1][1] == currentState.mBoard[2][2])
        return currentState.mBoard[0][0] == GameState::X ? 'X' : 'O';
    if (currentState.mBoard[0][2] != GameState::Empty && currentState.mBoard[0][2] == currentState.mBoard[1][1] && currentState.mBoard[1][1] == currentState.mBoard[2][0])
        return currentState.mBoard[0][2] == GameState::X ? 'X' : 'O';

    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (currentState.mBoard[r][c] == GameState::Empty)
                return ' ';

    return 'N';
}


 
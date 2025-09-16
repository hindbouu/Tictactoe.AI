// Copyright (c) 2025 Nathan Greenfield. All rights reserved

#include "tttgameai.h"

bool isThreeInARow(GameState::SquareState a, GameState::SquareState b, GameState::SquareState c) {
    return a != GameState::Empty && a == b && b == c;
}

bool hasEmpty(const GameState& state) {
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (state.mBoard[r][c] == GameState::Empty) return true;
    return false;
}

bool IsGameOver(const GameState& state)
{
    for (int i = 0; i < 3; ++i)
    {
        if (isThreeInARow(state.mBoard[i][0], state.mBoard[i][1], state.mBoard[i][2])) return true;
        if (isThreeInARow(state.mBoard[0][i], state.mBoard[1][i], state.mBoard[2][i])) return true;
    }
    if (isThreeInARow(state.mBoard[0][0], state.mBoard[1][1], state.mBoard[2][2])) return true;
    if (isThreeInARow(state.mBoard[0][2], state.mBoard[1][1], state.mBoard[2][0])) return true;
    return !hasEmpty(state);
}

float GetScore(const GameState& state)
{
    for (int i = 0; i < 3; ++i)
    {
        if (isThreeInARow(state.mBoard[i][0], state.mBoard[i][1], state.mBoard[i][2]))
            return state.mBoard[i][0] == GameState::O ? 1.0f : -1.0f;
        if (isThreeInARow(state.mBoard[0][i], state.mBoard[1][i], state.mBoard[2][i]))
            return state.mBoard[0][i] == GameState::O ? 1.0f : -1.0f;
    }
    if (isThreeInARow(state.mBoard[0][0], state.mBoard[1][1], state.mBoard[2][2]))
        return state.mBoard[0][0] == GameState::O ? 1.0f : -1.0f;
    if (isThreeInARow(state.mBoard[0][2], state.mBoard[1][1], state.mBoard[2][0]))
        return state.mBoard[0][2] == GameState::O ? 1.0f : -1.0f;
    return 0.0f;
}

void GenStates(GTNode* root, bool xPlayer)
{
    if (IsGameOver(root->mState)) return;
    for (int r = 0; r < 3; ++r)
    {
        for (int c = 0; c < 3; ++c)
        {
            if (root->mState.mBoard[r][c] == GameState::Empty)
            {
                GTNode* child = new GTNode;
                child->mState = root->mState;
                child->mState.mBoard[r][c] = xPlayer ? GameState::X : GameState::O;
                root->mChildren.push_back(child);
                GenStates(child, !xPlayer);
            }
        }
    }
}

float MinPlayer(const GTNode* node)
{
    if (node->mChildren.empty()) return GetScore(node->mState);
    float minVal = 1.0f;
    for (int i = 0; i < static_cast<int>(node->mChildren.size()); ++i)
    {
        float score = MaxPlayer(node->mChildren[i]);
        if (score < minVal) minVal = score;
    }
    return minVal;
}

float MaxPlayer(const GTNode* node)
{
    if (node->mChildren.empty()) return GetScore(node->mState);
    float maxVal = -1.0f;
    for (int i = 0; i < static_cast<int>(node->mChildren.size()); ++i)
    {
        float score = MinPlayer(node->mChildren[i]);
        if (score > maxVal) maxVal = score;
    }
    return maxVal;
}

const GTNode* MinimaxDecide(const GTNode* root)
{
    const GTNode* best = nullptr;
    float maxVal = -1.1f;
    for (int i = 0; i < static_cast<int>(root->mChildren.size()); ++i)
    {
        float score = MinPlayer(root->mChildren[i]);
        if (score > maxVal)
        {
            maxVal = score;
            best = root->mChildren[i];
        }
    }
    return best;
}

unsigned pickMove(const GameState& board)
{
    GTNode* root = new GTNode;
    root->mState = board;
    GenStates(root, false);
    const GTNode* choice = MinimaxDecide(root);

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board.mBoard[i][j] != choice->mState.mBoard[i][j])
            {
                for (int k = 0; k < static_cast<int>(root->mChildren.size()); ++k)
                    delete root->mChildren[k];
                delete root;
                return 3 * i + j + 1;
            }
        }
    }

    for (int k = 0; k < static_cast<int>(root->mChildren.size()); ++k)
        delete root->mChildren[k];
    delete root;
    return 0;
}

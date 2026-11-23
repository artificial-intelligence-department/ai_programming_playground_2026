#include <iostream>
#include <string>
using namespace std;

const int SIZE = 8;
const int STRAIGHT_ROW_STEP[4] = {-1, 1,  0, 0};
const int STRAIGHT_COL_STEP[4] = { 0, 0, -1, 1};
const int DIAGONAL_ROW_STEP[4] = {-1, -1, 1, 1};
const int DIAGONAL_COL_STEP[4] = {-1,  1,-1, 1};

bool insideBoard(int r, int c) {
    return r >= 0 && r < SIZE && c >= 0 && c < SIZE;
}

bool hasPieceOnRay(const string board[], int r, int c, int rowStep, int colStep, char piece) {
    r += rowStep;
    c += colStep;
    while (insideBoard(r, c)) {
        if (board[r][c] == piece) {
            return true;
        }
        r += rowStep;
        c += colStep;
    }
    return false;
}

bool attackedByPawn(const string board[], int r, int c) {
    for (int colStep = -1; colStep <= 1; colStep += 2) {
        int pr = r - 1;
        int pc = c + colStep;
        if (insideBoard(pr, pc) && board[pr][pc] == 'P') {
            return true;
        }
    }
    return false;
}
bool attackedByKnight(const string board[], int r, int c) {
    const int rowStep[8] = {-2, -2, -1, -1,  1, 1,  2, 2};
    const int colStep[8] = {-1,  1, -2,  2, -2, 2, -1, 1};
    for (int i = 0; i < 8; i++) {
        int nr = r + rowStep[i];
        int nc = c + colStep[i];
        if (insideBoard(nr, nc) && board[nr][nc] == 'N') {
            return true;
        }
    }
    return false;
}

bool attackedByKing(const string board[], int r, int c) {
    for (int rowStep = -1; rowStep <= 1; rowStep++) {
        for (int colStep = -1; colStep <= 1; colStep++) {
            if (rowStep == 0 && colStep == 0) {
                continue;                     
            }
            int nr = r + rowStep;
            int nc = c + colStep;
            if (insideBoard(nr, nc) && board[nr][nc] == 'K') {
                return true;
            }
        }
    }
    return false;
}

bool attackedByRook(const string board[], int r, int c) {
    for (int i = 0; i < 4; i++) {
        if (hasPieceOnRay(board, r, c, STRAIGHT_ROW_STEP[i], STRAIGHT_COL_STEP[i], 'R')) {
            return true;
        }
    }
    return false;
}

bool attackedByBishop(const string board[], int r, int c) {
    for (int i = 0; i < 4; i++) {
        if (hasPieceOnRay(board, r, c, DIAGONAL_ROW_STEP[i], DIAGONAL_COL_STEP[i], 'B')) {
            return true;
        }
    }
    return false;
}
bool attackedByQueen(const string board[], int r, int c) {
    for (int i = 0; i < 4; i++) {
        if (hasPieceOnRay(board, r, c, STRAIGHT_ROW_STEP[i], STRAIGHT_COL_STEP[i], 'Q') ||
            hasPieceOnRay(board, r, c, DIAGONAL_ROW_STEP[i], DIAGONAL_COL_STEP[i], 'Q')) {
            return true;
        }
    }
    return false;
}

int main() {
    string board[SIZE];
    for (int i = 0; i < SIZE; i++) {
        cin >> board[i];
    }

    int n;
    cin >> n;
    while (n--) {
        int x, y;                             
        cin >> x >> y;
        int r = x - 1;
        int c = y - 1;

        if (board[r][c] != 'O') {
            cout << "X" << endl;
            continue;
        }

        string result;
        if (attackedByBishop(board, r, c)) result += 'B';
        if (attackedByKing(board, r, c))   result += 'K';
        if (attackedByKnight(board, r, c)) result += 'N';
        if (attackedByPawn(board, r, c))   result += 'P';
        if (attackedByQueen(board, r, c))  result += 'Q';
        if (attackedByRook(board, r, c))   result += 'R';

        if (result.empty()) {
            result = "O";
        }
        cout << result << endl;
    }
    return 0;
}
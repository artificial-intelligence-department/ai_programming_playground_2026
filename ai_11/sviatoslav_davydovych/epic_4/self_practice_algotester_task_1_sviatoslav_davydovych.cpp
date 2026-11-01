/* 
Автор: Давидович Святослав
Група: ШІ-11
Умова: https://algotester.com/uk/ArchiveProblem/DisplayWithEditor/40633
*/

#include <iostream>
#include <vector>

using namespace std;

void modifyBoard(int n, vector<vector<bool>> &board, int row, int col);


void printSpace(int space){
    for (int s = 0; s<space; s++){
        cout << " ";
    }
}

void printBoard(int n, const vector<vector<bool>> &board, int space){
    for (int i = 0; i<n; i++){
        printSpace(space);
        for (int j = 0; j<n; j++){
            cout << int(board[i][j]) << " ";
        }
        cout << "\n";
    }
}

int countComb(int n, const vector<vector<bool>> board, int current_col){
    if (current_col==n) return 1;
    int result = 0;
    
    for (int current_row = 0; current_row<n; current_row++){
        if (!board[current_row][current_col]){
            vector<vector<bool>> copy = board;
            modifyBoard(n, copy, current_row, current_col);
            result+=countComb(n, copy, current_col+1);
        }
    }
    return result;
}

void modifyBoard(int n, vector<vector<bool>> &board, int row, int col){
    for (int i = 0; i<n; i++){
        board[row][(col+i)%n] = true;
        board[(row+i)%n][col] = true;
        if (col+i<n){
            if (row+i<n) board[row+i][col+i] = true;
            if (row-i>=0) board[row-i][col+i] = true;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<vector<bool>> board(n, vector<bool>(n,false));
    
    if (n==1) {
        cout << 1;
    }
    else if (n==2 || n==3){
        cout << 0;
    }
    else {
        vector<vector<bool>> board(n, vector<bool>(n,false));
        cout << countComb(n, board, 0);
    }
}
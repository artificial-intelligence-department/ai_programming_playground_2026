#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
using namespace std;
int main() {
    char board[8][8];
    for (int i = 0; i<8;i++){
        for(int j = 0; j<8; j++){
            cin >> board[i][j];
        }
    }
    int q;
    cin >> q;
    for (int i=0; i<q;i++) {
        int x,y;
        cin>>x>>y;
        x--;
        y--;
        if (board[x][y] != 'O') {
            cout << "X" << endl;
            continue;
        }
        bool king = false;
        bool knight = false;
        bool rook = false;
        bool bishop = false;
        bool queen = false;
        bool pawn = false;
        for (int r = 0; r < 8; r++) {
            for (int c = 0; c < 8; c++) {
                if (board[r][c] == 'K') {
                    if (abs(r - x) <= 1 && abs(c - y) <= 1) {
                        king = true;
                    }
                }
                if (board[r][c] == 'N') {
                    if ((abs(r-x) == 2 && abs(c-y) == 1) || (abs(r-x)==1 && abs(c-y)==2)){
                        knight = true;
                    }
                }
                if (board[r][c] == 'R'){
                    if(r == x || c==y){
                        rook = true;
                    }
                }
                if (board[r][c] == 'B'){
                    if(abs(r-x) == abs(c-y)){
                        bishop=true;
                    }
                }  
                if(board[r][c] == 'Q'){
                    if(r==x || c==y || abs(r-x)==abs(c-y)){
                        queen=true;
                    }
                }
                if (board[r][c] == 'P') {
                    if(x == r+1 && abs(c-y) == 1){
                        pawn = true;
                    }
                }
            }
        }
        string result = "";
        if (bishop) {
            result += 'B';
        }
        if (king) {
            result += 'K';
        }
        if (knight) {
            result += 'N';
        }
        if (pawn) {
            result += 'P';
        }
        if (queen) {
            result += 'Q';
        }
        if (rook) {
            result += 'R';
        }
        if (result.empty()) {
            result = "O";
        }
        cout << result << endl;
    }
    return 0;
}

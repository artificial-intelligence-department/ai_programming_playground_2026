/*  
Algotester 6
Варіант 2 
Ярошенко Володимир 
11 група 
*/
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

string play(char board[8][8], string& str, int x, int y) {
    bool check = true;
    if(board[x-1][y-1] != 'O') {
            str += 'X';
            return str;
}     
for(int i=1; i<=8; i++) {
    for(int j =1; j<=8; j++){
        if(board[i-1][j-1] == 'B') {
            if(abs(x - i) == abs(y - j))  {
                if (str.find('B') == string::npos) {
            str += 'B';
            };
                check = false;
            }
        }
        if(board[i-1][j-1] == 'K') {
            if(abs(i-x) <= 1 && abs(j-y) <= 1)  {
                if (str.find('K') == string::npos) {
            str += 'K';
            }
            check = false;
            }
        } 
        if(board[i-1][j-1] == 'N') {
            if((abs(x-i) == 2 && abs(y-j) == 1) || (abs(x-i) == 1 && abs(y-j) == 2)) {
                if (str.find('N') == string::npos) {
            str += 'N';
            }
                check = false;
            }
        }
        if(board[i-1][j-1] == 'P') {
            if((i==x-1) && (abs(y-j)) == 1) {
                if (str.find('P') == string::npos) {
            str += 'P';
            }
                check = false;
            }
        }
       if(board[i-1][j-1] == 'Q') {
            if((i == x ) || (j == y) ||abs(x - i) == abs(y - j) )  {
                if (str.find('Q') == string::npos) {
            str += 'Q';
            }
                check = false;
            }
        }
        if(board[i-1][j-1] == 'R') {
            if((i == x ) || (j == y)) {
                if (str.find('R') == string::npos) {
            str += 'R';
            }
                check = false;
            }
        }     
        }
    }
    if(check) {
            str += 'O';
        }
for(int i = 0; i < str.length()-1; i++) {
        for(int j = 0; j < str.length()-i-1; j++) {
            if(str[j] > str[j+1]) {
                char temp = str[j];
                str[j] = str[j+1];
                str[j+1] = temp;
            }
        }
    }
    return str;
}

int main() {
int q =0;
int x, y;
char board[8][8] = {};
for(int i =0; i<8;i++){
    for(int j=0; j<8;j++){
        cin >> board[i][j];
    }
}
cin >> q;
for(int i=0; i<q;i++){
    cin >> x >> y;
    string res = "";
    play(board, res, x ,y);
    cout << res << endl;
}
return 0;
}
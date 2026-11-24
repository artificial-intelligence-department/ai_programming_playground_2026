/*Лаба 6, варіант 2. Задача: атаки фігур на шаховій дошці
Автор: Матішак Михайло
Група: ШІ-11*/
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

bool isAttack(char piece, int pr, int pc, int tr, int tc){
    int dr = tr - pr;
    int dc = tc - pc;
    int adr = abs(dr);
    int adc = abs(dc);
    switch(piece){
        case 'P':
            return dr == 1 && adc == 1;
        case 'R':
            return dr == 0 || dc == 0;
        case 'N':
            return (adr == 1 && adc == 2) || (adr == 2 && adc == 1);
        case 'B':
            return adr == adc;
        case 'K':
            return adr <= 1 && adc <= 1;
        case 'Q':
            return dr == 0 || dc == 0 || adr == adc;
        default:
            return false;
    }
}

void printAnswer(string board[], int tr, int tc){
    if(board[tr][tc] != 'O'){
        cout << "X" << endl;
        return;
    }

    string res = "";
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] != 'O' && isAttack(board[i][j], i, j, tr, tc) && res.find(board[i][j]) == string::npos){
                res = res + board[i][j];
            }
        }
    }
    int n = res.length();
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - 1 - i; j++){
            if(res[j] > res[j + 1]){
                char temp = res[j];
                res[j] = res[j + 1];
                res[j + 1] = temp;
            }
        }
    }
    if(n == 0){
        cout << "O" << endl;
    }
    else{
        cout << res << endl;
    }
}
int main(){
    string board[8];
    for(int i = 0; i < 8; i++){
        cin >> board[i];
    }
    int q;
    cin >> q;
    for(int k = 0; k < q; k++){
        int x, y;
        cin >> x >> y;
        printAnswer(board, x - 1, y - 1);
    }
    return 0;
}
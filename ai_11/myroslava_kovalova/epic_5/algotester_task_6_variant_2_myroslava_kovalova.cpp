#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

const short int board_size = 8;
void is_Pawn (string board[], string& answer, int x, int y){
    if(x-1>=0 && y+1<=7){
        if (board[x-1][y+1]=='P'){
            answer+='P';
            return;
        }
    }
    if (x-1>=0 && y-1>=0){
       if (board[x-1][y-1]=='P'){
            answer+='P';
            return;
        } 
    }
}
void is_Rook(string board[], string& answer, int x, int y){
    for (int k=0; k<board_size; k++){
        if (board[x][k]=='R'){
            answer+='R';
            return;
        }
    }
    for (int i=0; i<board_size; i++){
        if (board[i][y]=='R'){
            answer+='R';
            return;
        }
    }
}
void is_Knight(string board[], string& answer, int x, int y){
    for (int i = 0; i<board_size; i++){
        if (abs(x-i)!=1 && abs(x-i)!=2 ) continue;
        for (int k = 0; k<board_size; k++){
            if(board[i][k]!='N') continue;
            if ((abs(y-k)==1 && abs(x-i)==2)||(abs(y-k)==2 && abs(x-i)==1)){
                answer+='N';
                return;
            }
        }
    }
}
void is_Bishop(string board[], string& answer, int x, int y){
    for (int i = 0; i<board_size; i++){
        for (int k = 0; k<board_size; k++){
            if(board[i][k]!='B') continue;
            if (abs(x-i)==abs(y-k)){
                answer+='B';
                return;
            }
        }
    }
}
void is_King(string board[], string& answer, int x, int y){
    for (int i = 0; i<board_size; i++){
        for (int k = 0; k<board_size; k++){
            if(board[i][k]!='K') continue;
            if (max(abs(x-i),abs(y-k))==1){
                answer+='K';
                return;
            }
        }
    }
}
void is_Queen(string board[], string& answer, int x, int y){
    for (int i = 0; i<board_size; i++){
        for (int k = 0; k<board_size; k++){
            if(board[i][k]!='Q') continue;
            if (x==i || y==k || (abs(x-i)==abs(y-k))){
                answer+='Q';
                return;
            }
        
        }
    }
}
int main(){
    string board[board_size];
    for (int i = 0; i<board_size; i++){
        cin>>board[i];
    }
    
    int request = 0;
    cin>>request;
    while(request--){
        int x,y;
        cin>>x>>y;
        x--;
        y--;
        string answer = "";
        if (board[x][y]!='O') {
            cout<<'X'<<endl;
            continue;
        }
        is_Pawn(board, answer,x,y);
        is_Rook(board, answer,x,y);
        is_Knight(board, answer,x,y);
        is_Bishop(board, answer,x,y);
        is_King(board, answer,x,y);
        is_Queen(board, answer,x,y);
        sort(answer.begin(), answer.end());
        
        if(answer=="") cout<< "O\n";
        else cout<<answer<<endl;
    }
    return 0;
}
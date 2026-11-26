#include <iostream>

using namespace std;

int main(){
    unsigned long long int a;
    cin>>a;
    bool board[8][8]={};
    for (int i = 63; i>=0; i--){
        if ((a>>i)&1) board[i/8][i%8]=true;
        else board[i/8][i%8]=false;
    }
    int N;
    cin>>N;
    int R,C;
    for (int k =1; k<=N;k++){
        cin>>R>>C;
        R-=1;
        C-=1;
        for (int i = 0; i<8; i++){
            board[R][i]=!board[R][i];
        }
        for (int j = 0; j<8; j++){
            board[j][C]=!board[j][C];
        }
        board[R][C]=!board[R][C];
    }
    unsigned long long int answer=0;
    
    for(int i = 0; i<8;i++){
        for(int j =0 ;j<8; j++){
            if(board[i][j]) answer=answer|(((unsigned long long int)1)<<(i*8+j));
        }
    }
    cout<<answer;
    return 0;
}
#include <iostream>
using namespace std;
int main(){
    char let;
    cin >> let;
    int num = 0;
    cin >> num;
    char *chess[8][8];
    for(int i = 0; i <= 7; i++){
        for(int j = 0; j <= 7; j++){
            if((i + j)%2 == 0){
                chess[i][j] = "Black";
            }
            else{
                chess[i][j] = "White";
            }
        }
    }
    int res1 = let - 'a';
    int res2 = num - 1;
    cout << chess[res1][res2];
    return 0;
}
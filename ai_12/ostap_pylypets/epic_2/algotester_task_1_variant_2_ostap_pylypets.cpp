#include <iostream>
using namespace std;
int main(){
    long long lengthChair[4], cutlengthChair[4];
    bool isTableFlipped = 0; //змінна для відстеження перевертання столу
    //записую виміри в масиви
    for (int i = 0; i < 4; i++){
        cin >> lengthChair[i];
    }
    for (int i = 0; i < 4; i++){
        cin >> cutlengthChair[i];
    }
    //перевіряю чи можна відрізати ніжки
    for (int i = 0; i < 4; i++){
        if (lengthChair[i] < cutlengthChair[i]){
             cout <<"ERROR";
             return 0;}
        }
    //відрізаю ніжки
    for (int i = 0; i < 4; i++){
        lengthChair[i] =lengthChair[i] - cutlengthChair[i];
        long long minimumLegLength = lengthChair[0]; 
        long long maximumLegLength = lengthChair[0];
        //шукаю найбільшу та найменшу ніжку
        for (int j = 1; j < 4; j++){
            if (lengthChair[j] < minimumLegLength) minimumLegLength = lengthChair[j]; 
            if (lengthChair[j] > maximumLegLength) maximumLegLength = lengthChair[j]; 
        }
        //перевіряю чи стіл не перевернутий
        if (maximumLegLength >= 2 * minimumLegLength){ 
            isTableFlipped = true; 
        }
    }
    
    if (isTableFlipped){
        cout <<"NO";
    }
    else{
        cout <<"YES";
    }
    return 0;
}
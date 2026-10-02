//Задача "Зуби"

#include <iostream>
using namespace std;

int main(){

    int n;
    cin >> n;

    int k;
    cin >> k;

    int currentMax = 0;
    int count = 0;

    for(int i = 0; i < n; i++){
        int currentTooth;
        cin >> currentTooth;
        if(currentTooth >= k){  
            count++;
        }       
        else{
            count = 0;
        }
        if(count > currentMax){
            currentMax = count;
        }
        
    }

    cout << currentMax;

    return 0;
}
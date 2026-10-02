//Хеловін

#include <iostream>

using namespace std;

int main(){

    int n, m;
    int min;
    int price = 0;
    
    cin >> n >> m;

    int candyn[n];
    int candym[m];

    for(int i = 0; i < n; i++){
        cin >> candyn[i];
    }
    for(int j = 0; j < m; j++){
        cin >> candym[j];
    }

    min = candyn[0];

    for(int i = 0; i < n; i++){
        if(candyn[i] < min){
            min = candyn[i];
        }
    }

    price += min;

    min = candym[0];

    for(int i = 0; i < m; i++){
        if(candym[i] < min){
            min = candym[i];
        }
    }

    price += min;

    cout << price;

    return 0;
}
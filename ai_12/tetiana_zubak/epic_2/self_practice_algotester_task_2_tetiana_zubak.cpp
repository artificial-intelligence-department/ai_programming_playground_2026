#include <iostream>

using namespace std;

int main(){
    int N, kanapka = 0, k = 0, a = 0, n = 0, p = 0;
    cin >> N;
    char dish[100000];
    for(int i = 0; i < N; i++){
    cin >> dish[i];
    }
    for(int i = 0; i < N; i++){
        switch(dish[i]){
        case 'k': k++; break;
        case 'a': a++; break;
        case 'n': n++; break;
        case 'p': p++; break;
        default: break;
        }
    }
    
    if(k >= 2 && a >= 3 && n > 0 && p > 0){
        for(int i = 1; i < N; i++){
            if(k >= (i + 1) && a >= (2*i + 1) && n >= i && p >= i) ++kanapka;
            else break;
        }
    }

    cout << kanapka << endl;

    return 0;
}
/*
Контест
Лабораторна №3
Варіан №2
Кузовніков В'ячеслав Євгеніойович
ШІ-13
*/

#include <iostream>
using namespace std;
int main (){
    int size_n = 0;
    cin >> size_n;
    if (size_n < 0 || size_n > 100){
        return 1;
    }

    int N[size_n] = {0};
    for (int i = 0; i < size_n; i++){
        cin >> N[i];
        if (N[i] < 0 || N[i] > 100){
            return 1;
        }
    }    
    int size_m = 0;
    cin >> size_m;
    if (size_m < 0 || size_m > 100){
        return 1;
    }

    int M[size_m] = {0};
    for (int i = 0; i < size_m; i++){
        cin >> M[i];
        if (M[i] < 0 || M[i] > 100){
            return 1;
        }
    }

    int spilni = 0;
    for (int i = 0; i < size_n; i++){
        for (int j = 0; j < size_m; j++){
            if(N[i] == M[j]){
                spilni++;
                break;
            }
        }

    }

    cout << spilni << endl;

    int unique_num = size_n + size_m - spilni;
    cout << unique_num;

    return 0;
}
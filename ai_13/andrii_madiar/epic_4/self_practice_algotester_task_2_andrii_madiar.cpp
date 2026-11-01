/*
self-practice algotester task 2 Цікаве листування, Андрій Мадяр
*/
#include <iostream>
#include <cmath>
using namespace std;
int main(){
    int n, k, a;
    cin >> n;
    k = sqrt(n);
    char arr[10][10];//двовимірний масив чарів щоб працював ввід без пробілів
    for(int i = 0; i<k; i++){
        for(int j = 0; j<k; j++){
            cin >> arr[i][j];
        }
    }
    for(a = 0; a<(2*k)-1; a++){//проходимся по всіх діагоналях кількість яких 2k-1
        for(int i = 0; i<k; i++){
            int j = a-i;//воно працює бо індекс рядка+індекс стовпця = індекс діагоналі на якій знаходиться елемент
                if(j>=0&&j<k)cout << arr[i][j];
        }
    }
    return 0;
}
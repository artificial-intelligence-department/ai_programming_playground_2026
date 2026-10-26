/*
Низьких вхід
Кузовніков  В'ячеслав Євгенійович
ШІ-13
*/

#include <iostream>
using namespace std;

int main (){
    int days = 0;
    int height = 0;

    cin >> days >> height;
    if (days < 1 || days > 100000){
        return 1;
    }

    if (height < 1 || height > 1000000000){
        return 1;
    }

    int a[days] = {0};
    for (int i = 0; i < days; i++){
        cin >> a[i];
        if (a[i] < 1 || a[i] > 1000000000){
            return 1;
        }
    }


    int b = 0;
    for (int i = 0; i < days; i++){
        if(height < a[i]){
            height++;
            b++;    
        }
             
    }

    cout << b;


    return 0;
}
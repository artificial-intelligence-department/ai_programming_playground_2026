/*
Lab 1v1
Кузовнііков В'ячеслав
Варіант - 1
ШІ-13
*/

#include <iostream>
using namespace std;
int main (){
    long long hp = 1; 
    long long ma = 1;
    cin >> hp >> ma;
    if (hp < 1 || hp > 10000000000000LL){
        return 0;
    }

    if (ma < 1 || ma > 10000000000000LL){
        return 0;
    }

    long long hp1 = 1;
    long long ma1 = 1;
    cin >> hp1 >> ma1;
    if (hp1 < 0 || hp1 > 10000000000000LL){
        return 0;
    }
    if (ma1 < 0 || ma1 > 10000000000000LL){
        return 0;
    }

    long long hp2 = 1;
    long long ma2 = 1;
    cin >> hp2 >> ma2;
    if (hp2 < 0 || hp2 > 10000000000000LL){
        return 0;
    }
    if (ma2 < 0 || ma2 > 10000000000000LL){
        return 0;
    }

    long long hp3 = 1;
    long long ma3 = 1;
    cin >> hp3 >> ma3;
    if (hp3 < 0 || hp3 > 10000000000000LL){
        return 0;
    }
    if (ma3 < 0 || ma3 > 10000000000000LL){
        return 0;
    }

    if (hp1 > 0 && ma1 > 0){
        cout << "NO";
        return 0;
    }

    if (hp2 > 0 && ma2 > 0){
        cout << "NO";
        return 0;
    }

    if (hp3 > 0 && ma3 > 0){
        cout << "NO";
        return 0;
    }

    if (hp - hp1 - hp2 - hp3 > 0 && ma - ma1 - ma2 - ma3 > 0){
        cout << "YES";
        return 0;
    }
    else {
        cout << "NO";
        return 0;
    }


    

    return 0;
}
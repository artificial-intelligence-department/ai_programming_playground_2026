/*
Апельсини
Кузовніков В'ячеслав
ШІ-13
*/

#include <iostream>
using namespace std;
int main (){
    int m = 0;
    int s = 0;
    int p = 0;

    cin >> m >> s >> p;
    if (m < 1 || m > 1000000000){
        return 1;
        if (s < 1 || s > 1000000000) {
            return 1;
            if (p < 1 || p > 1000000000) {
            return 1;
            }
        }
    }

    if (m + s > p){
        cout << "YES";
    }
    else {
        cout << "NO";
    }

    return 0;
}
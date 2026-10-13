/*
Епік 3. Self Practice: Algotester, задача "Існує дві дороги: Одна пряма, а інша …"
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
#include<cmath>
using namespace std;

int main () {

    int n; cin >> n;
    int sum = 0;

    for (int i = 0; i<n; i ++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        if ( abs(x1)>1000 || abs(x2)>1000 || abs(y1)>1000 || abs(y2)>1000) return 1;

        int lenght = sqrt(pow((x2-x1), 2) + pow((y2-y1), 2));
        sum += lenght;

    } 

    cout<< sum;
    
    return 0;
}
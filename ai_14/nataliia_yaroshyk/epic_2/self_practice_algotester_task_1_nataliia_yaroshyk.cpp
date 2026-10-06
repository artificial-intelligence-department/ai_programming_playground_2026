/* Algotester
   Існує дві дороги: Одна пряма, а інша …
   Ярошик Наталія
   ШІ-14 */
#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0, km = 0; 
    int n;

    cin >> n;

    for(int i=0; i<n; i++){
        cin >> x1 >> y1 >> x2 >> y2;
        int r1 = x2-x1;
        int r2 = y2-y1;
        int res = sqrt(pow(r1, 2) + pow(r2, 2));
        km += abs(res);
    }
    cout << km;

    return 0;
}
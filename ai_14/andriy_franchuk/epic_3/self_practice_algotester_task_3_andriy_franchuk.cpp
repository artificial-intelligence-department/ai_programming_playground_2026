/*Epic 3 - Існує дві дороги: Одна пряма, а інша …
Франчук Андрій
Ші - 14*/

#include <iostream>
#include <cmath>

using namespace std;

int main(){
    int n;
    cin >> n;

    int x1, y1, x2, y2;
    int len = 0;
    for(int i = 0; i < n; i++){
        cin >> x1 >> y1 >> x2 >> y2;
        len += sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    }

    cout << len;
    return 0;
}

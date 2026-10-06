/* Задача: Марічка і Печиво (Алгостестер)
   Виконав: Сукач Андрій, 
   Група: ШІ-14 
   Марічка і печиво
*/
#include <iostream>
using namespace std;
int main() {
int n;
cin >> n;
long long a = 0;
for (int i = 0; i < n; i++) {
    long long x;
    cin >> x;
    if (x>0) {
        a += (x-1);
    }
}
cout << a << endl;
return 0;
}
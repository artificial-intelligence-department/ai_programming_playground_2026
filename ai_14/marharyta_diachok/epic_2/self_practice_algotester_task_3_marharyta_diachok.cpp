/* 
Задача: Algotester Self-Practice №3.
Автор: Дячок Маргарита.
Група: ШІ-14
*/
#include <iostream>
using namespace std;
int main() {
   int n = 0;
   int m = 0;
   cin >> n >> m;
   int hodu = n * m;
   if (hodu % 2 == 0) {cout << "Dragon";}
   else {cout << "Imp";} 
    return 0;
}

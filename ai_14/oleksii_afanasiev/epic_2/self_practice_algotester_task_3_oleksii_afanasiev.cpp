/*
Задача: Скільки заплатити? (Algotester)
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>

using namespace std;

int main()
{
   int a, b, mn, mx;
   cin >> a >> b;

   if(a < b)
   {
        mn = a;
        mx = b;
   }
   else
   {
        mn = b;
        mx = a;
   }

   cout << (mx - mn == 1 ? -1 : mn + 1);
    

   return 0;
}

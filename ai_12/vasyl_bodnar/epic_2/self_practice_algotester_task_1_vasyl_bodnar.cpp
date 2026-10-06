#include <iostream>

using namespace std;

int main() {
   long long a, b;
   cin >> a >> b;

   if ((b-a) % 12 != 0) {
        cout << -1;
        return 0;
   }

   int diff = (b - a) / 12;
   long long result = (a + b) * 13 / 2;
   cout << result;
   return 0;
}
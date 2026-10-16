#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
   const double eps = 0.0001;
   double Sum = 0.0;
   int n = 1;
   double a = 2.0;

   while( a >= eps){
      Sum += a;
      a = a * 2.0 * pow((double)n / (n + 1), n);
      n++;
 }
 cout << "Сума: " << Sum << fixed << setprecision(6) << endl;
 cout << "Кількість членів: " << n - 1 << fixed << setprecision(6) << endl;
cout << "Точність: " << eps << fixed << setprecision(6) << endl;

return 0;

}
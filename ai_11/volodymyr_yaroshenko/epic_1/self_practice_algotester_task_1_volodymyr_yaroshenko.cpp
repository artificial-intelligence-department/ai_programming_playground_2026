#include <iostream>

 using namespace std;

int main() {
int n;   
cout << "Введіть суму: ";
cin >> n;
if(n<0 || n > 1000000000)  {
    cout << "Сума повинна бути в межах від 0 до 1000000000" << endl;
return 1;
}
 int k = n / 500;
 int res1 = n - k * 500;

 int l = res1 / 200;
 int res2 = res1 - l * 200;

 int z = res2 / 100;
 int res3 = res2 - z * 100;

 int x = res3 / 50;
 int res4 = res3 - x * 50;

 int c = res4 / 20;
 int res5 = res4 - c * 20;

 int v = res5 / 10;
 int res6 = res5 - v * 10;

 int b = res6 / 5;
 int res7 = res6 - b * 5;

 int y = res7 / 2;
 int res8 = res7 - y * 2;

 int m = res8 / 1;
 int res9 = res8 - m * 1;


  int res = k + l + z + x + c + v + b + y + m;
cout  << res<< endl;
    return 0;
}
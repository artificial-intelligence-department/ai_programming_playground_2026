#include <iostream>

 using namespace std;

int main() {
int n;   
cin >> n;

 int r1 = n / 500;
 int res1 = n - r1 * 500;

 int r2 = res1 / 200;
 int res2 = res1 - r2 * 200;

 int r3 = res2 / 100;
 int res3 = res2 - r3 * 100;

 int r4 = res3 / 50;
 int res4 = res3 - r4 * 50;

 int r5 = res4 / 20;
 int res5 = res4 - r5 * 20;

 int r6 = res5 / 10;
 int res6 = res5 - r6 * 10;

 int r7 = res6 / 5;
 int res7 = res6 - r7 * 5;

 int r8 = res7 / 2;
 int res8 = res7 - r8 * 2;

 int r9 = res8 / 1;
 int res9 = res8 - r9 * 1;


  int res = r1 + r2 + r3 + r4 + r5 + r6 + r7 + r8 + r9;
  cout << res << endl;
    return 0;
}
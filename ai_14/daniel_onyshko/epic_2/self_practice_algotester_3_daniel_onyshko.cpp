/*
   Задача: Зайчик та галявини (алготестер)
  Онишко Даніель
   Група ШІ-14
 

 */


#include <iostream>
using namespace std;


int main() {
    int n;
    cin >> n;


    long long maxArea;
    int maxIndex = 0;


    cin >> maxArea;
    for (int i = 1; i < n; i++) {
        long long a;
        cin >> a;
        if (a > maxArea) {
            maxArea = a;
            maxIndex = i;
        }
    }


    cout << maxIndex << endl;
    return 0;
}

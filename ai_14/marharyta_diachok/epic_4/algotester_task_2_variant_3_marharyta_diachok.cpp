/* 
Задача: Algotester Lab2 v3.
Автор: Дячок Маргарита.
Група: ШІ-14
*/

#include <iostream>
using namespace std;

int main() {
int N;
cin >> N;
if(N < 0 || N > 1000) return 0;
int* M = new int[N];
for(int i = 0; i < N; i++) {cin >> M[i]; if(M[i] > 5 || M[i] < 0) return 0;}
int dron1 = 0;
int dron2 = N - 1;

while(true) {
    if(dron1 == dron2) {cout << dron1 + 1 << " " << dron2 + 1; cout << "\nCollision"; break;}
    if(dron1 > dron2) {cout << dron1 + 1 << " " << dron2 + 1; cout << "\nMiss"; break;}
    if(dron1 + 1 == dron2) {cout << dron1 + 1 << " " << dron2 + 1; cout << "\nStopped"; break;}

dron1 +=  M[dron1];
dron2 -=  M[dron2];
}
delete[] M;


    return 0;
}
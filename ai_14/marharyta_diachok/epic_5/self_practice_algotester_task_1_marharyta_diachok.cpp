/*  
Задача: Self-practice. Завдання №1.
Автор: Дячок Маргарита. 
Група: ШІ-14 
*/ 

#include <iostream>
#include <string>

using namespace std;

int main() {
int n;
cin >> n;

int* p = new int[n];
int* pos = new int[n + 2];

for (int i = 0; i < n; i++) {
    cin >> p[i];
    pos[p[i]] = i + 1;}

pos[n + 1] = 0;
string s(n, 'a');
int k = 0;

for (int i = 0; i < n; i++) {
    if (i > 0) {
    if (pos[p[i - 1] + 1] > pos[p[i] + 1]) {k++;}}

if (k >= 26) {
    cout << -1 << endl;
            
delete[] p;
delete[] pos;
return 0;}

s[p[i] - 1] = 'a' + k;}
cout << s << endl;

delete[] p;
delete[] pos;

return 0;}

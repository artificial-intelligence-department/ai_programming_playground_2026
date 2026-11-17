/*
Задача: Lab 4v2 (stl)
Виконав: Сукач Андрій (ШІ-14)
*/
#include <vector>
#include <algorithm>
#include <iostream>


using namespace std;
int main(){
int n,k;

cin >> n >> k;
if (cin.fail() || n < 1 || n > 1000 || k < 1 || k > 1000) return 0;

vector<int> a(n);
for (int i = 0; i < n; i++){
    cin >> a[i];
}

sort(a.begin(), a.end());
auto it = unique(a.begin(), a.end());
a.erase(it, a.end());

int newSize = a.size();

if (newSize > 0) {
        k %= newSize; // захист, якщо k більше за розмір вектора
        rotate(a.begin(), a.begin() + k, a.end());
    }
cout << newSize << endl;

for (int i = 0; i < newSize; i++){
    cout << a[i] << " ";
}

return 0;
}
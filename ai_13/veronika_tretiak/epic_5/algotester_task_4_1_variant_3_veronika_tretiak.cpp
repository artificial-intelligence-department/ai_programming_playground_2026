/* 
Задача: Лабораторна робота Algotester №4(1)
Варіант: №3
Автор: Вероніка Третяк
Група: ШІ-13
*/
#include <algorithm>
#include <iostream>

using namespace std;
bool compareNumbers(int a, int b){
    if(a % 3 != b % 3){
        return a % 3 < b % 3;
    }
    if(a % 3 == 1){
        return a > b;
    }
    return a < b;
}

int main(){
int n;
cin >> n;
int numbers[1000];
for(int i = 0; i < n; i++){
    cin >> numbers[i];
}
sort(numbers, numbers + n, compareNumbers);
int a = unique(numbers, numbers + n) - numbers;

cout << a << '\n';
for(int i = 0; i < a; i++){
    if(i > 0){
        cout << ' ';
    }
    cout << numbers[i];
}
cout << '\n';
return 0;
}
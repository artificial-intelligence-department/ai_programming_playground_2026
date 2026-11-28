#include <iostream>

using namespace std;

int main(){

    int n;
    int a[100];

    cout << "Введіть к-сть елеменнтів:";
    cin >> n;

    if (cin.fail() || n < 1 || n > 100) {
        cout << "Помилка! К-сть елементів має бути числом від 1 до 100.";
        return 1;
    }

    for(int i = 0;i < n;i++){
        cout << "Введіть елемент " << i + 1 << ": ";
        cin >> a[i];
    }

    int k;
    cout << "Введіть К:";
    cin >> k;

    if (cin.fail() || k < 1 || k > n) {
        cout <<"Помилка введення К!";
        return 1;
    }

    int i = k - 1;
    cout <<"Обхід ліворуч ";
    for(int j = 0;j < n;j++){
        cout << a[i] <<" ";
        i = (i - 1 + n)% n;
    }

    cout << endl;

    for(int j = 0;j < n - 1;j++){
        a[j]=a[j + 1];
    }
    n--;

    n--;

    cout <<"Масив після видалення: ";
    for(int j = 0;j < n;j++){
        cout << a[j] <<" ";
    }

    cout << endl;

    i = k - 1;

    cout <<"Обхід праворуч ";

    for(int j = 0;j < n;j++){
        cout << a[i] <<" ";
        i = (i + 1) % n;
    }

    cout << endl;

    return 0;
}
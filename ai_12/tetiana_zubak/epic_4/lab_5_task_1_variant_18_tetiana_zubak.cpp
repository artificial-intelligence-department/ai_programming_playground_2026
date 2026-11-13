/*
Лабораторна робота № 5, Варіант 18
Зубак Тетяна
ШІ-12
*/
#include <iostream>
#include <string>
#include <sstream>
#include <locale>

using namespace std;

int Num(string text, int max){
    int num = 0;
    string trash;
  num:
    cout << text;
    cin >> num;
    if(cin.fail()){
        cout << "Введіть число!" << endl;
        cin.clear();
        getline(cin, trash);
        goto num;
    }
    if(num < 1 || num > max){
        cout << "Некоректне значення!" << endl;
        getline(cin, trash);
        goto num;
    }
    getline(cin, trash);
    return num;
}

void Arr(int a[], int n){
    string line;
  arr:
    cout << "Введіть елементи: ";
    getline(cin, line);
    stringstream ss(line);
    string word;
    bool error = false;
    int count = 0;
    while(ss >> word){
        if(count < n){
            stringstream num(word);
            int x;
            num >> x;
            if(num.fail() || !num.eof()) error = true;
            else a[count] = x;
        }
        count++;
    }
    if(count < n){
        cout << "Замало значень: потрібно " << n << ", введено " << count << "." << endl;
        goto arr;
    }
    if(count > n){
        cout << "Забагато значень: потрібно " << n << ", введено " << count << "." << endl;
        goto arr;
    }
    if(error){
        cout << "Введіть елементи цілими числами!" << endl;
        goto arr;
    }
}

void mx(int** a, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << a[i][j] << "\t";
        }
        cout << endl;
    }
}

void change(int** a, int n){
    for(int i = 0; i < n; i++){
        int right = n - 1 - i;
        int mr = i, mc = 0;
        for(int r = i; r < n; r++){
            for(int c = 0; c <= right; c++){
                if(a[r][c] > a[mr][mc]){
                    mr = r;
                    mc = c;
                }
            }
        }
        int* tmp = a[i];
        a[i] = a[mr];
        a[mr] = tmp;
        for(int r = 0; r < n; r++){
            int t = a[r][mc];
            a[r][mc] = a[r][right];
            a[r][right] = t;
        }
    }
}

bool isDescending(int** a, int n){
    for(int i = 0; i + 1 < n; i++){
        if(a[i][n - 1 - i] <= a[i + 1][n - 2 - i]) return false;
    }
    return true;
}

int main(){
    setlocale(LC_ALL, "uk_UA");

    int n = Num("Введіть N: ", 100);
    int** a = new int*[n];
    for(int i = 0; i < n; i++){
        a[i] = new int[n];
        cout << "Рядок " << i + 1 << endl;
        Arr(a[i], n);
    }

    cout << "Початкова матриця:" << endl;
    mx(a, n);

    change(a, n);

    cout << "Матриця після перестановок:" << endl;
    mx(a, n);

    cout << "Бічна діагональ: ";
    for(int i = 0; i < n; i++){
        cout << a[i][n - 1 - i] << " ";
    }
    cout << endl;

    if(isDescending(a, n)) cout << "Послідовність на бічній діагоналі спадаюча." << endl;
    else cout << "Послідовність на бічній діагоналі не спадаюча." << endl;

    for(int i = 0; i < n; i++) delete[] a[i];
    delete[] a;
    return 0;
}
/*
Лабораторна робота № 4, варіант 18
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

void print(int a[], int n, int k){
    if(n == 0){
        cout << "Кільце порожнє." << endl;
        return;
    }
    for(int i = 0; i < n; i++){
        cout << a[(k - 1 + i) % n] << " ";
    }
    cout << endl;
}

int* ends(int a[], int &n){
    int* b = new int[n + 2];
    b[0] = a[n - 1];
    for(int i = 0; i < n; i++){
        b[i + 1] = a[i];
    }
    b[n + 1] = a[0];
    n += 2;
    return b;
}

int* delEven(int a[], int &n){
    int cnt = 0;
    for(int i = 0; i < n; i++){
        if(a[i] % 2 != 0) cnt++;
    }
    int* b = new int[cnt > 0 ? cnt : 1];
    int j = 0;
    for(int i = 0; i < n; i++){
        if(a[i] % 2 != 0){
            b[j] = a[i];
            j++;
        }
    }
    n = cnt;
    return b;
}

int main(){
    setlocale(LC_ALL, "uk_UA");

    int n = Num("Введіть кількість елементів: ", 100000);
    int* a = new int[n];
    Arr(a, n);

    int k = Num("Введіть К: ", n);
    cout << "Кільце від К-ого елемента до К-1:";
    print(a, n, k);

    int* c = ends(a, n);
    delete[] a;
    cout << "Кільце з доданими першим і останнім елементами:";
    print(c, n, 1);

    int* d = delEven(c, n);
    delete[] c;
    cout << "Кільце без парних елементів, від К-ого елемента до К-1:";
    print(d, n, k);

    delete[] d;
    return 0;
}
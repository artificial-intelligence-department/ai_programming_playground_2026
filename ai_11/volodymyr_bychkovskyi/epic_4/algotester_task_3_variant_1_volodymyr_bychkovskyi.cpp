/*
Назва: Алготестер Лабораторна 3 варіант 1
Автор: Бичковський Володимир
Група: ШІ-11
*/
#include <iostream>
#include <string>
using namespace std;

int main (){
    int N;
    cin >> N;
    cin.ignore();
    string arr[N];
    for(int i = 0; i < N; i++){
        getline(cin, arr[i]);
    }
    
    int a = 0;
    bool is = true;
    for(int i = 0; i < N; i++){
        for (char c : arr[i]) {
            if (c == '#') {
                if(is){
                    a++;
                    is = false;
                }
            }
            else{
                is = true;
            }
        }
    }
    cout << a;
}
/*
Назва: Алготестер Лабораторна 2 варіант 3
Автор: Бичковський Володимир
Група: ШІ-11
*/
#include <iostream>
using namespace std;

int main (){
    int N;
    cin >> N;
    int arr[N];
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
    
    int x = 1;
    int y = N;
    bool is = true;
    while(is){
        if(x==y){
            cout << x << " " << y << endl;
            cout << "Collision";
            is = false;
            break;
        }
        else if(y-x==1){
            cout << x << " " << y << endl;
            cout << "Stopped";
            is = false;
            break;
        }
        else if(y<x){
            cout << x << " " << y << endl;
            cout << "Miss";
            is = false;
            break;
        }
        x += arr[x-1];
        y -= arr[y-1];
        
    }
}
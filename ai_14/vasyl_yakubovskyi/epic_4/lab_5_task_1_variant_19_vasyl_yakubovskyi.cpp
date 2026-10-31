/*
Task: lab 5 task 1 option 19
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/



#include <iostream>

using namespace std;

int main (){

    //Вводимо число N
    int N = 0; 
    cout << "Введіть значення N: " ;
    cin >> N;
    if(N < 0){
        cout << "Некоректний ввід!";
        return 1;
    }

    //Просимо ввести N*N елементів
    int a[N][N] = {0};
    cout << "Введіть " << (N*N) << " елементів: ";

    for (int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> a[i][j];
        }
    }

    //перевіряємо чи виконується умова що у першому стовпці матриці елементи йдуть у порядку зростання
    int countS = 0;
    for(int i = 1; i < N; i++){
        if(a[i-1][0] < a[i][0]){
            countS++;
        }

    }   

    bool isSuccess = false;
    if((countS + 1) == N){
        isSuccess = true;
    }
    

    //Виводимо матрицю
    cout << "\nМатриця: " << endl;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Чи виконується умова - " << (isSuccess ? "Так" : "Ні") << endl; 

    return 0;
}
/*
Task: lab 4 task 1 option 19
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/



#include <iostream>

using namespace std;

int const MAX = 100;

int main (){
    //просимо користувача ввести дані
    int n = 0;
    cout << "Enter number of elements: "; 
    cin >> n;
    if(n < 0) {cout << "Incorrect input!"; return 1;}

    int a[MAX] = {0};

    cout << "Enter elements : ";
    for(int i = 0; i < n; i++) cin >> a[i];

    int k = 0;
    cout << "Enter k: (smaller than " << n << " )";
    cin >> k;

    int i = k; 
    cout << "\n==============CIRCLE================" << endl;
    // виводимо кільце з k елементу до k + 1
    do
    {
        cout << a[i] << " ";


        if(i == 0){
            i = n - 1;    
        }else{ 
            i--;
        }
    } while (i != k);

    //додаємо до кільця перший та останній елемент
    n +=2;
    for(int i = 0; i < n - 2; i++){
        a[n - 2 - i] = a[n - 3 - i];
    }

    cout << endl;
    cout << "\nEnter first element to add: ";
    cin >> a[0];
    cout << "Enter last element to add: ";
    cin >> a[n - 1];
    

    int new_N = 0;
    int newA[MAX] = {0};

    //Видаляємо непарні елементи
    for(int i = 0; i < n; i++){
        if(a[i] != 0 && a[i] % 2 == 0){
            newA[new_N] = a[i];
            new_N++;
        }
    }

    //просимо користувача ввести новий k адже старий може бути більший за кількість елеметів.
    cout << "\nEnter k: (smaller than " << new_N << " )";
    cin >> k;
    if(k < 0 || k >= new_N){ cout << "Incorrect input!"; return 1;}

    // виводимо нове коло
    int j = k;
    cout << "\n===CIRCLE WITHOUT ODD NUMBERS==" << endl;
     do
    {
        cout << newA[j] << " ";


        if(j == 0){
            j = new_N - 1;    
        }else{ 
            j--;
        }
    } while (j != k);



    return  0;
}
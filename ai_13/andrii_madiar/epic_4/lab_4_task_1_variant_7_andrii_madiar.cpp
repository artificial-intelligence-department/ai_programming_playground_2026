/*
lab 4 task 1 variant 7, Андрій Мадяр
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main(){
    srand(time(NULL));//щоб завжди рандомні числа були
    bool exist = false;//бул який знадобиться при кінцевому виводі
    int n;
    cin >> n;
    int* arr = new int[n+1];//роблю всі елементи == 100 щоб у випадку чого не було мусорних даних в arr[n+1]
    for(int i = 0; i<n; i++){
        arr[i] = -30 + rand() % 61;//генерація рандомних від -30 до 30(можна змінити)
        cout << arr[i] << " "; 
    }
    arr[n] = 100;
    cout << "\n";
    for(int i = n-1; i>-1; i--){//пошук і "знищення" останнього елемента що = 0
        if(arr[i] == 0){
            for(int j = i; j<n; j++){
                arr[j] = arr[j+1];
            }
            exist = true;
            break;
        }
    }
    int choise = 0;
    while(!(cin >> choise) || choise < 0 || choise > n|| (exist && choise == n)){
        cout << "Виберіть існуючий індекс\n";
        cin.clear();
        cin.ignore(100, '\n');
    }
    for(int i = n; i>choise; i--){//створення елемента після того індекс якого вибрано
        (i == choise+1) ? (arr[i]=100) : (arr[i]=arr[i-1]);
    }
    if(exist){//вивід залежно від ситуації
        for(int i = 0; i<n; i++){
            cout << arr[i] << " ";
        }
    }else if(!exist && choise == n){
        for(int i = 0; i<n+1; i++){
        cout << arr[i] << " ";
    }
    }else{
        for(int i = 0; i<n+1; i++){
            cout << arr[i] << " ";
    }}
    delete[] arr;
    return 0;
}
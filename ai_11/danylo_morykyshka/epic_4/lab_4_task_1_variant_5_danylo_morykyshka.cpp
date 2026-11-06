#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_VALUE = 100;
int main()
{
    int arr[MAX_VALUE];
    cout << "Введіть довжину масиву: ";
    int arrLength;
    cin >> arrLength;
    cout << "Введіть мінімальне можливе значення масиву: ";
    int min;
    cin >> min;
    cout << "Введіть максимальне можливе значення масиву: ";
    int max;
    cin >> max;
    srand(time(0));
    for (int i = 0; i < arrLength; i++)
    {
        arr[i] = rand() % (max - min + 1) + min; 
    }
    cout << "Масив: ";
    for (int i = 0; i < arrLength; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    int tempArray1[MAX_VALUE];
    int newLen = 0;
    for (int i = 0; i < arrLength; i++)
    {
        if(arr[i]  % 7 != 0){
            tempArray1[newLen] = arr[i];
            newLen++;
        }
    }
    cout << "Оновлений масив з видаленими елементами, які кратні 7: ";
    for ( int i = 0; i < newLen; i++)
    {
        cout << tempArray1[i] << " ";
    }
    cout << endl;
    
    int tempArray2[MAX_VALUE * 2];
    int finalLen = 0;
    for (int i = 0; i < newLen; i++)
    {
        tempArray2[finalLen] = tempArray1[i];
        finalLen++;
        if(tempArray1[i] % 2 != 0){
            tempArray2[finalLen] = 0;
            finalLen++;
        }
    }
    
    cout << "Оновлений масив: ";
    for ( int i = 0; i < finalLen; i++)
    {
        cout << tempArray2[i] << " ";
    }
    cout << endl;

}
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX_SIZE = 100;

void fillArrRandom(int arr[], int size){
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 11 - 5;
    }
}
void printArr(int arr[],int size){
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void deleteLastZero(int arr[], int& size){
    for (int i = size-1; i >= 0; i--)
    {
        if (arr[i]==0) {
            for (int j = i; j < size-1; j++)
            {
                arr[j] = arr[j + 1];
            }
            size--;
            return;
        }
    }
}
void add100(int arr[], int& size, int index){
    if (index < 0 || index >= size || size >= MAX_SIZE) {
        cout << "Некоректний індекс або масив заповнений!";
        return;
    }

    for (int i = size; i > index+1; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[index + 1] = 100;
    size++;
}

int main()
{
    srand(time(0)); 
    int arr[MAX_SIZE];
    int N;
    cout << "Введіть розмір масиву: ";
    cin >> N;
    if (N > MAX_SIZE)
    {
        cout << "Введене значення більше за максимум!";
        return 1;
    }

    fillArrRandom(arr, N);
    printArr(arr, N);
    deleteLastZero(arr, N);

    int index;
    cout << "Введіть індекс елементу після якого додати 100: ";
    cin >> index;
    add100(arr, N, index);
    printArr(arr, N);
    return 0;
}
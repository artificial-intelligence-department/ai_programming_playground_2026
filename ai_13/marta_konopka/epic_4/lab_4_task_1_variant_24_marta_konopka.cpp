// variant 24
#include<iostream>
#include<cstdlib>
using namespace std;

const int MAX = 100;

void printRing(const int arr[], int size, int k){
    if(size == 0){
        cout << "Кільце порожнє" << endl;
        return;
    }
    int startIndex = (k - 1) % size;
    if(startIndex < 0){
        startIndex += size;}
        cout << "Друк кільця від елемента " << k << " до " << (k - 1 <= 0 ? size : k - 1) << ": ";
        for(int i = 0; i < size; i++){
        int currentIndex = (startIndex + i) % size;
        cout << arr[currentIndex] << " ";
    }
    cout << endl;

}
void sortRing(int arr[], int size){
    for(int i = 0; i < size - 1; i++){
        for(int j = 0; j < size - i -1; j++){
            if(arr[j] > arr[j + 1]){
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
}
int removeEvenElement(int arr[], int size){
    int newSize = 0;
    for(int i = 0; i < size; i++){
        if(abs(arr[i]) % 2 != 0){
            arr[newSize] = arr[i];
            newSize++;
        }
    }
    return newSize;
}

int main(){
    int ring[MAX];
    int size, k;

    cout << "Введіть реальну довжину масиву: ";
    cin >> size;

    if(size <= 0 || size > MAX){
        cout << "Помилка. Довжина не збігається з встановленими межами" << endl;
        return 1;
    }
    cout << "Введіть елемети кільця: " ;
    for(int i = 0; i < size; i++){
        cin >> ring[i];
    }
    cout << "Введіть позицію k: " ;
    cin >> k;

    cout << "Початкове кільце: " << endl;
    printRing(ring, size, k);
    cout << "Сортування за зростанням: " << endl;
    sortRing(ring, size);
    printRing(ring, size, k);
    cout << "Видалення парних елементів" << endl;
    size = removeEvenElement(ring, size);
    cout << "Кільце після видалення: " << endl;
    printRing(ring, size, k);



    return 0;
}

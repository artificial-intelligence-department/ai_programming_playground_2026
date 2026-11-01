/* 
Лабораторна робота н.4
Варіант: 6
Автор: Давидович Святослав
Група: ШІ-11
*/

#include <iostream>
#include <random>

using namespace std;

int getValidInteger() {
    int input;

    while (true) {
        cin >> input;

        if (cin.fail()) {
            cout << "Помилка вводу\n";
            
            cin.clear();
            cin.ignore(1000, '\n');
        } 
        else {
            cin.ignore(1000, '\n');
            return input;
        }
    }
}

int main(){
    const int RANGE = 1000;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(-RANGE, RANGE);

    const int N = 100;
    int* arr = new int[N];

    for (int i = 0; i<N; i++){
        arr[i] = distrib(gen);
    }

    cout << "Масив випадкових чисел [-1000, 1000]:\n";

    for (int i = 0; i<N; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";
    int I = -1;;
    do{
        cout << "I = ";
        I = getValidInteger();
    } while (I<0 || I>=N);
    
    int* arr1 = new int[N-1];
    for (int i = 0, j = 0; i<N; i++, j++){
        if (i==I){ // пропускаємо запис "знищеного" елемента
            j--;
            continue;
        }
        arr1[j]=arr[i];
    }

    int newEl = arr1[I-1]+2;

    int* arr2 = new int[N];
    for (int i = 0, j = 0; i<N; i++, j++){
        if (j!=i || (RANGE+arr1[j])%2==1) { // (RANGE+arr1[j])%2 гарантує, що отримане число буде додатним по модулю 
            arr2[j]=arr1[i];
        } else {
            arr2[j]=arr1[i];
            j++;
            arr2[j]=newEl;
        }
    }

    cout << "Модифікований масив:\n";
    for (int i = 0; i<N; i++){
        cout << arr2[i] << " ";
    }
    // звільнення пам'яті
    delete[] arr;
    delete[] arr1;
    delete[] arr2;
    cout << "\n";
}
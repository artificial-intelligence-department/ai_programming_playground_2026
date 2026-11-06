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

    const int N = 100; // початкова кількість елементів
    int arr[500]; // виділяємо пам'ять у статичному масиві "із запасом"

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
    } while (I<1 || I>=N);
    
    for (int i = I; i<N-1; i++){
        arr[i]=arr[i+1]; // зсув вліво
    }

    int newEl = arr[I-1]+2;

    int inserted_id = -1;
    for (int i = 0; i<N-1; i++){
        if ((RANGE+arr[i])%2==0){ // (RANGE+arr1[i])%2 гарантує, що отримане число буде додатним по модулю
            inserted_id = i+1;
            break;
        }
    }

    for (int i = N-1; i>inserted_id; i--){
        arr[i] = arr[i-1]; // зсув вправо
    }
    arr[inserted_id] = newEl;

    cout << "Модифікований масив:\n";
    for (int i = 0; i<N; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";
}
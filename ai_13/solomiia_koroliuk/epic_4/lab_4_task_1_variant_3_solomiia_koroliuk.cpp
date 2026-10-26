#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;


void printArray(const int arr[], int size);

int main(){

    const int n = 20;
    int sp[n];
    int size;

    srand(time(nullptr));
 
    // 1) Заповнення масиву
    cout << "Кількість елементів масиву: ";
    cin >> size;

    for (int i = 0; i < size; i++){
        int randomNum = rand() % 11 - 3; // Числа від -3 до 7
        sp[i] = randomNum;
    }

    // 2) Роздрукувати отриманий початковий масив 
    cout << "Початковий масив: " << endl;
    printArray(sp, size);

    // 3) Знищити всі елементи які дорівнюють 0 
    int new_n = 0;
    for (int i = 0; i < size; i++){
        if (sp[i] != 0){
            sp[new_n] = sp[i];
            new_n++;
        }
    }
    size = new_n;
            

    // 4) Додати після першого парного елемента елемент зі значенням M[I-1] + 2
    for (int i = 0; i < size; i++){
        if (sp[i] % 2 == 0){

            if (i == 0) {
                cout << "Перший елемент парний, перед ним немає sp[i-1]. Вставку пропущено." << endl;
                break; 
            }

            int newVal = sp[i - 1] + 2;

            for (int j = size; j > i + 1; j--){
                sp[j] = sp[j - 1];
            }

            sp[i + 1] = newVal;
            size++;
            break;
        }
    }

    // 5) Роздрукувати кінцевий масив 
    cout << "Оновлений масив" << endl;
    printArray(sp, size);

    return 0;
}

void printArray(const int arr[], int size){
    for (int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}
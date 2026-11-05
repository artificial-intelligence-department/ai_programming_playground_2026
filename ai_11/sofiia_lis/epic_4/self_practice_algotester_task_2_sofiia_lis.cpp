/* 
Епік 4. Self practice: Найдовший зростаючий підмасив
Авторка: Софія Ліс
Група: ші-11
*/

#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int * array = new int[n];

    for(int i = 0; i < n; i++) {
        cin >> *(array + i);
    }

    int counter = 1;
    int max_counter = 0;

    for(int i = 1; i < n; i++) {
        if(*(array + i - 1) < *(array + i)) {
            counter++;
        }
        else {
        counter = 1;
    }
    if(counter > max_counter) {
            max_counter = counter;
    }
    }
    cout << max_counter;
    delete[] array;
    array = nullptr;
    return 0;
}
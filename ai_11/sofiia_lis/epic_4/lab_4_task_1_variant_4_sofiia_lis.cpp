/* 
Епік 4. lab_4_task_1_variant_4
Авторка: Софія Ліс
Група: ші-11
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void fillArr(int* arr, int n) {
    for(int i = 0; i < n; i++) {
        *(arr + i) = rand()%101-50;
    }
}

void showArr(int* arr, int n) {
    for(int i = 0; i < n; i++) {
        cout << *(arr + i) << " ";
    }
    cout << endl;
}

int removeMultThree(int* arr, int n) {
    int newn = 0;
    for(int i = 0; i < n; i++) {
        if(i%3 != 0) {
            *(arr + newn) = *(arr + i);
            newn++; 
        }
    }
    return newn;
}

int addNumAfterNeg(int* arr, int n) {
    for(int i = 0; i < n; i++) {
        if(*(arr + i) >= 0) continue;

        for(int j = n; j > (i+1) ; j--) {
            *(arr + j) = *(arr + (j-1));
        }

        *(arr + i+1) = abs(*(arr + i) + 1);
        i++; //збільшуємо і, аби при наступній ітерації не треба було перевіряти на від'ємність
        n++;
    }
    return n;
}

int main() {
    srand(time(nullptr));
    const int N = 100;
    int array[N];
    int n;
    cout << "Введіть довжину масиву ";
    cin >> n;

    fillArr(array, n);
    showArr(array, n);
    n = removeMultThree(array, n);
    showArr(array, n);
    n = addNumAfterNeg(array, n);
    showArr(array, n);
    
    return 0;
}
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void print_arr(int a[], const int n){
    for(int i = 0; i < n; i++){
            cout << a[i] << " ";
    }
    cout << endl;
}

bool delete_element(int a[], int &n, int target){
    int index = -1;
    for( int i = 0; i < n; i++){
        if(a[i] == target){
            index = i;
            break;
        }
    }
    if(index == -1){
        return false;
    }
    n --;
    for(int i = index; i < n; i++){
        a[i] = a[i+1];
    }
    return true;
}

void move( int a[], int n, int k){
    if (n == 0) {
        return;
    }
    k %= n;
    while (k < 0) {
        k += n;
    }

    
    if (k == 0) {
        return;
    }

    int *b = new int[100];
    for(int i = n-1; i >= 0; i--){
        if(i + k > n-1){
            b[i+k-n] = a[i];
        }
        else{
            b[i+k] = a[i];
        }
    }
    for(int i = 0; i < n; i++){
        a[i] = b[i];
    }
    delete[] b;
    b = nullptr;
}

int main() {
    int *arr = new int[100];
    int n;

    srand((int)(time(nullptr)));

    cout << "Введiть кiлькiсть елементiв: ";
    cin >> n;
    if ( cin.fail() || n <= 0 || n > 100) {
        cout << "Помилка: некоректний розмiр.";
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 100;
    }

    cout << "\nПочатковий масив:" << endl;
    print_arr(arr, n);

    int target;
    cout << "\nВведiть елемент: ";
    cin >> target;

    if (delete_element(arr, n, target)) {
        cout << "Елемент " << target << " успiшно знищено." << endl;
        cout << "Масив:" << endl;
        print_arr(arr, n);
    } else {
        cout << "Елемент не знайдено." << endl;
    }

    int k;
    cout << "\nВведiть величину зсуву: ";
    cin >> k;

    move(arr, n, k);
    cout << "\nМасив пiсля циклiчного зсуву вправо на " << k << endl;
    print_arr(arr, n);
    delete[] arr;
    arr = nullptr;
    return 0;
}
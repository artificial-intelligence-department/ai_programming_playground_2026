#include <iostream>
#include <iomanip>
#include <cstdlib>   // rand, srand
#include <ctime>     // time

using namespace std;

const int N = 100;           
const int MIN_VALUE = -10;   
const int MAX_VALUE = 10;

void fillRandom(int a[], int n);
void printArray(const int a[], int n);
int findMin(const int a[], int n);
void removeMin(int a[], int &n, int minValue);
double average(const int a[], int n);
bool addAtStart(int a[], int &n, int count, int value);

int main() {
    int a[N];    
    int n;       

    cout << "Введіть довжину масиву (від 1 до " << N << "): ";
    if (!(cin >> n) || n < 1 || n > N) {
        cout << "Помилка! Потрібно ввести ціле число від 1 до " << N << "." << endl;
        return 1;
    }

    
    srand((unsigned)time(nullptr));      
    fillRandom(a, n);
    cout << "Початковий масив:" << endl;
    printArray(a, n);

    // Видалення всіх елементів, рівних мінімуму
    int minValue = findMin(a, n);
    int oldN = n;
    removeMin(a, n, minValue);
    cout << endl << "Мінімальне значення: " << minValue
         << ", видалено елементів: " << oldN - n << endl;
    cout << "Масив після видалення:" << endl;
    printArray(a, n);

    // Додавання трьох елементів зі значенням середнього
    if (n == 0) {
        cout << endl << "Масив порожній: середнє арифметичне обчислити неможливо, "
             << "додавання пропущено." << endl;
    } else {
        double avg = average(a, n);
        int value = (int)avg;            // беремо цілу частину
        cout << endl << fixed << setprecision(2)
             << "Середнє арифметичне: " << avg
             << " (у масив записуємо " << value << ")" << endl;

        if (!addAtStart(a, n, 3, value)) {
            cout << "Недостатньо місця: після додавання було б більше "
                 << N << " елементів." << endl;
        }
    }

    
    cout << endl << "Підсумковий масив:" << endl;
    printArray(a, n);

    return 0;
}

void fillRandom(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = rand() % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE;
    }
}

void printArray(const int a[], int n) {
    if (n == 0) {
        cout << "(масив порожній)" << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int findMin(const int a[], int n) {
    int minValue = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < minValue) {
            minValue = a[i];
        }
    }
    return minValue;
}

void removeMin(int a[], int &n, int minValue) {
    int k = 0;                       
    for (int i = 0; i < n; i++) {
        if (a[i] != minValue) {
            a[k] = a[i];
            k++;
        }
    }
    n = k;                           
}

double average(const int a[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return (double)sum / n;
}

/
bool addAtStart(int a[], int &n, int count, int value) {
    if (n + count > N) {
        return false;
    }
    for (int i = n - 1; i >= 0; i--) {   // зсув праворуч, з кінця
        a[i + count] = a[i];
    }
    for (int i = 0; i < count; i++) {
        a[i] = value;
    }
    n += count;                          
    return true;
}
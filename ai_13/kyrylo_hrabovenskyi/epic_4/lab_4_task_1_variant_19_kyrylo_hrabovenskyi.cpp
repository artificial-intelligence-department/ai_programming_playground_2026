// кільце однонаправлене
#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;
//Друк по кільцю справа наліво (вліво) від K до K+1
void print_left_cyclic(int length, int k, int A[]) {
    if (length == 0)
    {
        cout << "Ring is empty\n";
        return;
    }
    k = (k % length + length) % length;


    cout << "Ring from index " << k << " to left (right-to-left): ";
    int curr = k;
    for (int i = 0; i < length; i++) {
        cout << A[curr] << " ";
        curr = (curr - 1 + length) % length; // Перехід справа наліво за умовою
    }
        cout << endl;
}


// 19.3: Додати в кільце перший і останній елементи
void add_first_and_last(int A[], int& length, int max_capacity) {
    if (length <= 0) return;


    if (length + 2 > max_capacity) {
        cout << "Error: Not enough space in static array!\n";
        return;
    }


    int first_val = A[0];
    int last_val = A[length - 1];


    // Зсуваємо елементи вправо, щоб звільнити місце для першого елемента на індексі 0
    for (int i = length; i > 0; i--) {
        A[i] = A[i - 1];
    }


    A[0] = first_val; // Вставка копії першого на початок
    length++;


    A[length] = last_val; // Вставка копії колишнього останнього в кінець
    length++;
}


// 19.4: Знищити з кільця непарні елементи (залишаються тільки парні)
void destroy_odd_elements(int A[], int& length) {
    int write_index = 0;


    // Фільтруємо масив "на місці" (in-place) без додаткового масиву
    for (int i = 0; i < length; i++) {
        if (A[i] % 2 == 0) { // Якщо елемент парний — залишаємо
            A[write_index] = A[i];
            write_index++;
        }
    }
    length = write_index; // Оновлюємо реальну довжину масиву
}
int main() {
    srand(time(0));


    const int N = 100; // Максимальний розмір за методичними вказівками
    int A[N];
    int length;


    // 19.1: Сформувати одновимірний масив цілих чисел
    cout << "Enter length of array (1-90): ";
    cin >> length;


    if (length <= 0 || length > 90) {
        cout << "Invalid length!\n";
        return 1;
    }


    for (int i = 0; i < length; i++) {
        A[i] = rand() % 20 + 1; // Числа від 1 до 20
    }


    // Друк для контролю початкового стану масиву в лінійному вигляді
    cout << "Initial array (linear): ";
    for (int i = 0; i < length; i++) cout << A[i] << " ";
    cout << endl;


    cout << "Enter start index K: ";
        int k;
        cin >> k;


    // 19.2: Роздрукувати отриманий масив від К до К+1 (вліво)
    print_left_cyclic(length, k, A);


    // 19.3: Додати в кільце перший і останній елементи
    cout << "\n--- Adding first and last elements ---\n";
    add_first_and_last(A, length, N);


    cout << "Array after insertion (linear): ";
    for (int i = 0; i < length; i++) cout << A[i] << " ";
    cout << endl;


    // 19.4: Знищити з кільця непарні елементи
    cout << "\n--- Destroying odd elements ---\n";
    destroy_odd_elements(A, length);


    cout << "Array after destroying odd elements (linear): ";
    for (int i = 0; i < length; i++) cout << A[i] << " ";
    cout << endl;


    // 19.5: Роздрукувати отриманий масив від К до К+1 (вліво)
    print_left_cyclic(length, k, A);


    return 0;
}

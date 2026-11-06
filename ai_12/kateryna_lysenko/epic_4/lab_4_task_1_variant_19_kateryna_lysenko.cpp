/*
Назва:lab 4 task 1
Автор: Катерина Лисенко
Група: ШІ-12
*/
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int N = 100; // максимально можлива довжина масиву

// Наступний елемент кільця при русі справа наліво
int next_left(int i, int n)
{
    return (i - 1 + n) % n;
}

// Друк масиву в порядку індексів
void print_array(const int a[], int n)
{
    if (n == 0) {
        cout << "(кільце порожнє)" << endl;
        return;
    }
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

/*
 * Друк кільця, починаючи з k-ого елемента (нумерація з 1)
 * і рухаючись справа наліво по колу: k, k-1, ..., 1, n, ..., k+1.
 * Останнім друкується (k+1)-й елемент.
 */
void print_ring(const int a[], int n, int k)
{
    if (n == 0) {
        cout << "(кільце порожнє)" << endl;
        return;
    }
    int i = k - 1;
    for (int cnt = 0; cnt < n; cnt++) {
        cout << a[i] << " ";
        i = next_left(i, n);
    }
    cout << endl;
}

// Заповнення масиву випадковими числами з діапазону [-50; 50]
void fill_random(int a[], int n)
{
    for (int i = 0; i < n; i++)
        a[i] = rand() % 101 - 50;
}

// Вставка значення value на позицію pos (0-based); повертає нову довжину
int insert_element(int a[], int n, int pos, int value)
{
    for (int i = n; i > pos; i--)
        a[i] = a[i - 1];
    a[pos] = value;
    return n + 1;
}

// Знищення всіх непарних елементів; повертає нову довжину
int delete_odd(int a[], int n)
{
    int j = 0;
    for (int i = 0; i < n; i++)
        if (a[i] % 2 == 0)
            a[j++] = a[i];
    return j;
}

// Введення цілого числа з перевіркою вводу
int read_int(const char *prompt)
{
    int x;
    cout << prompt;
    if (!(cin >> x)) {
        cout << "Помилка вводу." << endl;
        exit(1);
    }
    return x;
}

// Введення K з перевіркою на діапазон 1..n
int read_k(int n)
{
    int k;
    do {
        cout << "Введіть номер K початкового елемента (1.." << n << "): ";
        if (!(cin >> k)) {
            cout << "Помилка вводу." << endl;
            exit(1);
        }
    } while (k < 1 || k > n);
    return k;
}

int main()
{
    int a[N];
    int n, k;

    srand((unsigned)time(NULL));

    // 1. Формування кільця
    do {
        cout << "Введіть довжину кільця (1.." << N << "): ";
        if (!(cin >> n)) {
            cout << "Помилка вводу." << endl;
            return 1;
        }
    } while (n < 1 || n > N);

    fill_random(a, n);

    cout << "\nМасив (n = " << n << "), у порядку індексів:" << endl;
    print_array(a, n);

    // 2. Друк кільця від K-ого елемента (справа наліво) до K+1
    cout << endl;
    k = read_k(n);
    cout << "\nКільце, починаючи з " << k << "-го елемента, справа наліво:" << endl;
    print_ring(a, n, k);

    // 3. Додавання в кільце першого і останнього елементів
    if (n + 2 > N) {
        cout << "\nМасив заповнений, додавання двох елементів неможливе." << endl;
    } else {
        cout << endl;
        int first = read_int("Введіть значення нового першого елемента: ");
        int last = read_int("Введіть значення нового останнього елемента: ");
        n = insert_element(a, n, 0, first); // новий перший
        n = insert_element(a, n, n, last);  // новий останній
    }

    cout << "\nМасив після додавання першого й останнього елементів (n = "
         << n << "):" << endl;
    print_array(a, n);

    // 4. Знищення непарних елементів
    n = delete_odd(a, n);

    cout << "\nМасив після знищення непарних елементів (n = " << n << "):" << endl;
    print_array(a, n);

    // 5. Друк кільця від K-ого елемента до K+1
    if (n > 0) {
        cout << endl;
        k = read_k(n);
        cout << "\nКільце, починаючи з " << k << "-го елемента, справа наліво:" << endl;
        print_ring(a, n, k);
    }

    return 0;
}
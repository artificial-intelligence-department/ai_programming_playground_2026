#include <iostream>
#include <vector>
#include <algorithm> // Для swap

using namespace std;

// Функція для формування матриці з одновимірного масиву (вашого рядка цифр)
void create_matrix(int N, const vector<int>& A, vector<vector<int>>& Atwo)
{
    int index = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            Atwo[i][j] = A[index];
            index++;
        }
    }
}

// Функція, яка сортує РЯДКИ матриці за першим елементом кожного рядка
void sort_matrix(int N, vector<vector<int>>& Atwo)
{
    // Метод бульбашки для перестановки цілих рядків
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            // Порівнюємо перші елементи сусідніх рядків (стовпець 0)
            if (Atwo[j][0] > Atwo[j + 1][0])
            {
                // Міняємо місцями рядки повністю
                swap(Atwo[j], Atwo[j + 1]);
            }
        }
    }
}

// Функція для перевірки, чи дійсно перший стовпець тепер впорядкований за зростанням
bool check_first_column(int N, const vector<vector<int>>& Atwo)
{
    for (int i = 0; i < N - 1; i++)
    {
        // Якщо наступний елемент менший або рівний попередньому — сортування не вийшло
        // Примітка: якщо викладач дозволяє однакові цифри (нестроге зростання), змініть на <=
        if (Atwo[i][0] >= Atwo[i + 1][0])
        {
            return false;
        }
    }
    return true;
}

// Функція для гарного виведення матриці на екран
void print_matrix(int N, const vector<vector<int>>& Atwo)
{
    cout << "\nПоточна матриця:\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << Atwo[i][j] << " ";
        }
        cout << "\n";
    }
}

int main()
{
    // Налаштування локалізації для коректного відображення української мови в консолі
    setlocale(LC_ALL, "Ukrainian");

    cout << "Введiть N: ";
    int N;
    cin >> N;

    int length_of_line = N * N;

    cout << "Введiть " << length_of_line << " цифр через пробiл: \n";
    vector<int> A(length_of_line);
    for (int i = 0; i < length_of_line; i++)
    {
        cin >> A[i];
    }

    vector<vector<int>> Atwo(N, vector<int>(N));

    // 1. Створюємо початкову матрицю
    create_matrix(N, A, Atwo);
    cout << "\nПочатковий вигляд матрицi:";
    print_matrix(N, Atwo);

    // 2. Сортуємо її рядки за першим стовпцем
    sort_matrix(N, Atwo);
    cout << "\nМатриця пiсля спроби впорядкування:";
    print_matrix(N, Atwo);

    // 3. Перевіряємо результат та виводимо відповідь за умовою задачі
    if (check_first_column(N, Atwo))
    {
        cout << "\nВiдповiдь: ТАК, можна розташувати в порядку зростання.\n";
    }
    else
    {
        cout << "\nВiдповiдь: НI, розташувати в порядку зростання неможливо (є однаковi цифри або помилка).\n";
    }

    return 0;
}
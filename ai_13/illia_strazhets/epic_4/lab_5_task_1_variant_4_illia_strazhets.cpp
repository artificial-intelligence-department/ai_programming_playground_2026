/*
Лабораторна робота №5. Варіант 4.
Автор: Illia Strazhets
Група: AI-13
Завдання: визначити, чи є матриця ортонормованою, тобто такою, що скалярний
добуток кожної пари різних рядків дорівнює 0, а скалярний добуток рядка
самого на себе дорівнює 1.
*/
#include <iostream>
#include <string>
using namespace std;

const int COLS = 100;
const int ROWS = 100;

// Безпечне зчитування цілого числа з перевіркою коректності вводу (cin.fail())
bool readNumber(int &value)
{
    cin >> value;
    if (cin.fail())
    {
        // Скидаємо прапорець помилки та очищаємо некоректний ввід до кінця рядка
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
    }
    return true;
}

// Зчитування елементів матриці; повертає false, якщо трапився нечисловий ввід
bool getMatrix(int matrix[ROWS][COLS], int rows, int cols)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (!readNumber(matrix[i][j]))
            {
                return false;
            }
        }
    }
    return true;
}

// Вивід матриці: рядок за рядком, числа через пробіл
void printMatrix(int matrix[ROWS][COLS], int rows, int cols)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Перевірка ортонормованості матриці; повертає «Так» або «Ні»
string isOrthonormal(int matrix[ROWS][COLS], int rows, int cols)
{
    // Ортонормована матриця за визначенням має бути квадратною
    if (rows != cols)
    {
        return "Ні";
    }

    // Перебираємо перший рядок пари
    for (int i = 0; i < rows; ++i)
    {
        // Перебираємо другий рядок пари (від i до кінця, щоб охопити і i==j, і пари без дублювання)
        for (int j = i; j < rows; ++j)
        {
            int dobutok = 0;

            // Рахуємо скалярний добуток між рядком i та рядком j
            for (int k = 0; k < cols; ++k)
            {
                dobutok += matrix[i][k] * matrix[j][k];
            }

            // Перевірка умов:
            if (i == j)
            {
                // Скалярний квадрат рядка має бути рівним 1
                if (dobutok != 1)
                {
                    return "Ні";
                }
            }
            else
            {
                // Скалярний добуток різних рядків має бути рівним 0
                if (dobutok != 0)
                {
                    return "Ні";
                }
            }
        }
    }

    // Якщо жодна перевірка не провалилася — матриця ортонормована
    return "Так";
}

// Головна функція: ввід розмірів і матриці, вивід результату перевірки
int main()
{
    int matrix[ROWS][COLS] = {{0}};
    int rows, cols;

    cout << "Введіть кількість рядків (не більше " << ROWS << "): ";
    if (!readNumber(rows) || rows <= 0 || rows > ROWS)
    {
        cout << "Помилка: кількість рядків має бути цілим числом від 1 до " << ROWS << ".\n";
        return 1;
    }

    cout << "Введіть кількість стовпців (не більше " << COLS << "): ";
    if (!readNumber(cols) || cols <= 0 || cols > COLS)
    {
        cout << "Помилка: кількість стовпців має бути цілим числом від 1 до " << COLS << ".\n";
        return 1;
    }

    cout << "Введіть елементи матриці " << rows << " x " << cols << ":\n";
    if (!getMatrix(matrix, rows, cols))
    {
        cout << "Помилка: елементи матриці мають бути цілими числами.\n";
        return 1;
    }

    cout << "\nВведена матриця:\n";
    printMatrix(matrix, rows, cols);
    cout << "Чи є матриця ортонормованою? " << isOrthonormal(matrix, rows, cols) << endl;
    return 0;
}

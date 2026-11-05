#include <iostream>
using namespace std;

void deletearr(int **&arr, int rows) // Звільнення пам'яті
{

    if (arr == nullptr)
        return;
    for (int i = 0; i < rows; i++)
    {

        delete[] arr[i]; // Звільнення пам'яті i рядка
    }
    delete[] arr; // звільнення масиву вказівників
    arr = nullptr;
}
void deleterow(int cols, int rows, int A, int B, int **arr, int **copyarr)
{
    A--;
    int difference = (B - A) + 1;
    int new_i = A;
    for (int i = B; i < rows; i++) // Зсуваємо рядки
    {
        for (int j = 0; j < cols; j++)
        {
            arr[new_i][j] = copyarr[i][j];
        }
        new_i++; // Використовуємо власну змінну, щоб не вийти за межі масиву
    }

    for (int i = rows - 1; i > ((rows)-difference); i--)
    { // міняємо останні B-A рядки на нулі бо ми їх зсунули
        for (int j = 0; j < cols; j++)
        {
            arr[i][j] = 0;
        }
    }
}

int main()
{
    int rows;
    int cols;
    cout << "Введіть кількість рядків(від 1 до 100): ";
    cin >> rows;
    if (rows > 100 || rows < 1)
    {
        cout << "Помилка.Кількість повинна бути від 1 до 100.";
        return 0;
    }
    cout << "Введіть кількість стовпців(від 1 до 100): ";
    cin >> cols;
    if (cols > 100 || cols < 1)
    {
        cout << "Помилка.Кількість повинна бути від 1 до 100." << endl;
        return 0;
    }
    int **arr = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        arr[i] = new int[cols]; // Для кожного рядка виділяємо пам'ять під cols елементів
    }
    int A, B;
    for (int i = 0; i < rows; i++)
    {
        cout << "Введіть елементи " << i + 1 << " рядка:";
        for (int j = 0; j < cols; j++)
        {
            cin >> arr[i][j];
        }
    }
    int **copyarr = new int *[rows]; // створємо копію масиву
    for (int i = 0; i < rows; i++)
    {
        copyarr[i] = new int[cols];
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            copyarr[i][j] = arr[i][j];
        }
    }

    cout << "Знищити від(A): ";
    cin >> A;
    if (A < 1 || A > rows)
    {
        cout << "Помилка.A повинна бути від 1 до " << rows << endl;
        deletearr(arr, rows);
        deletearr(copyarr, rows); // звільнення пам'яті

        return 0;
    }
    cout << "Знищити до(B): ";
    cin >> B;
    if (B < A)
    {
        cout << "Помилка.B повинна бути >=  " << A << endl;
        deletearr(arr, rows);
        deletearr(copyarr, rows);
        return 0;
    }
    cout << "Початковий масив: " << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    deleterow(cols, rows, A, B, arr, copyarr); // виклик функції для зміни матриці
    cout << "Результат: " << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    deletearr(arr, rows);
    deletearr(copyarr, rows); // звільнення пам'яті
    return 0;
}
/*
Редактор монохромного зображення
Автор: Illia Strazhets
Група: AI-13
*/
#include <iostream>
#include <iomanip>
using namespace std;

// Максимально допустимий розмір сторін зображення за умовою задачі
int const MAX = 20;

// Функція безпечного зчитування цілого числа з перевіркою на коректність вводу
bool readNumber(int &value)
{
    // Якщо користувач ввів число успішно — повертаємо true
    if (cin >> value)
        return true;

    // Перевірка на досягнення кінця файлу/потоку вводу (Ctrl+D / Ctrl+Z)
    if (cin.eof())
        return false;

    // Скидаємо прапорець помилки cin при введенні некоректних символів (наприклад, літер)
    cin.clear();
    // Очищаємо залишки некоректного вводу в буфері до кінця рядка
    cin.ignore(10000, '\n');
    return false;
}

// Виділення динамічної пам'яті під двовимірний масив (матрицю)
int **allocateImage(int rows, int cols)
{
    // 1. Виділяємо масив вказівників на рядки
    int **image = new int *[rows];
    // 2. Для кожного рядка виділяємо пам'ять під масив стовпців
    for (int i = 0; i < rows; ++i)
        image[i] = new int[cols];
    return image;
}

// Повне звільнення динамічної пам'яті двовимірного масиву для уникнення витоків
void freeImage(int **image, int rows)
{
    // Захист від подвійного або некоректного видалення нульового вказівника
    if (!image)
        return;
    // 1. Звільняємо пам'ять кожного окремого рядка
    for (int i = 0; i < rows; ++i)
        delete[] image[i];

    // 2. Звільняємо сам масив вказівників
    delete[] image;
}

// Вивід лише числових значень матриці: рядок за рядком, числа через пробіл
void printNumbers(int **image, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << image[i][j] << " ";
        }
        cout << "\n";
    }
}

// Вивід зображення у вигляді числової матриці з поточними розмірами
void printTable(int **image, int rows, int cols)
{
    cout << "\nЗображення " << rows << " x " << cols << ": \n";
    printNumbers(image, rows, cols);
}

// Вивід зображення псевдографікою за палітрою з 10 символів
void printImage(int **image, int rows, int cols)
{
    // Палітра: індекс символу відповідає яскравості від 0 (пробіл) до 9 (@)
    const char symbols[] = " .:-=+*#%@"; // 10 символів: від 0 (пробіл) до 9 (@)
    cout << "\nМалюнок: \n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int val = image[i][j];
            // Якщо значення в межах 0..9 — виводимо відповідний символ палітри
            if (val >= 0 && val <= 9)
                cout << symbols[val];
            else
                cout << '?'; // Захист на випадок некоректного значення
        }
        cout << "\n";
    }
    // Поточні розміри під зображенням (після повороту вони змінюються)
    cout << "Розміри: " << rows << " x " << cols << "\n";
}

// Пошук екстремумів (найтемнішого та найсвітлішого пікселів)
// Координати повертаються у викликаючий код через параметри-посилання (&)
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol)
{
    // Початково вважаємо першу комірку (0, 0) мінімумом і максимумом
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;

    // Зчитуємо початкові значення через розіменування вказівника *(img[0] + 0)
    int minVal = *(img[0] + 0);
    int maxVal = *(img[0] + 0);

    for (int i = 0; i < rows; ++i)
    {
        int *row = img[i]; // Отримуємо вказівник на початок i-го рядка
        for (int j = 0; j < cols; ++j)
        {
            // Звернення до елемента через арифметику вказівників
            int currentVal = *(row + j);

            // Строге порівняння (<) гарантує взяття першого входження при обході по рядках
            if (currentVal < minVal)
            {
                minVal = currentVal;
                minRow = i;
                minCol = j;
            }
            // Строге порівняння (>) зберігає перше знайдене максимальне значення
            if (currentVal > maxVal)
            {
                maxVal = currentVal;
                maxRow = i;
                maxCol = j;
            }
        }
    }
    // Вивід координат у форматі 1-based (індекси + 1 для зручності користувача)
    cout << "Найтемніший піксель: " << minVal << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")\n";
    cout << "Найсвітліший піксель: " << maxVal << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")\n";
}

// Розрахунок середньої яскравості всього зображення та кожного рядка окремо
void calculateAverages(int **img, int rows, int cols,
                       double &totalAvg, double *rowAvgs)
{
    int totalSum = 0;

    for (int i = 0; i < rows; ++i)
    {
        int *row = img[i]; // Вказівник на поточний рядок
        int rowSum = 0;

        for (int j = 0; j < cols; ++j)
        {
            rowSum += *(row + j); // Доступ до пікселя через зміщення вказівника
        }

        totalSum += rowSum;
        // Середнє значення для окремого i-го рядка
        rowAvgs[i] = static_cast<double>(rowSum) / cols;
    }

    // Середнє значення для всього зображення
    totalAvg = static_cast<double>(totalSum) / (rows * cols);

    // Форматування виводу: 2 знаки після коми для загального середнього
    cout << fixed << setprecision(2);
    cout << "Середня яскравість: " << totalAvg << "\n";

    // 1 знак після коми для середніх значень рядків
    cout << setprecision(1);
    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; ++i)
    {
        cout << rowAvgs[i] << " ";
    }
    cout << "\n";
}

// Інверсія яскравості на місці (in-place): темне стає світлим і навпаки
void invertBrightness(int **img, int rows, int cols)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            img[i][j] = 9 - img[i][j]; // Інвертуємо значення відносно 9
        }
    }
}

// Обмін двох чисел за допомогою вказівників та розіменування
void swapPixels(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Горизонтальне віддзеркалення зображення (in-place)
void flipHorizontal(int **img, int rows, int cols)
{
    cout << "\nЗображення віддзеркалено.\n";
    cout << "Початкове:\n";
    printNumbers(img, rows, cols);

    // Проходимо кожен рядок і міняємо стовпці дзеркально від країв до середини (cols / 2)
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols / 2; ++j)
        {
            // Передаємо адреси симетричних елементів у функцію swapPixels
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }

    cout << "\nРезультат:\n";
    printNumbers(img, rows, cols);
}

// Поворот зображення на 90 градусів праворуч (за годинниковою стрілкою)
int **rotateRight(int **img, int rows, int cols)
{
    // Оскільки розміри міняються місцями, виділяємо новий масив розміром cols x rows
    int **rotatedImg = allocateImage(cols, rows);

    // Правило повороту: рядок i стає стовпцем (rows - 1 - i) у новому масиві
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            rotatedImg[j][rows - 1 - i] = img[i][j];
        }
    }

    // Звільняємо пам'ять старої матриці для запобігання витоку пам'яті
    freeImage(img, rows);

    // Повертаємо адресу нової виділеної матриці
    return rotatedImg;
}

// Пункт меню 5: поворот, обмін розмірів місцями та вивід результату
// rows і cols передаються за посиланням, бо після повороту вони міняються місцями
int **rotateMenu(int **img, int &rows, int &cols)
{
    img = rotateRight(img, rows, cols);
    int temp = rows;
    rows = cols;
    cols = temp;

    cout << "\nЗображення повернуто. Нові розміри: " << rows << " x " << cols << "\n";
    printNumbers(img, rows, cols);
    return img;
}

// Головна функція: ввід зображення, меню операцій у циклі do-while та звільнення пам'яті
int main()
{
    int rows, cols;
    int minRow, minCol, maxRow, maxCol;
    double totalAvg;
    double rowAvgs[MAX];

    // Ввід та валідація висоти
    cout << "Висота зображення: ";
    if (!readNumber(rows) || rows < 1 || rows > MAX)
    {
        cout << "Помилка: висота зображення має бути від 1 до " << MAX << ".\n";
        return 1;
    }

    // Ввід та валідація ширини
    cout << "Ширина зображення: ";
    if (!readNumber(cols) || cols < 1 || cols > MAX)
    {
        cout << "Помилка: ширина зображення має бути від 1 до " << MAX << ".\n";
        return 1;
    }

    // Виділяємо пам'ять під матрицю ПІСЛЯ успішної перевірки розмірів
    int **image = allocateImage(rows, cols);

    // Ввід та валідація яскравості кожного пікселя
    cout << "Введіть яскравість пікселів (від 0 до 9):\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // Якщо значення не число або виходить за межі [0, 9] — очищаємо пам'ять і виходимо
            if (!readNumber(image[i][j]) || image[i][j] < 0 || image[i][j] > 9)
            {
                cout << "Помилка: яскравість пікселів має бути від 0 до 9.\n";
                freeImage(image, rows);
                image = nullptr; // Обнулення вказівника після звільнення
                return 1;
            }
        }
    }

    int choice;
    // Головний цикл меню, працює доки користувач не введе 0 (вихід)
    do
    {
        cout << "\n---------------- Редактор монохромного зображення ----------------\n";
        cout << "1  Показати зображення\n";
        cout << "2  Статистика яскравості\n";
        cout << "3  Інвертувати яскравість\n";
        cout << "4  Віддзеркалити по горизонталі\n";
        cout << "5  Повернути на 90 градусів праворуч\n";
        cout << "0  Вийти\n> ";

        // Валідація вибору пункту меню
        if (!readNumber(choice) || choice < 0 || choice > 5)
        {
            if (cin.eof())
                break;
            cout << "Помилка: введіть ціле число від 0 до 5.\n";
            // Після невдалого cin >> choice змінна стає 0, тому скидаємо її,
            // щоб умова while (choice != 0) не завершила програму
            choice = -1;
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            // Вивід числових значень та малюнка псевдографікою
            printTable(image, rows, cols);
            printImage(image, rows, cols);
            break;
        }
        case 2:
        {
            // Пошук екстремумів та розрахунок середньої яскравості
            findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);
            calculateAverages(image, rows, cols, totalAvg, rowAvgs);
            break;
        }
        case 3:
        {
            // Інверсія пікселів на місці та показ оновленої матриці
            invertBrightness(image, rows, cols);
            cout << "Яскравість інвертовано.\n";
            printNumbers(image, rows, cols);
            break;
        }
        case 4:
        {
            // Віддзеркалення стовпців матриці
            flipHorizontal(image, rows, cols); // всередині сама функція виведе і "Початкове:", і "Результат:"
            break;
        }
        case 5:
        {
            // Поворот матриці: функція повертає адресу нового масиву і міняє rows/cols місцями
            image = rotateMenu(image, rows, cols);
            break;
        }
        case 0:
        {
            cout << "Вихід з програми.\n";
            break;
        }
        }

    } while (choice != 0);

    // Звільнення динамічної пам'яті перед завершенням програми
    freeImage(image, rows);
    // Обнулення вказівника для безпеки (уникнення dangling pointer)
    image = nullptr;
    return 0;
}

/*
Редактор монохромного зображення
Карпінський Віталій
ШІ-14
*/
#include <iostream>
#include <iomanip>

using namespace std;

// Пункт 1: Вивід зображення в числовому вигляді
void choice_1(int **image, int rows, int cols) {
    cout << "Зображення " << rows << " x " << cols << ":\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }

// Вивід зображення пікселями у вигляді символів
    char draw[] = " .:-=+*#%@";
    cout << "Малюнок: " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int pixel = image[i][j];
            cout << draw[pixel];
        }
        cout << endl;
    }
}

// Пошук екстремумів через параметри-посилання
void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;
    int min = image[0][0];
    int max = image[0][0];

    for (int i = 0; i < rows; i++) {
        // Отримуємо вказівник на початок поточного рядка
        int *row = image[i];
        for (int j = 0; j < cols; j++) {
            // Звернення до елемента через розіменування адреси *(row + j)
            if (min > *(row + j)) {
                min = *(row + j);
                minRow = i;
                minCol = j;
            }
            if (max < *(row + j)) {
                max = *(row + j);
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

// Пункт 2: Обчислення середньої яскравості та вивід статистики
void choice_2(int **image, int rows, int cols) {
    int minRow = 0;
    int minCol = 0;
    int maxRow = 0;
    int maxCol = 0;

    findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);
    // Індексація через вказівник
    int minVal = *(image[minRow] + minCol);
    int maxVal = *(image[maxRow] + maxCol);

    cout << "Найтемніший піксель: " << minVal << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << maxVal << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;

    double sum = 0;
    double rowSum = 0;

    // Обчислення загальної середньої яскравості через вказівники *(row + j)
    for (int i = 0; i < rows; i++) {
        int *row = image[i];
        for (int j = 0; j < cols; j++) {
            sum += *(row + j);
        }
    }
    double average = sum / (rows*cols);
    cout << "Середня яскравість: " << fixed << setprecision(2) << average << endl;

    // Обчислення середньої яскравості для кожного рядка
    cout << "Середня по рядках: " << fixed << setprecision(1);
    for (int i = 0; i < rows; i++) {
        int *row = image[i];
        rowSum = 0;
        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j);
        }
        double rowAverage = rowSum / cols;
        cout << rowAverage << " ";
    } 
    cout << endl;
}

// Функція для звільнення динамічної пам'яті двовимірного масиву
void imageDelete(int **&image, int rows) {
    for (int i = 0; i < rows; i++) {
        // Спочатку звільняємо кожен рядок (масиви int)
        delete[] image[i];
        image[i] = nullptr;
    }
    // Потім звільняємо масив вказівників на рядки
    delete[] image;
    image = nullptr;
}

// Пункт 3: Інверсія яскравості
void choice_3(int **image, int rows, int cols) {
    cout << "Яскравість інвертовано:" << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            image[i][j] = 9 - image[i][j];
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
}

// Допоміжна функція для обміну значень двох пікселів через вказівники
void swapPixels(int *a, int *b) {
    int change = *a;
    *a = *b;
    *b = change;
}

// Пункт 4: Віддзеркалення по горизонталі
void choice_4(int **image, int rows, int cols) {
    cout << "Зображення віддзеркалено" << endl;
    cout << "Початкове:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
    // Міняємо місцями пікселі від країв до середини рядка
    cout << "Результат:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&image[i][j], &image[i][cols - j - 1]);
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
}

// Пункт 5: Поворот на 90 градусів праворуч зі зміною розміру
int **rotateRight(int **image, int rows, int cols) {
    // Виділяємо новий динамічний масив з інвертованими розмірами
    int ** image2 = new int *[cols];
    for (int i = 0; i < cols; i++) {
        image2[i] = new int [rows];
    }
    // Копіюємо елементи за правилом повороту
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            image2[j][rows - 1 - i] = image[i][j];
        }
    }
    // Звільняємо старий масив, щоб уникнути витоку пам'яті
    imageDelete(image, rows);
    cout << "Зображення перевернуто. Нові розміри: " << cols << " x " << rows << endl;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            cout << image2[i][j] << " ";
        }
        cout << endl;
    }
    // Повертаємо новий масив
    return image2;
}

int main() {
    // Ініціалізація та валідація даних
    int rows = 0;
    int cols = 0;

    cout << "Висота зображення: ";
    cin >> rows;
    if (cin.fail() || rows < 1 || rows > 20) {
        cout << "Помилка: висота повинна бути числом в діапазоні від 1 до 20" << endl;
        return 0;
    }

    cout << "Ширина зображення: ";
    cin >> cols;
    if (cin.fail() || cols < 1 || cols > 20) {
        cout << "Помилка: ширина повинна бути числом в діапазоні від 1 до 20" << endl;
        return 0;
    }

    int **image = new int *[rows];
    for (int i = 0; i < rows; i++) {
        image[i] = new int [cols];
    }

    cout << "Яскравість пікселів (0..9): " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> image[i][j];
            if (cin.fail() || image[i][j] < 0 || image[i][j] > 9 ) {
                cout << "Помилка: яскравість пікселя повинна бути числом від 0 до 9" << endl;
                imageDelete(image, rows);
                return 0;
            }
        }
    }

    short choice = -1;
    int temp;
    cin.ignore(10000, '\n');

    // Цикл do-while для повторення меню до вибору "0"
    do {
        cout << "\n==========МЕНЮ==========" << endl;
        cout << "1    Показати зображення" << endl;
        cout << "2    Статистика яскравості" << endl;
        cout << "3    Інвертувати яскравість" << endl;
        cout << "4    Віддзеркалити по горизонталі" << endl;
        cout << "5    Повернути на 90 градусів праворуч" << endl;
        cout << "0    Вийти" << endl;

        cout << "Виберіть пункт: ";
        cin >> choice;
        if (cin.fail()) {
            cout << "Помилка: некоректний ввід" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
            continue;
        }

        switch (choice){
            case 1:
                choice_1(image, rows, cols);
                break;
            case 2:
                choice_2(image, rows, cols);
                break;

            case 3:
                choice_3(image, rows, cols);
                break;
            case 4:
                choice_4(image, rows, cols);
                break;
            case 5: 
                image = rotateRight(image, rows, cols);
                temp = rows;
                rows = cols;
                cols = temp;
                break;
            
            case 0:
                break;
            default:
                cout << "Помилка: невідомий пункт" << endl;
                cin.ignore(10000, '\n');   
        }
    } while (choice != 0);

    // Очищення пам'яті
    imageDelete(image, rows);

    cout << "==========Завершення роботи==========\n" << endl;

    return 0;
}
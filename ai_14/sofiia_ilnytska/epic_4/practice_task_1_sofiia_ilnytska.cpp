/*
    Practice Task
    Автор: Ільницька Софія
    Група: ШІ-14
*/

#include <iostream>
#include <iomanip>
using namespace std;

void showImage (int** image, int rows, int cols);
void findExtremes(int** image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
void averageBrightness(int** image, int rows, int cols);
void brightnessStatistics(int** image, int rows, int cols);
void invertBrightness(int** image, int rows, int cols);
void swapPixels(int* a, int* b);
void mirrorHorizontal(int** image, int rows, int cols);
int** rotateRight(int** image, int rows, int cols);
void turnRight(int** &image, int &rows, int &cols);
void ending(int** &image, int rows);

int main() {
    int rows;  // Введення висоти з перевіркою допустимого діапазону
    cout << "Висота зображення: ";
    while (!(cin >> rows) || rows < 1 || rows > 20) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка. Висота зображення має бути від 1 до 20 пікселів: ";
    }

    int cols;  // Введення ширини з аналогічною перевіркою
    cout << "Ширина зображення: ";
    while (!(cin >> cols) || cols < 1 || cols > 20) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка. Ширина зображення має бути від 1 до 20 пікселів: ";
    }

    // Динамічне виділення пам'яті під двовимірний масив
    // Спочатку створюємо масив вказівників на рядки
    int** image = new int*[rows];
    // Для кожного рядка окремо виділяємо пам'ять під пікселі
    for (int i = 0; i < rows; i++) {
        image[i] = new int[cols]; 
    }

    // Заповнення зображення значеннями яскравості від 0 до 9
    cout << "Яскравість пікселів (0..9): " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Перевірка коректності кожного введеного пікселя
            while (!(cin >> image[i][j]) || image[i][j] < 0 || image[i][j] > 9) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Помилка. Яскравість пікселів повинна бути від 0 до 9: ";
            }
        }
    }
    int choice;
    do{  // Меню повторюється до вибору пункту 0
        cout << endl;
        cout << "Пункт    " << "Операція" << endl;
        cout << "1        " << "Показати зображення" << endl;
        cout << "2        " << "Статистика яскравості" << endl;
        cout << "3        " << "Інвертувати яскравість" << endl;
        cout << "4        " << "Віддзеркалити по горизонталі" << endl;
        cout << "5        " << "Повернути на 90 градусів праворуч" << endl;
        cout << "0        " << "Вийти" << endl;

        // Перевірка правильності вибраного пункту меню
        while (!(cin >> choice) || choice < 0 || choice > 5) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка. Введіть число від 0 до 5: ";
        }
        switch (choice) {  // Виклик відповідної функції залежно від вибору
            case 1: showImage(image, rows, cols); break;
            case 2: brightnessStatistics(image, rows, cols); break;
            case 3: invertBrightness(image, rows, cols); break;
            case 4: mirrorHorizontal(image, rows, cols); break;
            case 5: turnRight(image, rows, cols); break;
            case 0: ending(image, rows); break;
        }
    } while (choice != 0);

    return 0;
}

// Виведення зображення у числовому та символьному вигляді
void showImage (int** image, int rows, int cols) {
    cout << endl;
    cout << "Зображення " << rows << " на " << cols << ":" << endl;
    for (int i = 0; i < rows; i++) {  // Виведення числових значень яскравості пікселів
        for (int j = 0; j < cols; j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Малюнок:" << endl;
    for (int i = 0; i < rows; i++) {  // Перетворення кожного значення яскравості на символ
        for (int j = 0; j < cols; j++) {
            if (image[i][j] == 0) {
                cout << " ";
            } else if (image[i][j] == 1) {
                cout << ".";
            } else if (image[i][j] == 2) {
                cout << ":";
            } else if (image[i][j] == 3) {
                cout << "-";
            } else if (image[i][j] == 4) {
                cout << "=";
            } else if (image[i][j] == 5) {
                cout << "+";
            } else if (image[i][j] == 6) {
                cout << "*";
            } else if (image[i][j] == 7) {
                cout << "#";
            } else if (image[i][j] == 8) {
                cout << "%";
            } else if (image[i][j] == 9) {
                cout << "@";
            }
        }
        cout << endl;
    }
}

// Пошук найтемнішого та найсвітлішого пікселів
// Координати повертаються через параметри-посилання
void findExtremes(int** image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    // Початково мінімум і максимум — перший піксель
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;
    int min = image[0][0];
    int max = image[0][0];
    for (int i = 0; i < rows; i++) {
        int *row = image[i];  // Вказівник на початок поточного рядка
        for (int j = 0; j < cols; j++) {
            if ((*(row + j)) < min) { // *(row + j) — доступ до пікселя через арифметику вказівників
                min = *(row + j);
                minRow = i;
                minCol = j;
            }
            if ((*(row + j)) > max) { // Строгі порівняння зберігають перше входження екстремуму
                max = *(row + j);
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

// Обчислення середньої яскравості всього зображення та рядків
void averageBrightness(int** image, int rows, int cols) {
    double totalSum = 0;
    // Обчислення суми всіх пікселів через вказівники
    for (int i = 0; i < rows; i++) {
        int *row = image[i];
        for (int j = 0; j < cols; j++) {
            totalSum += *(row + j);
        }
    }
    // Середнє арифметичне всіх пікселів
    double average = totalSum / (rows * cols);
    cout << "Середня яскравість: " << fixed << setprecision(2) << average << endl;

    // Окреме обчислення середньої яскравості кожного рядка
    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++) {
        int *row = image[i];
        double rowSum = 0;
        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j);
        }
        double rowAverage = rowSum / cols;
        cout << fixed << setprecision(1) << rowAverage << " ";
    }
}

// Загальна функція виведення статистики яскравості
void brightnessStatistics(int** image, int rows, int cols) {
    int minRow, minCol, maxRow, maxCol;
    findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);
    cout << endl;
    cout << "Найтемніший піксель: " << image[minRow][minCol] << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << image[maxRow][maxCol] << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;
    averageBrightness(image, rows, cols);
    cout << endl;
}

// Інверсія яскравості без створення нового масиву
void invertBrightness(int** image, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            image[i][j] = 9 - image[i][j];
        }
    }
    cout << endl;
    cout << "Яскравість інвертовано." << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
}

// Обмін значень двох пікселів через їхні адреси
void swapPixels(int* a, int* b) {
    // Розіменування дозволяє змінювати початкові значення
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Горизонтальне віддзеркалення зображення
void mirrorHorizontal(int** image, int rows, int cols) {
    cout << endl;
    cout << "Зображення віддзеркалено." << endl;
    cout << "Початкове:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Результат: " << endl;
    // Обмін симетричних пікселів у кожному рядку
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {  // Достатньо пройти половину стовпців, щоб не скасувати обмін
            swapPixels(&image[i][j], &image[i][cols - 1 - j]);
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) { 
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
}

// Поворот зображення на 90 градусів праворуч
// Функція повертає вказівник на новий двовимірний масив
int** rotateRight(int** image, int rows, int cols) {
    // Створення нового масиву з переставленими розмірами
    // Нова кількість рядків = cols, стовпців = rows
    int** rotated = new int*[cols];
    for (int i = 0; i < cols; i++) {
        rotated[i] = new int[rows];
    }
    // Перенесення пікселів у нові координати
    // Перший рядок початкового зображення стає останнім стовпцем
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            rotated[j][rows - 1 - i] = image[i][j];
        }
    }

    // Звільнення пам'яті старого зображення після копіювання
    for (int i = 0; i < rows; i++) {
        delete[] image[i];
    }
    delete[] image;
    return rotated; // Повернення адреси нового масиву
}

// Оновлення зображення та його розмірів після повороту
void turnRight(int** &image, int &rows, int &cols) {
    image = rotateRight(image, rows, cols);  // Посилання на вказівник дозволяє замінити адресу масиву в main
    // Обмін висоти та ширини через параметри-посилання
    int temporary = rows;
    rows = cols;
    cols = temporary;
    cout << endl;
    cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
    // Виведення повернутого зображення
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
}

// Повне звільнення динамічної пам'яті перед завершенням програми
void ending(int** &image, int rows) {
    // Спочатку звільняємо пам'ять кожного рядка
    for (int i = 0; i < rows; i++) {
        delete[] image[i];
        image[i] = nullptr;
    }
    // Потім звільняємо масив вказівників на рядки
    delete[] image;
    image = nullptr;  // Обнуляємо головний вказівник, щоб він не вказував на звільнену пам'ять
}
/*
Редактор монохромного зображення
Небеснюк Маркіян
ШІ-12
*/

#include <iostream>
#include <string>
using namespace std;

// Виводить матрицю цифрами і сам малюнок
void Menu_1(int** img, int rows, int cols) {
    cout << "Зображення " << rows << " x " << cols << ":" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j];
            cout << " ";
        }
        cout << endl;
    }       

    cout << endl;
    cout << "Малюнок: " << endl;

    // Рядок-палітра: індекс символу відповідає значенню пікселя (0..9)
    string palitra = " .:-=+*#%@";

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << palitra[img[i][j]];
        }
        cout << endl;
    }
}

// Шукає координати та значення найтемнішого (min) і найсвітлішого (max) пікселів
void findExtremes (int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    minRow = 0; 
    minCol = 0;
    maxRow = 0; 
    maxCol = 0;

    int minVal = img[0][0]; 
    int maxVal = img[0][0];

    for (int i = 0; i < rows; i++) {
        int *row = img[i]; // Вказівник на початок поточного рядка
        for (int j = 0; j < cols; j++) {
            // Використання адресної арифметики замість img[i][j]
            if (*(row + j) > maxVal) {
                maxVal = *(row + j);
                maxRow = i;
                maxCol = j;
            }
            if (*(row + j) < minVal) {
                minVal = *(row + j);
                minRow = i;
                minCol = j; 
            }
        }
    }
}

// Рахує і виводить статистику (екстремуми та середню яскравість)
void Menu_2(int** img, int rows, int cols) {
    int minRow;
    int minCol;
    int maxRow;
    int maxCol;
    // Виклик функції пошуку (значення запишуться у змінні за посиланням)
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);
    cout << "Найтемніший піксель: " << img[minRow][minCol] 
         << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << img[maxRow][maxCol] 
         << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;
    
    double Sum = 0;
    for (int i = 0; i < rows; i++) {
        int *row = img[i];
        for (int j = 0; j < cols; j++) {
            Sum += *(row + j);
        }
    }
    double avgBrightness = Sum / (rows * cols);
    cout << "Середня яскравість: " << avgBrightness << endl;
    cout << "Середня по рядках:";
    double rowSum = 0;
    double row_avgBrightness = 0;
    // Рахуємо середню яскравість окремо для кожного рядка
    for (int i = 0; i < rows; i++) {
        rowSum = 0;
        int *row = img[i];
        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j);
        }    
        row_avgBrightness = rowSum / cols;
        cout << " " << row_avgBrightness;
    }
    cout << endl;
}

// Інвертує кольори за формулою (9 - поточне значення)
void Menu_3(int** img, int rows, int cols) {
    cout << "Яскравість інвертовано." << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img[i][j] = 9 - img[i][j];
            cout << img[i][j];
            cout << " ";
        }   
        cout << endl;
    }
}

// Допоміжна функція для обміну значень двох змінних через вказівники
void swapPixels(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Віддзеркалює зображення по горизонталі
void Menu_4(int** img, int rows, int cols) {
    cout << "Зображення відзеркалено." << endl;
    cout << "Початкове:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j];
            cout << " ";
        }
        cout << endl;
    }

    // Йдемо лише до середини стовпців і міняємо місцями лівий з правим
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }

    cout << "\nРезультат:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j];
            cout << " ";
        }
        cout << endl;
    }
} 

// Створює нову матрицю, повернуту на 90 градусів праворуч
int** rotateRight(int** img, int rows, int cols) {
    // Виділяємо пам'ять під нову матрицю з перевернутими розмірами
    int** newImg = new int*[cols];
    for (int i = 0; i < cols; i++) {
        newImg[i] = new int[rows];
    }   
    
    // Формуємо повернуте зображення
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newImg[j][rows - 1 - i] = img[i][j];
        }
    }

    // Очищаємо стару матрицю з пам'яті, щоб не було витоків
    for (int i = 0; i < rows; i++) {
        delete[] img[i];
    }
    delete[] img;
    img = nullptr;
    return newImg;
}

// Оновлює розміри та викликає поворот
void Menu_5(int** &img, int &rows, int &cols) {
    img = rotateRight(img, rows, cols); // Отримуємо нову повернуту матрицю

    // Міняємо місцями значення рядків і стовпців (swap)
    int temp = rows;
    rows = cols;
    cols = temp;

    cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j];
            cout << " ";
        }
        cout << endl;
    }
}

int main() {
    int rows;
    int cols;

    // Введення розмірів з перевіркою (валідацією)
    cout << "Висота зображення: ";
    cin >> rows;
    if (cin.fail() || rows < 1 || rows > 20) {
        cout << "Помилка: введіть дійсне значення." << endl;
        return 1;
    }

    cout << "Ширина зображення: ";
    cin >> cols;
    if (cin.fail() || cols < 1 || cols > 20) {
        cout << "Помилка: введіть дійсне значення." << endl;
        return 1; 
    }

    // Динамічне виділення пам'яті під двовимірний масив (матрицю)
    int** image = new int*[rows];
    for (int i = 0; i < rows; i++) {
        image[i] = new int[cols];
    }

    cout << "Яскравість пікселів (0..9): " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> image[i][j];
            // Якщо введено неправильне число — чистимо пам'ять і виходимо
            if (cin.fail() || image[i][j] < 0 || image[i][j] > 9) {
                cout << "Помилка: введіть дійсне значення." << endl;
                for (int k = 0; k < rows; k++) {
                    delete[] image[k];
                }
                delete[] image;
                image = nullptr;
                return 1; 
    }
        }
    }

    int menu;
    // Головне меню з циклом do-while (поки не виберуть 0)
    do {
        cout << endl;
        cout << "\tМеню" << endl;
        cout << "Пункт\t\t" << "Операція" << endl;
        cout << "1\t\t" << "Показати зображення" << endl;
        cout << "2\t\t" "Статистика яскравості" << endl;
        cout << "3\t\t" "Інвертувати яскравість" << endl;
        cout << "4\t\t" "Віддзеркалити по горизонталі" << endl;
        cout << "5\t\t" "Повернути на 90 градусів праворуч" << endl;
        cout << "0\t\t" "Вийти" << endl;

        // Захист від введення букв замість цифр у меню
        while (true) {
            cin >> menu;    
            if (cin.fail() || menu < 0 || menu > 5) {
                cout << "Помилка: введіть дійсне значення." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
            else {
                break;
            }
        }

        // Виклик функцій залежно від вибору
        switch (menu) {
        case 1:
            cout << endl;
            Menu_1(image, rows, cols);
            break;
        case 2:
            cout << endl;
            Menu_2(image, rows, cols);
            break;
        case 3:
            cout << endl;
            Menu_3(image, rows, cols);
            break;
        case 4:
            cout << endl;
            Menu_4(image, rows, cols);
            break;
        case 5:
            cout << endl;
            Menu_5(image, rows, cols);
            break;
        case 0:
            // Перед виходом обов'язково звільняємо пам'ять (запобігання витоку)
            for (int i = 0; i < rows; i++) {
                delete[] image[i];
            }
            delete[] image;
            image = nullptr;
            break;
        }

    } while (menu != 0);
    
    return 0;
}
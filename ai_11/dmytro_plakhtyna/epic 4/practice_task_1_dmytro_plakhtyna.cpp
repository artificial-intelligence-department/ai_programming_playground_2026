/*Плахтина Дмитро
ШІ-11
простий редактор зображень у відтінках сірого.
Зображення задається прямокутною таблицею чисел від 0 до 9, де 0 це чорний піксель,
а 9 найсвітліший. Програма показує таку таблицю як малюнок із символів
і дозволяє застосовувати до неї перетворення.*/
#include <iostream>
using namespace std;   
const char PALETTE[] = " .:-=+*#%@";

void printNumbers(int **img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}
// Показ зображення
void showImage(int **img, int rows, int cols) {
cout << "Зображення " << rows << " x " << cols << ":" << endl;
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        cout << img[i][j] << " ";
    }
    cout << endl;
}
cout << endl;
cout << "Малюнок: " << endl;
for (int i = 0; i < rows; i ++) {
    for (int j = 0; j < cols; j++) {
        cout << PALETTE[img[i][j]];
    }
    cout << endl;
}
cout << "Розміри: " << rows << " x " << cols << endl;
}
// Показ менб
void showMenu() {
    cout << "1 - Показати зображення" << endl;
    cout << "2 - Статистика яскравості" << endl;
    cout << "3 - Інвертувати яскравість" << endl;
    cout << "4 - Віддзеркалити по горизонталі" << endl;
    cout << "5 - Повернути на 90 градусів праворуч" << endl;
    cout << "0 - Вийти" << endl;
    cout << "Ваш вибір: ";
}
//Інверсія
void invertImage (int **img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j ++) {
            img[i][j] = 9 - img[i][j];
        }
    }
}
//Обмін двох чисел
void swapPixels(int *a, int *b) {
    int t;
    t = *a;
    *a = *b;
    *b = t;
}
//Дзеркало
void mirrorImage (int **img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for(int j = 0; j < cols/2; j ++){
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }

}
//Мінімальне і максимальне значення
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
minRow = 0, minCol = 0, maxRow = 0, maxCol = 0;
 for (int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j ++){
            if (img[i][j] < img[minRow][minCol]) {
                minRow = i;
                minCol = j;
            }
            if (img[i][j] > img[maxRow][maxCol]) {
                maxRow = i;
                maxCol = j;
            }
        }
    }
}
// Статистика
void showStats(int **img, int rows, int cols) {
    int minRow = 0, minCol = 0, maxRow = 0, maxCol = 0;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);
    cout << "Найтемніший піксель: " << img[minRow][minCol] << " (рядок "  << minRow + 1 << ", " << "стовпець " << minCol + 1 << ")" <<  endl;
    cout << "Найсвітліший піксель: " << img[maxRow][maxCol] << " (рядок "  << maxRow + 1 << ", " <<"стовпець " << maxCol + 1 << ")" << endl;
    int total = 0;
    for (int i = 0; i < rows; i++) {
    int *row = img[i];
    for (int j = 0; j < cols; j++) {
        total = total + *(row + j);
    }
}
    cout.precision(2);
    cout << "Середня яскравість: " << (double)total / ((double)cols * (double)rows) << endl;
    double rowSum = 0.0;
    cout.precision(1);
    cout << "Середня по рядках:";
    for (int i = 0; i < rows; i++) {
    int *row = img[i];
    rowSum = 0.0;
    for (int j = 0; j < cols; j++) {
        rowSum = rowSum + *(row + j);   
    }
    cout << " " << rowSum / cols;
}
cout << endl;
}
// Поворот
int** rotateRight(int **img, int rows, int cols) {
int **result = new int*[cols];
for (int i = 0; i < cols; i++) {
    result[i] = new int[rows];
}
for (int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j ++){
               result[j][rows - 1 - i] = img[i][j];
        }
    }
  for (int i = 0; i < rows; i++) {
    delete[] img[i];
    }
    delete[] img;
    img = nullptr;
return result;
}
int main() {
    cout.setf(ios::fixed);
    cout.precision(2);  
    //Введення розмірів та яскравості, перевірка на правильність
int rows, cols;
cout << "Введіть висоту зображення: ";
cin >> rows;
if (cin.fail() || rows < 1 || rows > 20) {
    cout << "Помилка! Значення має бути від 1 до 20" << endl;
    return 1;
}
cout << "Введіть ширину зображення: ";
cin >> cols;
if (cin.fail() || cols < 1 || cols > 20){
    cout << "Помилка! Значення має бути від 1 до 20" << endl;
    return 1;
}
int **img = new int*[rows];
for (int i = 0; i < rows; i++) {
    img[i] = new int[cols];
}
cout << "Яскравість пікселів (від 0 до 9): " << endl;
for (int i = 0; i < rows; i ++) {
    for (int j = 0; j < cols; j++) {
        cin >> img[i][j];
        if (cin.fail() || img[i][j] < 0 || img[i][j] > 9) {
            cout << "Помилка! Значення має бути від 0 до 9"<< endl;
            for (int k = 0; k < rows; k++) {
                delete[] img[k];
                }
                delete[] img;
                img = nullptr;
            return 1;
        }
    }
}
//Показ меню та виконання його функцій
int choice;
do {
    showMenu();
    cin >> choice;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка: введіть номер пункту цифрою." << endl;
        choice = -1;
        continue;
    }
    switch (choice) {
        case 1:
        showImage(img, rows, cols);
        break;
        case 2:
        showStats(img, rows, cols);
        break;
        case 0: cout << "Вихід" << endl;
        break;
        case 3: 
        cout << "Яскравість інвертовано." << endl;
        cout << "Початкове:" << endl;
        printNumbers(img, rows, cols);
        invertImage(img, rows, cols);
        cout << endl;
        cout << "Результат:" << endl;
        printNumbers(img, rows, cols);
        break;
        case 4: 
        cout << "Зображення віддзеркалено." << endl;
        cout << "Початкове:" << endl;
        printNumbers(img, rows, cols);
        mirrorImage(img, rows, cols);
        cout << endl;
        cout << "Результат:" << endl;
        printNumbers(img, rows, cols);
        break;
        case 5: {
        img = rotateRight(img, rows, cols);
        int t = rows;
        rows = cols;
        cols = t;
        cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
        printNumbers(img, rows, cols);
        break; }
        default:
        cout << "Немає такого пункту." << endl;
    }
} while (choice != 0);
//Очищаєм
for (int i = 0; i < rows; i++) {
    delete[] img[i];
    }
    delete[] img;
    img = nullptr;
    return 0;
}
/*
Редактор монохромного зображення
    Челяда Андрій, ШІ - 13
*/

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int** createImage(int rows, int cols); // виділяє памʼять під зображення rows x cols
void deleteImage(int** &img, int rows); // звільняє памʼять і обнуляє вказівник
void printNumbers(int** img, int rows, int cols); // допоміжна: виводить зображення таблицею чисел
void showImage(int** img, int rows, int cols); // пункт 1: числа, малюнок символами і розміри
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol); // знаходить координати найтемнішого і найсвітлішого пікселів, повертає через посилання
void showStats(int** img, int rows, int cols); // пункт 2: екстремуми, середня яскравість і середні по рядках
void invertImage(int** img, int rows, int cols); // пункт 3: замінює кожен піксель на 9 - x
void swapPixels(int *a, int *b); // міняє місцями два пікселі за їхніми адресами
void mirrorImage(int** img, int rows, int cols); // пункт 4: віддзеркалює зображення по горизонталі
int** rotateRight(int** img, int rows, int cols); // створює повернутий на 90° масив, звільняє старий, повертає новий
void rotateImage(int** &img, int &rows, int &cols); // пункт 5: поворот, обмін rows і cols, вивід результату

int main(){
    // Введення розмірів: при неправильному значенні програма завершується (код 1 = помилка)
    int rows, cols;
    cout << "Висота зображення (1..20): ";
    cin >> rows;
    if (cin.fail() || rows < 1 || rows > 20) {
        cout << "Помилка: висота має бути цілим числом від 1 до 20." << endl;
        return 1;
    }

    cout << "Ширина зображення (1..20): ";
    cin >> cols;
    if (cin.fail() || cols < 1 || cols > 20) {
        cout << "Помилка: ширина має бути цілим числом від 1 до 20." << endl;
        return 1;
    }

    // Виділення динамічної памʼяті під зображення і введення пікселів
    int** img = createImage(rows, cols);
    cout << "Яскравість пікселів (0..9):" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> img[i][j];
            if (cin.fail() || img[i][j] < 0 || img[i][j] > 9) {
                cout << "Помилка: яскравість має бути цілим числом від 0 до 9." << endl;
                deleteImage(img, rows); // памʼять уже виділена, тому звільняємо її перед виходом
                return 1;
            }
        }
    }

    // Меню повторюється, доки користувач не вибере 0
    int choice;
    do{
        cout << "------Меню-------" << endl;
        cout << "1) Показати зображення" << endl;
        cout << "2) Статистика яскравості" << endl;
        cout << "3) Інвертувати яскравість" << endl;
        cout << "4) Віддзеркалити по горизонталі" << endl;
        cout << "5) Повернути на 90 градусів праворуч" << endl;
        cout << "0) Вийти" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        // Нечислове введення або неіснуючий пункт: чистимо потік і показуємо меню знову
        if(choice < 0 || choice > 5 || cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Немає такого варіанту меню!!" << endl;
            choice = -1; // щоб цикл не завершився, якщо після помилки choice став 0
            continue;
        }
        switch (choice){
            case 1:
                showImage(img, rows, cols);
                break;

            case 2:
                showStats(img, rows, cols);
                break;

            case 3:
                invertImage(img, rows, cols);
                break;

            case 4:
                mirrorImage(img, rows, cols);
                break;

            case 5:
                rotateImage(img, rows, cols);
                break;

            case 0:
                cout << "Вихід з програми." << endl;
                break;

            default:
                cout << "Немає такого пункту меню" << endl;
                break;

        }
    }
    while (choice != 0);

    // Звільнення памʼяті перед завершенням програми
    deleteImage(img, rows);
    return 0;
}

int** createImage(int rows, int cols){
    int** image = new int* [rows]; // масив вказівників на рядки
    for(int i = 0; i < rows; i++){
        image[i] = new int [cols]; // кожен рядок окремо
    }
    return image;
}

void deleteImage(int** &img, int rows){
    for(int i = 0; i < rows; i++){
        delete[] img[i]; // спершу кожен рядок
        img[i] = nullptr; // обнуляємо вказівник на рядок
    }
    delete[] img; // потім масив вказівників
    img = nullptr; // вказівник більше ні на що не вказує
}

void printNumbers(int** img, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

void showImage(int** img, int rows, int cols){
    printNumbers(img, rows, cols);
    cout << "Малюнок: " << endl;
    string palette = " .:-=+*#%@"; // позиція символу відповідає яскравості 0..9
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << palette[img[i][j]];
        }
        cout << endl;
    }
    cout << "Розміри: " << rows << " x " << cols << endl;
}

void invertImage(int** img, int rows, int cols){
    // Перетворення на місці, без виділення нової памʼяті
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            img[i][j] = 9 - img[i][j];
        }
    }
    cout << "Яскравість інвертовано." << endl;
    printNumbers(img, rows, cols);
}

void swapPixels(int* a, int* b){
    // Обмін значень через розіменування адрес
    int temp = *a;
    *a = *b;
    *b = temp;
}

void mirrorImage(int** img, int rows, int cols){
    cout << "Зображення віддзеркалено." << endl;
    cout << "Початкове:" << endl;
    printNumbers(img, rows, cols);
    for(int i = 0; i < rows; i++){
        // Лише до середини, інакше кожна пара обміняється двічі
        for (int j = 0; j < cols / 2; j++){
            swapPixels( &img[i][j], &img[i][cols - 1 - j]);
        }
    }
    cout << "Результат: " << endl;
    printNumbers(img, rows, cols);
}

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
    // Стартуємо з першого пікселя [0][0]
    minRow = 0;
    maxRow = 0;
    minCol = 0;
    maxCol = 0;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            // Строгі < і > : при однакових значеннях лишається перше в порядку обходу
            if(img[i][j] < img[minRow][minCol]){
                minRow = i;
                minCol = j;
            }
            if(img[i][j] > img[maxRow][maxCol]){
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void showStats(int** img, int rows, int cols){
    int minRow, maxRow, minCol, maxCol;
    double sum = 0;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);
    // Координати в масиві з 0, користувачу показуємо з 1
    cout << "Найтемніший піксель: " << img[minRow][minCol] << " (рядок "<< minRow + 1 << ", " << "стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << img[maxRow][maxCol] << " (рядок "<< maxRow + 1 << ", " << "стовпець " << maxCol + 1 << ")" << endl;

    // Загальна середня яскравість, обхід рядка через вказівник
    for(int i = 0; i < rows; i++){
        int* row = img[i];
        for(int j = 0; j < cols; j++){
            int pixel = *(row + j);
            sum += pixel;
        }
    }
    double average = sum / (rows * cols);
    cout << fixed << setprecision(2) <<  "Середня яскравість: " << average << endl;

    // Середня яскравість кожного рядка окремо
    cout << "Середня по рядках: ";
    for(int i = 0; i < rows; i++){
        double rowSum = 0;
        int* row = img[i];
        for(int j = 0; j < cols; j++){
            int pixel = *(row + j);
            rowSum += pixel;
        }
        cout << fixed << setprecision(1) << rowSum / cols << " ";
    }
    cout << endl;
}

int** rotateRight(int** img, int rows, int cols){
    int** rotated = createImage(cols, rows); // розміри міняються місцями
    // Перший рядок старого зображення стає останнім стовпцем нового
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            rotated[j][rows - i - 1] = img[i][j];
        }
    }
    deleteImage(img, rows); // старий масив звільняємо лише після перенесення пікселів
    return rotated;
}

void rotateImage(int** &img, int &rows, int &cols){
    img = rotateRight(img, rows, cols);
    // Після повороту висота і ширина міняються місцями
    int temp = rows;
    rows = cols;
    cols = temp;
    cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
    printNumbers(img, rows, cols);
}
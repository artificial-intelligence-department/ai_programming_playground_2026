#include <iostream>

using namespace std;

bool readInt(int &x){ // зчитуємо ціле число, false якщо ввід нечисловий

    cin >> x;

    if (cin.fail()){ // замість числа ввели символи
        cin.clear();
        cin.ignore(1000000, '\n');
        return false;
    }

    return true;
}

int** createImage(int rows, int cols){ // виділяємо пам'ять під зображення

    int** img = new int*[rows]; // масив рядків
    for (int i = 0; i < rows; i++){
        img[i] = new int[cols];
    }

    return img;
}

void freeImage(int**& img, int rows){ // звільняємо пам'ять: спершу рядки, потім масив вказівників, щоб не було витоку

    for (int i = 0; i < rows; i++){
        delete[] img[i];
        img[i] = nullptr;
    }

    delete[] img;
    img = nullptr;
}

bool readImage(int** img, int rows, int cols){ // зчитуємо пікселі, false якщо значення некоректне

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (!readInt(img[i][j]) || img[i][j] < 0 || img[i][j] > 9){
                return false;
            }
        }
    }

    return true;
}

void printTable(int** img, int rows, int cols){ // друк таблиці чисел 

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (j > 0) { cout << " ";}
            cout << img[i][j];
        }
        cout << endl;
    }
}

void showImage(int** img, int rows, int cols){ // показати зображення

    const char* p = " .:-=+*#%@"; // палітра, позиція символу = яскравість

    cout << "Зображення " << rows << " x " << cols << ":" << endl;
    printTable(img, rows, cols);

    cout << "Малюнок:" << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << p[img[i][j]]; // символ за яскравістю
        }
        cout << endl;
    }

    cout << "Розміри: " << rows << " x " << cols << endl;
}

void findExtremes(int** img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){ // координати найтемнішого і найсвітлішого

    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;

    int mn = *(img[0]); // поточний мінімум
    int mx = *(img[0]); // поточний максимум

    for (int i = 0; i < rows; i++){
        int *row = img[i]; // вказівник на рядок
        for (int j = 0; j < cols; j++){
            if (*(row + j) < mn){ // строго менше, тому лишається перший у порядку обходу
                mn = *(row + j);
                minRow = i;
                minCol = j;
            }
            if (*(row + j) > mx){ // строго більше, тому лишається перший у порядку обходу
                mx = *(row + j);
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void showStats(int** img, int rows, int cols){ // статистика яскравості

    int minRow,minCol,maxRow,maxCol;

    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

    cout << "Найтемніший піксель: " << *(*(img + minRow) + minCol) << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << *(*(img + maxRow) + maxCol) << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;

    int total = 0; // сума яскравості всього зображення
    double* avg = new double[rows]; // середні по рядках

    for (int i = 0; i < rows; i++){
        int *row = img[i]; // вказівник на рядок
        int s = 0; // сума рядка
        for (int j = 0; j < cols; j++){
            s += *(row + j);
        }
        total += s;
        avg[i] = (double)s / cols;
    }

    cout << "Середня яскравість: " << (double)total / (rows * cols) << endl;

    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++){
        if (i > 0) { cout << " ";}
        cout << avg[i];
    }
    cout << endl;

    delete[] avg; // звільняємо допоміжний масив
    avg = nullptr;
}

void invertImage(int** img, int rows, int cols){ // інверсія на місці

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            img[i][j] = 9 - img[i][j]; // темне стає світлим
        }
    }

    cout << "Яскравість інвертовано." << endl;
    printTable(img, rows, cols);
}

void swapPixels(int *a, int *b){ // обмін двох пікселів за адресами для віддзеркалення

    int t = *a;
    *a = *b;
    *b = t;
}

void mirrorImage(int** img, int rows, int cols){ // віддзеркалення по горизонталі 
    
    cout << "Зображення віддзеркалено." << endl;
    cout << "Початкове:" << endl;
    printTable(img, rows, cols);

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols / 2; j++){ // лише до середини
            swapPixels(&img[i][j], &img[i][cols - 1 - j]); // стовпець j міняємо з дзеркальним
        }
    }

    cout << "Результат:" << endl;
    printTable(img, rows, cols);
}

int** rotateRight(int** img, int rows, int cols){ // повертає новий масив cols*rows , при повороті на право

    int** res = createImage(cols, rows); // новий масив з іншими розмірами

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            res[j][rows - 1 - i] = img[i][j]; // перший рядок стає останнім стовпцем
        }
    }

    freeImage(img, rows); // старий масив звільняємо лише після перенесення

    return res;
}

void rotateImage(int**& img, int& rows, int& cols){ // поворот на 90 градусів праворуч

    img = rotateRight(img, rows, cols);

    int t = rows; // висота і ширина міняються місцями
    rows = cols;
    cols = t;

    cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
    printTable(img, rows, cols);
}

int main(){

    int rows,cols; // розміри зображення

    cout << "Висота зображення: ";
    if (!readInt(rows) || rows < 1 || rows > 20){
        cout << "Помилка: висота має бути цілим числом від 1 до 20" << endl;
        return 0;
    }

    cout << "Ширина зображення: ";
    if (!readInt(cols) || cols < 1 || cols > 20){
        cout << "Помилка: ширина має бути цілим числом від 1 до 20" << endl;
        return 0;
    }

    int** img = createImage(rows, cols); // зображення в динамічній пам'яті

    cout << "Яскравість пікселів (0..9):" << endl;
    if (!readImage(img, rows, cols)){
        cout << "Помилка: яскравість має бути цілим числом від 0 до 9" << endl;
        freeImage(img, rows); // звільняємо пам'ять перед виходом
        return 0;
    }

    int c; // пункт меню

    do{
        cout << endl;
        cout << "1 - показати зображення" << endl;
        cout << "2 - статистика яскравості" << endl;
        cout << "3 - інвертувати яскравість" << endl;
        cout << "4 - віддзеркалити по горизонталі" << endl;
        cout << "5 - повернути на 90 градусів праворуч" << endl;
        cout << "0 - вийти" << endl;
        cout << "Ваш вибір: ";

        if (!readInt(c)){ // нечисловий ввід
            cout << "Помилка: введіть число від 0 до 5" << endl;
            c = -1;
        }
        else if (c == 1){
            showImage(img, rows, cols);
        }
        else if (c == 2){
            showStats(img, rows, cols);
        }
        else if (c == 3){
            invertImage(img, rows, cols);
        }
        else if (c == 4){
            mirrorImage(img, rows, cols);
        }
        else if (c == 5){
            rotateImage(img, rows, cols);
        }
        else if (c != 0){ // число поза меню
            cout << "Помилка: такого пункту немає" << endl;
        }
    } while (c != 0);

    freeImage(img, rows); // звільняємо пам'ять перед виходом

return 0;
}
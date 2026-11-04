#include <iostream>
#include <iomanip>
using namespace std;

const char PALETTE[10] = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};

// очищення буфера після помилки
void clearinput(){
    cin.clear();
    while (cin.get() != '\n'); //ігноруємо все до кінця рядка
}

//звільнення динамічної пам'яті та обнулення вказівника
void freeimage(int**& img, int rows){
    if (img != nullptr){
        //cпочатку видаляємо кожен окремий рядок
        for (int i = 0; i < rows; i++){
            delete[] img[i];
        }
        //видаляємо головний масив вказівників
        delete[] img;
        img = nullptr;
    }
}

// виділення динамічної пам'яті під зображення
int** allocateimage(int rows, int cols){
    int** img = new int*[rows];
    //для кожного рядка виділяємо пам'ять
    for (int i = 0; i < rows; i++){
        img[i] = new int[cols];
    }
    return img; // повертаємо адресу головного масиву

}
//1. показати зображення
void showimage(int** img, int rows, int cols){
    //табличний вивід 0-9
    cout << endl << "Зображення " << rows << "x" << cols << endl;
    for (int i = 0; i < rows; i++){
        for( int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
    //графічний
    cout << "Малюнок:" << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << PALETTE[img[i][j]];
        }
        cout << endl;
    }
    cout << "Поточні розміри:" << rows << "x" << cols << endl;
}

//пошук найтемнішого і найсвітлішого
void findextrimes(int** img, int rows, int cols, int &minrow, int &mincol, int &maxrow, int &maxcol){
    // ввважаєм що перша комірка найбільша і найменша
    minrow = 0; mincol = 0;
    maxrow = 0; maxcol = 0;

    for(int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if(img[i][j] < img[minrow][mincol]){
                minrow = i;
                mincol = j;
            }
            if (img[i][j] > img[maxrow][maxcol]){
                maxrow = i;
                maxcol = j;
            }
        }
    }
}

void printstatistics(int** img, int rows, int cols){
    int minrow, mincol, maxrow, maxcol;
        findextrimes(img, rows, cols, minrow, mincol, maxrow, maxcol);

    cout << "\nНайтемніший піксель: " << img[minrow][mincol]
         << " (рядок " << (minrow + 1) << ", стовпець " << (mincol + 1) << ")\n";
        cout << "Найсвітліший піксель: " << img[maxrow][maxcol]
         << " (рядок " << (maxrow + 1) << ", стовпець " << (maxcol + 1) << ")\n";
    

    double totalsum = 0;
    //рахуєм заг cуму кількість пікселів
    for(int i = 0; i < rows; i++){
        int* row = img[i]; //вказівник на почтаок поточного рядка
        for(int j = 0; j < cols; j++){
            totalsum += *(row + j);
        }
    }

    //середня ясккравість
    double totalavg = totalsum / (rows * cols);
    cout << fixed << setprecision(2) << "Середня яскравість: " << totalavg << endl;

    //середня яскравість для кожного рядка
    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++){
        int* row = img[i]; //переставляєм вказівник на поточний рядок
        double rowsum = 0; 
        for(int j = 0; j < cols; j++){
            rowsum += *(row + j);
        }
        cout << fixed << setprecision(2) << (rowsum / cols) << " ";
    }
    cout << endl;
}

//інвертуввання яскравості
void invertbrightness(int** img, int rows, int cols){
    for( int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            img[i][j] = 9 - img[i][j];
        }
    }
    cout << "\nЯскравість інвертовано.\n";
}

// перестановка ел за адресою
void swapPixels(int* a, int* b) {
    int temp = *a; 
    *a = *b;       
    *b = temp;    
}
//віддзеркалення по горизонталі
void fliphorizontal(int** img, int rows, int cols){
    for (int i = 0; i < rows; i++) {
        // цикл йде до середини рядка, інакше пікселі повернуться назад
        for (int j = 0; j < cols / 2; j++) {
            // передаємо адреси лівого пікселя та протилежного правого
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }
    cout << "\nЗображення віддзеркалено.\n";
}

// поворот на 90
int** rotateright(int** img, int rows, int cols) {
    // при повороті ширина стає висотою і тд
    int newrows = cols;
    int newcols = rows;
    //виідялєм память під новий масив
    int** newimg = allocateimage(newrows, newcols);
    //перенесення у новий масив
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            //перший рядок початкового зображення стає останнім стовпцем нового
            newimg[j][rows - 1 -i] = img[i][j];
        }
    }
    freeimage(img, rows);
    return newimg;
}

int main() {
    int rows, cols;

    cout << "Висота зображення (1..20): ";
    if (!(cin >> rows) || rows < 1 || rows > 20) {
        cout << "Помилка: Некоректне значення висоти!\n";
        return 1;
    }

    cout << "Ширина зображення (1..20): ";
    if (!(cin >> cols) || cols < 1 || cols > 20) {
        cout << "Помилка: Некоректне значення ширини!\n";
        return 1;
    }

    // виділення памяті під зображення 
    int **img = allocateimage(rows, cols);

    //зчитаування пікселів
    cout << "Яскравість пікселів (0..9):\n";
    for ( int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if(!(cin >> img[i][j]) || img[i][j] < 0 || img[i][j] > 9){
                cout << "Помилка! Піксель виходить за межі." << endl;
                freeimage(img, rows);
                return 1;
            }
        }
    }

    int choice;

    do {
        cout << "\n================ МЕНЮ ================\n"
             << "1. Показати зображення\n"
             << "2. Статистика яскравості\n"
             << "3. Інвертувати яскравість\n"
             << "4. Віддзеркалити по горизонталі\n"
             << "5. Повернути на 90 градусів праворуч\n"
             << "0. Вийти\n"
             << "Оберіть пункт: ";

        if (!(cin >> choice)){
            cout << "Помилка: Введіть числове значення!\n";
            clearinput();
            continue;
        }

        switch (choice) {
            case 1: showimage(img, rows, cols); break;
            case 2: printstatistics(img, rows, cols); break;
            case 3: invertbrightness(img, rows, cols); break;
            case 4: fliphorizontal(img, rows, cols); break;
            case 5: {
                img = rotateright(img, rows, cols);

                int temp = rows;
                rows = cols;
                cols = temp;
                cout << "\nЗображення повернуто. Нові розміри: " << rows << " x " << cols << "\n";
                break;
            }
            case 0:
                cout << "\nЗавершення роботи...\n";
                break;
            default:
                cout << "Невідомий пункт меню! Спробуйте ще раз.\n";
                break;
        }

    } while (choice !=0);
    // прибираєм память
    freeimage(img, rows);

    return 0;
}

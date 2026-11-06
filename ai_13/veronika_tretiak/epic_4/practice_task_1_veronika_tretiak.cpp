/*
Автор: Вероніка Третяк
Задача: Редактор монохромного зображення
Група: ШІ-13
*/
#include <iostream>
#include <iomanip>

using namespace std;
//Оголошення функцій
void Showimage(int** img, int rows, int cols);
int** createImage(int rows, int cols);
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
void showStatistic(int** img, int rows, int cols);
void invertBrightness(int** img, int rows, int cols);
void swapPixels(int *a, int *b);
void Reflection (int** img, int rows, int cols);
int** rotateRight(int** img, int rows, int cols);
void Delete(int** &img, int rows);
void rotateAndShow(int** &image, int &rows, int& cols);

int main(){
    //Оголошуємо змінні для висоти, ширини матриці та вибору пункта меню
    int rows, cols, choice;
    //Ввід ширини та висоти зображення + валідація
    cout << "Введіть висоту зображення у пікселях: " << endl;
    cin >> rows;
    if (cin.fail()) {
        cout << "Помилка: Введіть число." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return 1;
    }
    if(rows < 1 || rows > 20){
        cout << "Помилка: Введіть число від 1 до 20." << endl;
        return 1;
    }
    cout << "Введіть ширину зображення у пікселях: " << endl;
    cin >> cols;
    if(cin.fail()){
        cout << "Помилка: Введіть число." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return 1;
    }
    if(cols < 1 || cols > 20){
        cout << "Помилка: Введіть число від 1 до 20." << endl;
        return 1;
    }
     //Створюю динамічну матрицю та зберігаю її адресу
     int** image = createImage(rows, cols);

     cout << "Введіть яскравість зображення(0..9): " << endl;
     for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cin >> image[i][j];
     if(cin.fail()){ 
        cout << "Помилка: Введіть число." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        Delete(image, rows);
        return 1;
    }
    //Перевірка чи допустима яскравість  пікселів
    if(image[i][j] < 0 || image[i][j] > 9){
        cout << "Помилка: Введіть число від 0 до 9." << endl;
        Delete(image, rows);
        return 1;
    }
}
}

//Виконуємо показ меню щонайменше один раз
     do{ menu:
        cout << "1 - Показати зображення" << endl;
        cout << "2 - Статистика яскравості" << endl;
        cout << "3 - Інвертувати яскравість" << endl;
        cout << "4 - Віддзеркалити по горизонталі" << endl;
        cout << "5 - Повернути на 90 градусів праворуч" << endl;
        cout << "0 - Вийти" << endl;
        cin >> choice;
        //Перевірка вводу меню
        if(cin.fail()){
            cout << "Помилка: Введіть число." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            goto menu;
        }
        if(choice < 0 || choice > 5){
            cout << "Помилка: Введіть пункт з меню." << endl;
            goto menu;
        }
        if(cin.peek() == ',' || cin.peek() == '.'){
            cout << "Помилка: Введіть ціле число від 0 до 5." << endl;
            cin.ignore(100000, '\n');
            goto menu;
        }
        //Виконуємо операцію до відповідного пункту меню
        switch(choice){
            case 1:{
            Showimage(image, rows, cols);
            break;
            }
            case 2:{
            showStatistic(image, rows, cols);
            break;
            }
            case 3: {
            invertBrightness( image , rows, cols);
            break;
            }
            case 4:{
            Reflection (image, rows, cols);
            break;
            }
            case 5: {
            rotateAndShow(image, rows, cols);
            break;
            }
            case 0: {
                break;
            }

        }


     }
     while(choice != 0);
     //Звільнимо зображення за його поточною кількістю рядків
   Delete(image, rows);
   return 0;
}
//Функція для виведення зображення числами та символами палітри
void Showimage(int** img, int rows, int cols){
    const char palette[] = " .:-=+*#%@";
    cout << "Зображення розміру " << rows << "x" << cols << " :" << endl;
    for(int i = 0; i < rows; i++){
     for(int j = 0; j < cols; j++){
        cout << img[i][j] << " ";
     }
     cout << "\n";
    }
    cout << "Малюнок символами палітри: " << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << palette[img[i][j]];
        }
        cout << endl;
    }
}
//Функція виділяє динамічну памʼять для двовимірного масиву
int** createImage(int rows, int cols){
    int** img = new int*[rows];
    for(int i = 0; i < rows; i++){
        img[i] = new int[cols];
    }
            return img;
}
//Функція знаходить найсвітліший та найтемніший пікселі
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
 minRow = 0;
 minCol = 0;
 maxRow = 0;
 maxCol = 0;

 int min = *img[0];
 int max = *img[0];
 for(int i = 0; i < rows; i++){
    int* row = img[i];
    for(int j = 0; j < cols; j++){
        int pixel = *(row + j);

        if(pixel < min){
            min = pixel;
            minRow = i;
            minCol = j;
        }

        if(pixel > max){
            max = pixel;
            maxRow = i;
            maxCol = j;
        }
    }
 }
}
//Функція для виведення мінімуму, максимуму та середньої яскравості зображення
void showStatistic(int** img, int rows, int cols){
    int minRow, minCol, maxRow, maxCol;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);
    cout << "Найтемніший піксель: " << *(img[minRow] + minCol) << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << *(img[maxRow] + maxCol) << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;
    int totalSum = 0;
    for(int i = 0; i < rows; i++){
        int* row = img[i];
        for(int j = 0; j < cols; j++){
            totalSum += *(row + j);
        }
    }
    double average = (double)totalSum / (rows * cols);
    cout << "Середня яскравість: " << fixed << setprecision(2) << average << endl;
    cout << "Середня по рядах: ";
    for(int i = 0; i < rows; i++){
        int* row = img[i];
        int rowSum = 0;
        for(int j = 0; j < cols; j++){
            rowSum += *(row + j);
        }
        double rowaverage = (double)rowSum / cols;
        cout << fixed << setprecision(1) << rowaverage << " ";
    }
  cout << endl;
}
//Функція заміняє яскравість кожного пікселя на протилежний
void invertBrightness(int** img, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            img[i][j] = 9 - img[i][j];
        }
    }
    cout << "Яскравість інвертовано." << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;;
    }
}
//Функція обмінює значення двох пікселів через вказівники
void swapPixels(int *a, int *b){
 int tmp;
 tmp = *a;
 *a = *b;
 *b = tmp;
}
//Функція змінює місцями ліві та праві елементи кожного рядка
void Reflection (int** img, int rows, int cols){
    cout << "Зображення віддзеркалено." << endl;
    cout << "Початкове: " << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    } 
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < (cols/2); j++){
            swapPixels( &img[i][j] , &img[i][cols - 1 - j]);
        }
    }
    cout << "Результат:" << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }

}
//Функція створює зображення, повернуте на 90 градусів праворуч та звільняє старе
int** rotateRight(int** img, int rows, int cols){
int** picture = new int*[cols];
for(int i = 0; i < cols; i++){
    picture[i] = new int [rows];
}
for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
    picture[j][rows - 1 - i] = img[i][j];
    }
}
for(int i = 0; i < rows; i++){
    delete[] img[i];
    img[i] = nullptr;
}
delete[] img;
img = nullptr;
return picture;
}
//Функція звільняє рядки, масив вказівників та обнуляє головний вказівник
void Delete(int** &img, int rows){
    for(int i = 0; i < rows; i++){
        delete[] img[i];
        img[i] = nullptr;
    }
    delete[] img;
    img = nullptr;
}
//Функція для повернення зображення на 90 градусів
void rotateAndShow(int** &image, int &rows, int& cols){
image = rotateRight(image, rows, cols);
            int tmp;
            tmp = rows;
            rows = cols;
            cols = tmp;
            cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
            Showimage(image, rows, cols);
}
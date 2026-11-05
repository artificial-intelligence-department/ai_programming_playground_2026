/*
 * Задача: Редактор монохромного зображення
 * Автор: Морикишка Данило
 * Група: ШІ-11
*/
#include <iostream>
#include <iomanip>
using namespace std;
//Оголошую функції перед їхім використанням:
void ShowMenu();
void ShowImage(int** image, int heigth, int width);
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
void showStats(int **img, int rows, int cols);
void doInvertImage(int **img, int rows, int cols);
void swapPixels(int *a, int *b);
void doMirrorImage(int **img, int rows, int cols);
int** rotateRight(int** img, int rows, int cols);
// Ініціалізовую константи для подальшої валідації:
const int MIN_HEIGHT_VALUE = 1;
const int MAX_HEIGHT_VALUE = 20;
const int MIN_WIDTH_VALUE = 1;
const int MAX_WIDTH_VALUE = 20;
const int MIN_PIXEL_VOLUME = 0;
const int MAX_PIXEL_VOLUME = 9;
const int COUNT_OF_PIXEL_TYPE = 10;
const char TYPE_OF_PIXELS[COUNT_OF_PIXEL_TYPE] = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};
int main()
{
    //Реалізовую процес валідації через умовні оператори, в разі помилки використовую оператор goto:
    tryagainHeight:
    cout << "Висота зображення: ";
    int height;
    if(!(cin >> height) || height < MIN_HEIGHT_VALUE || height > MAX_HEIGHT_VALUE)
    {
        cout << "Помилка!Спробуйте ще раз." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto tryagainHeight;
    }
    tryagainWidth:
    cout << "Ширина зображення: ";
    int width;
    if(!(cin >> width) || width < MIN_WIDTH_VALUE || width > MAX_WIDTH_VALUE)
    {
        cout << "Помилка!Спробуйте ще раз." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto tryagainWidth;
    }
    int** image = new int*[height];
    for (int i = 0; i < height; i++)
    {
        image[i] = new int[width];
    }
    tryagainPixels:
    cout << "Яскравість пікселів (0..9):" << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if(!(cin >> image[i][j]) || image[i][j] < MIN_PIXEL_VOLUME || image[i][j] > MAX_PIXEL_VOLUME){
                cout << "Помилка!Масив містить елементи в рядку " << i <<" , неприпустимі для умови завдання.Спробуйте ще раз." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                goto tryagainPixels;
            }
        }
    }
    cout << endl;
    bool isWorking = true;
    int choice;
    // Використовую цикл do while для повтору виведення меню і можливості вибору користувачем певних опцій:
    do
    {
      ShowMenu();
    tryAgainChoice:
      cout << "Ваш вибір: ";
      if(!(cin >> choice)){
        cout << "Помилка!Некоректне значення вводу.Спробуйте ще раз.";
        cin.clear();
        cin.ignore(10000, '\n');
        goto tryAgainChoice;
      }
      switch (choice)
      {
      case 1:
        ShowImage(image, height, width);
        break;
      case 2:
       showStats(image, height, width);
       break;
      case 3:
        doInvertImage(image, height, width);
        break;
      case 4:
        doMirrorImage(image, height, width);
        break;
     case 5:
     {
         image = rotateRight(image, height, width);
         swapPixels(&height, &width);
        cout << "Зображення повернуто. Нові розміри: " << height << " x " << width << endl;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                cout << image[i][j] << " ";
            }
            cout << endl;
        }
        break;
     }
      case 0:
      cout << "Вихід з програми." << endl;
      isWorking = false;
      break;   
      default:
        cout << "Такої опції немає.Спробуйте ще раз." << endl;
        goto tryAgainChoice;
        break;
      }
    } while (isWorking);
    for (int i = 0; i < height; i++)
    {
        delete[] image[i];
        image[i] = nullptr;
    }
    // Через оператор delete звільнюю пам'ять та зануляю вказівник:
    delete[] image;
    image = nullptr;
}
// Реалізовую функцію показу головного меню:
void ShowMenu()
{
    cout << "1.     Показати зображення\n"
    "2.     Статистика яскравості\n"
    "3.     Інвертувати яскравість\n"
    "4.     Віддзеркалити по горизонталі\n"
    "5.     Повернути на 90 градусів праворуч\n"
    "0.     Вийти\n";
}
// Реалізовую функцію для показу зображення та його розміру відповідно:
void ShowImage(int** image, int heigth, int width)
{
    cout << "Зображення " << heigth << " x " << width << ":" << endl;
    for (int i = 0; i < heigth; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\n" << "Малюнок: \n";
    for (int i = 0; i < heigth; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << TYPE_OF_PIXELS[image[i][j]];
        }
        cout << endl;
    }
    cout << endl;  
}
// Реалізовую функцію для пошуку найтемнішого та найсвітлішого пікселів:
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol)
{
   int minValue = img[0][0];
   int maxValue = img[0][0];
    for (int i = 0; i < rows; i++)
    {
        int *row = img[i];
        for (int j = 0; j < cols; j++)
        {
            if(*(row + j) < minValue){
                minValue = *(row + j);
                minRow = i;
                minCol = j;
            }
            if(*(row + j)  > maxValue){
                maxValue = *(row + j);
                maxRow = i;
                maxCol = j;
            }
        }
    }
    cout << "Найтемніший піксель: " << minValue << " (рядок " << minRow + 1 << ", стовпець "<< minCol + 1<<")" << endl;
    cout << "Найсвітліший піксель: " << maxValue << " (рядок " << maxRow + 1 << ", стовпець "<< maxCol + 1<<")" << endl;
}
// Реалізовую функцію для показу статистики зображення:
void showStats(int **img, int rows, int cols)
{
   int minRow = 0;
   int minCol = 0;
   int maxRow = 0;
   int maxCol = 0;
   findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);
    int sumOfArr = 0;
    for (int i = 0; i < rows; i++)
    {
        int *ptr = img[i];
        for (int j = 0; j < cols; j++)
        {
            sumOfArr += *(ptr + j);
        }
    }
    double average = sumOfArr/(double)(rows * cols);
    cout << "Середня яскравість: " << setprecision(2) << fixed << average << endl;
    cout << "Середня по рядках: ";
    int sumOfRow = 0;
    for (int i = 0; i < rows; i++)
    {
        int *ptr = img[i];
        for (int j = 0; j < cols; j++)
        {
            sumOfRow += *(ptr + j);
        }
        cout << setprecision(1) << fixed << sumOfRow/(double)cols << " ";
        sumOfRow = 0;
    }
    cout << endl;
}
// Реалізовую функцію для інвертування зображення:
void doInvertImage(int **img, int rows, int cols)
{
    cout << "\nЯскравість інвертовано." << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            img[i][j] =MAX_PIXEL_VOLUME - img[i][j];
        }
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
     cout << endl;
}
// Реалізовую функцію для зміни між собою пікселів місцями:
void swapPixels(int *a, int *b)
{
    // Ініціалізовую змінну temp для зберігання значення розіменованого вказівника:
    int temp = *a;
    *a = *b;
    *b = temp;  
}
// Реалізовую функцію для віддзеркалення зображення:
void doMirrorImage(int **img, int rows, int cols)
{
    cout << "Зображення віддзеркалено." << endl;
    cout << "Початкове: " << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Результат: " << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols/2; j++)
        {
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
// Реалізовую функцію для повороту зображення на 90 градусів:
int** rotateRight(int** img, int rows, int cols)
{
    int** updImage = new int*[cols];
    for (int i = 0; i < cols; i++)
    {
        updImage[i] = new int[rows];
    }
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            updImage[i][j] = img[rows - 1 -j][i];
        }
    } 
    for (int i = 0; i < rows; i++)
    {
         delete[] img[i];
    }
    // Через оператор delete звільнюю пам'ять та зануляю вказівник:
    delete[] img;
    // Повертаю оновлене зображення, помінявши місцями висоту та ширину:
    return updImage;
}
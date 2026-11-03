#include <iostream>
using namespace std;
void ShowMenu();
void ShowImage(int** image, int heigth, int width);
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
const int MIN_HEIGHT_VALUE = 0;
const int MAX_HEIGHT_VALUE = 100;
const int MIN_WIDTH_VALUE = 0;
const int MAX_WIDTH_VALUE = 100;
const int MIN_PIXEL_VOLUME = 0;
const int MAX_PIXEL_VOLUME = 9;
const int COUNT_OF_PIXEL_TYPE = 11;
const char TYPE_OF_PIXELS[COUNT_OF_PIXEL_TYPE] = {' ',' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};
int main()
{
    tryagainHeight:
    cout << "Висота зображення:";
    int height;
    if(!(cin >> height) || height < MIN_HEIGHT_VALUE || height > MAX_HEIGHT_VALUE)
    {
        cout << "Помилка!Спробуйте ще раз.";
        cin.clear();
        cin.ignore(10000, '\n');
        goto tryagainHeight;
    }
    tryagainWidth:
    cout << "Ширина зображення:";
    int width;
    if(!(cin >> width) || width < MIN_WIDTH_VALUE || width > MAX_WIDTH_VALUE)
    {
        cout << "Помилка!Спробуйте ще раз.";
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
    bool isWorking = true;
    int choice;
    do
    {
      ShowMenu();
    tryAgainChoice:
      cout << "Ваш вибір: ";
      cin >> choice;
      switch (choice)
      {
      case 1:
        ShowImage(image, height, width);
        break;
      case 0:
      cout << "Вихід з програми." << endl;
      isWorking = false;
      break;   
      default:
        cout << "Такої опції нмає.Спробуйте ще раз." << endl;

        break;
      }
    } while (isWorking);
}
void ShowMenu()
{
    cout << "1.     Показати зображення\n"
    "2.     Статистика яскравості\n"
    "3.     Інвертувати яскравість\n"
    "4.     Віддзеркалити по горизонталі\n"
    "5.     Повернути на 90 градусів праворуч\n"
    "0.     Вийти\n";
}
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
            cout << TYPE_OF_PIXELS[image[i][j]] << " ";
        }
        cout << endl;
    }
    cout << endl;  
}
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol)
{
    
}
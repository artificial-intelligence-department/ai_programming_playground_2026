/* Редактор монохромного зображення
   Конопка Марта ШІ - 13
*/

#include<iostream>
#include<iomanip>

using namespace std;

// Символьна палітра яскравості(від 0 до 9)
const char PALETTE[] = " .:-=+*#%@" ;

//Перевірка на неправильно введені значення
bool readInteger(int &value){
    cin >> value;
    if(cin.fail()){
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
    }
    return true;
}

// Вивід зображення у вигляді матриці та символьного малюнка
void showImage(int rows, int cols, int** image){
     cout << "Зображення " << rows << " x " << cols << endl;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
        cout << image[i][j] << " ";
        
        }
        cout << endl;
  }
  cout << "Малюнок: " << endl;
  for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
         cout << PALETTE[image[i][j]] ;
        }
        cout << endl;
    } 
}

//Пошук найсвітлішого і найтемнішого пікселів
void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
    int minVal = image[0][0];
    int maxVal = image[0][0];
    minRow = 1;
    minCol = 1;
    maxRow = 1;
    maxCol = 1;
     for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(image[i][j] < minVal){
                minVal = image[i][j] ; 
                minRow = i + 1;
                minCol = j + 1;
            }
            if (image[i][j] > maxVal){
                maxVal = image[i][j];
                maxRow = i + 1;
                maxCol = j + 1;

            }
      }
     } cout << "Найтемніший піксель: " << minVal << "(рядок " << minRow << ", стовпець " << minCol << ")" << endl; 
       cout  << "Насвітліший піксель: " << maxVal << "(рядок " << maxRow << ", стовпець " << maxCol << ")" << endl; 
    }
    // Середня яскравість рядків та всього зображення
    void averageBright(int **image, int rows, int cols){
        double totalSum = 0;
        
        cout << "Середнє по рядках: ";
        for(int i = 0; i < rows; i++){
            int *row = image[i];
            double sum = 0;
            for(int j = 0; j < cols; j++){
                sum += *(row + j);
            }
            totalSum += sum;
            double averageRow = sum / cols;
            cout << fixed << setprecision(2) << averageRow << " ";
        }
        double average = totalSum / (rows * cols);
        cout << "\nСередня яскравість: " << fixed << setprecision(2) << average << endl;
    
}
// Інвертування яскравості пікселів
void invertBright(int **image, int rows, int cols){
    cout << "Яскравість інвертовано." << endl;
     for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            image[i][j] = 9 - image[i][j];
            cout << image[i][j] << " ";

        }
        cout << endl;
     }
}
// Обмін значень двох пікселів
void swapPixels(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}
// Горизонтальне віддзеркалення зображення
void flipHorizontally(int** image, int rows, int cols){ 
     for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols / 2; j++){
            swapPixels(&image[i][j], &image[i][cols - j - 1]);
        }
} 
}
// Поворот зображення на 90 градусів праворуч
int** rotateRight(int** img, int rows, int cols){
    int newrows = cols;
    int newcols = rows;
    int** newImage = new int*[newrows];
    for(int i = 0; i < newrows; i++){
        newImage[i] = new int[newcols];

    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            newImage[j][rows - 1 - i] = img[i][j];
        }
    }
    for(int i = 0; i < rows; i++){
        delete[] img[i];
        img[i] = nullptr;
    }
    delete[] img;
    return newImage;

}
// Звільнення динамічної пам'яті двовимірного масиву та обнулення вказівника
void freeImage(int **&image, int rows){
    if(image != nullptr){
        for(int i = 0; i < rows; i++){
            delete[] image[i];
            image[i] = nullptr;
        }
        delete[] image;
        image = nullptr;
    }
}

int main(){
    int choice;
    int rows = 0;
    int cols = 0;
    int minRow = 0;
    int minCol = 0;
    int maxCol = 0;
    int maxRow = 0;
     cout << "Висота зображення: ";
   if(!readInteger(rows) || rows < 1 || rows > 20){
    cout << "Помилка. Висота має бути цілим числом в межах від 1 до 20" << endl;
    return 1;
}
   cout << "Ширина зображення: ";
   if(!readInteger(cols) || cols < 1 || cols > 20){ 
    cout << "Помилка. Ширина має бути цілим числом в межах від 1 до 20" << endl;
    return 1;
}

// Динамічне виділеня пам'яті під двовимірний масив
int **image = new int*[rows] ;
for(int i = 0; i < rows; i++){
       image[i] = new int[cols];
}
 cout << "Яскравість пікселів(0..9): ";
for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(!readInteger(image[i][j]) || image[i][j]  < 0 || image[i][j] > 9){ 
                cout << "Помилка. Яскравість має бути числом в межах від 0 до 9" << endl;
                freeImage(image, rows);
                return 1;
            }
        }
    }

    do{
        cout << left << setw(15) << "\nПункт " << "Операція" << endl;
        cout << left << setw(10) << "1" << "Показати зображення" << endl;
        cout << left << setw(10) << "2" << "Статистика яскравості" << endl;
        cout << left << setw(10) << "3" << "Інвертувати яскравість" << endl;
        cout << left << setw(10) << "4" << "Віддзеркалити по горизонталі" << endl;
        cout << left << setw(10) << "5" << "Повернути на 90 градусів праворуч" << endl;
        cout<< left << setw(10)  << "0" << "Вийти" << endl;
        cout << left << setw(10) << "Оберіть пункт меню: " << endl;
         if(!readInteger(choice)) {
            cout << "Помилка. Потрібно ввести ціле число від 0 до 5" << endl;
            choice = -1;
            continue;
         }
       
        switch(choice){
            case 1:
            showImage(rows, cols, image);
            break;
            case 2: 
            findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol) ;
            averageBright(image, rows, cols);
            break;
            case 3: 
            invertBright(image, rows, cols);
            break;
            case 4:
            cout << "Зображення віддзеркалено." << endl;
            cout << "Початкове: " << endl;
             showImage(rows, cols, image);
             cout << "Результат: " << endl;
            flipHorizontally(image, rows, cols);
            showImage(rows, cols, image);
            break; 
            case 5: { 
            image = rotateRight(image, rows, cols);
            int t = rows;
            rows = cols;
            cols = t;
            cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
            showImage(rows, cols, image);
            break;
            }
            case 0: 
            cout << "Програму завершено." << endl;
            break;
            default:
            cout << "Введено неправильне значення." << endl;
            break;
       
        }
    }
    while(choice!=0);
    freeImage(image, rows);

    return 0;
}
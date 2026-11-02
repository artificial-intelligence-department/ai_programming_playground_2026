/*
Task: Practice_task_Редактор монохромного зображення
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/


#include <iostream>
#include <iomanip>

using namespace std;

void showImage(int **m, int rows, int cols);
void findExtremes(int **m, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
void statisticImage(int **m, int rows, int cols, int minRow, int minCol, int maxRow, int maxCol);
void invertImage(int **m, int rows, int cols);
void swapPixels(int *a, int *b);
void imageReflection(int **m, int rows, int cols);
int** rotateRight(int** m, int rows, int cols);
void imageRotate(int ** &m, int &rows, int &cols);

int main(){
    setlocale(LC_ALL, "uk_UA");


    int rows = 0;
    int cols = 0;
    //Просимо користувача ввести висоту(rows) ширину(cols) 
    cout << "Введіть висоту зображення: ";
    if(!(cin >> rows) || rows < 1 || rows > 20){
        cout << "НЕ КОРЕКТНИЙ ВВІД! Введіть нове значення від 1 до 20 " << endl;
        return 1;
    }

    cout << "Введіть ширину зображення: ";
    if(!(cin >> cols) || cols < 1 || cols > 20){
        cout << "НЕ КОРЕКТНИЙ ВВІД! Введіть нове значення від 1 до 20 " << endl;
        return 1;
    }

    //створюємо масив вказівників
    int **image = new int*[rows];

    //виділяємо пам'ять під кожний рядок
    for(int i = 0; i < rows; i++){
        image[i] = new int[cols];
    }

    //просимо користувача задати яскравість зображення. 
    cout << "Введіть яскравість пікселів (0 ... 9): " << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(!(cin >> image[i][j]) || image[i][j] < 0 || image[i][j] > 9){
                cout << "НЕ КОРЕКТНИЙ ВВІД! Введіть нове значення від 0 до 9 " << endl;
                
                for(int i = 0;  i < rows; i++) delete [] image[i];
                delete [] image;
                image = nullptr;
                return 1;
            }
        }
    }

    int action = image[0][0];

    int minRow = image[0][0];
    int minCol = image[0][0]; 
    int maxRow = image[0][0];
    int maxCol = image[0][0];

    do{
        MENU_START:

        cout << endl;
        cout << "\n======================МЕНЮ==========================" << endl;
        cout << "1 \t Показати зображення" << endl;
        cout << "2 \t Статистика яскравості" << endl;
        cout << "3 \t Інвертувати яскравість" << endl;
        cout << "4 \t Віддзеркалити по горизонталі" << endl;
        cout << "5 \t Повернути на 90 градусів праворуч" << endl;
        cout << "0 \t ВИЙТИ" << endl;

        cout << "Оберіть ДІЮ: ";
        if (!(cin >> action)) {
            cout << "Помилка вводу!" << endl;
            cin.clear();               // Скидаємо прапорець помилки cin
            cin.ignore(10000, '\n');   // Очищаємо буфер
            goto MENU_START;           // Кидаємо користувача назад до меню
        }
        
        switch (action)
        {
        case 1:
            showImage(image, rows, cols);
            break;
        case 2: 
            statisticImage(image, rows, cols, minRow, minCol, maxRow, maxCol);
            break;    
        case 3:
            invertImage(image, rows, cols);
            break;
        case 4: 
            imageReflection(image, rows, cols); 
            break;  
        case 5:
            imageRotate(image, rows, cols);
            break;
        case 0:
            break;
        default:
            cout << "Помилка вводу!" << endl;
            goto MENU_START;
            break;
        }



    } while (action != 0);
    
    for(int i = 0;  i < rows; i++){
        delete [] image[i];
    }
    delete [] image;
    image = nullptr;

    return 0; 
}
// Функція для показу картинки
void showImage(int **m, int rows, int cols){

    cout << "Зображення " << rows << " x " << cols << ": "<< endl;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << m[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nМалюнок: " << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            switch (m[i][j])
            {
            case 0:
                cout << " ";
                break;
            case 1:
                cout << ".";
                break;
            case 2:
                cout << ":";
                break;
            case 3:
                cout << "-";
                break;        
            case 4:
                cout << "=";
                break;
            case 5:
                cout << "+";
                break;
            case 6:
                cout << "*";
                break;
            case 7:
                cout << "#";
                break; 
            case 8:
                cout << "%";
                break;
            case 9:
                cout << "@";
                break;              
            default:
                break;
            }
        }
        cout << endl;
    }

}
// функція для пошуку найтемнішого та та найсвітлішого пікселя
void findExtremes(int **m, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){

    bool isfoundMin = false;
    //шукаємо найсвітліший піксель
     for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(m[i][j] == 0){
                minRow = i;
                minCol = j;
                isfoundMin = true;
                break;
            }
        }
        if(isfoundMin) break;
     }
     if(!isfoundMin) minRow = -1;


      bool isfoundMax = false;
     //шукаємо найтемніший піксель
     for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(m[i][j] == 9){
                maxRow = i;
                maxCol = j;
                isfoundMax = true;
                break;
            }
        }
        if(isfoundMax) break;
     }

     if(!isfoundMax) maxRow = -1;

}


// виводимо статистику
void statisticImage(int **m, int rows, int cols, int minRow, int minCol, int maxRow, int maxCol){

    //Рахуємо середню яскравість картинки
    double aveImage = 0;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            aveImage += m[i][j];
        }
     }
     aveImage /= double((rows*cols)); 

     findExtremes(m, rows, cols, minRow, minCol, maxRow, maxCol);
    
     
    if(minRow != -1){
        cout << "Найменший піксель: 0 (рядок " << (minRow + 1)<< ", стовпець  " << (minCol + 1)<< ")" << endl;
    }else{
        cout << "Найменший піксель: 0 - ВІДСУТНІЙ" << endl;
    }
    
    if(maxRow != -1){
        cout << "Найбільший піксель: 9 (рядок " << (maxRow + 1) << ", стовпець  " << (maxCol + 1) << ")" << endl;
    }else{
        cout << "Найбільший піксель: 9 - ВІДСУТНІЙ" << endl;
    }
    
    cout << fixed << setprecision(2) << "Середня яскравість: " << aveImage << endl;
    cout << "Середня по рядках: ";

    //РАХУЄМО СЕРЕДНЄ ПО РЯДКАХ
     double aveImgRow = 0;
      for(int i = 0; i < rows; i++){
        int *row = m[i];
        for(int j = 0; j < cols; j++){
            aveImgRow += *(row + j);
        }
        aveImgRow /= double(cols);
        cout << fixed << setprecision(1) << aveImgRow << " ";
        aveImgRow = 0;
     }


}

//функція для інвертування зображення
void invertImage(int **m, int rows, int cols){

    cout << "Яскравість інвертовано! " << endl;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            m[i][j] = (9 - m[i][j]);
            cout << m[i][j] << " ";  
        }
        cout << endl;
    }

}

//функція для обміну пікселів
void swapPixels(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}


//функція для віддзркалення зображення
void imageReflection(int **m, int rows, int cols){

    cout << "Зображення віддзеркалено. "<< endl;
    cout << "Початкове: " << endl;

    //Виводимо початкове зображення 
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << m[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nРезультат: " << endl;


    //віддзеркалюємо по горизонталі
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols / 2; j++){
            swapPixels(&m[i][j], &m[i][cols - 1 - j]);
        }
    }

    //Виводимо віддзеркалене зображення
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << m[i][j] << " ";
        }
        cout << endl;
    }

}


//Функція для повороту зображення
int** rotateRight(int** m, int rows, int cols){
      
    //створюємо новий масив де міняємо стовпці з рядками
    int **newM = new int*[cols];
    
    for(int i = 0; i < cols; i++){
        newM[i] = new int[rows];
    }
    

    //заповнюємо його значеннями де перший рядок початкового зображення стає останнім стовпцем нового.

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            newM[j][rows - 1 - i] = m[i][j];

        }
        delete [] m[i]; //очищаємо рядки старого масиву 
    }

    //очищаємо старий масив вказівників
    delete [] m;
    m = nullptr;

    return newM;

}


// функція для виводу поверненого зображення
void imageRotate(int ** &m, int &rows, int &cols){
    m = rotateRight(m, rows, cols);

    //міняємо значення стовпців з рядками
    int t = cols;
    cols = rows;
    rows = t;

    cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << m[i][j] << " ";
        }
        cout << endl;
    }

}



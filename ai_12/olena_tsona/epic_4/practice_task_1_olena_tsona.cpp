#include <iostream>
#include <iomanip>

using namespace std;

const char palet[] = " .:-=+*#%@";

void showTabl (int **image, int rows, int cols);
void showImage (int **image, int rows, int cols);
void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
void showStatistic (int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
void swapPixels(int *a, int *b);
void invertImage(int **image, int rows, int cols);
void mirrorImage(int **image, int rows, int cols);
int **rotateRight(int** image, int rows, int cols);
void rotateAction(int **&image, int &rows, int &cols);


int main() {

    int minRow = 0;
    int minCol = 0;
    int maxRow = 0;
    int maxCol = 0;
    int rows = 0;
    int cols = 0;
    

    cout << "Висота зображення: ";
    cin >> rows;
    if (cin.fail() || rows < 1 || rows > 20) {
        cin.clear();                
        cin.ignore(10000, '\n');    
        cout << "Помилка! Потрібно ввести число від 1 до 20 ";
        return 1;
    }

    cout << "Ширина зображення: ";
    cin >> cols;
    if (cin.fail() || cols < 1 || cols > 20) {
        cin.clear();                
        cin.ignore(10000, '\n');    
        cout << "Помилка! Потрібно ввести число від 1 до 20 ";
        return 1;
    }

    int **image = new int *[rows];
    
    for (int i = 0; i < rows; i++) {
        image[i] = new int [cols];
    }

    int light = 0;
    cout << "Яскравість зображення: " << endl;
    for (int i = 0; i < rows; i++) {
        for ( int j = 0; j < cols; j++) {
            if (cin >> light) {
                if (light < 0 || light > 9) {
                    cin.clear();                
                    cin.ignore(10000, '\n');    
                    cout << "Помилка! Потрібно ввести числа від 0 до 9 ";

                    for (int k = 0; k < rows; k++) {
                        delete[] image[k];        
                        image[k] = nullptr;
                    }
                    delete[] image;               
                    image = nullptr;  

                    return 1;
                }
                image [i][j] = light;
            }  
        }
    }

    int choice = -1;
    do {

        cout <<"Оберіть дію:" <<endl;
        cout <<"1-Показати зображення" <<endl;
        cout <<"2-Статистика яскравості" <<endl;
        cout <<"3-Інвертувати яскравість" <<endl;
        cout <<"4-Віддзеркалити по горизонталі" <<endl;
        cout <<"5-Повернути на 90 градусів праворуч" <<endl;
        cout <<"0-Вийти" <<endl;

        cout <<"Ваш вибір дії: ";
        cout << endl;
        
        if (!(cin >> choice)) {
            if (cin.eof()) {        //перевірка чи заінчений ввід
                choice = 0;  
            }                     
        

            else {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Помилка! Потрібно ввести число від 0 до 5" << endl;
                choice = -1;                      
            }
        

        }
        else {
            switch(choice) {
                case 1:
                    showImage (image, rows, cols);
                    break;
                case 2:
                    showStatistic (image, rows, cols, minRow, minCol, maxRow, maxCol);
                    break;
                case 3:
                    invertImage(image, rows, cols);
                    break;
                case 4:
                    mirrorImage(image, rows, cols);
                    break;
                case 5:
                    rotateAction(image, rows, cols);
                    break;
                case 0:
                    cout << "До побачення!" << endl;
                    break;
                default: cout << "Помилка: такого пункту меню немає." << endl;

            }
        }

    } while ( choice != 0);
    for (int i = 0; i < rows; i++) {
        delete[] image[i];        
        image[i] = nullptr;
    }
    delete[] image;               
    image = nullptr;  

    return 0;
}

void showTabl (int **image, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
}

void showImage (int **image, int rows, int cols) {
    showTabl ( image, rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << palet[image[i][j]];
        }
        cout << endl;
    }
    cout << "ширина зображення " << cols << endl;
    cout << "висота зображення " << rows << endl;

}

void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    int max = -1;
    int min = 10;
    for (int i = 0; i < rows; i++) {
        int *row = image[i];
        for (int j = 0; j < cols; j++) {
            int pic = *(row + j);
            if ( pic > max) {
                max = pic;
                maxRow = i;
                maxCol = j;
            }
            if ( pic < min) {
                min = pic;
                minRow = i;
                minCol = j;
            }   
        }
    }
    cout << "Найтемніший піксель: " << min << "(рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << max << "(рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;
    cout << endl;
    
}

void showStatistic (int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    findExtremes (image, rows, cols, minRow, minCol, maxRow, maxCol);
    int sumAll = 0;
    int Nrows = 0;
    int Ncols = 0;
    double serTotal = 0;
    double *serRow = new double[rows];
    for (int i = 0; i < rows; i++) {
        int *row = image[i];
        int sumRow = 0;
        for (int j = 0; j < cols; j++) {
            sumRow += *(row + j);
            Ncols = j + 1;
            
        } 
        
        sumAll += sumRow; 
        Nrows = i + 1;  
        serRow[i]= ((double)sumRow) / Ncols;   
    }

    serTotal = ((double)sumAll) / (Nrows * Ncols);
    

    cout << fixed << setprecision(2);
    cout << "Cередня яскравість: " << serTotal << endl;
    cout << fixed << setprecision(1);
    cout << "Cередня по рядках: ";
    for (int i = 0; i < rows; i++) {
        cout << serRow[i] << " ";

    } 
    delete[] serRow;              
    serRow = nullptr;   

    cout << endl;
    
}

void invertImage(int **image, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            image[i][j] = 9 - image[i][j];
        }
    }
    cout << "Яскравість інвертовано." << endl;
    showTabl(image, rows, cols);
}

void swapPixels(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void mirrorImage(int **image, int rows, int cols) {
    cout << "Зображення віддзеркалено." << endl;
    cout << "Початкове:" << endl;
    showTabl(image, rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&image[i][j], &image[i][cols - 1 - j]);
        }
    }
    cout << endl << "Результат:" << endl;
    showTabl(image, rows, cols);
}

int **rotateRight(int** image, int rows, int cols) {
    int **newImage = new int*[cols];
    for (int i = 0; i < cols; i++) {
        newImage[i] = new int[rows];    
    }
    
    for (int i = 0; i < rows; i++) {              
        for (int j = 0; j < cols; j++) {
            newImage[j][rows - 1 - i] = image[i][j];
        }
    }
    for (int i = 0; i < rows; i++) {
        delete[] image[i];
    }
    delete[] image;
    image = nullptr;
    return newImage;
}

void rotateAction(int **&image, int &rows, int &cols) {
    image = rotateRight(image, rows, cols);
    int tmp = rows;                               
    rows = cols;
    cols = tmp;
    cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
    showTabl(image, rows, cols);
}

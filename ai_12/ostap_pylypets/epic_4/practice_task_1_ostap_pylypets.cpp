/*practice task #2 v3*/
#include <iostream>
#include <iomanip>
using namespace std;
//функція яка перевіряє на валідність значення
void validCheck(int rows, int cols, bool& exit){
    if(rows <1 || rows >20 || cols <1 || cols >20){
        cout <<"Введіть дійсні значення";
        exit = true;
    }
}
//виводимо menu
void menuOutput(){
    cout << "Пункт |Операція\n";
    cout << "   1 |Показати зображення\n";
    cout << "   2 |Статистика яскравості\n";
    cout << "   3 |Інвертувати яскравість\n";
    cout << "   4 |Віддзеркалити по горизонталі\n";
    cout << "   5 |Повернути на 90 градусів\n";
    cout << "   0 |Вийти\n";
}
//виводимо зображення
void showImage(int** image, int rows, int cols){
    char palette[] = " .:-=+*#%@";
    for(int i = 0; i< rows; i++){
        for(int q = 0; q<cols; q++){
            cout << image[i][q] <<" ";
        }
        cout << endl;
    }
    //виводимо яскравість за символами
    for(int i = 0; i< rows; i++){
        for(int q = 0; q<cols; q++){
            cout << palette[image[i][q]];
        }
        cout << endl;
    }
    cout << "Розмір зображення: " << rows << "x"<< cols << endl;
}
//виводимо статистику
void statistics(int** image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
    double avg = 0; 
    int num = rows * cols;
    double avgRes = 0, avgPerRow = 0;
    //вкладеними циклами і за допомогою вказівника та звернення сумуємо всі елементи масиву
    for(int i = 0; i< rows; i++){
        int* row = image[i];
        for(int j = 0; j< cols; j++){
            avg += *(row +j);
        }
    }
    avgRes = avg/num;
    cout << fixed << setprecision(2);
    //виводимо статистику
    cout << "Найтемніший піксель: " << image[minRow][minCol]
    << " (рядок "<< minRow +1 <<", стовпець "<< minCol+1 << ")" << endl;
    cout << "Найсвітліший піксель: " << image[maxRow][maxCol]
    << " (рядок "<< maxRow +1 <<", стовпець "<< maxCol+1 << ")" << endl;
    cout << "Середня яскравість: " << avgRes << endl;
    cout << "Середня яскравість по рядках: ";
    //виводимо середнє значення за рядком 
    for(int i = 0; i< rows; i++){
        int* row = image[i];
        for(int j = 0; j< cols; j++){
            avgPerRow += *(row +j);
        }
        cout << avgPerRow/cols <<" ";
        avgPerRow = 0;
    }
    cout << endl;
}
void findExtremes(int **image,int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
    int darkest = image[0][0], brightest = image[0][0];
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;
    //шукаємо найтемніше та найсвітліше значення
    for(int i = 0; i< rows; i++){
        for(int q = 0; q<cols; q++){
            if(image[i][q] < darkest){
                darkest = image[i][q];
                minRow = i;
                minCol = q;
            }
            if(image[i][q] > brightest){
                brightest = image[i][q];
                maxRow = i;
                maxCol = q;
            }
        }
    }
}
void invertion(int** image, int rows, int cols){
    // вкладеним циклом інвертуємо зображення
    for(int i = 0; i< rows; i++){
        for(int q = 0; q<cols; q++){
            image[i][q] = 9 - image[i][q];
        }
    }
}
void swapPixels(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
// відзеркалюємо зображення
void mirror(int** image, int rows, int cols){
    for(int i = 0; i< rows; i++){
        //cols/2 бо перевіряти треба 2 рази менше
        for(int q = 0; q<cols/2; q++){
            swapPixels(&image[i][q], &image[i][cols-1-q]);
        }
    }
}
void memoryrelease(int**& image, int rows){
    //вивільняємо пам'ять
    //якщо у image щось є то
    if(image != nullptr){
        //видаляємо image[i] та присвоюємо nullptr
        for(int i = 0; i< rows; i++){
            delete[] image[i];
            image[i] = nullptr;
        }
        //видаляємо масив та присвоюємо nullptr
        delete[] image;
        image = nullptr;
    }
}
int** rotateRight(int** image, int rows, int cols){
    //міняємо місцями рядки та колоки
    int** newImage = new int*[cols];
    for(int i = 0; i< cols; i++){
        newImage[i] = new int[rows];
    }
    //перезаписуємо значення
    for(int i = 0; i< rows; i++){
        for(int j = 0; j< cols; j++){
            newImage[j][rows - 1 - i] = image[i][j];
        }
    }
    memoryrelease(image, rows);
    return newImage;
}
int main(){
    bool exit = false;
    int rows, cols, choice;
    int minRow, minCol, maxRow, maxCol;

    cout <<"Введіть висоту пікселів: ";
    if(!(cin >> rows)){
        cout << "Некоректне введення";
        return 0;
    }
    cout <<"Введіть ширину пікселів: ";
    if(!(cin >> cols)){
        cout << "Некоректне введення";
        return 0;
    }
    validCheck(rows, cols, exit);
    if(exit) return 0;
    cout <<"Введіть яскравість пікселів: ";
    //створюємо масив елементів
    int** image = new int*[rows];
    for (int i = 0; i<rows; i++){
        image[i] = new int[cols];
    }
    //валідкємо значення
    for(int i = 0; i< rows; i++){
        for(int q = 0; q<cols; q++){
            if(!(cin >> image[i][q]) || image[i][q] <0 || image[i][q] > 9){
                cout <<"Введіть значення від 0 до 9";
                memoryrelease(image, rows);
                return 0;
            }
        }
    }
    do{
        menuOutput();
        if(!(cin >> choice)){
            if(cin.eof()){
                exit = true;
                break;
            }
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Введіть число від 0 до 5\n";
            continue;
        }
        switch (choice){
            case 1:
                showImage(image, rows, cols);
                break;
            case 2:
                findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);
                statistics(image, rows, cols, minRow, minCol, maxRow, maxCol);
                break;
            case 3:
                invertion(image, rows, cols);
                cout << "Яскравість інвертовано.\n";
                break;
            case 4:
                mirror(image, rows, cols);
                cout << "Зображення віддзеркалено.\n";
                break;
            case 5: {
                image = rotateRight(image, rows, cols);
                int temp = rows;
                rows = cols;
                cols = temp;
                cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
                break;
            }
            case 0:
                exit = true;
                break;
            default:
                cout << "Введіть число від 0 до 5\n";
                break;
        }
    }while(exit == false);
    memoryrelease(image, rows);
    return 0;
}

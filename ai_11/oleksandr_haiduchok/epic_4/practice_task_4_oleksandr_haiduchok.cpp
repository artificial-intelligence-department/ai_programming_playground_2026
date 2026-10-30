#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;
// знаходимо наше зображеня з символів за допомогою заміни цифр на символи
void Image(int **img, int rows, int cols){
    cout << "Зображення " << rows << " x " << cols << ":\n";
    for(int h = 0; h < rows; h++){
        for(int l = 0; l < cols; l++){
            cout << img[h][l] << " ";
        }
        cout << "\n";
    }
    cout << "Малюнок:\n";
    int vybyr = 0;
    for (int g = 0; g < rows; g++){
        for(int v = 0; v < cols; v++){
            vybyr = img[g][v];
            switch(vybyr){
            case 0: cout << " "; break;
            case 1: cout << "."; break;
            case 2: cout << ":"; break;
            case 3: cout << "-"; break;
            case 4: cout << "="; break;
            case 5: cout << "+"; break;
            case 6: cout << "*"; break;
            case 7: cout << "#"; break;
            case 8: cout << "%"; break;
            case 9: cout << "@"; break;
        }
    }
    cout << "\n";
}
}
//пошук найтемнішого та найсвітлішого пікселя
void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
    minRow = 1;
    maxRow = 1;
    minCol = 1;
    maxCol = 1;
    int Dark = *(*(img + 0) + 0);
    int Light = *(*(img + 0) + 0);
    for (int i = 0; i < rows; i++){
        int *row = img[i];
        for(int j = 0; j < cols; j++){
            int find = *(row + j);
            if(find < Dark){
                Dark = find;
                minRow = i + 1;
                minCol = j + 1;
            }
            if(find > Light){
                Light = find;
                maxRow = i + 1;
                maxCol = j + 1;
            }
        }
    }
    cout << "Найтемніший піксель: " << Dark << " (рядок " << minRow << ", стовпець " << minCol << ")\n";
    cout << "Найсвітліший піксель: " << Light << " (рядок " << maxRow << ", стовпець " << maxCol << ")\n";
    
}
//підрахунок середнього в двовимірному масиві через цикли
void Shine(int **img, int rows, int cols, double &Seredne){
    Seredne = 0;
    double counts = 0;
    for (int i = 0; i < rows; i++){
        int *sum = img[i];
        for(int j = 0; j < cols; j++){
                counts++;
                Seredne += *(sum + j); 
        }
    }
    if(counts > 0){
    Seredne = Seredne/counts;
    }
    else{
        Seredne = 0;
    }
    cout << "Середня яскравість: " << fixed << setprecision(2) << Seredne << "\n";
}
//підрахунок середнього по рядках
void Shinerows(int **img, int rows, int cols, double &Serednerows){
    double countr = 0;
    cout << "Середня по рядках: ";
    for (int i = 0; i < rows; i++){
        int *tem = img[i];
        countr = 0;
        Serednerows = 0;
        for(int j = 0; j < cols; j++){
                countr++;
                Serednerows += *(tem + j); 
        }
        if(countr > 0){
    Serednerows = Serednerows/countr;
    }
    else{
        Serednerows = 0;
    }
        cout << fixed << setprecision(1) << Serednerows << " ";
    }
    cout << "\n";
}
//інвертуємо наші цифри
void Inverse(int **img, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            img[i][j] = 9 - img[i][j];
        }
    }
    cout << "Яскравість інвертовано.\n";
    for (int g = 0; g < rows; g++){
        for(int v = 0; v < cols; v++){
            cout << img[g][v] << " ";  
    }
    cout << "\n";
}
cout << "\n";
}
//міняємо пікселі місцями
void swapPixels(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
//міняємо наші стовпці місцями
void swapRows(int **img, int rows, int cols){
    cout << "Зображення віддзеркалено. \n" << "Початкове:\n";
    for(int r = 0; r < rows; r++){
        for(int t = 0; t < cols; t++){
            cout << *(*(img + r) + t) << " ";
        }
        cout << "\n";
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols/2; j++){
            swapPixels(*(img + i) + j, *(img + i) + cols - j - 1);
    }
    }
    cout << "Результат:\n";
    for(int f = 0; f < rows; f++){
        for(int x = 0; x < cols; x++){
            cout << *(*(img + f) + x) << " ";
        }
        cout << "\n";
    }
}
//поворот за рахунок створення нового динамічного масиву з новою розмірністю
int** rotateRight(int** img, int rows, int cols){
    int **img2 = new int*[cols];
    for(int y = 0; y < cols; y++){
        img2[y] = new int[rows];
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
        *(*(img2 + j) + rows - 1 - i) = *(*(img + i) + j);
    }
}
cout << "Зображення повернуто. Нові розміри: " << cols << " x " << rows << "\n";
    for(int i = 0; i < cols; i++){
        for(int j = 0; j < rows; j++){
            cout << *(*(img2 + i) + j) << " ";
        }
        cout << "\n";
}
for(int g = 0; g < rows; g++){
        delete[] img[g];
}
delete[] img;
return img2;
}


int main(){
    int rows = 0;
    int cols = 0;
    cout << "Введіть висоту зображення: ";
    cin >> rows;
    if(cin.fail() || rows <= 0 || rows > 20){
        cout << "Помилка. Не правильний ввід!\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return 0;
    }
    cout << "Введіть ширину зображення: ";
    cin >> cols;
    if(cin.fail() || cols <= 0 || cols > 20){
        cout << "Помилка. Не правильний ввід!\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return 0;
    }
    int **img = new int*[rows];
    for(int y = 0; y < rows; y++){
        img[y] = new int[cols];
    }
    cout << "Яскравість пікселів (0..9):\n";
//зчитуємо наші пікселі
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cin >> img[i][j];
            if((img[i][j] < 0) || (img[i][j] > 9) || cin.fail()){
            cout << "Помилка. Погане значення!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            for(int s = 0; s < rows; s++){
                delete[] img[s];
            }
            delete [] img;
            return 0;
        }
    }
}
int minRow = 1; 
int minCol = 1;
int maxRow = 1; 
int maxCol = 1;
double Seredne = 0;
double Serednerows = 0;
int choice = 0;
// цикл ду виводить кожен раз наше меню
    do{
        cout << "1\t\tПоказати зображення\n";
        cout << "2\t\tСтатистика яскравості\n";
        cout << "3\t\tІнвертувати яскравість\n";
        cout << "4\t\tВіддзеркалити по горизонталі\n";
        cout << "5\t\tПовернути на 90 градусів праворуч\n";
        cout << "0\t\tВийти\n";
        cin >> choice;
        if(cin.fail() || choice < 0 || choice > 5){
        cout << "Помилка. Введіть коректне число!\n";
        choice = -1;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
    }
    switch(choice){
        case 0: for(int g = 0; g < rows; g++){
        delete[] img[g];
}
        delete[] img;
        img = nullptr;
        return 0; 
        break;
        case 1: Image(img, rows, cols); break;
        case 2: findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);
        Shine(img, rows, cols, Seredne);
        Shinerows(img, rows, cols, Serednerows);
        break;
        case 3: Inverse(img, rows, cols); break;
        case 4: swapRows(img, rows, cols); break;
        case 5:{ 
        img = rotateRight(img, rows, cols);
        int temp = 0;
        temp = rows;
        rows = cols;
        cols = temp;
        break;
        }
        
    }
}
while(choice != 0);
for(int q = 0; q < rows; q++){
        delete[] img[q];
}
delete[] img;
img = nullptr;

    return 0;
}
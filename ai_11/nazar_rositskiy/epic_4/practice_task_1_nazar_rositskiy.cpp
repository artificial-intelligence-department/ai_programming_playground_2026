#include <iostream>

using namespace std;

//Функція що виводить меню
int menu(){
    //мітка goto
    invalidOption:
    //ініціалізація answear
    int answear;
    //виведення меню
    std::cout << std::endl;
    std::cout << "1   Показати зображення" << std::endl;
    std::cout << "2   Статистика яскравості" << std::endl;
    std::cout << "3   Інвертувати яскравість" << std::endl;
    std::cout << "4   Віддзеркалити по горизонталі" << std::endl;
    std::cout << "5   Повернути на 90 градусів праворуч" << std::endl;
    std::cout << "0   Вийти" << std::endl;
    //відпоівідь
    std::cin >> answear;
    //перевірка на помилку і виведення ще раз за потреби
    if(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        goto invalidOption;
    }  
    //повернення відповіді
    return answear;
}

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol){
    //Ініціалізація змінних
    int min = img[0][0];
    int max = img[0][0];
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;

    //Знаходження координат максимальних мінімальних значень
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(img[i][j] > max){
                max = img[i][j];
                maxRow = i;
                maxCol = j;
            }
            if(img[i][j] < min){
                min = img[i][j];
                minRow = i;
                minCol = j;
            }
        }
    }
}

void swapPixels(int* a, int* b){
    //Змінення пікселів місцями
    int c = *b;
    *b = *a;
    *a = c;
}

void menu1(int** img, int rows, int cols){
    cout << endl;

    //Виведення зображення
    cout << "Зображення " << rows << "x" << cols << ":" << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    //Виведення малюнка для зображення
    cout << "Малюнок: " << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            switch (img[i][j]){
            case 0:
                cout << "  ";
                break;
            case 1:
                cout << ". ";
                break;
            case 2:
                cout << ": ";
                break;
            case 3:
                cout << "- ";
                break;
            case 4:
                cout << "= ";
                break;
            case 5:
                cout << "+ ";
                break;
            case 6:
                cout << "* ";
                break;
            case 7:
                cout << "# ";
                break;
            case 8:
                cout << "% ";
                break;
            case 9:
                cout << "@ ";
                break;
            default:
                break;
            } 
        }
        cout << endl;
    }
}

void menu2(int** img, int rows, int cols){

    //Ініціалізація змінних
    int minRow, minCol, maxRow, maxCol;

    //Виклик функції для знаходження мінімальних та максимальних значень
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);
    cout << endl;

    //виведення найтемнішого та найсвітлішого пікселів їх координат
    cout << "Найтемніший піксель: " << img[minRow][minCol] << "(рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << img[maxRow][maxCol] << "(рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;

    //Обчислення суми всіх значення яскравості
    float sum = 0;
    for(int i = 0; i < rows; i++){
        int *row = img[i]; 
        for(int j = 0; j < cols; j++){
            sum = sum + *(row + j); 
        }
    }

    //Знаходження та виведення середньої яскравості
    cout << "Середня яскравість: " << sum/(rows*cols) << endl;

    //Знаходження та виведення середньої яскравості по рядках
    cout << "Середня по рядках: ";
    for(int i = 0; i < rows; i++){
        int *row = img[i]; 
        float rowSum = 0;
        for(int j = 0; j < cols; j++){
            rowSum = rowSum + *(row + j);
        }
        cout << rowSum/cols << " ";
    }
    cout << endl;

}

void menu3(int** img, int rows, int cols){
    cout << endl;

    //Інверсія яскравості
    cout << "Яскравість інвертовано "<< endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            img[i][j] = 9 - img[i][j];
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void menu4(int** img, int rows, int cols){
    cout << endl;
    cout << "Зображення віддзеркалено "<< endl;

    //Виведення початкового зображення
    cout << "Початкове: "<< endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }

    //віддзеркалення зображення
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols/2; j++){
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }

    //Виведення віддзеркалення зображення
    cout << "Результат: " << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

int** rotateRight(int** img, int rows, int cols){

    //Виділення пам'яті під нове повернене зображення
    int** newImg = new int* [cols];
    for (int i = 0; i < cols; i++) {
        newImg[i] = new int[rows];
    }

    //створення нового повернутого зображення
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            newImg[j][rows - 1 - i] = img[i][j];
        }
    }

    //Видалення старого зображення з пам'яті
    for (int i = 0; i < rows; i++) {
           delete[] img[i];
        }
    delete[] img;
    img = nullptr;

    //Повернення нового зображення
    return newImg;
}

void menu5(int** &img, int &rows, int &cols){

    //Виклик функції перевертання зображення
    img = rotateRight(img, rows, cols);

    //Заміна рядків і стовпців місцями
    int newCols = rows;
    rows = cols;
    cols = newCols;
    cout << endl;

    //виведення повернутого зображення та його розмірів
    cout << "Зображення повернуто. Нові розміри: " << rows << "x" << cols << ":" << endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    //Ініціалізація змінних
    int rows, cols;
    int answear;
    bool exit = 0;

    //Введення висоти з перевіркою
    cout << "Висота зображення: ";
    cin >> rows;
    if(cin.fail() || rows <= 0){
        cout << "Неприпустимі розміри";
        return 0;
    }

    //введення ширини з перевіркою
    cout << "Ширина зображення: ";
    cin >> cols;
    if(cin.fail() || cols <= 0){
        cout << "Неприпустимі розміри";
        return 0;
    }


    //виділяємо пам'ять під матрицю
    int** img = new int*[rows];
    for (int i = 0; i < rows; i++) {
        img[i] = new int[cols];
    }

    //Введення яскравості з перевіркою
    cout << "Яскравість пікселів (0..9): " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) { 
            cin >> img[i][j];
            if(img[i][j] > 9 || img[i][j] < 0 || cin.fail()){
                cout << "Неприпустима яскравість";
                return 0;
            }      
        }
    }

    //Цикл для меню
    do {
        answear = menu();
        switch (answear)
        {
        case 0:
            exit = 1;
            //Видалення з пам'яті
            for (int i = 0; i < rows; i++) {
                delete[] img[i];
            }
            delete[] img;
            img = nullptr;
            break;
        case 1:
            menu1(img, rows, cols);
            break;
        case 2:
            menu2(img, rows, cols);
            break;
        case 3:
            menu3(img, rows, cols);
            break;
        case 4:
            menu4(img, rows, cols);
            break;
        case 5:
            menu5(img, rows, cols);
            break;
        default:
            break;
        }
    } while (!exit); 

}
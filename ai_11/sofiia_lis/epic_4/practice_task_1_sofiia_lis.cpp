/* 
Епік 4. Практичне завдання: Редактор монохромного зображення
Авторка: Софія Ліс
Група: ші-11
*/

#include <iostream>
#include <iomanip>

using namespace std;

void clearMemory(int ** &img, int rows) {
    for(int i = 0; i < rows; i++) {
        delete[] *(img + i);
        *(img + i) = nullptr;
    }
    delete[] img;
    img = nullptr;
}

// 1 пункт меню
void showImage(int ** img, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << *(*(img + i) + j) << " ";
        }
        cout << endl;
    }

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            switch (*(*(img + i) + j)) {
                case 0:
                cout << ' ';
                break;
                case 1:
                cout << '.';
                break;
                case 2:
                cout << ':';
                break;
                case 3:
                cout << '-';
                break;
                case 4:
                cout << '=';
                break;
                case 5:
                cout << '+';
                break;
                case 6:
                cout << '*';
                break;
                case 7:
                cout << '#';
                break;
                case 8:
                cout << '%';
                break;
                case 9: 
                cout << '@';
                break;
            }
        }
        cout << endl;
    }
    cout << rows << 'x' << cols << endl;
}

// допоміжні функції для статистики
void findExtremes(int ** img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(*(*(img + i) + j) < (*(*(img + minRow) + minCol))) {
                minRow = i;
                minCol = j;
            }
            if(*(*(img + i) + j) > (*(*(img + maxRow) + maxCol))) {
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

double averageValue(int ** img, int rows, int cols) {
    double sum = 0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            sum += (*(*(img + i) + j));
        }
    }
    return sum / (rows*cols);
}

void swapPixels(int * a, int * b) {
    int c = *a;
    *a = *b;
    *b = c;
}

// 2 пункт меню
void statistics(int ** img, int rows, int cols) {
    int mR, mC, mxR, mxC;
    findExtremes(img, rows, cols, mR, mC, mxR, mxC);
    cout << "Найтемніший піксель: " << (*(*(img + mR) + mC)) << " (рядок " << mR + 1 << ", стовпець " << mC + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << (*(*(img + mxR) + mxC)) << " (рядок " << mxR + 1 << ", стовпець " << mxC + 1 << ")" << endl;
    cout << "Середня яскравість: " << averageValue(img, rows, cols) << endl;
    cout << "Середня по рядках: ";
    for(int i = 0; i < rows; i++) {
        double sum = 0; 
        int * row = img[i]; 
        for(int j = 0; j < cols; j++) {
            sum += *(row + j);
        }
        cout << (sum / cols) << ' '; 
      
    }
    cout << endl;
}

// 3 пункт меню
void inversion(int ** img, int rows, int cols) {
    cout << "Яскравість інвертовано." << endl;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << (*(*(img + i) + j) = 9 - *(*(img + i) + j)) << ' ';
        }
        cout << endl;
    }
}

// 4 пункт меню
void mirror(int ** img, int rows, int cols) {
    int left = 0;
    int right = cols - 1;
    while(left < right) {
        for(int i = 0; i < rows; i++) {
            swapPixels(*(img + i) + left, *(img + i) + right);
        }
        left++;
        right--;
    }
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << (*(*(img + i) + j)) << ' ';
        }
        cout << endl;
    }
}

// 5 пункт меню
int ** rotateRight(int ** img, int rows, int cols) {
    int ** rotatedimage = new int*[cols];
    for(int i = 0; i < cols; i++) {
        *(rotatedimage + i) = new int[rows];
    }
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
           *(*(rotatedimage + j) + (rows - 1 - i)) = *(*(img + i) + j);
        }
    }
    
    //очищення пам'яті
    clearMemory(img, rows);

    for(int i = 0; i < cols; i++) {
        for(int j = 0; j < rows; j++) {
            cout << *(*(rotatedimage + i) + j) << ' ';
        }
        cout << endl;
    } 

    return rotatedimage;
}

int main() {

    cout << fixed << setprecision(2);

    int rows, cols;

    cout << "Введіть висоту зображення(1-20): ";
    cin >> rows;
    if(cin.fail() || rows < 1 || rows > 20) {
        cout << "Введіть ціле число в проміжку(1-20)" << endl;
        return 1;
    }

    cout << "Введіть ширину зображення(1-20): ";
    cin >> cols;
    if(cin.fail() || cols < 1 || cols > 20) {
        cout << "Введіть ціле число в проміжку(1-20)" << endl;
        return 1;
    }

    int ** image = new int*[rows];

    cout << "Введіть значення яскравості пікселів(0-9):" << endl;

    for(int i = 0; i < rows; i++) {
        *(image + i) = new int[cols];
        for(int j = 0; j < cols; j++) {
            cin >> *(*(image + i) + j);
            
            if(cin.fail() || *(*(image + i) + j) < 0 || *(*(image + i) + j) > 9) {
                cout << "Введіть ціле число в проміжку(0-9)" << endl;
                clearMemory(image, i + 1);
                return 1;
            }
        }
    }

    int action;

    do{
        cout << "Пункт     Операція" << endl;
        cout << "1         Показати зображення" << endl;
        cout << "2         Статистика яскравості" << endl;
        cout << "3         Інвертувати яскравість" << endl;
        cout << "4         Віддзеркалити по горизонталі" << endl;
        cout << "5         Повернути на 90 градусів праворуч" << endl;
        cout << "0         Вийти" << endl;

        cin >> action;
        if(cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            action = -1;
        }
        switch(action) {
            case 1:
                showImage(image, rows, cols);
            break;
            case 2:
                statistics(image, rows, cols);
            break;
            case 3:
                inversion(image, rows, cols);
            break;
            case 4:
                mirror(image, rows, cols);
            break;
            case 5:
            {
                image = rotateRight(image, rows, cols);
                int n = rows;
                rows = cols;
                cols = n;
                cout << rows << "x" << cols << endl; 
            }
            break;
            case 0:
                cout << "Вихід." << endl;
                clearMemory(image, rows);
            break;
            default: 
                cout << "Введіть значення меню!" << endl;
            break;
        }
    }
    while(action != 0);


    return 0;
}
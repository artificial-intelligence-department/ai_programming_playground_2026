#include <iostream>
#include <iomanip>
using namespace std;

void findextremes(int **image, int rows, int cols, int &minrow, int &mincol, int &maxrow, int &maxcol) {
    int min = 10;
    int max = -1;
    for (int i = 0; i < rows; i++) {
        int *row = *(image + i);
        for (int j = 0; j < cols; j++) {
            int current = *(row + j);
            if (current == min || current == max) continue;
            if (current > max) {
                max = current;
                maxrow = i;
                maxcol = j;
            }
        
            if (current < min) {
                min = current;
                minrow = i;
                mincol = j; 
            }
        }
    }
    cout << "Найтемніший піксель: " << min << " (рядок " << minrow + 1 << ", стовпець " << mincol + 1 << ")\n";
    cout << "Найсвітліший піксель: " << max << " (рядок " << maxrow + 1 << ", стовпець " << maxcol + 1 << ")\n";
}

void averages(int cols, int rows, int **image) {
    double total = 0;
    double rowavg[rows];
    for  (int i = 0; i < rows; i++) {
        double rowsum = 0;
        int *row = image[i];

        for (int j = 0; j < cols; j++) {
            rowsum += *(row + j);
        }
        rowavg[i] = rowsum / cols;
        total += rowsum;
    }
    double avg = total / (rows * cols);
    cout << "Середня яскравість: " << fixed << setprecision(2) << avg << "\nСередня по рядках: ";
    for (int i = 0; i < rows; i++) {
        cout << fixed << setprecision(1) << rowavg[i] << " ";
    }
    cout << "\n";
}

void swappixels(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int** rotateright(int** image, int rows, int cols) {
    int **rimage = new int*[cols];
    for (int i = 0; i < cols; i++) rimage[i] = new int[rows];
    for (int i = 0; i <  rows; i++) {
        for (int j = 0; j < cols; j++)
            rimage[j][rows - 1 - i] = image[i][j];
    }
    for (int i = 0; i < rows; i++) delete[] image[i];
    delete[] image;
    image = nullptr;
    return rimage;
}

int main() {
 
    int option, rows, cols;
    cout << "Висота зображення: ";
    if (!(cin >> rows) || rows <= 0) {
        cout << "Некоректний ввід!\n";
        return 0;
    }
    cout << "Ширина зображення: ";
    if (!(cin >> cols) || cols <= 0) {
        cout << "Некоректний ввід!\n";
        return 0;
    }
    int **image = new int*[rows];
    for (int i = 0; i < rows; i++) 
        image[i] = new int[cols];
    cout << "Яскравість пікселів (0..9):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
        if (!(cin >> image[i][j])) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Некоректний ввід!\n";
        for (int i = 0; i < rows; i++) {
            delete[] image[i];
        }
        delete[] image;
        image = nullptr;
        return 0;
        }
        if (image[i][j] < 0 || image[i][j] > 9) {
            cout << "Некоректний ввід!\n";
            for (int i = 0; i < rows; i++) {
                delete[] image[i];
            }
            delete[] image;
            image = nullptr;
            return 0;
        }
        
        }
    }
    menu:
    do { 
    cout << "1\tПоказати зображення\n" << "2\tСтатистика яскравості\n" << "3\tІнвертувати яскравість\n" << "4\tВіддзеркалити по горизонталі\n" << "5\tПовернути на 90 градусів праворуч\n" << "0\tВийти\n" << "> ";
    if (!(cin >> option)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Некоректний ввід. Перенаправляємо до основного меню..\n";
        goto menu;
    }
    switch (option) {
        case 1: {
        cout << "Зображення " << rows << " x " << cols << ":\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << image[i][j] << " ";
                if (j == cols - 1) cout << "\n";
            }
        }
        cout << "\nМалюнок:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                switch (image[i][j]) {
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
                }
                if (j == cols - 1) cout << "\n";
            }
        }
        break;
        }
        case 2: 
        {
            int minrow, mincol, maxrow, maxcol;
            findextremes(image,rows,cols, minrow, mincol, maxrow, maxcol);
            averages(cols, rows, image);
            break;
        }
        case 3: 
        {
            cout << "Яскравість інвертовано:\n";
            for (int i = 0; i < rows; i++) {
                for  (int j = 0; j < cols; j++) {
                    cout << 9 - image[i][j] << " ";
                    if (j == cols - 1) cout << endl;
                }
            }
            break;
        }
        case 4:
        {   
            cout << "Зображення віддзеркалено.\nПочаткове зображення:\n";
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                cout << image[i][j] << " ";
                if (j == cols - 1) cout << "\n";
                }
            }
            cout << "Результат:\n";
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols / 2; j++) {
                    swappixels(&image[i][cols - j - 1], &image[i][j]);
                }
            }
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    cout << image[i][j] << " ";
                    if (j == cols - 1) cout << "\n";
                }
            }
            break;
        }
        case 5:
        {
            image = rotateright(image, rows, cols);
            int temprow = rows;
            rows = cols;
            cols =  temprow;
            cout << "Зображення перевернуто. Нові розміри: " << rows << " x " << cols << endl;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    cout << image[i][j] << " ";
                    if (j == cols - 1) cout << "\n";
                }
            }
            break;
        }
        default: 
        {
            if (option == 0) break;
            else cout << "Некоректний ввід!\n";
            goto menu;
        }
    }
    } while (option != 0);
    
    for (int i = 0; i < rows; i++) {
        delete[] image[i];
    }
    delete[] image;
    image = nullptr;
    return 0;
}



    

   
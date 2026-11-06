#include <iostream>
#include <iomanip>
using namespace std;

void freespace(int*** img, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] (*img)[i];
        (*img)[i] = nullptr;
    }
    delete[] *img;
    *img = nullptr;
}

void show_image(int** image, int rows, int cols) {
    string** cimage = new string*[rows];

    for (int i = 0; i < rows; ++i) {
        cimage[i] = new string[cols];
    }

    cout << "Зображення " << rows << " x " << cols << ":" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++){
            switch (image[i][j]) {
                case 0:
                    cimage[i][j]=" ";
                    break;
                case 1: 
                    cimage[i][j]=".";
                    break;
                case 2: 
                    cimage[i][j]=":";
                    break;
                case 3: 
                    cimage[i][j]="-";
                    break;
                case 4: 
                    cimage[i][j]="=";
                    break;
                case 5: 
                    cimage[i][j]="+";
                    break;
                case 6: 
                    cimage[i][j]="*";
                    break;
                case 7: 
                    cimage[i][j]="#";
                    break;
                case 8: 
                    cimage[i][j]="%";
                    break;
                case 9: 
                    cimage[i][j]="@";
                    break;
            }
        }
    
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++){
            cout << cimage[i][j];
        }
        cout << endl;
    }
    for (int i = 0; i < rows; i++) {
        delete[] cimage[i];
    }
    
    delete[] cimage;
}

void findExtremes(int** img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    minRow = maxRow = 0;
    minCol = maxCol = 0;
    int min = img[0][0];
    int max = img[0][0];

    for (int i = 0; i < rows; i++) {
        int* row = img[i];
        for (int j = 0; j < cols; j++) {
            if (*(row + j) < min) {
                min = *(row + j);
                minRow = i;
                minCol = j;
            }
            if (*(row + j) > max) {
                max = *(row + j);
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void StatsBrightness(int** img, int rows, int cols) {
    int minRow, minCol, maxRow, maxCol;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

    cout << "Найтемніший піксель: " << img[minRow][minCol] << " (рядок " << minRow+1 << ", стовпець " << minCol+1 << ")\n";
    cout << "Найсвітліший піксель: " << img[maxRow][maxCol] << " (рядок " << maxRow+1 << ", стовпець " << maxCol+1 << ")\n";

    double sum = 0.0;
    for (int i = 0; i < rows; i++) {
        int* row = img[i];
        for (int j = 0; j < cols; j++){
            sum += *(row + j);
        }
    }

    cout << fixed << setprecision(2);
    cout << "Середня яскравість: " << sum/(rows*cols) << endl;

    cout << fixed << setprecision(1);
    cout << "Середня по рядках:";
    for (int i = 0; i < rows; i++) {
        int* row = img[i];
        double sumRow = 0;
        for (int j = 0; j < cols; j++) {
             sumRow += *(row + j);
        }
        cout << ' ' << sumRow/cols;
    }
    cout << endl;
}   

void invertBrightness(int** img, int rows, int cols) {
    cout << "Яскравість інвертовано." << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img[i][j] = 9 - img[i][j];
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j] << " ";
        }
    cout << endl;
    }
}

void swapPixels(int *a, int *b) {
    int intervar = *a;
    *a = *b;
    *b = intervar;
}

void mirroring(int** img, int rows, int cols) {
    cout << "Зображення віддзеркалено." << endl;
    cout << "Початкове :" << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j] << " ";
        }
    cout << endl;
    }
    cout << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&img[i][j], &img[i][cols - j - 1]);
        }
    }

    cout << "Результат:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}



int** rotateRight(int** img, int rows, int cols) {
    int** rotated = new int*[cols];
    for (int i = 0; i < cols; ++i) {
        rotated[i] = new int[rows];
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            rotated[j][rows - 1 - i] = img[i][j];
        }
    }

    freespace(&img, rows);

    return rotated;
}

int main() {
    int rows, cols;

    cout << "Введіть висоту зображення (від 1 до 20 пікселів): ";
    cin >> rows;
    if (rows < 1 || rows > 20) {
        cout << "Помилка: висота зображення повинна бути від 1 до 20 пікселів\n";
        return 1;
    }

    cout << "Введіть ширину зображення (від 1 до 20 пікселів): ";
    cin >> cols;
    if (cols < 1 || cols > 20) {
        cout << "Помилка: ширина зображення повинна бути від 1 до 20 пікселів\n";
        return 1;
    }

    int** image = new int*[rows];

    // 2. Виділення пам'яті для кожного рядка
    for (int i = 0; i < rows; ++i) {
        image[i] = new int[cols];
    }

    cout << "Яскравість пікселів (0..9):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> image[i][j];
            if (image[i][j] < 0 || image[i][j] > 9){
                cout << "Помилка : число має бути від 0 до 9\n";
                return 1;
            }
        }
    }

    int choice=0;
    do {
        cout << "=== МЕНЮ ===" << endl;
        cout << "1. Показати зображення" << endl;
        cout << "2. Статистика яскравості" << endl;
        cout << "3. Інвертувати яскравість" << endl;
        cout << "4. Віддзеркалити по горизонталі" << endl;
        cout << "5. Повернути на 90 градусів праворуч" << endl;
        cout << "0. Вихід" << endl;
        
        input:
            cout << "Виберіть опцію: ";
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(1000, '\n');
                choice = -1;
            }

        switch (choice) {
            case 1:
                show_image(image, rows, cols);
                break;
            case 2:
                StatsBrightness(image, rows, cols);
                break;
            case 3:
                invertBrightness(image, rows, cols);
                break;
            case 4:
                mirroring(image, rows, cols);
                break;
            case 5:
                image = rotateRight(image, rows, cols);
                swap(rows, cols);
                cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        cout << image[i][j] << " ";
                    }
                    cout << endl;
                }
                cout << endl << endl;
                break;
            case 0:
                freespace(&image, rows);
                cout << "Вихід з програми." << endl;
                break;
            default:
                cout << "Невірний вибір. Спробуйте ще раз." << endl;
                goto input;
        }
    } while (choice != 0);
    return 0;
}
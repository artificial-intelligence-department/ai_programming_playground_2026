#include <iostream>
#include <iomanip>

using namespace std;

bool invalid_input(int &value, int min, int max, bool single = true) {
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        return true;
    }
 
    int next = cin.peek();
    if (next != EOF && next != ' ' && next != '\t' && next != '\r' && next != '\n') {
        cin.ignore(1000, '\n');
        return true;
    }
 
    if (single) {
        while (next == ' ' || next == '\t' || next == '\r') {
            cin.get();
            next = cin.peek();
        }
        if (next != '\n' && next != EOF) {
            cin.ignore(1000, '\n');
            return true;
        }
    }
 
    return (value < min || value > max);
}

int** create_image(int rows, int cols) {
    int **img = new int*[rows];

    for (int i = 0; i < rows; i++) img[i] = new int[cols];
    
    return img;
}

void clear_memory(int** &img, int rows) {
    if (img == nullptr) return;
    for (int i = 0;i < rows; i++){
        delete[] img[i];
        img[i] = nullptr;
    }
    delete[] img;
    img = nullptr;
}

bool input_image(int **&img, int &rows, int &cols) {
    cout << "Висота зображення: ";
    if (invalid_input(rows, 1, 20)) {
        cout << "Помилка: висота має бути цілим числом від 1 до 20." << endl;
        return false;
    }

    cout << "Ширина зображення: ";
    if (invalid_input(cols, 1, 20)) {
        cout << "Помилка: ширина має бути цілим числом від 1 до 20." << endl;
        return false;
    }

    img = create_image(rows, cols);

    cout << "Яскравість пікселів (0..9): " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (invalid_input(img[i][j], 0, 9, (i == rows -1 && j == cols - 1))) {
                cout << "Помилка: яскравість має бути цілим числом від 0 до 9." << endl;
                clear_memory(img, rows);
                return false;
            }
        }
    }
    return true;
}

void show_image(int** img, int rows, int cols) {
    const char pixels[] = " .:-=+*#%@";

    cout << "Зображення " << rows << " x " << cols << ":" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j] << " ";
        }
        cout << endl;
    }

    cout << "==========================================" << endl;
    cout << "Малюнок:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << pixels[img[i][j]];
        }
        cout << endl;
    }
}

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol) {
    minRow = minCol = maxRow = maxCol = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (img[i][j] < img[minRow][minCol]) {
                minRow = i;
                minCol = j;
            }
            if (img[i][j] > img[maxRow][maxCol]) {
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void show_stats(int** img, int rows, int cols) {
    int minr, minc, maxr, maxc;
    findExtremes(img, rows, cols, minr, minc, maxr, maxc);

    int* pminr = img[minr];
    int* pmaxr = img[maxr];
    cout << "Найтемніший піксель: " << *(pminr + minc)
         << " (рядок " << minr + 1 << ", стовпець " << minc + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << *(pmaxr + maxc)
         << " (рядок " << maxr + 1 << ", стовпець " << maxc + 1 << ")" << endl;

    double *row_average = new double[rows];
    int total_sum = 0;
    for (int i = 0; i < rows; i++) {
        int *row = img[i];
        int sum_in_row = 0;
        for (int j = 0; j < cols; j++) {
            sum_in_row += *(row + j);
        }
        total_sum += sum_in_row;
        row_average[i] = (double)sum_in_row / cols;
    }

    cout << fixed << setprecision(2);
    cout << "Середня яскравість: " << (double)total_sum / (rows * cols) << endl;
    cout << "Середня по рядках: ";
    cout << fixed << setprecision(1);
    for (int i = 0; i < rows; i++) {
        cout << *(row_average + i) << " ";
    }
    cout << endl;

    delete[] row_average;
    row_average = nullptr;

}

void invert_image(int **img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img[i][j] = 9 - img[i][j];
        }
    }
}

void swapPixels(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void mirror_image(int **img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }
}

int** rotateRight(int **img, int rows, int cols) {
    int **rotated_img = create_image(cols, rows);
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            rotated_img[i][j] = img[rows - j -1][i];
        }
    }
    clear_memory(img, rows);
    return rotated_img;
}

void print_menu() {
    cout << "=============== Меню =================" << endl;
    cout << "1 - Показати зображення" << endl;
    cout << "2 - Статистика яскравості" << endl;
    cout << "3 - Інвертувати яскравість" << endl;
    cout << "4 - Віддзеркалити по горизонталі " << endl;
    cout << "5 - Повернути на 90 градусів праворуч " << endl;
    cout << "0 - Вийти " << endl;
    cout << "======================================" << endl;
    cout << "Ваш вибір: ";
}

void run_main(int **&img, int &rows, int &cols) {
    int choice = -1;

    do {
        print_menu();
        if (invalid_input(choice, 0, 5)) {
            cout << "Помилка: виберіть пункт меню від 0 до 5." << endl;
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1:
                show_image(img, rows, cols);
                break;
            case 2:
                show_stats(img, rows, cols);
                break;
            case 3:
                invert_image(img, rows, cols);
                cout << "Яскравість інвертовано." << endl;
                show_image(img, rows, cols);
                break;
            case 4:
                mirror_image(img, rows, cols);
                cout << "Зображення віддзеркалено." << endl;
                show_image(img, rows, cols);
                break;
            case 5:
                img = rotateRight(img, rows, cols);
                swap(rows, cols);
                cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
                show_image(img, rows, cols);
                break;
            case 0:
                cout << "Роботу програми завершено." << endl;
                break;
        }
    } while (choice != 0);
}

int main () {
    int **img = nullptr;
    int rows = 0, cols = 0;

    if (!input_image(img, rows, cols)) {
        return 1;
    }

    run_main(img, rows, cols);
    clear_memory(img, rows);
}
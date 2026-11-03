#include <iostream>
#include <iomanip>
using namespace std;

void showImage(int** img, int rows, int cols) {
    cout << "Image:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
    const char palette[] = " .:-=+*#%@";
    cout << "Picture:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << palette[img[i][j]];
        }
        cout << endl;
    }
    cout << "Size: " << rows << " x " << cols << endl;
}
void findExtremes(int** img, int rows, int cols,
                  int& minRow, int& minCol,
                  int& maxRow, int& maxCol) {
    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;
    int minValue = *img[0];
    int maxValue = *img[0];
    for (int i = 0; i < rows; i++) {
        int* row = img[i];
        for (int j = 0; j < cols; j++) {
            int value = *(row + j);
            if (value < minValue) {
                minValue = value;
                minRow = i;
                minCol = j;
            }
            if (value > maxValue) {
                maxValue = value;
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void showStatistics(int** img, int rows, int cols) {
    int minRow, minCol, maxRow, maxCol;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);
    int minValue = *(img[minRow] + minCol);
    int maxValue = *(img[maxRow] + maxCol);
    cout << "Darkest pixel: " << minValue
         << " (row " << minRow + 1
         << ", column " << minCol + 1 << ")" << endl;
    cout << "Brightest pixel: " << maxValue
         << " (row " << maxRow + 1
         << ", column " << maxCol + 1 << ")" << endl;
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        int* row = img[i];
        for (int j = 0; j < cols; j++) {
            sum += *(row + j);
        }
    }
    double average = sum * 1.0 / (rows * cols);
    cout << "Average brightness: "
         << fixed << setprecision(2) << average << endl;
    cout << "Average per row: ";
    for (int i = 0; i < rows; i++) {
        int rowSum = 0;
        int* row = img[i];
        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j);
        }
        double rowAverage = rowSum * 1.0 / cols;
        if (i > 0) {
            cout << " ";
        }
        cout << fixed << setprecision(1) << rowAverage;
    }

    cout << endl;
}
void invertImage(int** img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img[i][j] = 9 - img[i][j];
        }
    }
    cout << "Brightness inverted." << endl;
}
void swapPixels(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void mirrorImage(int** img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }
    cout << "Image mirrored." << endl;
}
int** rotateRight(int** img, int rows, int cols) {
    int** rotated = new int*[cols];
    for (int i = 0; i < cols; i++) {
        rotated[i] = new int[rows];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            rotated[j][rows - 1 - i] = img[i][j];
        }
    }
    for (int i = 0; i < rows; i++) {
        delete[] img[i];
        img[i] = nullptr;
    }
    delete[] img;
    img = nullptr;
    return rotated;
}
int main() {
    int rows, cols;
    int** img = nullptr;
    cout << "Enter rows: ";
    cin >> rows;
    cout << "Enter cols: ";
    cin >> cols;
    if (!cin || rows < 1 || rows > 20 || cols < 1 || cols > 20) {
        cout << "Invalid image size!" << endl;
        return 1;
    }
    img = new int*[rows];
    for (int i = 0; i < rows; i++) {
        img[i] = new int[cols];
    }
    bool validPixels = true;
    cout << "Enter pixel brightness (0-9):" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> img[i][j];
            if (!cin || img[i][j] < 0 || img[i][j] > 9) {
                validPixels = false;
                break;
            }
        }
        if (!validPixels) {
            break;
        }
    }
    if (!validPixels) {
        cout << "Invalid pixel brightness!" << endl;
    }
    if (validPixels) {
        int choice = 0;
        do {
            cout << "1. Show image" << endl;
            cout << "2. Brightness statistics" << endl;
            cout << "3. Invert brightness" << endl;
            cout << "4. Mirror horizontally" << endl;
            cout << "5. Rotate 90 degrees right" << endl;
            cout << "0. Exit" << endl;
            cout << "Choose an operation: ";
            cin >> choice;
            if (!cin) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input!" << endl;
                choice = -1;
                continue;
            }
            if (choice < 0 || choice > 5) {
                cout << "Invalid choice!" << endl;
                continue;
            }
            if (choice == 1) {
                showImage(img, rows, cols);
            }
            else if (choice == 2) {
                showStatistics(img, rows, cols);
            }
            else if (choice == 3) {
                invertImage(img, rows, cols);
            }
            else if (choice == 4) {
                mirrorImage(img, rows, cols);
            }
            else if (choice == 5) {
                img = rotateRight(img, rows, cols);
    int temp = rows;
    rows = cols;
    cols = temp;
    cout << "Image rotated. New size: "
         << rows << " x " << cols << endl;
    showImage(img, rows, cols);
}
        } while (choice != 0);
    }
    for (int i = 0; i < rows; i++) {
        delete[] img[i];
        img[i] = nullptr;
    }
    delete[] img;
    img = nullptr;

    return 0;
}
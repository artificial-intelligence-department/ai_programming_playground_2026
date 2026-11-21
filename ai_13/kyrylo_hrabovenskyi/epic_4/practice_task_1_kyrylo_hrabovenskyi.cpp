#include <iostream>
#include <iomanip>

using namespace std;

// Character palette (0 - space, 9 - '@')
const char PALETTE[] = " .:-=+*#%@";

// Function to clear input stream in case of invalid input
void clearInput() {
    cin.clear();
    while (cin.get() != '\n');
}

// 1. Print Image
void printImage(int** img, int rows, int cols) {
    cout << "\n--- Image " << rows << " x " << cols << " ---\n";
    // Numbers output
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << img[i][j] << " ";
        }
        cout << "\n";
    }

    // Palette characters output
    cout << "\nPicture:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << PALETTE[img[i][j]];
        }
        cout << "\n";
    }
    cout << "------------------------\n";
}

// 2. Brightness Statistics
void findExtremes(int** img, int rows, int cols, int& minRow, int& minCol, int& maxRow, int& maxCol) {
    int minVal = 10;
    int maxVal = -1;

    for (int i = 0; i < rows; i++) {
        int* row = img[i]; // Traverse row via pointer as per requirements
        for (int j = 0; j < cols; j++) {
            int current = *(row + j);
            if (current < minVal) {
                minVal = current;
                minRow = i;
                minCol = j;
            }
            if (current > maxVal) {
                maxVal = current;
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void showStatistics(int** img, int rows, int cols)
{
    int minRow = 0, minCol = 0, maxRow = 0, maxCol = 0;
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

    cout << "\nDarkest pixel: " << img[minRow][minCol] << " (row " << minRow + 1 << ", column " << minCol + 1 << ")\n";
    cout << "Brightest pixel: " << img[maxRow][maxCol] << " (row " << maxRow + 1 << ", column " << maxCol + 1 << ")\n";

    double totalSum = 0;
    cout << "Average by rows: ";
    for (int i = 0; i < rows; i++) {
        int* row = img[i];
        double rowSum = 0;
        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j);
        }
        totalSum += rowSum;
        cout << fixed << setprecision(1) << (rowSum / cols) << " ";
    }
    cout << "\nAverage brightness: " << fixed << setprecision(2) << (totalSum / (rows * cols)) << "\n";
}

// 3. Invert Brightness
void invertBrightness(int** img, int rows, int cols)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img[i][j] = 9 - img[i][j];
        }
    }
    cout << "\nBrightness inverted.\n";
}

// 4. Mirror Horizontally
void swapPixels(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void mirrorHorizontal(int** img, int rows, int cols)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }
    cout << "\nImage mirrored horizontally.\n";
}

// 5. Rotate 90 Degrees Clockwise
int** rotateRight(int** img, int& rows, int& cols)
{
    // Create a new matrix with swapped sizes
    int** newImg = new int* [cols];
    for (int i = 0; i < cols; i++) {
        newImg[i] = new int[rows];
    }

    // Pixel transfer
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newImg[j][rows - 1 - i] = img[i][j];
        }
    }

    // Free old memory
    for (int i = 0; i < rows; i++) {
        delete[] img[i];
    }
    delete[] img;

    // Update dimensions directly via references
    int temp = rows;
    rows = cols;
    cols = temp;

    cout << "\nImage rotated.\n";
    return newImg;
}

// 6. Free dynamic memory
void freeImage(int**& img, int rows) {
    if (img != nullptr) {
        for (int i = 0; i < rows; i++) {
            delete[] img[i];
            img[i] = nullptr;
        }
        delete[] img;
        img = nullptr;
    }
}

int main() {
    int rows = 0, cols = 0;

    // Size validation
    while (true) {
        cout << "Image height (1..20): ";
        if (cin >> rows && rows >= 1 && rows <= 20) break;
        cout << "Error! Enter an integer from 1 to 20.\n";
        clearInput();
    }

    while (true) {
        cout << "Image width (1..20): ";
        if (cin >> cols && cols >= 1 && cols <= 20) break;
        cout << "Error! Enter an integer from 1 to 20.\n";
        clearInput();
    }

    // Dynamic memory allocation
    int** image = new int* [rows];
    for (int i = 0; i < rows; i++) {
        image[i] = new int[cols];
    }

    // Pixels input
    cout << "Enter pixel brightness (" << rows << " rows of " << cols << " numbers from 0 to 9):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            while (true) {
                if (cin >> image[i][j] && image[i][j] >= 0 && image[i][j] <= 9) {
                    break;
                }
                cout << "Error in pixel [" << i + 1 << "][" << j + 1 << "]! Must be a number from 0 to 9. Try again: ";
                clearInput();
            }
        }
    }

    int choice;
    do {
        cout << "\n=== MENU ===\n"
            << "1. Show image\n"
            << "2. Brightness statistics\n"
            << "3. Invert brightness\n"
            << "4. Mirror horizontally\n"
            << "5. Rotate 90 degrees right\n"
            << "0. Exit\n"
            << "Your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid choice! Please choose a number from the menu.\n";
            clearInput();
            choice = -1;
            continue;
        }

        switch (choice) {
        case 1:
            printImage(image, rows, cols);
            break;
        case 2:
            showStatistics(image, rows, cols);
            break;
        case 3:
            invertBrightness(image, rows, cols);
            break;
        case 4:
            mirrorHorizontal(image, rows, cols);
            break;
        case 5:
            image = rotateRight(image, rows, cols);
            break;
        case 0:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "No such menu item!\n";
            break;
        }
    } while (choice != 0);

    freeImage(image, rows);
    return 0;
}
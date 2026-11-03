/*
 * Task: Class Practice Work - Monochrome Image Editor
 * Author: Davyd Bahatskyi
 * Group: AI-14
 */

#include <iostream>
#include <limits>
#include <print>
#include <utility>

const char PALETTE[] = " .:-=+*#%@";

int read_val(const std::string &prompt, int min_val, int max_val,
             bool isprompt = true) {
  int value;
  while (true) {
    if (isprompt) {
      std::print("{}({} to {}): ", prompt, min_val, max_val);
    }
    if (std::cin >> value && value <= max_val && value >= min_val) {
      return value;
    } else {
      std::println("Error: input must be from {} to {}", min_val, max_val);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}

int **newImage(int rows, int cols) {
  int **img = new int *[rows];
  for (int i = 0; i < rows; ++i) {
    img[i] = new int[cols];
  }
  return img;
}

void delImage(int **&img, int rows) {
  if (img != nullptr) {
    for (int i = 0; i < rows; ++i) {
      delete[] img[i];
      img[i] = nullptr;
    }
    delete[] img;
    img = nullptr;
  }
}

void swapPixels(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void showImage(int **img, int rows, int cols) {
  std::println("\nImage {}x{}:", rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      std::print("{}{}", img[i][j], (j + 1 == cols ? "" : " "));
    }
    std::println();
  }

  std::println("\nDrawing:");
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      std::print("{}", PALETTE[img[i][j]]);
    }
    std::println();
  }
  std::println("Current dimensions: {}x{}", rows, cols);
}

void findExtremes(int **img, int rows, int cols, int &minRow, int &minCol,
                  int &maxRow, int &maxCol) {
  int minVal = 10;
  int maxVal = -1;

  for (int i = 0; i < rows; ++i) {
    int *row = img[i];
    for (int j = 0; j < cols; ++j) {
      int val = *(row + j);
      if (val < minVal) {
        minVal = val;
        minRow = i + 1; // 1-based indexing for display
        minCol = j + 1;
      }
      if (val > maxVal) {
        maxVal = val;
        maxRow = i + 1;
        maxCol = j + 1;
      }
    }
  }
}

void showStatistics(int **img, int rows, int cols) {
  int minRow = 1, minCol = 1, maxRow = 1, maxCol = 1;
  findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

  int minVal = img[minRow - 1][minCol - 1];
  int maxVal = img[maxRow - 1][maxCol - 1];

  std::println();
  std::println("Darkest pixel: {} (row {}, col {})", minVal, minRow, minCol);
  std::println("Brightest pixel: {} (row {}, col {})", maxVal, maxRow, maxCol);

  double totalSum = 0.0;
  double *rowAverages = new double[rows];

  for (int i = 0; i < rows; ++i) {
    int *row = img[i];
    double rowSum = 0.0;
    for (int j = 0; j < cols; ++j) {
      rowSum += *(row + j); // Mandatory pointer traversal
    }
    rowAverages[i] = rowSum / cols;
    totalSum += rowSum;
  }

  std::println("Average brightness: {:.2f}", totalSum / (rows * cols));

  std::print("Row averages: ");
  for (int i = 0; i < rows; ++i) {
    std::print("{:.1f} ", rowAverages[i]);
  }
  std::println();

  delete[] rowAverages;
}

void invertImage(int **img, int rows, int cols) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      img[i][j] = 9 - img[i][j];
    }
  }
  // std::println("\nBrightness inverted successfully.");
}

void flipHorizontal(int **img, int rows, int cols) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols / 2; ++j) {
      swapPixels(&img[i][j], &img[i][cols - 1 - j]);
    }
  }
  // std::println("\nImage mirrored horizontally.");
}

int **rotateRight(int **img, int rows, int cols) {
  int **newImg = newImage(cols, rows);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      newImg[j][rows - 1 - i] = img[i][j];
    }
  }

  delImage(img, rows);
  return newImg;
}

int main() {
  int rows = 0, cols = 0;

  cols = read_val("Enter image width", 1, 20);
  rows = read_val("Enter image height", 1, 20);

  int **img = newImage(rows, cols);

  std::println("Enter pixels brightness (0..9) for {}x{}:", cols, rows);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      img[i][j] = read_val("Enter pixel brightness", 0, 9, false);
    }
  }

  int choice = -1;
  while (true) {
    std::println("1. Show image");
    std::println("2. Brightness statistics");
    std::println("3. Invert brightness");
    std::println("4. Mirror horizontally");
    std::println("5. Rotate 90 deg clockwise");
    std::println("0. Exit");

    choice = read_val("Select operation", 0, 5);

    switch (choice) {
    case 1: {
      showImage(img, rows, cols);
      break;
    }
    case 2: {
      showStatistics(img, rows, cols);
      break;
    }
    case 3: {
      invertImage(img, rows, cols);
      break;
    }
    case 4: {
      flipHorizontal(img, rows, cols);
      break;
    }
    case 5: {
      img = rotateRight(img, rows, cols);
      std::swap(rows, cols);
      std::println("\nImage rotated. New dimensions: {} x {}", rows, cols);
      break;
    }
    case 0: {
      std::println("Exiting program...");
      delImage(img, rows);
      return 0;
    }
    default: {
      std::println("Error: unknown menu option.");
      break;
    }
    }
  }
}

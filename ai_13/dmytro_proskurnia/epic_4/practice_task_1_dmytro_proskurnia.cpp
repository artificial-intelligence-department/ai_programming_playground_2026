//Проскурня Дмитро ШІ-13
//Редактор Монохромного Зображення

#include <iostream>
#include <iomanip>

void printMatrix(const int* const* matrix, int n, int m);
void showImage(const int* const* image, int n, int m);
void brightnessStatistics(const int* const* image, int n, int m,
                          int& min_row, int& min_col, int& max_row, int& max_col);
void invertBrightness(int** image, int n, int m);
void reflectImage(int** image, int n, int m);
void rotate(int**& image, int& n, int& m);
void exit(int**& image, int n, int m);

int main() {
    std::cout << "Висота зображення: ";
    int n{};
    std::cin >> n;
    if(n <= 0 || n > static_cast<int>(1e4)) {
        std::cout << "Висота мусить бути числом від 1 до 10000" << std::endl;
        return 1;
    }

    std::cout << "Ширина зображення: ";
    int m{};
    std::cin >> m;
    if (m <= 0 || m > static_cast<int>(1e4)) {
        std::cout << "Ширина мусить бути числом від 1 до 10000" << std::endl;
        return 1;
    }

    int** image = new int* [n]; //створюємо динамічну матрицю
    for (int i = 0; i < n; i++) {
        image[i] = new int[m];
    }

    std::cout << "Яскравість пікселів (0..9):" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> image[i][j];
            if (image[i][j] < 0 || image[i][j] > 9) {
                std::cout << "Елементом зображення має бути число від 0 до 9" << std::endl;
                return 1;
            }
        }
    }

    do {
        int action{};
        std::cout << "1 Показати зображення"               << std::endl;
        std::cout << "2 Статистика яскравості"             << std::endl;
        std::cout << "3 Інвертувати яскравість"            << std::endl;
        std::cout << "4 Віддзеркалити по горизонталі"      << std::endl;
        std::cout << "5 Повернути на 90 градусів праворуч" << std::endl;
        std::cout << "0 Вийти"                             << std::endl;

        std::cout << "Введіть вашу дію: "                  << std::endl;
        std::cin >> action;
        std::cout << std::endl;
        if (action < 0 || action > 5) {
            std::cout << "Такої дії не існує" << std::endl;
            continue;
        }

        switch (action)
        {
        case 1:
            showImage(image, n, m);
            break;

        case 2:
            int min_row, min_col, max_row, max_col;
            brightnessStatistics(image, n, m, min_row, min_col, max_row, max_col);
            break;

        case 3:
            invertBrightness(image, n, m);
            break;

        case 4:
            reflectImage(image, n, m);
            break;

        case 5:
            rotate(image, n, m);
            break;

        case 0:
            exit(image, n, m);
            std::cout << "Роботу завершено" << std::endl;
            return 0;
            break;

        default:
            break;
        }

        std::cout << std::endl;
    } while (true);


    return 0;
}

void printMatrix(const int* const* matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void showImage(const int* const* image, int n, int m) {
    std::cout << "Зображення " << n << " х " << m << std::endl;
    printMatrix(image, n, m);

    std::string brightness = " .:-=+*#%@";
    std::cout << "Малюнок:" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << brightness[image[i][j]];
        }
        std::cout << std::endl;
    }
}

void brightnessStatistics(const int* const* image, int n, int m,
                          int& min_row, int& min_col, int& max_row, int& max_col) {
    int min_el = **image, max_el = **image;
    min_row = 0, min_col = 0, max_row = 0, max_col = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (*(image[i] + j) < min_el) {
                min_el = *(image[i] + j);
                min_row = i, min_col = j;
            }
            if (*(image[i] + j) > max_el) {
                max_el = *(image[i] + j);
                max_row = i, max_col = j;
            }
        }
    }
    min_row++, min_col++, max_row++, max_col++;

    double* average_col = new double[n];
    double average = 0;
    for (int i = 0; i < n; i++) {
        average_col[i] = 0;
        for (int j = 0; j < m; j++) {
            average_col[i] += *(image[i] + j);
            average += *(image[i] + j);
        }
        average_col[i] /= m;
    }

    average /= (n * m);

    std::cout << "Найтемніший піксель: " << max_el << " (рядок "  << max_row << ", стовпець "
                                                                  << max_col << ")" << std::endl;
    std::cout << "Найсвітліший піксель: " << min_el << " (рядок " << min_row << ", стовпець "
                                                                  << min_col << ")" << std::endl;

    std::cout << std::fixed << std::setprecision(2) << "Середня яскравість: " << average << std::endl;
    std::cout << "Середня по рядках: ";
    for (int i = 0; i < n; i++) {
        std::cout << std::fixed << std::setprecision(2) << average_col[i] << " ";
    }
    std::cout << std::endl;

    delete[] average_col;
}

void invertBrightness(int** image, int n, int m) {
    std::cout << "Яскравість інвертовано" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            image[i][j] = 9 - image[i][j];
        }
    }

    printMatrix(image, n, m);
}

void reflectImage(int** image, int n, int m) {
    std::cout << "Зображення віддзеркалено" << std::endl;
    std::cout << "Початкове:" << std::endl;
    printMatrix(image, n, m);

    std::cout << std::endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m / 2; j++) {
            std::swap(image[i][j], image[i][m - j - 1]);
        }
    }

    std::cout << "Результат:" << std::endl;
    printMatrix(image, n, m);
}

void rotate(int**& image, int& n, int& m) {
    int** new_image = new int* [m];
    for (int i = 0; i < m; i++) {
        new_image[i] = new int[n] {};
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            new_image[j][n - i - 1] = image[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        delete[] image[i];
    }
    delete[] image;
    image = nullptr;

    image = new_image;
    std::swap(m, n);

    new_image = nullptr;

    std::cout << "Зображення повернуто. Нові розміри:" << n << " x " << m << std::endl;
    printMatrix(image, n, m);
}

void exit(int**& image, int n, int m) {
    for (int i = 0; i < n; i++) {
        delete[] image[i];
    }

    delete[] image;
}

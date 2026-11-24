#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_SIZE = 20;        // Обмеження за розміром захищає масив від занадто великих виділень пам'яті
const int MAX_BRIGHTNESS = 9;   // 9 є верхньою межею яскравості пікселів.

// Позиція символу в палітрі дорівнює яскравості пікселя (0..9)
const char PALETTE[] = " .:-=+*#%@";

// Створює масив рядків і нулями заповнює всі пікселі
int** createImage(int rows, int cols) {
    int** img = new int*[rows];

    for (int i = 0; i < rows; i++) {
        img[i] = new int[cols]();
    }

    return img;
}

// Спочатку звільняє рядки, потім масив вказівників
void deleteImage(int**& img, int rows) {
    if (img == nullptr) {
        return;
    }

    // Спочатку рядки: після delete[] img адреси рядків уже не прочитати
    for (int i = 0; i < rows; i++) {
        delete[] img[i];
        img[i] = nullptr;
    }

    delete[] img;
    img = nullptr;
}

// Перевіряє розмір: ціле число від 1 до MAX_SIZE
bool inputSize(const char* message, int& value) {
    cout << message;
    cin >> value;

    if (cin.fail()) {
        cout << "Помилка: потрібно ввести ціле число." << endl;
        return false;
    }

    if (value < 1 || value > MAX_SIZE) {
        cout << "Помилка: розмір має бути від 1 до " << MAX_SIZE << "." << endl;
        return false;
    }

    return true;
}

// Заповнює пікселі рядок за рядком
bool inputImage(int** img, int rows, int cols) {
    cout << "Яскравість пікселів (0.." << MAX_BRIGHTNESS << "):" << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int value;
            cin >> value;

            if (cin.fail()) {
                cout << "Помилка: яскравість має бути цілим числом." << endl;
                return false;
            }

            if (value < 0 || value > MAX_BRIGHTNESS) {
                cout << "Помилка: яскравість має бути від 0 до "
                     << MAX_BRIGHTNESS << "." << endl;
                return false;
            }

            img[i][j] = value;
        }
    }

    return true;
}

// Виводить числову матрицю по одному рядку за раз
void showTable(int** img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j > 0) {
                cout << " ";
            }
            cout << img[i][j];
        }
        cout << endl;
    }
}

// Пункт 1: одночасно друкує поточні числові дані і їхній символьний вигляд
// Кожне число індексує палітру PALETTE, тому в малюнку світліші пікселі мають густішу позначку
void showImage(int** img, int rows, int cols) {
    cout << "\nЗображення " << rows << " x " << cols << ":" << endl;
    showTable(img, rows, cols);

    cout << "\nМалюнок:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << PALETTE[img[i][j]];
        }
        cout << endl;
    }
}

// Одна функція повертає чотири числа через параметри-посилання
// Знаки < і > строгі: рівне значення не замінює вже знайдене, тому залишається перше в порядку обходу по рядках
void findExtremes(int** img, int rows, int cols,int& minRow, int& minCol, int& maxRow, int& maxCol) {
    int minValue = *(img[0]);
    int maxValue = minValue;

    minRow = 0;
    minCol = 0;
    maxRow = 0;
    maxCol = 0;

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

// Пункт 2: обчислює координати мінімуму й максимуму, загальне середнє та середнє кожного рядка
// Для статистики масив читається через вказівники на рядки й арифметику адрес: int* row = img[i],тоді піксель номер j у поточному рядку отримується виразом *(row + j)
void showStatistics(int** img, int rows, int cols) {
    int minRow, minCol, maxRow, maxCol;
        
    findExtremes(img, rows, cols, minRow, minCol, maxRow, maxCol);

    // Усередині програми індекси з нуля, користувачу показуємо з одиниці
    int* minRowPtr = img[minRow];
    int* maxRowPtr = img[maxRow];

    cout << "\nНайтемніший піксель: " << *(minRowPtr + minCol)
         << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найсвітліший піксель: " << *(maxRowPtr + maxCol)
         << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;

    // Суми спочатку зберігаються в int, щоб не втрачати точність під час накопичення
    int total = 0;
    double* rowAverage = new double[rows];

    for (int i = 0; i < rows; i++) {
        int* row = img[i];
        int rowSum = 0;

        for (int j = 0; j < cols; j++) {
            rowSum += *(row + j);
        }

        rowAverage[i] = static_cast<double>(rowSum) / cols;
        total += rowSum;
    }

    cout << fixed << setprecision(2);
    cout << "Середня яскравість: "
         << static_cast<double>(total) / (rows * cols) << endl;

    cout << setprecision(1);
    cout << "Середня по рядках:" << endl;
    for (int i = 0; i < rows; i++) {
        cout << "Рядок " << i + 1 << ": " << *(rowAverage + i) << endl;
    }

    delete[] rowAverage;
    rowAverage = nullptr;
}

// Пункт 3: інвертує яскравість за формулою 9 - поточне_значення
// Функція змінює пікселі напряму в існуючому масиві, тому виділяти нову пам'ять не потрібно
void invertImage(int** img, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img[i][j] = MAX_BRIGHTNESS - img[i][j];
        }
    }

    cout << "Яскравість інвертовано." << endl;
    showTable(img, rows, cols);
}

// Обмін двох пікселів через розіменування адрес
void swapPixels(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Пункт 4: дзеркалить кожен рядок незалежно від решти зображення
// За непарної ширини центральний піксель автоматично не береться в обмін і лишається незмінним
void mirrorImage(int** img, int rows, int cols) {
    cout << "Зображення віддзеркалено." << endl;
    cout << "Початкове:" << endl;
    showTable(img, rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            swapPixels(&img[i][j], &img[i][cols - 1 - j]);
        }
    }

    cout << "Результат:" << endl;
    showTable(img, rows, cols);
}

// Пункт 5: поворот праворуч створює нову матрицю розміром cols x rows.
// Тому спочатку копіюються дані в rotated, а потім видаляється старий масив (запобігає втраті пікселів)
int** rotateRight(int** img, int rows, int cols) {
    int** rotated = createImage(cols, rows);

    // Піксель (i, j) потрапляє в (j, rows - 1 - i): перший рядок початкового зображення стає останнім стовпцем нового
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            rotated[j][rows - 1 - i] = img[i][j];
        }
    }

    // img — копія вказівника, тому обнуляється лише вона
    deleteImage(img, rows);

    return rotated;
}

// Обгортка пункту 5: після повороту висота і ширина міняються місцями
void rotateAndShow(int**& img, int& rows, int& cols) {
    img = rotateRight(img, rows, cols);

    int temp = rows;
    rows = cols;
    cols = temp;

    cout << "Зображення повернуто. Нові розміри: " << rows << " x " << cols << endl;
    showTable(img, rows, cols);
}

void showMenu() {
    cout << "\n===== РЕДАКТОР ЗОБРАЖЕНЬ =====" << endl;
    cout << "1. Показати зображення" << endl;
    cout << "2. Статистика яскравості" << endl;
    cout << "3. Інвертувати яскравість" << endl;
    cout << "4. Віддзеркалити по горизонталі" << endl;
    cout << "5. Повернути на 90 градусів праворуч" << endl;
    cout << "0. Вийти" << endl;
    cout << "Ваш вибір: ";
}

int inputMenuChoice() {
    int choice;

    while (true) {
        cin >> choice;

        if (cin.eof()) {
            return 0;   // ввід закінчився: виходимо
        }

        if (cin.fail()) {
            cin.clear();               
            cin.ignore(1000, '\n');    
            cout << "Це не число. Введіть пункт від 0 до 5: ";
            continue;
        }

        cin.ignore(1000, '\n');        

        if (choice < 0 || choice > 5) {
            cout << "Немає такого пункту. Введіть пункт від 0 до 5: ";
            continue;
        }

        return choice;
    }
}

int main() {
    int rows, cols;

    if (!inputSize("Висота зображення (1-20): ", rows) ||
        !inputSize("Ширина зображення (1-20): ", cols)) {
        return 1;  
    }

    int** img = createImage(rows, cols);

    // Пам'ять уже виділена, тому при помилці вводу звільняємо її перед виходом
    if (!inputImage(img, rows, cols)) {
        deleteImage(img, rows);
        return 1;
    }

    int choice;

    do {
        showMenu();
        choice = inputMenuChoice();

        switch (choice) {
            case 1: showImage(img, rows, cols);      break;
            case 2: showStatistics(img, rows, cols); break;
            case 3: invertImage(img, rows, cols);    break;
            case 4: mirrorImage(img, rows, cols);    break;
            case 5: rotateAndShow(img, rows, cols);  break;
            case 0: cout << "До побачення!" << endl; break;
        }
    } while (choice != 0);

    deleteImage(img, rows);

    return 0;
}
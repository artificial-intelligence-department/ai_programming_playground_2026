/*Практична задача - "Редактор монохромного зображення"
Максімко Павло - СШІ-13*/

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

//Оголошую константи, щоб потім не додавати їх у функції як окремі параметри
const int MAX_IMAGE_BRIGHT = 9;
const int MIN_IMAGE_BRIGHT = 0;

//Прототипи функцій, щоб main міг викликати їх до того як вони визначені нижче
bool check_cin(int num, const int MIN, const int MAX);
void symbol_trans(int a);
void show_brightness(int **image, int rows, int cols);
void show_image(int **image, int rows, int cols);
void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol);
void average_brightness(int **image, int rows, int cols);
void stats_brightness(int **image, int rows, int cols);
void invert(int **image, int rows, int cols);
void swapPixels(int *a, int *b);
void reflect_horizontal(int **image, int rows, int cols);
int** rotateRight(int** image, int rows, int cols);
void memory_clear(int **&image, int rows);

int main()
{
    int rows, cols; 
    //Оголошуємо константи-максимуми для того, щоб можна було швидко змінювати максимуми і мінімуми ширини і висоти
    const int ROWS_MAX = 20;
    const int ROWS_MIN = 1;
    const int COLS_MAX = 20;
    const int COLS_MIN = 1;
    cout << "Введіть висоту пікселів: ";
    cin >> rows;
    if(check_cin(rows, ROWS_MIN, ROWS_MAX))
    {
        cout << "Висота пікселів повинна бути цілим числом від " << ROWS_MIN << " до " << ROWS_MAX << "!" << endl;
        return 1;
    }

    cout << "Введіть ширину пікселів: ";
    cin >> cols;
    if(check_cin(cols, COLS_MIN, COLS_MAX))
    {
        cout << "Ширина пікселів повинна бути цілим числом від " << COLS_MIN << " до " << COLS_MAX << "!" << endl;
        return 1;
    }

    //Створюємо динамічний масив, оскільки не знаємо, скільки елементів повинен мати масив
    int **image = new int*[rows]; 
    for(int i = 0; i < rows; i++)
    {
        //Створюємо для кожного елемента динамічного масиву ще один динамічний масив, 
        //таким чином створюємо двовимірний динамічний масив
        image[i] = new int[cols];
    }

    cout << "Введіть значення яскравості кожного пікселя (від 0 до 9): " << endl;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            cin >> image[i][j];
            if(check_cin(image[i][j], MIN_IMAGE_BRIGHT, MAX_IMAGE_BRIGHT))
            {
                cout << "Значення яскравості повинне бути цілим числом від " << MIN_IMAGE_BRIGHT << " до " << MAX_IMAGE_BRIGHT << "!" << endl;
                //Очищуємо пам'ять, щоб не було її витоку
                memory_clear(image, rows);
                return 1;
            }
        }
    }

    int action;
    do {
        act:cout << "======== МЕНЮ ========" << endl;
        cout << "Дії:" << endl;
        cout << "1 - Показати зображення" << endl;
        cout << "2 - Статистика яскравості" << endl;
        cout << "3 - Інвертувати яскравість" << endl;
        cout << "4 - Віддзеркалити по горизонталі" << endl;
        cout << "5 - Повернути на 90 градусів праворуч" << endl;
        cout << "0 - Вийти" << endl;
        cout << "Введіть дію: ";
        cin >> action;
        if(cin.fail() || (cin.peek() != EOF && !isspace(cin.peek())))
        {
            cout << "Дія повинна бути цілим числом!" << endl;
            //Очищуємо буфер введення, щоб програма не зациклювалася через неправильне введення даних
            cin.clear();
            cin.ignore(1000000, '\n');
            //Перевірка на кінець вводу, щоб програма не ввійшла в нескінченний цикл введення даних та очищення буферу введених даних
            if(cin.eof())
            {
                memory_clear(image, rows);
                return 1;
            }
            goto act;
        }
        switch (action)
        {
        case 1:
            cout << "Ви вибрали дію 1: " << endl; 
            show_image(image, rows, cols);
            break;
        case 2:
            cout << "Ви вибрали дію 2: " << endl; 
            stats_brightness(image, rows, cols);
            break;
        case 3:
            cout << "Ви вибрали дію 3: " << endl; 
            invert(image, rows, cols);
            break;
        case 4:
            cout << "Ви вибрали дію 4: " << endl; 
            reflect_horizontal(image, rows, cols);
            break;
        case 5:
            cout << "Ви вибрали дію 5: " << endl; 
            cout << "------ Перевертання ------" << endl;
            cout << "Зображення перевернуто на 90 градусів праворуч. Нові розміри " << cols << " x " << rows << ":" << endl;
            //Присвоюємо адресу новоутвореного масиву колишньому масиву
            image = rotateRight(image, rows, cols);
            swapPixels(&rows, &cols);
            show_brightness(image, rows, cols);
            break;
        case 0:
            cout << "Ви вибрали дію 0: " << endl;
            cout << "До побачення!" << endl;
            memory_clear(image, rows);
            return 0;
        default:
            cout << "Такої дії не існує!" << endl;
            //Очищуємо буфер введення, щоб програма не зациклювалася через неправильне введення даних
            cin.clear();
            cin.ignore(1000000, '\n');
            goto act;
        }
    }
    while(true);
}

bool check_cin(int num, const int MIN, const int MAX)
{
    return (cin.fail() || num < MIN || num > MAX || (cin.peek() != EOF && !isspace(cin.peek())));
}

void symbol_trans(int a)
{
    switch(a)
    {
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
        default:
            cout << " ";
            break;
    }
    return;
}

void show_brightness(int **image, int rows, int cols)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
    return;
}

void show_image(int **image, int rows, int cols)
{
    cout << "------ Зображення ------" << endl;
    cout << "Зображення розміру " << rows << " x " << cols << ": " << endl;
    show_brightness(image, rows, cols);

    cout << "Малюнок: " << endl;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            symbol_trans(image[i][j]);
        }
        cout << endl;
    }
    return;
}

void findExtremes(int **image, int rows, int cols, int &minRow, int &minCol, int &maxRow, int &maxCol)
{
    //Присвоюємо значення індексів першому елементу масиву
    minCol = 0; 
    minRow = 0;
    maxCol = 0; 
    maxRow = 0;
    //Присвоюємо початкове значення максимуму і мінімуму до першого елемента масиву
    int min = *(image[0]);
    int max = *(image[0]);
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            int *row = image[i];
            if(min > *(row + j))
            {
                min = *(row + j);
                minRow = i;
                minCol = j;
            }
            if(max < *(row + j))
            {
                max = *(row + j);
                maxRow = i;
                maxCol = j;
            }
        }
    }
    return;
}

void average_brightness(int **image, int rows, int cols)
{
    int sum = 0;
    //Створюємо новий динамічний масив для обчислення суми елементів рядка
    int *sum_row = new int[rows];
    for(int i = 0; i < rows; i++)
    {
        *(sum_row + i) = 0;
        for(int j = 0; j < cols; j++)
        {
            int *row = image[i];
            *(sum_row + i) += *(row + j);
            sum += *(row + j);
        }
    }

    //Перетворюємо на тип double значення суми, щоб середнє значення було у double
    double avg = (double)sum / (cols * rows);
    cout << "Середня яскравість: " << fixed << setprecision(2) << avg << endl;

    cout << "Середня яскравість по рядках: ";
    for(int i = 0; i < rows; i++)
    {
        //Перетворюємо на тип double значення суми рядка, щоб середнє значення рядка було у double
        double avg_row = (double)(*(sum_row + i)) / cols;
        cout << fixed << setprecision(1) << avg_row << " ";
    }
    cout << endl;

    //Звільняємо пам'ять на масив та обнулюємо його адресу
    delete[] sum_row;
    sum_row = nullptr;

    return;
}

void stats_brightness(int **image, int rows, int cols)
{
    cout << "------ Статистика ------" << endl;
    int minRow, maxRow;
    int minCol, maxCol;
    findExtremes(image, rows, cols, minRow, minCol, maxRow, maxCol);
    cout << "Найтемніший піксель: " << *(image[minRow] + minCol) << " (рядок " << minRow + 1 << ", стовпець " << minCol + 1 << ")" << endl;
    cout << "Найяскравіший піксель: " << *(image[maxRow] + maxCol) << " (рядок " << maxRow + 1 << ", стовпець " << maxCol + 1 << ")" << endl;
    average_brightness(image, rows, cols);
    return;
}

void invert(int **image, int rows, int cols)
{
    cout << "------ Інвертування ------" << endl;
    cout << "Яскравість інвертовано:" << endl;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            image[i][j] = MAX_IMAGE_BRIGHT - image[i][j];
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
    return;
}

void swapPixels(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
    return;
}

void reflect_horizontal(int **image, int rows, int cols)
{
    cout << "------ Віддзеркалення ------" << endl;

    cout << "До віддзеркалення: " << endl;
    show_brightness(image, rows, cols);

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols / 2; j++)
        {
            //Подаємо адреси та змінюємо елементи одночасно, а не їх копії
            swapPixels(&image[i][j], &image[i][cols - j - 1]);
        }
    }

    cout << "Після віддзеркалення: " << endl;
    show_brightness(image, rows, cols);
    return;
}

int** rotateRight(int** image, int rows, int cols)
{
    //Створюємо новий динамічний масив, після зміни якого його адресу будемо повертати
    int **image_rotated = new int *[cols];
    for(int i = 0; i < cols; i++)
    {
        //Створюємо для кожного елементу динамічного масиву ще свій динамічний масив,
        //таким чином створюємо двовимірний динамічний масив
        image_rotated[i] = new int[rows];
    }

    for(int i = 0; i < cols; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            image_rotated[i][j] = image[rows - j - 1][i];
        }
    }

    for(int i = 0; i < rows; i++)
    {
        //Звільняємо пам'ять для кожного елементу попереднього масиву, щоб уникнути витоку пам'яті
        delete[] image[i];
        //Обнулюємо адресу кожного елемента
        image[i] = nullptr;
    }
    //Звільняємо пам'ять під попередній масив
    delete[] image;

    //Повертаємо адресу нового масиву
    return image_rotated;
}

void memory_clear(int **&image, int rows)
{
    //Для уникнення витоку пам'яті створив окрему функцію для видалення динамічної пам'яті
    for(int i = 0; i < rows; i++)
    {
        //Звільняємо пам'ять для кожного елементу масиву
        delete[] image[i];
        //Обнулюємо кожну адресу кожного елементу масиву
        image[i] = nullptr;
    }
    //Звільняємо динамічну пам'ять
    delete[] image;
    //Обнулюємо адресу динамічного масиву
    image = nullptr;

    return;
}
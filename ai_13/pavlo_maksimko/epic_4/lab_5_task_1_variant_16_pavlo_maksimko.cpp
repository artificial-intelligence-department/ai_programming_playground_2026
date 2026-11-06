/*Лабораторна 5 задача 1 варіант 16
Максімко Павло - СШІ-13*/

#include <iostream>
#include <algorithm>
#include <climits>
#include <cctype>

using namespace std;

//Оголошуємо константи максимум і мінімум для кількості елементів
const int N_MAX = 100;
const int N_MIN = 1;

bool check_validation(int element, const int MAX, const int MIN);
//Використовуємо константу, щоб компілятор міг прочитати розмір рядка у двовимірному масиві
bool can_be_rearanged(int array[][N_MAX], int n);

int main()
{
    int n;
    cout << "Введіть кількість елементів у рядку та стовпцю (одне число): ";
    cin >> n;
    if(check_validation(n, N_MAX, N_MIN))
    {
        cout << "Кількість елементів у рядку та стовпцю повинне бути цілим числом від " << N_MIN << " до " << N_MAX << "!" << endl;
        return 1;
    }

    //Оголошуємо двовимірний масив двома константами, адже стандарт C++ не приймає оголошення масивів змінної довжини (але в деяких компіляторів це є розширенням)
    int array[N_MAX][N_MAX];
    
    cout << "Введіть елементи: " << endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> array[i][j];
            if(check_validation(array[i][j], INT_MAX, INT_MIN))
            {
                cout << "Елемент повинен бути цілим числом!" << endl;
                return 1;
            }
        }
    }

    if(can_be_rearanged(array, n)) 
    {
        cout << "Можна розташувати елементи на бічній діагоналі так, щоб вони зростали." << endl;
        for(int i = 0 ; i < n; i++)
            cout << array[i][n - i - 1] << " ";
        cout << endl;
    }
    else cout << "Не можна." << endl;
    
    return 0;
}

bool check_validation(int element, const int MAX, const int MIN)
{
    return (cin.fail() || element > MAX || element < MIN || (cin.peek() != EOF && !isspace(cin.peek())));
}

bool can_be_rearanged(int array[][N_MAX], int n)
{
    if(n != 1)
    {
        //Початкове значення "попереднього знайденого значення" неважливе, адже ми приймаємо елемент, якщо він є першим елементом бічної діагоналі, або більший від цього знайденого значення
        int previous = 0;
        for(int j = 0; j < n; j++)
        {   
            int best_index = -1;
            for(int i = 0; i < n; i++)
            {
                //Перевіряємо чи елемент є першим елементом бічної діагоналі або чи він більший за "попереднє знайдене значення", щоб знати, чи він підходить
                bool element_fits = (j == 0) || (array[i][n - j - 1] > previous);
                if(element_fits && (best_index == -1 || array[best_index][n - j - 1] > array[i][n - j - 1])) 
                {
                    //Шукаємо індекс найменшого елемента у стовпці, щоб потім поміняти його значення із потрібним елементом у стовпці
                    best_index = i; 
                }
            }
            //Якщо найкращого індекса не існує, то це означає, що елемента, який більший за попереднє знайдене значення немає 
            //і переставити елементи у порядку зростання на бічній діагоналі неможливо
            if(best_index == -1) return false; 
            //Інакше, якщо індекс існує, міняємо значення елементів місцями, щоб сформувати правильну бічну діагональ для масиву 
            swap(array[j][n - j - 1], array[best_index][n - j - 1]);
            //Переприсвоюємо нове значення для "попереднього знайденого значення", щоб пізніше порівнювати наступні елементи до нього
            previous = array[j][n - j - 1];
        }
    }
    return true;
}
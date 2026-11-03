/*Лабораторна 4 задача 1 варіант 16
Максімко Павло - СШІ-13*/

#include <iostream>
#include <cctype>
#include <string>


using namespace std;

//Оголошуємо константи, щоб потім їх використати в коді
const int N_MAX = 100;
const int N_MIN = 1;

//Прототипи функцій, щоб main міг викликати їх до того як вони визначені нижче
void add(const string &element, string queue[], int &n);
void remove(int index, string queue[], int &n);
void show(const string queue[], int n);

int main()
{
    int n; 
    cout << "Введіть людей у черзі: " << endl;
    cin >> n;

    //Перевірка на правильно введений тип даних та на межі введеного значення
    //cin.peek() для перевірки наступного введеного символу (якщо він не пробіл або кінець рядка, то умова виконується і програма закінчується)
    if(cin.fail() || n < N_MIN || n > N_MAX || (cin.peek() != EOF && !isspace(cin.peek())))
    {
        cout << "Кількість людей у черзі - ціле число від " << N_MIN << " до " << N_MAX << "!" << endl;
        return 1;
    }

    //Очищення буферу введення від залишкового елементу '\n' після введення числа n
    cin.ignore(100000, '\n');

    //Оголошуємо масив на константний максимум елементів, адже стандарт C++ не приймає масив зі змінною кількістю елементів
    //Справжня кількість елементів - n, але щоб пізніше можна було додати більшу кількість, береться N_MAX
    cout << "Введіть чергу: " << endl;
    string queue[N_MAX];
    for(int i = 0; i < n; i++)
    {
        getline(cin, queue[i]);
    }
    
    //Щоб не створювати для кожного доданого елементу нову змінну, просто вводимо дані в одну й ту саму змінну
    string element;
    cout << "Додайте людину до черги: ";
    int k = 1;
    //Цикл триватиме поки елементи будуть вводитися або до ctrl + D, або до 20 введених елементів
    while(k <= 20 && getline(cin, element))
    {
        k++;
        cout << "Приходить нова людина " << element << " до черги: " << endl; 
        add(element, queue, n);
        show(queue, n);
        cout << "Перша людина в черзі " << queue[0] << " іде! " << endl;
        remove(0, queue, n);
        show(queue, n);
        if(k <= 20) cout << "Додайте людину до черги: ";
    }
    cout << "У чергу більше не приходили люди!" << endl;
    return 0;
}

//Функція для додавання елемента до масиву
//Оскільки масив створений на максимальну кількість елементів, то доки n != N_MAX, нові вільні комірки будуть використані для доданого елементу
void add(const string &element, string queue[], int &n)
{
    if(n < N_MAX)
    {
        queue[n] = element;
        n++;
        return;
    }
    else
    {
        cout << "Черга переповнена!" << endl;
        return;
    }
   
}

//Функція для видалення елементу із масиву за індексом
//Зсуваємо за індексом вліво всі дані, після чого зменшуємо загальну кількість елементів введених користувачем
void remove(int index, string queue[], int &n)
{
    if(n == 0)
    {
        cout << "Черга закінчилася!" << endl;
        return;
    }
    else if(index > n - 1 || index < 0)
    {
        cout << "Такого індекса не існує!" << endl;
        return;
    }
    for(int i = index; i < n - 1; i++)
    {
        queue[i] = queue[i + 1];
    }
    n--;
    return;
}

//Функція, щоб вивести масив
//Виводимо одним циклом
void show(const string queue[], int n)
{
    cout << "Люди в черзі: " << endl;
    for(int i = 0; i < n; i++)
    {
        cout << queue[i] << " ";
    }
    cout << endl;
    return;
}

/*
Lab 1 task 2, Олексій Рубакха, ШІ-13, Варіант 11
*/

#include <iostream>

using namespace std;

int main()
{
    //оголошення змінних n та m
    int n, m;

    //введення значення n
    cout << "Enter n: ";
    cin >> n;

    //введення значення m
    cout << "Enter m: ";
    cin >> m;

    //виведення початкових значень n та m
    cout << "\nInitial values: n = " << n << ", m = " << m << endl;

    // 1) n++ * m
    // додаєм до змінної n одиницю після використання її значення у виразі та множимо на m
    int result1 = n++ * m;

    //виведення результату та значень n та m після операції
    cout << "\n1) n++ * m" << endl;
    cout << "Result = " << result1 << endl;
    cout << "After operation: n = " << n << ", m = " << m << endl;

    // 2) n++ < m
    // додаєм до змінної n одиницю після використання її значення у виразі та порівнюємо з m
    int result2 = n++ < m;

    //виведення результату та значень n та m після операції
    cout << "\n2) n++ < m" << endl;
    cout << "Result = " << result2 << endl;
    cout << "After operation: n = " << n << ", m = " << m << endl;

    // 3) m-- > m
    // віднімаєм від змінної m одиницю після використання її значення у виразі та порівнюємо з m
    int result3 = m-- > m;

    //виведення результату та значень n та m після операції
    cout << "\n3) m-- > m" << endl;
    cout << "Result = " << result3 << endl;
    cout << "After operation: n = " << n << ", m = " << m << endl;

    return 0;
}
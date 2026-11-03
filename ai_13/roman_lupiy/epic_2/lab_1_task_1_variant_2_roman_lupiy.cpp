/*
Задача: Лабораторна робота 1, завдання 1
Автор: Роман Лупій
Група: ШІ-13
Варіант: 2
*/

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    // Встановлюємо виведення десяти знаків після крапки
    cout << fixed << setprecision(10);

    // Обчислення з типом float
    float aFloat = 1000.0f;
    float bFloat = 0.0001f;

    // Обчислюємо першу частину чисельника: (a - b)²
    float aMinusBFloat = aFloat - bFloat;
    float firstSquareFloat = aMinusBFloat * aMinusBFloat;

    // Обчислюємо другу частину чисельника: a² - 2ab
    float aSquaredFloat = aFloat * aFloat;
    float twoABFloat = 2.0f * aFloat * bFloat;
    float secondPartFloat = aSquaredFloat - twoABFloat;

    // Знаходимо чисельник і знаменник дробу
    float numeratorFloat = firstSquareFloat - secondPartFloat;
    float denominatorFloat = bFloat * bFloat;

    // Обчислюємо та виводимо результат для float
    float resultFloat = numeratorFloat / denominatorFloat;
    cout << "Результат для float: " << resultFloat << '\n';

    // Повторюємо обчислення з типом double
    double aDouble = 1000.0;
    double bDouble = 0.0001;

    // Обчислюємо першу частину чисельника: (a - b)²
    double aMinusBDouble = aDouble - bDouble;
    double firstSquareDouble = aMinusBDouble * aMinusBDouble;

    // Обчислюємо другу частину чисельника: a² - 2ab
    double aSquaredDouble = aDouble * aDouble;
    double twoABDouble = 2.0 * aDouble * bDouble;
    double secondPartDouble = aSquaredDouble - twoABDouble;

    // Знаходимо чисельник і знаменник дробу
    double numeratorDouble = firstSquareDouble - secondPartDouble;
    double denominatorDouble = bDouble * bDouble;

    // Обчислюємо та виводимо результат для double
    double resultDouble = numeratorDouble / denominatorDouble;
    cout << "Результат для double: " << resultDouble << '\n';

    return 0;
}
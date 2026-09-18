/* Задача: Автономність портативної зарядної станції
 * Автор: Швець Аріна
 * Група: ШІ-13 */

#include <iostream>  
#include <string>    
#include <cmath>     

using namespace std;

int main() 
{
    // Змінні для збереження вхідних даних
    string modelStation;
    double capacity;
    int years;
    int charge;
    double efficiency;
    double power;

    // Введення даних та їх валідація
    cout << "Модель станції: ";
    cin >> modelStation;
    if (modelStation.length() > 31) 
    {
        cout << "Помилка" << endl;
        return 1;
    }

    cout << "Ємність: ";
    cin >> capacity;
    if (capacity <= 0 || capacity > 5000) 
    {
        cout << "Помилка" << endl;
        return 1;
    }

    cout << "Вік станції: ";
    cin >> years;
    if (years < 0 || years > 20) 
    {
        cout << "Помилка" << endl;
        return 1;
    }

    cout << "Рівень заряду: ";
    cin >> charge;
    if (charge < 0 || charge > 100) 
    {
        cout << "Помилка" << endl;
        return 1;
    }

    cout << "ККД інвертора: ";
    cin >> efficiency;
    if (efficiency <= 0 || efficiency > 100) 
    {
        cout << "Помилка" << endl;
        return 1;
    }

    cout << "Потужність приладу: ";
    cin >> power;
    if (power <= 0) 
    {
        cout << "Помилка" << endl;
        return 1;
    }

    // Відсоток втрат ємності акумулятора за рік
    const double degradation_rate = 2.0; 

    // 1. Фактична ємність (з урахуванням віку)
    double c_eff = capacity * pow(1.0 - degradation_rate / 100.0, years);

    // 2. Запас енергії при поточному заряді
    double e_stored = c_eff * charge / 100.0;

    // 3. Корисна енергія, що дійде до приладу
    double e_useful = e_stored * efficiency / 100.0;

    // 4. Втрати на перетворенні напруги
    double e_loss = e_stored - e_useful;

    // 5. Загальний час роботи
    double T = e_useful / power;

    // 6. Повні години
    int h = (int)T;

    // 7. Хвилини, що залишились
    int m = (int)((T - h) * 60.0);

    // Виведення результатів
    cout << endl;
    cout << "Модель: " << modelStation << endl;
    cout << "Паспортна ємність: " << capacity << " Вт·год" << endl;
    cout << "Вік станції: " << years << " р." << endl;
    cout << "Фактична ємність: " << c_eff << " Вт·год" << endl;
    cout << "Рівень заряду: " << charge << " %" << endl;
    cout << "ККД інвертора: " << efficiency << " %" << endl;
    cout << "Запас енергії: " << e_stored << " Вт·год" << endl;
    cout << "Корисна енергія: " << e_useful << " Вт·год" << endl;
    cout << "Втрати на перетворенні: " << e_loss << " Вт·год" << endl;
    cout << "Час роботи: " << T << " год  = " << h << " год ";

    // Форматування хвилин з нулем попереду (наприклад, "05 хв")
    if (m < 10) 
    {
        cout << "0";
    }
    cout << m << " хв" << endl;

    return 0;
}
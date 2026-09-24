#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

/*
Автономність портативної зарядки
Група: ШІ-11
Автор: Щербак Орислав
*/

int main() {
    string model;
    double C, P, eff;
    int years, charge;

    // Зчитуємо модель станції
    cout << "Station model: ";
    cin >> model;
    // Назва станції не повинна перевищувати 31 символ
    if (model.length() > 31) {
        cout << "Error, station name cannot be longer than 31 characters." << endl;
        return 1;
    }

    // Зчитуємо паспортну ємність
    cout << "Rated capacity (Wh): ";
    // Якщо введено не число, завершити програму
    if (!(cin >> C)) {
        cout << "Error, rated capacity must be a number." << endl;
        return 1;
    }
    // Ємність повинна бути більше за 0, інакше зарядка не має сенсу
    if (C <= 0) {
        cout << "Error, rated capacity must be greater than 0." << endl;
        return 1;
    }

    // Зчитуємо вік станції
    cout << "Station age (years): ";
    // Якщо введено не ціле число, завершити програму
    if (!(cin >> years)) {
        cout << "Error, station age must be an integer." << endl;
        return 1;
    }
    // Вік обмжений від 0 до 20 років
    if (years < 0 || years > 20) {
        cout << "Error, station age must be between 0 and 20 years." << endl;
        return 1;
    }

    // Зчитуємо рівень заряду
    cout << "Charge level (%): ";
    // Якщо введено не ціле число, завершити програму
    if (!(cin >> charge)) {
        cout << "Error, charge level must be an integer." << endl;
        return 1;
    }
    // Заряд повинен бути в межах від 0 до 100 відсотків
    if (charge < 0 || charge > 100) {
        cout << "Error, charge level must be between 0 and 100." << endl;
        return 1;
    }

    // Зчитуємо ККД інвертора
    cout << "Inverter efficiency (%): ";
    // Якщо введено не число, завершити програму
    if (!(cin >> eff)) {
        cout << "Error, inverter efficiency must be a number." << endl;
        return 1;
    }
    // ККД повинно бути більше 0 і не більше 100
    if (eff <= 0 || eff > 100) {
        cout << "Error, inverter efficiency must be between 0 and 100." << endl;
        return 1;
    }

    // Зчитуємо потужність приладу
    cout << "Device power (W): ";
    // Якщо введено не число, завершити програму
    if (!(cin >> P)) {
        cout << "Error, device power must be a number." << endl;
        return 1;
    }
    // Потужність не може бути нульовою чи від'ємною
    if (P <= 0) {
        cout << "Error, device power must be greater than 0." << endl;
        return 1;
    }

    // Відсоток втрати ємності акумулятора за один рік експлуатації
    const double degradation = 2.0;

    // Враховуємо старіння акумулятора
    double C_eff = C * pow(1.0 - degradation / 100.0, years);

    // Визначаємо, скільки енергії реально запасено при поточному рівні заряду
    double E_stored = C_eff * charge / 100.0;

    // Рахуємо корисну енергію, що дійде до приладу після втрат в інверторі
    double E_useful = E_stored * eff / 100.0;

    // Різниця між запасеною і корисною енергією
    double E_loss = E_stored - E_useful;

    // Час роботи приладу від корисної енергії при його потужності
    double T = E_useful / P;

    // Виділяємо цілу кількість годин з дробового часу роботи
    int h = static_cast<int>(T);

    // Залишок часу переводимо у хвилини
    int m = static_cast<int>((T - h) * 60);

    // Виводимо підсумкову інформацію
    const int labelWidth = 24;
    const int valueWidth = 20;

    cout << "\n";
    cout << left << setw(labelWidth) << "Model:" << right << setw(valueWidth) << model << endl;

    cout << fixed << setprecision(1);
    cout << left << setw(labelWidth) << "Rated capacity:" << right << setw(valueWidth - 6) << C << " Wh" << endl;
    cout << left << setw(labelWidth) << "Station age:" << right << setw(valueWidth - 5) << years << " yrs" << endl;
    cout << left << setw(labelWidth) << "Actual capacity:" << right << setw(valueWidth - 6) << C_eff << " Wh" << endl;
    cout << left << setw(labelWidth) << "Charge level:" << right << setw(valueWidth - 3) << charge << " %" << endl;

    cout << fixed << setprecision(2);
    cout << left << setw(labelWidth) << "Inverter efficiency:" << right << setw(valueWidth - 3) << eff << " %" << endl;

    cout << fixed << setprecision(1);
    cout << left << setw(labelWidth) << "Stored energy:" << right << setw(valueWidth - 6) << E_stored << " Wh" << endl;
    cout << left << setw(labelWidth) << "Useful energy:" << right << setw(valueWidth - 6) << E_useful << " Wh" << endl;
    cout << left << setw(labelWidth) << "Conversion losses:" << right << setw(valueWidth - 6) << E_loss << " Wh" << endl;

    cout << fixed << setprecision(2);
    cout << left << setw(labelWidth) << "Runtime:" << right << setw(valueWidth) << T << " h = "
         << h << " h "
         << setfill('0') << setw(2) << m << " min" << endl;

    return 0;
}
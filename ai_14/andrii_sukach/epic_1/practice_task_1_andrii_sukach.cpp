//Задача: Розрахунок автономності портативної зарядної станції
  //  Автор: Сукач Андрій
    //Група: ШІ-14

    #include <iostream>
    #include <iomanip>
    #include <cmath>
    #include <string>

using namespace std;

int main()
{
    string model; //Назва моделі станції
    double C;     //Паспортна ємність
    int years;    //Вік станції
    int charge;    //Рівень заряду
    double eff;    //ККД інвентора
    double P;     //Потужність приладу

    cout << "Модель станції: ";
    getline(cin, model);

    if (model.length() > 31)
    {
        cout << "Помилка: модель станції не може містити більше 31 символу." << endl;
        return 0;
    }
     if (model.find(' ') != string::npos)
{
    cout << "Помилка: назва станції має складатися тільки з одного слова (без пробілів)." << endl;
    return 0;
}

cout << "Паспортна ємність (Вт·год): ";
    cin >> C;

    if (cin.fail() || C < 0)
    {
        cout << "Помилка: паспортна ємність повинна бути числом більше 0." << endl;
        return 0;
    }

    cout << "Вік станції (років): ";
    cin >> years;

    if (cin.fail() || years < 0 || years > 20)
    {
        cout << "Помилка: вік станції мусить бути цілим числом від 0 до 20." << endl;
        return 0;
    }

    cout << "Рівень заряду (%): ";
    cin >> charge;

    if (cin.fail() || charge < 0 || charge > 100)
    {
        cout << "Помилка: рівень заряду мусить бути цілим числом від 0 до 100." << endl;
        return 0;
    }

    cout << "ККД інвертора (%): ";
    cin >> eff;

    if (cin.fail() || eff <= 0 || eff > 100)
    {
        cout << "Помилка: ККД інвертора мусить бути число більше 0 і не більше 100." << endl;
        return 0;
    }

    cout << "Потужність приладу (Вт): ";
    cin >> P;

    if (cin.fail() || P <= 0)
    {
        cout << "Помилка: потужність приладу повинна бути числом більше 0." << endl;
        return 0;
    }

    const double DEGRADATION = 2.0; //писало в перщому кроці про деградацію вирівшив взяти константу
    double C_eff = C * pow(1.0 - DEGRADATION / 100.0, years);
    double E_stored = C_eff * charge / 100.0; //Запас енергії при поточному заряді, Вт*год
    double E_useful = E_stored * eff / 100.0; //Корисна енергія, що дійде до приладу, Вт*год
    double E_loss = E_stored - E_useful;      //Втрати на перетворенні напруги, Вт*год
    double T = E_useful / P;        //Час роботи, годин
    int h = static_cast<int>(T);   // h= Повні години роботи

    int m = static_cast<int>((T - h) * 60); // m= хвилини

    if (m == 60)
    {
        h++;
        m = 0;
    }

    
    cout << "       РЕЗУЛЬТАТ РОЗРАХУНКУ\n";
    

    cout << left << setw(35) << "Модель:"
         << model << endl;

    cout << left << setw(35) << "Паспортна ємність:"
         << fixed << setprecision(1) << C << " Вт·год" << endl;

    cout << left << setw(35) << "Вік станції:"
         << years << " р." << endl;

    cout << left << setw(35) << "Фактична ємність:"
         << fixed << setprecision(1) << C_eff << " Вт·год" << endl;

    cout << left << setw(35) << "Рівень заряду:"
         << charge << " %" << endl;

    cout << left << setw(35) << "ККД інвертора:"
         << fixed << setprecision(2) << eff << " %" << endl;

    cout << left << setw(35) << "Запас енергії:"
         << fixed << setprecision(1) << E_stored << " Вт·год" << endl;

    cout << left << setw(35) << "Корисна енергія:"
         << fixed << setprecision(1) << E_useful << " Вт·год" << endl;

    cout << left << setw(35) << "Втрати на перетворенні:"
         << fixed << setprecision(1) << E_loss << " Вт·год" << endl;

    cout << left << setw(35) << "Час роботи:"
         << fixed << setprecision(2) << T << " год = "
         << h << " год "
         << right << setfill('0') << setw(2) << m //щоб нуль йшов в правильну сторону
         << setfill(' ') << " хв" << endl;

    cout << "============================================\n";

    return 0;
}
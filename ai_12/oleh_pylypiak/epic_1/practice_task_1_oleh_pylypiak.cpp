/*
Епік 1. Практичне завдання 1:Автономнність потативної зарядної станції
Автор: Пилип'як Олег
Група: ШІ-12
*/

#include <iostream> //отримувати або виводити дані на екран
#include <math.h> //Для матем обчислень
#include <iomanip> //Для виводу
#include <cmath> //Для заокруглення чисел
using namespace std; //щоб не писати коден раз std::...

int main() { //головна функція,яка запускає код
    
    string model_name;
    cout << "Вкажіть назву моделі станції:";
    cin >> model_name;
    if (model_name.length() > 31){
        cout << "ПОМИЛКА! Назва моделі станції не може мати більше 31 символу" << endl;
        return 1;
    }
    double C;
    cout << "Вкажіть паспортну ємність станції(Вт*год):";
    cin >> C;
    if(C<=0) {
        cout << "ПОМИЛКА! Значенням ємності має бути натуральним числом" << endl;  
        return 1;    
    }
    int years;
    cout << "Вкажіть вік станції(у роках):";
    cin >> years;
    if(years<0) {
        cout << "ПОМИЛКА! Такої станції не існує" << endl;
        return 1;
    }
    if(years>20) {
        cout << "ПОМИЛКА! Станції старше 20 років несправні" << endl;
        return 1;
    }
    int charge;
    cout << "Вкажіть рівень заряду станції(у відсотках0):";
    cin >> charge;
    if(charge<0 || charge>100){
        cout << "ПОМИЛКА! Рівень заряду станції не може бути менше 0% або більше 100%" << endl;
        return 1;
    }
    float eff;
    cout << "Введіть ККД інвертора(у відсотках):";
    cin >> eff;
    if(eff<0 || eff>=100){
        cout << "ПОМИЛКА! ККД інвертора не може бути менше 0% або бути більшим/дорівнювати 100%" << endl;
        return 1;
    }
    int P;
    cout << "Введіть потужність приладу(Вт):";
    cin >> P;
    if(P<=0){
        cout << "ПОМИЛКА! Потужність приладу не може бути меншою або дорівнювати 0" << endl;
        return 1;
    }
    const double degr=2.0;//відсоток втрати ємності щороку
    double C_eff=C * pow(1-degr / 100.0, years);//обчислюємо фактичну ємність з урахуванням віку станції
    double E_stored = C_eff * charge / 100;//обчисл запас енергії при поточному заряді
    double E_useful = E_stored * eff / 100;//обчисл корисну енергію
    double E_loss = E_stored - E_useful;//обчисл втрати на перетворенні напруги
    double T = E_useful / P;//очисл час роботи(год)
    int h = int(T);//округлюємо до цілих годин
    int m = int((T - h) * 60);//обчисл хвилини,що залишились
    cout<<"Модель:" << model_name << endl;
    cout<<"Паспортна ємність:" << fixed << setprecision(1)<< C << " Вт*год" << endl;
    cout<<"Вік станції:" << years << " p." <<endl;
    cout<<"Фактична ємність:" << fixed << setprecision(1)<< C_eff << " Вт*год" << endl;
    cout<<"Рівень заряду:" << charge << " %" <<endl;
    cout<<"ККД інвертора:" << fixed << setprecision(2)<< eff << " %" <<endl;
    cout<<"Запас енергії:" << fixed << setprecision(1)<< E_stored << " Вт*год" << endl;
    cout<<"Корисна енергія:" << fixed << setprecision(1) << E_useful << " Вт*год" << endl;
    cout<<"Втрати на перетворенні:" << fixed << setprecision(1)<< E_loss << " Вт*год"<< endl;
    cout<<"Час роботи:" << fixed << setprecision(2) << T << " год" << " = " << h <<" год " <<setfill('0')<<setw(2)<< m << " хв" << endl;
    return 0;
}
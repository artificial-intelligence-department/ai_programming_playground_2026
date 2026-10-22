/* Аналізатор місячного бюджету
Гайдучок Олександр
ШІ-11*/
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
using namespace std;
//функція для обрахування максимальної та мінімальної витрати
void vytraty(double a[], int b, double &Max, double &Min){
     Max = a[0];
     Min = a[0];
    for(int j = 0; j < b; j++){
    if(a[j] > Max){
        Max = a[j];
    }
    if(a[j] < Min){
        Min = a[j];
    }
    }
    
}
//рекурсивна функція для обрахування всієї суми витрат за усі дні
double Suma(double a[], int b, int start){
    if(start >= b){
        return 0;}
        //старт задається через виклик функції, уже в мейні задаємо значення старт
    return a[start] + Suma(a, b, start + 1);
    }
//у разі вибору 1, вивід усіх днів через цикл у функції
void choice1(double spending[], int N){
    cout << "День\t\tВитрати, грн\n";
        for(int i = 1; i <= N; i++){
        cout << i << "\t\t" << setprecision(2) << fixed << setw(0) << spending[i - 1] << endl;
        }
}
//у разі вибору 2, вивід мінімальних, максимальних, сумарних витрат
void choice2(double spending[], int N, double budget){
    double Max = 0;
    double Min = 0;
    double perevytrata = 0;
    int Daybuy = 0;
    double Seredne = 0;
     vytraty(spending, N, Max, Min);
     double SS = Suma(spending, N, 0);
        cout << "Мінімальні витрати: " << setprecision(2) << fixed << setw(0) << Min << " грн" << endl;
        cout << "Максимальні витрати: " << setprecision(2) << fixed << setw(0) << Max << " грн"  << endl;
        cout << "Сумарні витрати: " << setprecision(2) << fixed << setw(0) << SS << " грн" << endl;
        if(SS > budget){
            // перевитрата рахується через модуль числа
            perevytrata = fabs(budget - SS);
        }
            cout << "Перевитрата понад бюджет:" << setprecision(2) << fixed << setw(0) << perevytrata << " грн"  << endl;
            // підрахунок днів з покупками
            for(int x = 0; x < N; x++){
                if(spending[x] == 0){
                    continue;
                }
                Daybuy++;
            }
            cout << "Днів з покупками:" << Daybuy << endl;
            if(Daybuy > 0){
            // підрахунок середніх витрат, без урахування днів без витрат
            Seredne = SS/Daybuy;}
            cout << "Середні витрати за такий день:" << setprecision(2) << fixed << setw(0) << Seredne << " грн" << endl;
            int Day = 0;
            int Daycount = 0;
            double Nakopycheno = 0;
            while( Day < N){
            // підрахунок накопичених витрат та дня коли бюджет було вичерпано
            Nakopycheno += spending[Day];
            if(Nakopycheno > budget){
                Daycount = Day + 1;
                break;
            }
            Day++;
            }
            double Zalyshok = budget - Nakopycheno;
            if (Daycount != 0){
                cout << "Бюджет вичерпано на дні " << Daycount  << ", накопичено " << setprecision(2) << fixed << setw(0) << Nakopycheno << " грн.\n";
            }
            else{
                cout << "Бюджету вистачило на всі дні. Залишок: " << setprecision(2) << fixed << setw(0) << Zalyshok << " грн\n";
            }
}
void choice3(double spending[], int N, double Limit = 1000){
    cout << "Денний ліміт (грн, 0 = за замовчуванням): \n";
        double userlimit = 0;
        cin >> userlimit;
        // перевірка на введений 0-ий ліміт
        if(userlimit != 0){
            Limit = userlimit;
        }
        cout << "Ліміт: " << Limit << " грн\n";
        int c = 0;
        // підрахунок днів, що перевищують ліміт
        for(int x = 0; x < N; x++){
            if (spending[x] > Limit){
                cout << "День " << x+1 << ":  " << spending[x] << " грн" << endl;
                c++;
            }
        }
        cout << "Разом днів з перевищенням: " << c << endl;

}

void choice4(double spendingcopy[], int N){
        double tym;
        // сортування масиву від найменшого до найбільшого методом сортування бульбашкою
        for(int q = 0; q < N - 1; q++){
            for(int w = 0; w < N - q - 1; w++){
                if(spendingcopy[w] > spendingcopy[w + 1]){
                    tym = spendingcopy[w];
                    spendingcopy[w] = spendingcopy[w + 1];
                    spendingcopy[w + 1] = tym;
                }

            }
        }
        if(N<3){
            // вивід топ-3 витрат у разі меншої кількості за 3
            cout << "Топ-3 витрат: ";
            for(int i = N-1; i >= 0; i--){
                cout << spendingcopy[i] << " ";
            }
            cout << "грн\n";
        }
        else{
            // вивід топ-3 витрат 
            cout << "Топ-3 витрат: ";
            for(int i = N-1; i >= N-3; i--){
                cout << spendingcopy[i] << " ";
            }
            cout << "грн\n";

        }
}

int main(){
    double budget = 0;
    int N = 0;
    while(true){
    cout << "Бюджет на місяць (грн): ";
    cin >> budget;
    if(cin.fail()){
    cout << "Помилка. Введіть коректне число!\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    continue;
    }

    if(budget < 0){
        cout << "Помилка. Введіть додатнє число!\n";
        continue;
    }
    break;
}
    while(true){
    cout << "Кількість днів обліку: ";
    cin >> N;
    if(cin.fail()){
    cout << "Помилка. Введіть коректну кількість днів!\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    continue;
    }
    if(N <= 0 || N > 31){
    cout << "Помилка. Місяць обмежений від 1 до 31 днів, введіть ще раз кількість днів обліку!\n";
    continue;
    }
    break;
 }
    

    double spending[N];
    double spendingcopy[N];
    while(true){
    bool mistake = false;
    cout << "Витрати по днях (грн): ";
    for(int i = 0; i < N; i++){
        cin >> spending[i];
    
    if(cin.fail()){
    mistake = true;
    cout << "Помилка. Введіть коректну суму витрати!\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    break;
    }
    if(spending[i] < 0){
        mistake = true;
        cout << "Помилка. Введіть додатню суму витрат\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }
    }
    if(mistake){
        continue;
    }
    break;
    }
    int choice = 0;
    // цикл ду вайл повертає нам кожен раз меню
    do{
    // мітка goto
    menu:
    cout << "\t\tMenu\t\t\n";
    cout << "1" << "\t Показати витрати по днях\n";
    cout << "2" << "\t Статистика витрат\n";
    cout << "3" << "\tДні з перевищенням денного ліміту\n";
    cout << "4" << "\tТри найдорожчі дні\n";
    cout << "0" << "\tВийти\n";
    // у разі введення не цифри, наголошуємо на помилці, задаємо значення змінній та чистимо, ігноруємо потік даних
    cin >> choice;
    if(cin.fail()){
    choice = -1;
    cin.clear();
    cin.ignore();
}
// копіюємо масив
    for(int d= 0;d < N; d++){
        spendingcopy[d] = spending[d];
    }
    // залежно від введених цифр викликаємо відповідну функцію, перериваємо брейком
    switch(choice){
        case 1: choice1(spendingcopy, N); break;
        case 2: choice2(spendingcopy, N, budget); break;
        case 3: choice3(spendingcopy, N); break;
        case 4: choice4(spendingcopy, N); break;
        case 0: cout << "Ви вийшли з меню!\n"; break;
        // через те, що ми працювали з помилкою потоку, наша змінна choice = -1, тому через goto ми повертаємось на нашу мітку
        default: cout << "Виберіть пункт меню!\n"; goto menu; break;
    }
   
}
while(choice != 0);
return 0;
}

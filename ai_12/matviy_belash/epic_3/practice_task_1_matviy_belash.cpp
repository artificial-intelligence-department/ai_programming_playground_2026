/*
Белаш Матвій ШІ-12
Практична задача
*/
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void Vt(double spending[], int N){
    cout << endl << endl;
    cout << "День  " << "Витрати, грн" << endl;
    cout << fixed << setprecision(2);
    for(int i = 0; i < N; i++){
        cout << setw(2) << i + 1 << setw(14) << spending[i] << endl;
    } 
    cout << endl << endl;
}

void mnx_2(double spending[], int N, double &mn, double &mx){
    mn = spending[0];
    mx = spending[0];
    for(int i = 1; i < N; i++){
        if(spending[i] < mn) mn = spending[i];
        if(spending[i] > mx) mx = spending[i];
    }
}

void mnx(double spending[], int N){ 
    cout << endl << endl;
    cout << fixed << setprecision(2);
    double mn, mx;
    mnx_2(spending, N, mn, mx);
    cout << "Мінімальні витрати за день:  " << mn << " грн" << endl;
    cout << "Максимальні витрати за день:  " << mx << " грн" << endl;
}

double sumr(double spending[], int N){ 
    if(N <= 0) return 0;
    
    return spending[N - 1] + sumr(spending, N - 1);
}

void prVt(double budget, double total){
    if(budget < total){
        double prVt = abs(budget - total); 
        cout << fixed << setprecision(2);
        cout << "Перевитрата понад бюджет:  " << prVt << " грн" << endl;
    }else{ 
        double prVt = budget - total; 
        cout << fixed << setprecision(2);
        cout << "Залишок бюджету:  " << prVt << " грн" << endl; 
    }
}

void pk(double spending[], int N){
    int dpk = 0;
    for(int i = 0; i < N; i++){
        if(spending[i] != 0){
            dpk ++;
        }
    }
    cout << "Днів з покупками:  " << dpk << endl; 
}

void sVt(double spending[], int N){
    double sar = 0;
    double sum_Vt = 0;
    double sr;
    for(int i = 0; i < N; i++){
        if(spending[i] == 0){
            continue;
        }else{  
            sar ++;
            sum_Vt += spending[i];
        }
    }
    if(sar == 0) sr = 0;
    else sr = sum_Vt / sar;
    cout << fixed << setprecision(2);
    cout << "Середні витрати за такий день:  " << sr << " грн" << endl;
}

void vch(double spending[], int N, double budget){
    int i = 0;
    double zalishok = budget;
    double sum = 0;
    while(zalishok >= 0 && i < N){
        zalishok -= spending[i];
        sum += spending[i];
        if(zalishok < 0){
            cout << fixed << setprecision(2);
            cout << "Бюджет вичерпано на дні " << i + 1 << ", накопичено " << sum << " грн" << endl;
            break;
        }
        i ++;
    }
    if(zalishok >= 0){
        cout << fixed << setprecision(2);
        cout << "Бюджет не вичерпано. Залишок:  " << zalishok << " грн" << endl;
    }
    cout << endl << endl;
}

void lmt(double spending[], int N, double limit = 1000.0){
    int prlmt = 0;
    cout << fixed << setprecision(2);
    cout << "Ліміт: " << limit << " грн" << endl;
    for(int i = 0; i < N; i++){
        if(spending[i] > limit){
            prlmt ++;
            cout << "  день " << i + 1 << ": " << spending[i] << " грн" << endl;
        }
    }
    cout << "Разом днів з перевищенням: " << prlmt;
    cout << endl << endl;
}

void top3(double spending[], int N){
    cout << fixed << setprecision(2);
    cout << endl << endl;
    double copy_spending[N];
    for(int i = 0; i < N; i++){
        copy_spending[i] = spending[i];
    }
    for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(copy_spending[i] > copy_spending[j]){
                    double temp = copy_spending[i];
                    copy_spending[i] = copy_spending[j];
                    copy_spending[j] = temp;
                } 
            }
        }
    if(N >= 3){
        cout << "Топ-3 витрат: ";
        for(int i = 0; i < 3; i++){
            cout << copy_spending[i] << (i < 2 ? ", " : " ");
        }
    }else{
        cout << "Топ витрат: ";
        for(int i = 0; i < N; i++){
            cout << copy_spending[i] << (i < N - 1 ? ", " : " ");
        } 
    }
    cout << "грн" << endl << endl;
}

void viv2(double spending[], int N){
    cout << fixed << setprecision(2);
    cout << "Сумарні витрати:  " << sumr(spending, N) << " грн" << endl;
}

void prvlim(double &limit){
    cout << endl << endl;
    start_limit:
    cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
    cin >> limit;
    if(cin.fail() || limit < 0){
        cout << "Некоректні дані, спробуйте ще раз." << endl; 
        cin.clear();
        cin.ignore(10000, '\n');
        cout << endl << endl;
        goto start_limit;
    }   
}

void menu2(double spending[], int N, double budget){
    mnx(spending, N);
    viv2(spending, N);
    prVt(budget, sumr(spending, N));
    pk(spending, N); 
    sVt(spending, N);
    vch(spending, N, budget);
}

void menu3(double spending[], int N, double limit){
    prvlim(limit);
    if(limit == 0){
        lmt(spending, N); //тут не вводимо ліміт якщо він має бути за замовчуванням     
    } else {
        lmt(spending, N, limit);
    }
}

int main() {

    setlocale(LC_ALL, "uk_UA");

    double budget;
    int N; //к-сть днів
    int v; //змінна для користування меню
    double limit = 1000.00; //ліміт для третього пункту

    cout << "Бюджет на місяць (грн): ";  //вводимо бюджет (перевіряємо на коректний ввід)
    cin >> budget;
    if (cin.fail()){
    cout << "Помилка: потрібно ввести число." << endl;
    return 0;
    }
    if(budget <= 0){
        cout << "Помилка: бюджет має бути більшим за 0." << endl;
        return 0;
    }

    cout << "Кількість днів обліку: ";  //вводимо кількість днів (перевіряємо на коректний ввід)
    cin >> N; 
    if (cin.fail()) {
    cout << "Помилка: потрібно ввести число." << endl;
    return 0;
    }
    if(N <= 0 || N > 31){
        cout << "Помилка: кількість днів обліку має бути більшою за 0 і не бути більшою за 1 календарний місяць." << endl;
        return 0;
    }

    double spending[N];

    cout << "Витрати по днях (грн): "; //вводимо витрати за кожен день 
    for(int i = 0; i < N; i++){
        cin >> spending[i];
        if (cin.fail()){  //перевіряємо на коректний ввід
            cout << "Помилка: потрібно ввести число." << endl;
            return 0;
        }
        if(spending[i] < 0){
            cout << "Помилка: витрати за день не можуть бути меншими за 0." << endl;
            return 0;
        }
    }
     
    cout << endl << endl;

    do{ 
        
        start:

        cout << "1   Показати витрати по днях" << endl;
        cout << "2   Статистика витрат" << endl;
        cout << "3   Дні з перевищенням денного ліміту" << endl;
        cout << "4   Три найдорожчі дні" << endl;
        cout << "0   Вихід" << endl;

        cin >> v;
        if(cin.fail() || v < 0 || v > 4){  //перевіряємо чи користувач уводить коректне значення v
            cout << endl << endl;
            cout << "Некоректний вибір, спробуйте ще раз." << endl;
            v = -1;  //надаємо v нейтральне значення -1
            cin.clear();
            cin.ignore(10000, '\n');
            cout << endl << endl;   
            goto start;
        }

        if(v == 1){
            Vt(spending, N);
        }
        if(v == 2){
            menu2(spending, N, budget);
        }   
        if(v == 3){
            menu3(spending, N, limit);
        }
        if(v == 4){
            top3(spending, N);
        }

    }while(v != 0);

    return 0;
}

#include <iostream>
#include <cmath>

using namespace std;

int main(){
    //Ініціалізація змінних і надання початкових значень
    double a = 0.1;
    double b = 1;
    int n = 10;
    double step = (b-a)/10;
    double ln3 = log(3);
    //Більших цикл, що змінює x на step (0.09)
    for(double x = a; x <= b; x+=step){
        //ініціалізація змінних у циклі
        double sn = 1;
        double se = 1;
        double sn0 = 1;
        double se0 = 1;
        double y = pow(3,x);
        //Обчислення SN
        for(int i = 1; i <= n; i++){
            sn0 = sn0 * ln3 * x / i;
            sn = sn + sn0;
        }
        //ініціалізація змінної-лічильника і
        int i = 1;
        //Обчислення SE
        while(se0 >= 0.0001){
            se0 = se0 * ln3 * x / i;
            se = se + se0;
            i++;
        }
        //Виведення рядку результатів
        cout << "X= " << x << " SN= " << sn << " SE= " << se << " Y= " << y << endl;
    }
}
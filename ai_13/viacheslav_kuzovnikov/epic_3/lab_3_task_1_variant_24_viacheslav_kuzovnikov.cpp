/*
Лабораторна робота №3
Варіант №24
Кузовніков В'ячеслав Євгенійович
ШІ-13
*/

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const float a = -2;
const float b = -0.1;
const int k = 10;
const int N = 40;
const float epsilon = 0.0001;
const float h = (b-a)/k;

int main (){

    cout << "Обчислення функції" << endl;
    cout << "X            SN (n=40)        SE(e=0.0001)             Y" << endl;

    float x = -2;
    
    for (int i = 0; i <= k; i++){
        x = a + i *h;
        float SN = 0;
        float t  = pow(1+x, 2);
        float u_potochne = -t;
        float n = 1;
        for (n = 1; n <= N; n++){
            SN +=u_potochne;
            u_potochne = u_potochne *(-t) * (n/(n+1));
        }

        float SE = 0;
        u_potochne = -t;
        n = 1;
        while (fabs(u_potochne) >= epsilon){
            SE +=u_potochne;
            u_potochne = u_potochne *(-t) * (n/(n+1));
            n++;
        }

        float Y = log(1/(2+2*x+pow(x,2)));
        cout << fixed << setprecision(2) << x << "       " << fixed << setprecision(6) << SN << "         " << SE << "            " << Y << endl;

    }

    return 0;
}
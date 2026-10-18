/*Epic 3 - Завдання 1 лабораторної 3 варіант 15
Бурбан Данило
Ші - 14*/
#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
using namespace std;

int main(){
    int n=1;
    double S30=0.0;
    const double epsilon = pow(10,-4);
    double SE = 0.0;
    double prev_SE = 0.0;
    double y = 0;
    while (true){
        double x;
        cout<<"type x: ";
        if ((cin >> x) && (x>=0.1f && x<=1.0f)){
            while(n<30){
                S30+=pow(-1,n+1)*(pow(x,2*n+1)/(4*pow(n,2)-1));
                n++;
            }
            n=1;
            do {
            prev_SE = SE;
            SE +=pow(-1,n+1)*(pow(x,2*n+1)/(4*pow(n,2)-1));
            n++;
            } while (fabs(SE - prev_SE) > epsilon);
            n=1;

            y=((1+x*x)/2*atan(x)-(x/2));

            cout<<"X = "<<x<<endl;
            cout<<"S30 = "<<S30<< setprecision(10) <<endl;
            cout<<"SE = "<<SE<< setprecision(10) <<endl;
            cout<<"Y = "<<y<<endl;
            S30 = 0;
            SE = 0;

        } else {
            cout<<"incorrect value!"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return 0;
}
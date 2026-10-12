/*Lab 3 Task 1 Variant 25
Автор:Сенько Вікторія
Група: ШІ-12 group3*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
//y=(e^x-e^(-x))/2
int main() {
    const double a=0.1;
    const double b=1.0;
    const int k=10;
    const int N=20;
    const double eps = 0.0001;
    const double step =(b-a)/k;
    //Перше x - це мінімальне з межі
    double x=a;
    while(x<=b){
        cout<<fixed<<setprecision(6);
        //на початку задаємо значення E1(an)=x, суми теж =x
        double E1=x, SN=x, SE=x;
        double y=(exp(x)-exp(-x))/2;
        for(int i=1; i<N; i++){
            //рекурентна формула a_(n+1)=a_n*(x^2)/(2n+2)(2n+3), змінна 2 елементу E2(a_(n+1))
            double E2 = E1 * pow(x, 2) / ((2 * N / 2) * (2 * N + 3));
            SN += E2;
            if(E2>=eps){
                SE += E2; 
            }
            E1=E2;
        }
        cout<<"X="<<x<<"  \t"<<"SN="<<SN<<"  \t"<<"SE="<<SE<<"  \t"<<"Y="<<y<<endl;
        x+=step;
    }
    return 0;
}
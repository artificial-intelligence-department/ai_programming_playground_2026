/*
Task: lab 2 task 1 option 14
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/



#include <iostream>
#include <cmath>

using namespace std;



int main (){
    
    setlocale(LC_ALL, "uk_UA");

    const double eps = 0.0001;
    int n = 1;
    double sum = 0;
    double a = 1.0/3.0;

    while(a >= eps){
        sum += a;
        a = a* pow(static_cast<double> (n) / (n+1), n); //static_cast шоб перетворити значення n на числовий тип з плавачою комою.
        n++;
    }
    
    cout << "Сума ряду = " << sum << endl;
    return 0;
}
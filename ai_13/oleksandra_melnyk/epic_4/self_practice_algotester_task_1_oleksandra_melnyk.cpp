/*
Трикутник і коло

Обмеження: 2 сек., 256 МіБ
Дано невироджений трикутник зі сторонами 𝑎, 𝑏, 𝑐 і коло радіуса 𝑟. Вивести два знаки в один рядок:
Якщо трикутник «поміститься» в коло, вивести +, інакше -.
Якщо коло «поміститься» в трикутник, вивести +, інакше -.
*/
#include <iostream>
#include <cmath>
using namespace std;
double area1(int a, int b, int c, int r){
    double p=(a+b+c)/2.0;
    double S=sqrt(p*(p-a)*(p-b)*(p-c));
    double R=(a*b*c)/(4.0*S);
    if (R<=r)
    {
        cout<<"+";
    }
    else{
        cout<<"-";
    }
    return 0;
}
double area2(int a, int b, int c, int r){
    double p=(a+b+c)/2.0;
    double S=sqrt(p*(p-a)*(p-b)*(p-c));
    double r1=S/p;
    if (r<=r1){
        cout<<"+";
    }
    else{
        cout<<"-";
    }
    return 0;
}
int main()
{
    int a,b,c,r;
    cin>>a>>b>>c>>r;
    area1(a,b,c,r);
    area2(a,b,c,r);
}
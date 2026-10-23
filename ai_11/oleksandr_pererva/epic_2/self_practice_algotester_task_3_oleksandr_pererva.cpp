/*
Різниця у часі
Перерва Олександр
ШІ-11
*/
#include <iostream>
#include <string>

using namespace std;

int main(){
    int h1,m1,s1,h2,m2,s2;
    cin>>h1>>m1>>s1;
    cin>>h2>>m2>>s2;
    m1+=h1*60;
    m2+=h2*60;
    s1+=m1*60;
    s2+=m2*60;
    cout<<s2-s1;

    return 0;
}
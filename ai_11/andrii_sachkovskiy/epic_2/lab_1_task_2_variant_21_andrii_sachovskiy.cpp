/*
Задача: lab_1_task_2_variant_21
Автор: Сачковський Андрій
Група: ШІ-11
*/

#include <iostream>
int main(){
using namespace std;
int m, n, resaults1 ;
 bool resaults2 , resaults3;
cout<<"ведіть значення m ";
cin>>m;
cout<<"ведіть значення n ";
cin>>n;
resaults1 = n++-m;
resaults2 = m--<n;
resaults3 = n++>m;

cout<<"1)з типом n++-m="<<resaults1<<endl;
cout<<"2)з типом m--<n="<<resaults2<<endl;
cout<<"3)з типом n++>m="<<resaults3<<endl;

}

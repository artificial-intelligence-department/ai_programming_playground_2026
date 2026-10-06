/*Epic 2 - Завдання 1 лабораторної 2 варіант 21
Бурбан Данило
Ші - 14*/


#include <iostream> 


using namespace std;
int main(){
    float m;
    cin>>m;
    float n;
    cin>>n;

    float f_result= n++-m;
    bool s_result=m-->n;
    bool d_result=n-->m;

    cout<<"first result: "<<f_result<<endl;
    cout<<"second result: "<<s_result<<endl;
    cout<<"third result: "<<d_result<<endl;

}
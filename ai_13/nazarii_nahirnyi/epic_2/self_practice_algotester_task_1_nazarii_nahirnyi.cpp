/*
    Задача: Коля, Вася і теніс
    Автор: Нагірний Назарій
    Група: СШІ-13
*/
#include <iostream>
using namespace std;
int main(){
    long long c=0,w=0,k=0,v=0,n;
    cin>>n;
    if ( cin.fail() || n <= 0) {
        cout << "помилка вводу";
        return 0;}
    char v1 [n];
    for(int i=0;i<n;i++) {
        cin>>v1[i];
        if (v1[i] != 'K' && v1[i] != 'V') {
            cout << "помилка вводу";
            return 0;}
    }
    for(int i=0;i<n;i++) {
        if (v1[i]=='K') {c++;}
        else {w++;}
        if (c>10&&c >= w + 2) {c=0; w=0;k++;}
        if (w>10&&w >= c + 2) {c=0; w=0;v++;}
        }
        cout<<k<<":"<<v<<endl;
        if(c>0||w>0) {cout<<c<<":"<<w;}
    return 0;
}
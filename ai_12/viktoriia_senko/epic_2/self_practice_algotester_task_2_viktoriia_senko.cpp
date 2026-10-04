/*Задача №0031 "Коля, Вася і теніс"*/
#include <iostream>
using namespace std;
int main() {
    int n, v=0, k=0, vpoints=0, kpoints=0;
    char c;    
    cin>>n;
    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;
        //Рахуємо кількість очків у Колі та у Васі
        if (c == 'V') {
            vpoints ++;
        }
        else if (c == 'K') {
            kpoints ++;
        }
        //Перевіряємо чи є виграні партії, якщо є, то обнуляємо кількість очків
        if(kpoints>=11 && (kpoints-vpoints)>=2){
            k++;
            vpoints=0;
            kpoints=0;
        }
        else if(vpoints>=11 && (vpoints-kpoints)>=2){
            v++;
            vpoints=0;
            kpoints=0;
        }
    }
    cout<<k<<":"<<v<<endl;
    //Перевіряємо, чи залишилися недограні партії
    if(kpoints>0 || vpoints>0){
        cout<<kpoints<<":"<<vpoints<<endl;
    }
    return 0;
}
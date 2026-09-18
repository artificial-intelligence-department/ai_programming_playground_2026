//Задача №1792 "Стипендія"
#include <iostream>
using namespace std;
int main() {
    int n, i, a[7];
    int s_pidv=0, s_zvych=0, bez_s=0;
    cin>>n;
    //за допомогою цикла аналізуємо кількість іспитів
    for(i=0; i<n; i++)
       {
         cin>>a[i];
         //аналізуємо результати кожного іспиту
              if(a[i]>=90) s_pidv++;
              if(a[i]>=51 && a[i]<90) s_zvych++;
              if(a[i]<51)  bez_s++;
       }
       //робимо висновок на основі результатів
                    if (s_pidv==n) cout<<"Pidvyshchena";
                     else if (bez_s>0) cout<<"Zabud pro stypendiiu";
                     else cout<<"Zvychaina";
    return 0;
}
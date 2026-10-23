/*задача: Хелловін(алготестер)
Виконавець Сукач Андрій*/
#include <iostream>
using namespace std;
int main(){
int n,m;
int a[10000];
int b[10000];
int aMin, bMin;

cin >> n >> m;



for (int j = 0; j < n; j++){
    cin >> a[j];

}
for (int j = 0; j < m; j++){
cin >> b[j];

}

aMin = a[0];
bMin = b[0];
for (int j = 0; j < n; j++){
    if (aMin > a[j]) aMin = a[j];

}
for (int j = 0; j < m; j++){
    if (bMin > b[j]) bMin = b[j];

}
cout << aMin + bMin;
return 0;
}
/*Algotester Task 2 Variant 1
Автор:Сенько Вікторія
Група: ШІ-12 group3*/
#include <iostream>
using namespace std;
const int MaxSize = 100000;
int minmaxdiff(int r[], int n){
    int maxvalue = -1;
    int maxprevious = -1;
    int minvalue = 100000;
    int minnext = 100000;
    for(int i = 0; i<n; i++){
        if(r[i] > maxvalue) {
            maxprevious = maxvalue;
            maxvalue = r[i];

        }
        else if(r[i] > maxprevious) maxprevious = r[i];
        if(r[i] < minvalue){ 
        minnext = minvalue;
        minvalue = r[i];}
        else if(r[i] < minnext) minnext = r[i];
    }
    //різнця, якщо викинемо найменше
    int a = maxvalue - minnext;
    //різниця, якщо видалимо найбільше
    int b = maxprevious - minvalue;
    return (a<b) ? a:b; 
}

int main() {
    int N;
    cin >> N;

    while(cin.fail()||N<=0){
        cout << "Довжина має бути більшою за 0. Спробуйте ще раз.";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> N;
    }

    int r[MaxSize];
    for(int i=0; i<N; i++){
        cin >> r[i];
    }
    if(N == 1){
        cout<<"0"<<endl;
        return 0;
    }
    int difference = minmaxdiff(r, N);
    cout << difference << endl;
    return 0;
}
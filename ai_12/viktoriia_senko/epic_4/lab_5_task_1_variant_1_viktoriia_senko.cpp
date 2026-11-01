/*Lab 5 Task 1 Variant 1
Автор:Сенько Вікторія
Група: ШІ-12 group3*/
#include <iostream>
#include <cstring>
using namespace std;

const int maxlength = 60;
const int maxRows = 10;
const int maxLines = 100;

void makeGroup(const char resArray[], char group[]) {
    int k = 0;
    group[k] = '(';
    k++;
    for(int i = 0; resArray[i] != '\0'; i++){
        if(resArray[i] == '0') group[k] = ',';
        else group[k] = resArray[i];
        k++;
    }
    group[k - 1] = ')'; 
    group[k] = '\0';
}

int main() {
    char a[maxRows][maxLines];
    int n;
    cout <<"Введіть кількість рядків: ";
    cin >> n;
    cout<< "Введіть елементи кожного рядка масиву: ";
    for(int i=0; i<n; i++){
        cin >> a[i];
    }
    int lineLen = 0;
    cout << "Результат: ";
    for(int i = 0; i < n; i++){
        char group[maxLines + 2];
        makeGroup(a[i], group);
        int len = strlen(group);
        if(lineLen + len > maxlength){
            cout << endl;
            lineLen = 0;
        }
        cout << group;
        lineLen += len;
    }
    cout << endl;
    return 0;
}
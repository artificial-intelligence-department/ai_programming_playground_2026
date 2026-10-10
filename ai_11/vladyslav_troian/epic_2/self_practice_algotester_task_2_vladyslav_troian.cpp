#include <iostream>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    int a[n] = {0};
    int b[n] = {0};
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            if (j < n && a[i] == a[j]){
                b[j] = 1; //визначаємо однакові члени масиву
            } 
        }   
    }
    int y = 0;
    for (int i = 0; i < n; i++){
        y += b[i]; // кількість повторень
    }
    //оскільки відповідь до задачі це кількість значень в масиві з урахуванням повторень
    cout << (n - y) << endl;
}
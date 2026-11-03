/*Задача: Симетрична матриця
Виконав: Сукач Андрій (ШІ-14)*/
#include <iostream>

using namespace std;
int main(){
    int n;
    cin >> n;
   if (n > 1000 || n < 1) return 0;
    char arr[1005][1005] = {0};

    for (int i = 0; i < n ; i++){
            cin >> arr[i];
    }

    


  bool symetry = true; //перевірка на симетрію
          for (int i = 0; i<n; i++){
                for (int j = 0; j<n; j++){
           if (arr[i][j] != arr[j][i]) {
            symetry = false;
            break;
           }
            }
            if (!symetry) break;
        }
       
        if (symetry == true)  cout << "Yes" << endl;
            else cout << "No" << endl;
    }
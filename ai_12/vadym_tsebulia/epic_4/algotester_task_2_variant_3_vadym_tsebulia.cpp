/*
Algotester Лабораторна робота №2, Завдання №1, Варіант №3.
Цебуля Вадим
ШІ-12
*/
#include <iostream>
using namespace std;

int main(){
        int N;
        cin >> N;

        int arr[1010];
        for (int i = 1; i <= N; i++){
                cin >> arr[i];
        }
        int left = 1;
        int right = N;

        while (true){
                if (left == right){
                        cout << left << " " << right << endl;
                        cout << "Collision" << endl;
                        return 0;
                }
                else if (left > right){
                        cout << left << " " << right << endl;
                        cout << "Miss" << endl;
                        return 0;
                }
                else if (right - left == 1){
                        cout << left << " " << right << endl;
                        cout << "Stopped" << endl;
                        return 0;
                }

                int speed_left = arr[left];
                int speed_right = arr[right];

                left += speed_left;
                right -= speed_right;
        }
return 0;
}
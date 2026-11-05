#include <iostream>

using namespace std;

int main(){
    int len;
    int res = 1;
    cin >> len;
    int *mas = new int[len];

    for(int i = 0; i < len; i++){
        cin >> mas[i];
    }

    int *tmp = new int[len];

    for (int i = 0; i < len; i++) {
        tmp[i] = 1;
    }

    for(int i = 0; i < len; i++){
        for(int j = 0; j < i; j++){
            if(mas[i] > mas[j]){
                if(tmp[j] + 1 > tmp[i]){
                    tmp[i] = tmp[j] + 1;
                }
            }
        }
        if(tmp[i] > res){
            res = tmp[i];
        }
    }

    cout << res;

    delete[] mas;
    mas = nullptr;
    delete[] tmp;
    tmp = nullptr;
    return 0;
}
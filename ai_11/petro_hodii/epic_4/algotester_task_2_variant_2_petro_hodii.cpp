#include <iostream>

using namespace std;


int main(){
    int len,a,b,c;
    cin >> len;
    int* mas = new int[len];
    for(int i = 0; i < len; i++){
        cin >> mas[i];
    }
    cin >> a >> b >> c;

    int last = -1;
    for(int i = 0; i < len; i++){
        if(mas[i] != a && mas[i] != b && mas[i] != c){
            last++;
            int temp = mas[i];
            mas[i] = mas[last];
            mas[last] = temp;
        }
    }


    if(last+1 == 1 || last+1 == 0){cout << "0";}
    else{
        cout << last << endl;
        for(int i = 0; i < last; i++){
            cout << mas[i]+mas[i+1] << " "; 
        }
    }

    delete[] mas;
    mas = nullptr;

    return 0;
}
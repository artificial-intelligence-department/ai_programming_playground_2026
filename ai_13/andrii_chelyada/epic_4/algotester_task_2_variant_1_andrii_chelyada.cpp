// Algotester Lab 2v1, Челяда Андрій, ШІ-13

#include <iostream>
using namespace std;

int main(){
    int len;
    cin >> len;
    int way[len];
    for (int i = 0; i < len; i++){
        cin >> way[i];
    }
    for(int i = 0; i < len - 1; i++){
        for(int j = 0; j < len - i - 1; j++){
            if(way[j] > way[j + 1]){
                int temp = way[j];
                way[j] = way[j + 1];
                way[j + 1] = temp;
            }
        }
    }
    if(len == 1){
        cout << "0";
        return 0;
    }
    int a = way[len - 1] - way[1];
    int b = way[len - 2] - way[0];

    if( a < b){
        cout << a << endl;
    }
    else{
        cout << b << endl;
    }

    return 0;
}

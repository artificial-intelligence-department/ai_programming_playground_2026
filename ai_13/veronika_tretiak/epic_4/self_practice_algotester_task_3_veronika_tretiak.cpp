/*
Задача: Сапер
*/
#include <iostream>

using namespace std;

char* Result(const char* field, int size){
    char* result = new char[size];
    for(int i = 0;i < size; i++){
        if(field[i] == '*'){
            result[i] = '*';
        } else {
            int count = 0;

            if(i > 0 && field[i - 1] == '*'){
                count++;
            }
            if(i < size - 1 && field[i + 1] == '*'){
                count++;
            }
            result[i] = '0' + count;
        }
    }
    return result;
}

int main(){
    int n;
    cin >> n;
    char* field = new char[n];
    for(int i = 0; i < n; i++){
        cin >> field[i];
    }
    char* result = Result(field, n);

    for(int i = 0; i < n; i++){
        cout << result[i];
    }
    cout << '\n';
    delete[] field;
    field = nullptr;

    delete[] result;
    result = nullptr;
    return 0;
}

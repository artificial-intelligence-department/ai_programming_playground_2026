//Задача 0031 - "Коля, Вася і Теніс"
#include <iostream>
#include <string>

using namespace std;

int main() {

    long long n;
    if (!(cin >> n)) return 0;

    int vasya = 0; 
    int kolya = 0; 
    int winv = 0;  
    int wink = 0;  

    string match;
    cin >> match;

    for (int i = 0; i < n; i++) {
        if (match[i] == 'V') {
            vasya++;
        } else if (match[i] == 'K') {
            kolya++;
        }

        if (vasya >= 11 && vasya - kolya >= 2) {
            winv++;
            vasya = 0; 
            kolya = 0;
        } 

        else if (kolya >= 11 && kolya - vasya >= 2) {
            wink++;
            vasya = 0; 
            kolya = 0;
        }
    }

    cout << wink << ':' << winv << "\n";

    if (kolya > 0 || vasya > 0) {
        cout << kolya << ':' << vasya << "\n";
    }

    return 0;
}
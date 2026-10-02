#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int people[n];
    int count = 0;
    for (int i = 0; i < n; i++){
        cin >> people[i];
        if (people[i] <= 2){
            count++;
        }
        else if (people[i] >= 3 && people[i] <= 7){
            count += 2;
        }
        else if (people [i] >= 8 && people[i] <= 47){
            count += 3;
        }
        else if (people[i] > 47){
            count += 4;
        }
    }
    cout << count;
}
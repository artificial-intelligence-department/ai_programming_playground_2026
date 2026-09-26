#include <iostream>
#include <vector>
using namespace std;
int main(){
    long long result = 0;
    long long n;
    cin >> n;
    vector<int> list_of_denominations = {500, 200, 100, 50, 20, 10, 5, 2, 1};
    int current_list_pos = 0;
    while (n != 0){
        if (n >= list_of_denominations[current_list_pos]){
            n -= list_of_denominations[current_list_pos];
            result++;        
        } else{
            current_list_pos++;
        }
    }
    cout << result;
    return 0;
}
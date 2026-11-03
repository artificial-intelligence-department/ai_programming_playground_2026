/*
Task 3 from algotester option 3
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/


#include <iostream>
#include <string>

using namespace std;

int main(){
    string S;
    cin >> S;
    long long count = 1;

    string result;

        for(size_t i = 1; i < S.length(); i++){
                if(S[i - 1] == S[i]){
                    count++;
                }else{
                    result += S[i - 1];
                    if(count > 1){
                        result += to_string(count);
                        
                    }
                    count = 1;
                }
        }
        
        result += S.back();
        if(count > 1){
            result += to_string(count);

        }
        cout << result;

    return 0;
}


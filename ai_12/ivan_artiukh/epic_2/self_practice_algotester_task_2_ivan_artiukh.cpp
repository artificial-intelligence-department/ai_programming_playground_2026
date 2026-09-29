#include <iostream>
#include <cmath>
using namespace std;
int main(){
    int n = 0;
    cin>>n;
    int tmp_1_1 = 0;
    int tmp_2_1 = 0;
    int tmp_1_2 = 0;
    int tmp_2_2 = 0;
    int tmp_1_3= 0;
    int tmp_2_3 = 0;
    long long prod = 0;
    int left = 0;
    int right = 0;
    for(int i = 0; i < n; i++){
        tmp_1_1 = tmp_1_2;
        tmp_2_1 = tmp_2_2;
        tmp_1_2 = tmp_1_3;
        tmp_2_2 = tmp_2_3;
        cin>>tmp_1_3>>tmp_2_3;
        if(i > 1){
        prod = (tmp_1_2 - tmp_1_1) * (tmp_2_3 - tmp_2_2) - (tmp_2_2 - tmp_2_1) * (tmp_1_3 - tmp_1_2);
        if(prod < 0) right++;
        else if(prod > 0) left++;
        }
    }
    cout<<left<<" "<<right;
}
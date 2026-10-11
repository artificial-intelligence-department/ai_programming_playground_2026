//toilet man
#include <iostream>
#include <cmath>
using namespace std;
int main(){
    int n = 0;
    cin>>n;
    int tmp_x_1 = 0;
    int tmp_y_1 = 0;
    int tmp_x_2 = 0;
    int tmp_y_2 = 0;
    int tmp_x_3= 0;
    int tmp_y_3 = 0;
    long long prod = 0;
    int left = 0;
    int right = 0;
    for(int i = 0; i < n; i++){
        tmp_x_1 = tmp_x_2;
        tmp_y_1 = tmp_y_2;
        tmp_x_2 = tmp_x_3;
        tmp_y_2 = tmp_y_3;
        cin>>tmp_x_3>>tmp_y_3;
        if(i > 1){
        prod = (tmp_x_2 - tmp_x_1) * (tmp_y_3 - tmp_y_2) - (tmp_y_2 - tmp_y_1) * (tmp_x_3 - tmp_x_2);
        if(prod < 0) right++;
        else if(prod > 0) left++;
        }
    }
    cout<<left<<" "<<right;
}

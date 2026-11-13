/*
Непарний масив
Перерва Олександр
ШІ-11
*/
#include <iostream>
#include <cmath>

using namespace std;

int main(){
    int n,count=0,count_even=0,count_odd=0,count1=0,count2=0;
    const int max_n=100000;
    long long a[max_n],even[max_n],odd[max_n],sorted_a[max_n];
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<n;i++){
        for(int j=count++;j<n;j++){
            if(a[j]%2==0){
                even[i-count_odd]=a[j];
                count_even++;
                break;
            }
            else{
                odd[i-count_even]=a[j];
                count_odd++;
                break;
            }
        }
    }

    if(abs(count_even-count_odd)>1){
        cout<<"-1";
        return 0;
    }
    if(count_even-count_odd==1){
        for(int i=0;i<n;i++){
            if(i%2==0){
              sorted_a[i]=even[i-count2];
              count1++;
            }  
            else{
              sorted_a[i]=odd[i-count1];
              count2++;
            }  
        }
    }
    if(count_even-count_odd==-1){
        for(int i=0;i<n;i++){
            if(i%2==0){
              sorted_a[i]=odd[i-count2];
              count1++;
            }  
            else{
              sorted_a[i]=even[i-count1];
              count2++;
            }  
        }
    }
    if(count_even-count_odd==0){
        for(int i=0;i<n;i++){
            if(i%2==0){
              sorted_a[i]=even[i-count2];
              count1++;
            }  
            else{
              sorted_a[i]=odd[i-count1];
              count2++;
            }  
        }
    }
    for(int i=0;i<n;i++){
        cout<<sorted_a[i]<<" ";
    }
}
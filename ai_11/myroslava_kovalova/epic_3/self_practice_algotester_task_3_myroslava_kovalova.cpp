#include <iostream>

using namespace std;
int main (){
    unsigned int n = 0;
    long int array[100000] = {0};
    long int result[100000] = {0};
    cin>>n;
    for (int i = 0; i<n; i++){
        cin>>array[i];
    }
    unsigned int count_odd =0;
    unsigned int count_even=0;
    for (unsigned int i = 0; i<n; i++){
        if (array[i]%2==0){
            count_even++;
        }else{
            count_odd++;
        }
    }
    unsigned int even_index, odd_index;
    
    if(count_even>count_odd){
        even_index = 0;
        odd_index = 1;
    }else{
        even_index = 1;
         odd_index = 0;
    }
    
    if(!(count_even==count_odd || count_even==count_odd+1 || count_odd==count_even+1)) {
        cout<<"-1";
        return 0;
    }else{
        for (unsigned int i = 0; i<n;i++){
            if(array[i]%2==0){
                result[even_index]=array[i];
                even_index+=2;
            }else{
                long int temp = array[odd_index];
                result[odd_index]=array[i];
                odd_index+=2;
            }
        }
    }
    for (unsigned int i =0;i<n;i++){
        cout<<result[i]<<" ";
    }
    return 0;
}
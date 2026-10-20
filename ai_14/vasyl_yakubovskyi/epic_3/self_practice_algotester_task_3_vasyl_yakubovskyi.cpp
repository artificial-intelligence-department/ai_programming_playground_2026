/*
Task: self_practice_algotester_task_3 (Халява)
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/


#include <iostream>

using namespace std ;


int main(){


    int n = 0;
    cin >> n;
    if(n < 1 || n > 100) return 0;

    int temp_nums[n] = {0};

    for (int i = 0; i < n; i++){
        cin >> temp_nums[i];
        if(temp_nums[i] < 1 || temp_nums[i] > 100) return 0;
    }


    int nums[n] = {0};
    int uniqN = 0;
 //sorting for unique values
    for(int i = 0; i < n; i++){
        bool exist = false;
        for(int j = 0; j < uniqN; j++){
            if(temp_nums[i] == nums[j]){
                exist = true;
            }
        }
        if(!exist){
            nums[uniqN] = temp_nums[i] ;
            uniqN++;
        }
    }


// sorting
    for(int i = 0; i < uniqN - 1; i++){
        bool issort = false;
        for (int j = 0; j < uniqN - i - 1 ; j++){
            
            if(nums[j] > nums[j + 1]){
                int temp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = temp;
                issort = true;
            }            
        }
        if(!issort) break;
    }

    int ways = 1;
 //counting ways
    for (int i = uniqN - 1; i > 0; i--){
        for(int j = uniqN  - (uniqN - i); j > 0; j--){
            if(nums[j] > nums[j-1]){
                ways++;
                break;
            }

        }
    }

    
    cout << ways << endl;

    return 0;
}


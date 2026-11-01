#include <iostream>
#include <limits>

using namespace std;

void matrix_check(int **arr, int n);

int main(){
    int number_of_elements;
    while (true)
    {
        cout<<"please type in 'number of elements': ";
        if(!(cin>>number_of_elements)|| number_of_elements<=0){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        } else{
            break;
        }
    }
    int **matrix= new int*[number_of_elements];
    for (int i = 0; i<number_of_elements; i++){
        matrix[i]= new int[number_of_elements];
    }
    
    for(int i=0; i<number_of_elements; i++){
        for(int j=0;j<number_of_elements;j++){
            while (true){
                cout<<"element on "<<i<<" row "<< j <<" column>>";
                if(!(cin>>matrix[i][j])){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }else break;
            }
        }
    }

    matrix_check( matrix, number_of_elements);


    for (int i = 0; i < number_of_elements; i++) {
        delete[] matrix[i]; 
    }
    delete[] matrix;
    return 0;
}
void matrix_check(int **arr, int n){
    bool is_ortonormal=true;
    for (int row = 0; row < n; row++)
    {
        int product_of_self=0;
        for(int iterable_row = 0; iterable_row<n;iterable_row++){
            int product_of_iterable=0;
            
            for (int column = 0; column < n; column++)
            {
            if(iterable_row==row){
                product_of_self+=arr[row][column]*arr[iterable_row][column];
            }else{
                product_of_iterable+=arr[row][column]*arr[iterable_row][column];
            }
            }
            if(product_of_iterable!=0){
                is_ortonormal=false;
            }
            
        }
        if(product_of_self!=1){
                is_ortonormal=false;
            }
        
    }
    cout<<"is matrix ortonormal = "<<is_ortonormal<<endl;
    
}
#include <iostream>
using namespace std;

void check ( int **arr, int rows, int cols){
    for (int i=0; i<rows; i++){
        bool isdown=true;
        for (int j=0; j<cols-1; j++){
            if (arr[i][j]<=arr[i][j+1]){
                isdown=false;
                break;
            }
        }
        if (!isdown){
            for (int k=0; k<cols-1; k++){
                for (int j=0; j<cols-k-1; j++){
                    if (arr[i][j]> arr[i][j+1]){
                        int temp = arr[i][j];
                        arr[i][j]=arr[i][j+1];
                        arr[i][j+1]=temp;
                        
                    }
                }
            }
        }
    }
}
int main(){
int rows, cols;
bool isval=false;

while (!isval){
cout<<"Введіть кількість рядків та стовпців: "<<endl;
if (cin>>rows>>cols && rows>0 && cols>0){
    isval=true;
}else{
    cout<<"Помилка, введіть додатні числа! "<<endl;
    cin.clear();
    cin.ignore(10000, '\n');
}
}
int **arr = new int*[rows];
    for (int i=0; i<rows; i++){
        arr[i]= new int[cols];
    }
cout<<"Введіть елементи масиву (кількість повинна дорівнювати добутку рядків на стовпці): " << endl;
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            bool symval=false;
            while (!symval){
           if (cin>> arr[i][j]){
            symval=true;
           }else{
            cout<<"Помилка! Введіть числа. "<<endl;
            cin.clear();
            cin.ignore(10000, '\n');
           }
        }
    }
}
    check (arr, rows, cols);
    cout<<"Результати обробки масиву: "<<endl;
        for(int i=0; i<rows; i++){
            for (int j=0; j<cols; j++){
                cout<<arr[i][j]<<" ";
            }
            cout<<endl;
        }

for (int i=0; i<rows; i++){
    delete[] arr[i];
}
delete [] arr;
    return 0;
}

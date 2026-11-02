#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(){
srand(static_cast<unsigned int>(time(0)));
int size;
cout<<"Введіть кількість елементів масиву: "<<endl;
cin>>size;
if (size<=5){
    cout<<"Введіть значення більше за 5!"<<endl; 
    return 0;
}

int arr[100];
cout<<"Масив заповнений рандомними числами:"<<" ";
    for (int i=0; i<size; i++){
        arr[i]=rand()%100; 
        cout<<arr[i]<<" ";
    }
    cout<<"\n";
    int sizeone=size-5;
        for (int k=sizeone-1; k>=0; k--){
            arr[k+3]=arr[k];
        }
    int sizetwo= sizeone+3;
        arr[2]=arr[3]+2;
        arr[1]=arr[2]+2;
        arr[0]=arr[1]+2;
    cout<<"Відформатований масив: "<<" ";
    for (int m=0; m<sizetwo; m++){
    cout<<arr[m]<<" ";
    }
        cout<<"\n";
    return 0;
}

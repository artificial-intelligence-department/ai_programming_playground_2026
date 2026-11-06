/*
 * Задача: algotester_task_4_1_variant_1 без стл 
 * Автор: Сачковський Андрій
 * Група: AI-11
*/

#include <iostream>

using namespace std;

//фнкція яка сортує масив і виводить: кількість, потім числа
void vyvid(int a[], int k)
{
    for (int i = 0; i < k - 1; i++)
    {
        for (int j = 0; j < k - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
    cout << k << endl;
    for (int i = 0; i < k; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl << endl;
}

int main (){
//користовач водить свої дані 
    int N[100], M[100];
int n, m;
    cin>>n;
    for  (int i = 0 ; i <n ; i++){
        cin>>N[i];
    }

cin>>m;
      for  (int i = 0 ; i <m ; i++){
        cin>>M[i];
      }


int N_minus_M = 0;
bool found;
int N_M[100];
int N_peretin_M[100];
int N_peretin_M_rahunok = 0 ;
//нам потрібно щоб елемент належав N але не повинен належати M
for (int i = 0; i < n; i++)
{
    found = false;

    for (int j = 0; j < m; j++)
    {
        
        if (N[i] == M[j])     
        {
            found = true;
            M[j] = 0;          
            break;              
        }
    }

    if (found == false)
    {
        
        N_M[N_minus_M] = N[i];
        N_minus_M++;
    }
    else
    {
      
        N_peretin_M[N_peretin_M_rahunok]= N[i];
        N_peretin_M_rahunok++;
    }
}
vyvid(N_M, N_minus_M);         

//нам потрібно щоб елемент належав M але не повинен належати N
int M_minus_N = 0;
int M_N[100];

for (int i = 0; i < m; i++)
{

    if (M[i] != 0)             
    {
        M_N[M_minus_N] = M[i];
        M_minus_N++;
    }
}
vyvid(M_N, M_minus_N);      

vyvid(N_peretin_M, N_peretin_M_rahunok);    

//шукаємо обєднання і виводимо його 
int N_obednini_M[200];               
int N_obedneni_M_rahunok = 0 ;

for (int i = 0 ; i < n; i ++){
    N_obednini_M[N_obedneni_M_rahunok]=N[i];
    N_obedneni_M_rahunok++;
}
for (int i = 0 ; i < M_minus_N; i ++){
    N_obednini_M[N_obedneni_M_rahunok]=M_N[i];
    N_obedneni_M_rahunok++;
}
vyvid(N_obednini_M, N_obedneni_M_rahunok); 

//виводимо симетричну різницю все з N-M і все з M-N разом
int sym[200];                  
int sym_rahunok = 0;

for (int i = 0; i < N_minus_M; i++)    
{
    sym[sym_rahunok] = N_M[i];
    sym_rahunok++;
}

for (int i = 0; i < M_minus_N; i++)   
{
    sym[sym_rahunok] = M_N[i];
    sym_rahunok++;
}
vyvid(sym, sym_rahunok);      

return 0;
}

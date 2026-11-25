/*
 * Задача: algotester_task_6_variant_3 
 * Автор: Сачковський Андрій
 * Група: AI-11
*/

/*  суть завданя користувач вводить:

розмір поля
саме поле
скільки буде запитань
координати кожної клітинки спочатку рядок потім стовпець

Дальше перевіряються весь рядок і весь стовпець, які проходять через цю клітинку кординати якої вів користовач 
наша задача вевести яких цифр немає від 1 до N в поярдку зростання важливо  якщо в тих кординатах є число т о просто його вивести


*/
#include <iostream>



using namespace std;

void vidpovid(int a[], int b, int n){

for (int i = 0; i < b - 1; i++)
{
    for (int j = 0; j < b - 1 - i; j++)
    {
        if (a[j] > a[j + 1])
        {
            int tmp = a[j];
            a[j] = a[j + 1];
            a[j + 1] = tmp;
        }
    }
}

// чистка щоб було в масиві тільки по 1 унікальному елементу
int kilkist_unik = 0;          
for (int i = 0 ; i < b ; i++){

    if ( i == 0 || a[i] != a[i-1] ){
        a[kilkist_unik] = a[i];
        kilkist_unik++;
    }
}

int new_array[100];            
int kilkist = 0;
     
// тут робиться перевірка які цифри від 1 до n є в масиві  а яких немає
for ( int j = 1 ; j <= n ; j++ ){

    bool ye = false;
    for ( int i = 0 ; i < kilkist_unik ; i++ ){
        if ( a[i] == j ){
            ye = true;
        }
    }

    if ( ye == false ){        
        new_array[kilkist] = j;
        kilkist++;
    }
}

// тут вже вивод
cout << kilkist << endl;
for(int i = 0 ; i < kilkist; i++){
cout<<new_array[i]<<" ";
}
cout<<endl<<endl;
}

int main(){
    //користвач водить дані 
int N[9][9];                   
int n;
cin>>n;
for (int i = 0 ; i < n ; i ++){
    int chyslo;
    cin>>chyslo;                  
    //розідялємо число на цифри 
    for (int j = n - 1 ; j >= 0 ; j--){
        N[i][j] = chyslo % 10;    
        chyslo = chyslo / 10;      
    }
}

int q;
cin>>q;


for(int i = 0 ; i < q; i++){

    int x, y;
    cin>>x>>y;
    x--;                    
    y--;
//якщо в кординатах є число то просто його виводим 
    if ( N[x][y] != 0 ){        
        cout << 1 << endl;
        cout << N[x][y] << endl << endl;
    }
    //робимо масив куда запихаємо всі числа які є в стопці і рядку 
    else{
        int array[20];          
        int k = 0;

        for ( int j = 0 ; j < n ; j++ ){    // весь рядок x
            array[k] = N[x][j];
            k++;
        }
        for ( int j = 0 ; j < n ; j++ ){    // увесь стовпець y
            array[k] = N[j][y];
            k++;
        }

        vidpovid(array, k, n);
    }
}

return 0;
}                               
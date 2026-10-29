/*
 * Задача: Редактор монохромного зображення
 * Автор: Сачковський Андрій
 * Група: AI-11
*/
#include <iomanip>
#include <iostream>
using namespace std;

void freeImg(int **&img, int visota1){
    for (int i = 0; i < visota1; i++) {
        delete[] img[i];
        img[i] = nullptr;
    }
    delete[] img;
    img = nullptr;
}

//користовач вибрав в меню 1 
void point1(int **img, int visota1, int shirina1){
    
    //вивід циферок
    cout<<"Зображення "<< visota1 << " x " << shirina1 <<":"<< endl;
for (int i = 0; i < visota1; i++) {
    for (int j = 0; j < shirina1; j++) {
        cout << img[i][j] << " ";
    }
    cout << endl;
}

 //вивід малюнка
 cout<<endl<<"Малюнок:"<<endl;
    for (int i = 0; i < visota1; i++) {
    for (int j = 0; j < shirina1; j++) {
        switch (img[i][j]) {
            case 1: cout << "."; 
            break;
            case 2: cout << ":";
            break;
            case 3: cout << "-";
            break;
            case 4: cout << "="; 
            break;
            case 5: cout << "+"; 
            break;
            case 6: cout << "*"; 
            break;
            case 7: cout << "#"; 
            break;
            case 8: cout << "%"; 
            break;
            case 9: cout << "@"; 
            break;
            case 0: cout << " "; 
            break;
        }
    }
    cout << endl;   
}
}
//пошуки найбільших і найменших значень
void findExtremes(int **img, int visota1, int shirina1, int &rMin, int &sMin, int &rMax, int &sMax)
{
    rMin = 0; sMin = 0; rMax = 0; sMax = 0;
   int min = *(img[0]);
   int max = *(img[0]);
    for (int i = 0; i < visota1; i++) {
        int *row = img[i];
        for (int j = 0; j < shirina1; j++) {
            int v = *(row + j);
            if (v < min) {
                min = v;
                rMin = i;
                sMin = j;
            }
            if (v > max) {
                max = v;
                rMax = i;
                sMax = j;
            }
        }
    }
}
//користовач вибрав в меню 2 
void point2(int **img, int visota1, int shirina1)
{

 int rMin, sMin, rMax, sMax;
 findExtremes(img, visota1, shirina1, rMin, sMin, rMax, sMax);
   cout << "Найтемніший піксель: " << *(img[rMin] + sMin)
         << " (рядок " << rMin + 1 << ", стовпець " << sMin + 1 << ")" << endl;

   cout << "Найсвітліший піксель: " << *(img[rMax] + sMax)
         << " (рядок " << rMax + 1 << ", стовпець " << sMax + 1 << ")" << endl;
//серединє значення 
int suma = 0;
double sredniaRyadka[20];
for (int i = 0; i < visota1; i++) {
    int *row = img[i];
    int sumaRyadka = 0;
    for (int j = 0; j < shirina1; j++) {
        sumaRyadka += *(row + j);
    }
    suma += sumaRyadka;
    sredniaRyadka[i] = (double)sumaRyadka / shirina1;
}

    cout << fixed << setprecision(2);
    cout << "Середня яскравість: " << (double)suma / (visota1 * shirina1) << endl;
    cout << fixed << setprecision(1);
    cout << "Середня по рядках:";
    for (int i = 0; i < visota1; i++) {
        cout << " " << sredniaRyadka[i];
    }
    cout << endl;
}
    
//користовач вибрав в меню 3 
void point3(int **img, int visota1, int shirina1) {
    cout << "Яскравість інвертовано." << endl;

    // інвертуємо
    for (int i = 0; i < visota1; i++) {
        for (int j = 0; j < shirina1; j++) {
            img[i][j] = 9 - img[i][j];
        }
    }   

    // виводимо
    for (int i = 0; i < visota1; i++) {
        for (int j = 0; j < shirina1; j++) {
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

//заміна місцями
void swapPixels(int *a,int *b){
int perehod;
perehod = *b; 
*b = *a;
*a = perehod;

}

//користовач вибрав в меню 4 
void point4(int **img, int visota1, int shirina1){
//вивід початковго значення
cout<<"Зображення віддзеркалено."<<endl;
cout<<"Початкове:"<<endl;

    for (int i = 0; i < visota1; i++) {
        for (int j = 0; j < shirina1; j++) {
            cout << img[i][j] << " ";
        }
        cout << endl;
    }


cout<<endl;
//відзеркалення 
  for (int i = 0; i < visota1; i++) {
        for (int j = 0; j < shirina1/2; j++) {
swapPixels(&img[i][j], &img[i][shirina1 - 1 - j]);
        }
    }

//вивід відзеркаленого 
cout<<"Результат:"<<endl;
  for (int i = 0; i < visota1; i++) {
        for (int j = 0; j < shirina1; j++) {
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}

int** rotateRight(int** img, int rows, int cols) {
   // новий масив розміром cols на rows
    int **newImg = new int*[cols];
    for (int i = 0; i < cols; i++) {
        newImg[i] = new int[rows];
    }

    // переносимо числа зі старого в новий
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newImg[rows][cols] = img[i][j];
        }
    }


    freeImg(img, rows);

    
    return newImg;
}

//користовач вибрав в меню 5
void point5(int **img, int visota1, int shirina1) {
    cout << "Зображення повернуто. Нові розміри: " << visota1 << " x " << shirina1 << endl;
    for (int i = 0; i < visota1; i++) {
        for (int j = 0; j < shirina1; j++) {
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
}


int main(){

int visota; 
int shirina;

//користовач водить різні значення також для кожного воду робиться перевірка
cout<<"Ведіть висоту зображення (від 1 до 20): ";
cin>>visota;
if(cin.fail()){
    cout<<"Ви вели не число"<<endl;
    return 0;
}
if (cin.peek() != '\n')
{
    cout<<"Ви вели не ціле число"<<endl;
    return 0;
}
if ( visota < 1 || visota>20 )
{
    cout<<"Ви вели число не з проміжку від 1 до 20"<<endl;
    return 0;
}

cout<<"Ведіть ширину зображення (від 1 до 20): ";
cin>>shirina;
if (cin.fail())
{
    cout<<"Ви вели не число"<<endl;
    return 0;
}
if (cin.peek() != '\n')
{
    cout<<"Ви вели не ціле число"<<endl;
    return 0;
}
if ( shirina < 1 ||shirina>20 )
{
    cout<<"Ви вели число не з проміжку від 1 до 20"<<endl;
    return 0;
}

int **img = new int*[visota];
for (int i = 0; i < visota; i++) {
    img[i] = new int[shirina];
}

cout << "Введіть яскравість пікселів від 0 до 9 (через enter)" << endl;
int n = visota * shirina ;

for (int i = 0; i < visota; i++) {
    for (int j = 0; j < shirina; j++){
        cout <<"Кількість пікселів яку треба розукрасити -> " << n<<endl; 
        cin >> img[i][j];
        n--;
        if (cin.fail()) {
            cout << "Ви вели не число" << endl;
            freeImg(img, visota);
            return 0;
        }
        int next = cin.peek();
        if (next != '\n' && next != ' ' && next != '\t' && next != '\r' && next != EOF) {
            cout << "Ви вели не ціле число" << endl;
            freeImg(img, visota);
            return 0;
        }
        if (img[i][j] < 0 || img[i][j] > 9) {
            cout << "Число не з проміжку від 0 до 9" << endl;
            freeImg(img, visota);
            return 0;
        }
    }
}
//користовач вибирає якусь дію в меню
int vibor;
do 
{
    cout<<"МЕНЮ:"<<endl;
    cout<<"1    Показати зображення"<<endl;
    cout<<"2    Статистика яскравості"<<endl;
    cout<<"3    Інвертувати яскравість"<<endl;
    cout<<"4    Віддзеркалити по горизонталі"<<endl;
    cout<<"5    Повернути на 90 градусів праворуч"<<endl;
    cout<<"0    Вийти"<<endl;
    cin>>vibor;
    if (cin.fail())
    {
        if (cin.eof()) break;
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Ви вели не число спробуйте ще раз "<<endl;
        vibor = -1;
        continue;
    }
    if (cin.peek() != '\n')
    {
        cin.ignore(1000, '\n');
        cout<<"Ви вели не ціле число спробуйте ще раз "<<endl;
        vibor = -1;
        continue;
    }
    if ( vibor < 0 ||vibor>5 )
    {
        cout<<"Ви вели число не з проміжку від 0 до 5 спробуйте ще разок"<<endl;
        continue;
    }
    switch (vibor) {
    case 1:
        point1(img , visota, shirina);
        break;
    case 2:
        point2(img , visota, shirina);
        break;
    case 3:
        point3(img , visota, shirina);
        break;
    case 4:
        point4(img , visota, shirina);
        break;
    case 5:
    {
        img = rotateRight(img, visota, shirina);  
        int tmp = visota;                         
        visota = shirina;
        shirina = tmp;
        point5(img, visota, shirina);             
        break;
    }
    case 0:
        break;
    }
}
while(vibor != 0);

freeImg(img, visota);
return 0;
}
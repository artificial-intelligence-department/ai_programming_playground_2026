/*
Назва задачі: Інтерактивне число
Автор: Петро Стецюк
Група: ШІ-12
*/
#include <iostream>

using namespace std;

int main()
{
    long long left=1,right=1000000000;
    while(left<=right)
    {
        long long x=left+(right-left)/2;

        cout<<x<<endl;

        char input;
        cin>>input;

        if(input=='=')
        {
            break;
        }
        else if(input=='<')
        {
            left=x+1;
        }
        else if(input=='>')
        {
            right=x-1;
        }
    }

    return 0;
}
/*
Lab 10 Task 1 Variant 2
Козій Василь Іванович
група: ШІ-12
*/
#include <iostream>
using namespace std;
struct point
{
    int key;
    point* next;
};
point* make_list(int n)
{
    if(n<=0) return nullptr;
    point *head=nullptr, *p=nullptr;
    for(int i=0; i<n ;i++)
    {
        point *new_p=new point;
        cin>>new_p->key;
        new_p->next=nullptr;
        if(head==nullptr){head=new_p; p=head;}
        else{p->next=new_p; p=new_p;}
    }
    return head;
}
void print_list(point* head)
{
    if(head==nullptr)
    {
        cout <<"Список пустий";
    }
    point* p=head;
    while(p!=nullptr)
    {
        cout <<p->key <<" ";
        p=p->next;
    }
    cout <<endl;
}
void del(point*& head, int key)
{
    if (head==nullptr) return;
    if (head->key==key)
    {
        point* t=head;
        head=head->next;
        delete t;
        return;
    }
    point* p=head;
    while (p->next!=nullptr)
    {
        if (p->next->key==key)
        {
            point* t=p->next;
            p->next=p->next->next;
            delete t;
            return;
        }
        p=p->next;
    }
}
void add(point*& head, int key, int value)
{
    if (head == nullptr) return;
    if (head->key==key)
    {
        point* new_p = new point;
        new_p->key=value;
        new_p->next=head;
        head=new_p;
        return;
    }
    point* p = head;
    while (p->next != nullptr)
    {
        if (p->next->key==key)
        {
            point* new_p = new point;
            new_p->key=value;
            new_p->next=p->next;
            p->next=new_p;
            return;
        }
        p=p->next;
    }
}
void free_list(point*& head)
{
    while (head!=nullptr)
    {
        point* temp=head;
        head=head->next;
        delete temp;
    }
}
int main()
{
    int size;
    cout <<"Введіть розмір списку, будь ласка: ";
    cin >>size;
    cout <<"Введіть, будь ласка, елементи списку: "; 
    point *start=make_list(size);
    cout <<"Початковий список: ";
    print_list(start);
    int choice, key, value;
    do
    {
        cout <<"1-Знищити елемент із заданим ключем" <<endl;
        cout <<"2-Додати елемент перед елементом із заданим ключем" <<endl;
        cout <<"0-Вийти" <<endl;
        cout <<"Будь ласка, виберіть дію: " <<endl;
        cin >>choice;
        switch(choice)
        {
            case 0:
            {
                break;
            }
            case 1:
            {
                cout <<"Будь ласка, введіть значення елемента, який хочете видалити: ";
                cin >>key;
                del(start, key);
                cout <<"Новий список:" <<endl;
                print_list(start);
                break;
            }
            case 2:
            {
                cout <<"Будь ласка, введіть значення, елемента перед яким хочете додати інший елемент: ";
                cin >>key;
                cout <<"Будь ласка, введіть значення елементу, який хочете додати: ";
                cin >>value;
                add(start, key, value);
                cout <<"Новий список:" <<endl;
                print_list(start);
                break;
            }
            default:
            {
                cout <<"Виберіть одну з дій, будь ласка" <<endl;
                break;
            }
        }
    } while(choice!=0);
    free_list(start);
}
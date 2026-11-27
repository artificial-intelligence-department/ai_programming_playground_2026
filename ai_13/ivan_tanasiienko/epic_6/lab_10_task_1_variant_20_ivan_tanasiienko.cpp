
/*
    Lab 10 Task 1, Variant 20, Танасієнко Іван, ШІ-13
*/
#include<iostream>
#include<cstdio>
#include<cstring>


struct DoubleLinkedCharArray
{
    struct Node
    {
        char* data;
        Node* prev = nullptr;
        Node* next = nullptr;
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    int size = 0;

    void Append(char* data)
    {
        Node* el = new Node;
        el->data = new char[strlen(data) + 1];
        strcpy(el->data, data);

        if(head == nullptr)
        {
            head = el;
            tail = head;
        }
        else
        {
            tail->next = el;
            el->prev = tail;
            tail = el;
        }
        size++;
    }
    void Insert(int id, char* data)
    {
        if(id < 0 || id > size) return;

        Node* ptr = head;
        for(int i = 0; i < id; i++) ptr = ptr->next;

        Node* el = new Node{};
        el->data = new char[strlen(data) + 1];
        strcpy(el->data, data);
        el->next = ptr;

        if(ptr != nullptr)
        {
            el->prev = ptr->prev;
            ptr->prev = el;
        }
        else
        {
            el->prev = tail;
            tail = el;
        }

        if(el->prev != nullptr) el->prev->next = el;
        else head = el;

        size++;
    }

    void Delete(char* key)
    {
        if(head == nullptr) return;
        Node* ptr = head;
        while(ptr != nullptr && strcmp(ptr->data, key) != 0) ptr = ptr->next;
        if(ptr == nullptr) return;
        if(ptr->prev != nullptr) ptr->prev->next = ptr->next;
        else head = ptr->next;
        if(ptr->next != nullptr) ptr->next->prev = ptr->prev;
        else tail = ptr->prev;
        delete[] ptr->data;
        delete ptr;
        size--;
    }
    void Print()
    {
        Node* ptr = head;
        if(ptr == nullptr) printf("Список порожній");
        while(ptr != nullptr)
        {
            printf("%s", ptr->data);
            ptr = ptr->next;
        }
        printf("\n");
    }
    void Destroy()
    {
        Node* ptr = head;
        while(ptr != nullptr)
        {
            Node* next = ptr->next;
            delete[] ptr->data;
            delete ptr;
            ptr = next;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
};


int main()
{
    char* str = new char[512];
    DoubleLinkedCharArray arr;
    int count;
    printf("Скільки елементів у списку: ");
    std::cin >> count;
    std::cin.ignore(10000, '\n');
    for(int i = 0; i < count; i++)
    {
        printf("Ключ %d: ", i+1);
        if(fgets(str, 255, stdin) == nullptr)
        {
            delete[] str;
            arr.Destroy();
            return 0;
        }
        str[strcspn(str, "\n")] = '\0';
        arr.Append(str);
    }

    printf("Знищити елемент з ключем: ");
    if(fgets(str, 255, stdin) == nullptr)
    {
        delete[] str;
        arr.Destroy();
        return 0;
    }
    str[strcspn(str, "\n")] = '\0';
    arr.Delete(str);

    int els;
    printf("Скільки елементів додати на початок і кінець: ");
    std::cin >> els;
    std::cin.ignore(10000, '\n');

    for(int i = 0; i < els; i++)
    {
        printf("Ключ для початку %d: ", i+1);
        if(fgets(str, 255, stdin) == nullptr)
        {
            delete[] str;
            arr.Destroy();
            return 0;
        }
        str[strcspn(str, "\n")] = '\0';
        arr.Insert(i, str);
    }
    for(int i = 0; i < els; i++)
    {
        printf("Ключ для кінця %d: ", i+1);
        if(fgets(str, 255, stdin) == nullptr)
        {
            delete[] str;
            arr.Destroy();
            return 0;
        }
        str[strcspn(str, "\n")] = '\0';
        arr.Append(str);
    }
    delete[] str;
    arr.Print();
    arr.Destroy();
    return 0;
}

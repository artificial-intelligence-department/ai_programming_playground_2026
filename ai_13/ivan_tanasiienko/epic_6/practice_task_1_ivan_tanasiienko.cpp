/*
    Class Practice Task, Танасієнко Іван, ШІ-13
*/
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<cctype>

void printMenu();

enum class DeviceType { PHONE = 1, LAPTOP, TV };
enum class Status { WAITING, REPAIR, DONE };
enum class ActionType { ADD, REMOVE };

struct Money
{
    int hrn;
    int kop;
    Money(int hrn = 0, int kop = 0)
    {
        this->hrn = hrn;
        this->kop = kop;
    }
};

struct Date
{
    int day;
    int month;
    int year;
};

struct Client
{
    char name[16];
    char phone[11];
};

union DeviceInfo
{
    int imei;
    char serial[12];
    int inches;
};

struct Order
{
    int id;
    Client client;
    Date date;
    DeviceType type;
    DeviceInfo info;
    char problem[81];
    int priority;
    Money price;
    Status status;
    char master[24];
};

struct OrderNode
{
    Order data;
    OrderNode* prev = nullptr;
    OrderNode* next = nullptr;
};

struct OrderList
{
    OrderNode* head = nullptr;
    OrderNode* tail = nullptr;
    int size = 0;

    void Append(const Order &data)
    {
        if(head == nullptr)
        {
            head = new OrderNode;
            tail = head;
            head->data = data;
        }
        else
        {
            tail->next = new OrderNode;
            tail->next->prev = tail;
            tail = tail->next;
            tail->data = data;
        }
        size++;
        return;
    }
    void Remove(OrderNode* node)
    {
        if(node == nullptr) return;

        if(node->prev != nullptr) node->prev->next = node->next;
        else head = node->next;
        if(node->next != nullptr) node->next->prev = node->prev;
        else tail = node->prev;

        delete node;
        size--;
    }
    void Reverse()
    {
        OrderNode* ptr = head;
        OrderNode* temp = nullptr;

        while(ptr != nullptr)
        {
            temp = ptr->next;
            ptr->next = ptr->prev;
            ptr->prev = temp;
            ptr = temp;
        }
        temp = head;
        head = tail;
        tail = temp;
    }
    void Clear()
    {
        OrderNode* temp = nullptr;
        OrderNode* ptr = head;
        while(ptr != nullptr)
        {
            temp = ptr->next;
            delete ptr;
            ptr = temp;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
};

struct QNode
{
    Order* order = nullptr;
    QNode* next = nullptr;
};

struct PriorityQueue
{
    QNode* head = nullptr;
    int size = 0;

    void Enqueue(Order* order)
    {
        if(order == nullptr) return;

        QNode* node = new QNode;
        node->order = order;
        node->next = nullptr;

        if(head == nullptr || order->priority > head->order->priority)
        {
            node->next = head;
            head = node;
        }
        else
        {
            QNode* ptr = head;

            while(ptr->next != nullptr &&
                ptr->next->order->priority >= order->priority)
            {
                ptr = ptr->next;
            }

            node->next = ptr->next;
            ptr->next = node;
        }

        size++;
    }
    Order* Dequeue()
    {
        if(head == nullptr) return nullptr;

        QNode* copy = head;
        Order* order = copy->order;

        head = head->next;
        delete copy;
        size--;

        return order;
    }

    void RemoveFromQueue(Order* order)
    {
        QNode* ptr = head;
        QNode* prev = nullptr;

        while(ptr != nullptr)
        {
            if(ptr->order == order)
            {
                if(ptr == head)
                {
                    head = ptr->next;
                }
                else
                {
                    prev->next = ptr->next;
                }

                delete ptr;
                size--;
                return;
            }

            prev = ptr;
            ptr = ptr->next;
        }
    }

    void ClearQueue()
    {
        QNode* temp = nullptr;
        QNode* ptr = head;
        while(ptr != nullptr)
        {
            temp = ptr->next;
            delete ptr;
            ptr = temp;
        }
        head = nullptr;
        size = 0;
    }
};

struct Master
{
    char name[24];
    int completed = 0;
    Money earnings = {0, 0};
    Master* next = nullptr;
};

struct MasterRing
{
    Master* first = nullptr;
    Master* last = nullptr;
    Master* current = nullptr;
    int size = 0;

    void Add(const char* name)
    {
        Master* master = new Master;
        strcpy(master->name, name);
        if(first == nullptr)
        {
            first = master;
            last = master;
            master->next = first;
            current = first;
        }
        else
        {
            last->next = master;
            last = master;
            last->next = first;
        }
        size++;
    }

    Master* TakeNext()
    {
        if(first == nullptr) return nullptr;
        Master* ret = current;
        current = current->next;
        return ret;
    }

    Master* FindByName(const char* name)
    {
        if(first == nullptr) return nullptr;
        Master* ptr = first;
        do
        {
            if(strcmp(ptr->name, name) == 0)
            {
                return ptr;
            }
            ptr = ptr->next;
        }while(ptr != first);
        return nullptr;
    }

    void Clear()
    {
        if(first == nullptr) return;

        last->next = nullptr;

        Master* temp = nullptr;
        Master* ptr = first;

        while(ptr != nullptr)
        {
            temp = ptr->next;
            delete ptr;
            ptr = temp;
        }

        first = nullptr;
        last = nullptr;
        current = nullptr;
        size = 0;
    }
};

struct Action
{
    ActionType type;
    Order order;
    Action* next = nullptr;
};

struct ActionStack
{
    Action* top = nullptr;
    int size = 0;

    void Push(ActionType type, const Order &order)
    {
        Action* action = new Action;
        action->type = type;
        action->order = order;
        action->next = top;
        top = action;
        size++;
        return;
    }

    bool Pop(ActionType &type, Order &order)
    {
        if(top == nullptr) return false;
        type = top->type;
        order = top->order;
        Action* ptr = top;
        top = top->next;
        delete ptr;
        size--;
        return true;
    }

    void Clear()
    {
        Action* ptr = top;
        while(ptr != nullptr)
        {
            Action* temp = ptr->next;
            delete ptr;
            ptr = temp;
        }
        top = nullptr;
        size = 0;
    }
};

struct NumNode
{
    Money value;
    NumNode* next = nullptr;
};

struct NumStack
{
    NumNode* top = nullptr;
    int size = 0;

    void Push(const Money &value)
    {
        NumNode* node = new NumNode;
        node->value = value;
        node->next = top;
        top = node;
        size++;
    }

    bool Pop(Money &value)
    {
        if(top == nullptr) return false;

        value = top->value;
        NumNode* ptr = top;
        top = top->next;
        delete ptr;
        size--;

        return true;
    }

    void Clear()
    {
        NumNode* ptr = top;
        while(ptr != nullptr)
        {
            NumNode* temp = ptr->next;
            delete ptr;
            ptr = temp;
        }

        top = nullptr;
        size = 0;
    }
};

Money operator+(const Money &a, const Money &b);
Money operator-(const Money &a, const Money &b);
Money operator*(const Money &a, int k);
bool operator<(const Money &a, const Money &b);
std::ostream &operator<<(std::ostream &os, const Money &money);

std::ostream &operator<<(std::ostream &os, const Order &order);
OrderNode *findById(const OrderList &list, int id);

bool evalRPN(const char *expr, Money &res);

Money revenue(const OrderNode *p);

bool readLine(char* buffer, int capacity);
bool parseInt(const char* text, int &value);
bool validLatinName(const char* name, int maxLength);
bool validPhone(const char* phone);
bool parseDate(const char* text, Date &date);
bool readMasters(MasterRing &masters);
bool readOrder(Order &order);
bool parseMoney(const char* token, Money &value);
void addOrder(OrderList &list, PriorityQueue &queue, ActionStack &history, int &nextId);
void printJournal(const OrderList &list, const PriorityQueue &queue);
void reverseJournal(OrderList &list);
void assignOrder(PriorityQueue &queue, MasterRing &masters);
void finishRepair(OrderList &list, MasterRing &masters);
void deleteOrder(OrderList &list, PriorityQueue &queue, ActionStack &history);
void undoAction(OrderList &list, PriorityQueue &queue, ActionStack &history);
void printReport(const OrderList &list, const MasterRing &masters);

int main()
{
    OrderList list;
    PriorityQueue queue;
    MasterRing masters;
    ActionStack history;
    int nextId = 101;

    if(!readMasters(masters))
    {
        masters.Clear();
        return 0;
    }

    char line[512];
    bool running = true;

    while(running)
    {
        printMenu();

        if(!readLine(line, sizeof(line)))
        {
            if(std::cin.eof()) break;
            continue;
        }

        int choice;
        if(!parseInt(line, choice))
        {
            std::cout << "Помилка: введіть номер пункту меню.\n";
            continue;
        }

        switch(choice)
        {
            case 1: addOrder(list, queue, history, nextId); break;
            case 2: printJournal(list, queue); break;
            case 3: assignOrder(queue, masters); break;
            case 4: finishRepair(list, masters); break;
            case 5: deleteOrder(list, queue, history); break;
            case 6: undoAction(list, queue, history); break;
            case 7: printReport(list, masters); break;
            case 8: reverseJournal(list); break;
            case 0: running = false; break;
            default:
                std::cout << "Помилка: пункту " << choice << " немає в меню.\n";
        }

        if(std::cin.eof()) break;
    }

    queue.ClearQueue();
    history.Clear();
    list.Clear();
    masters.Clear();
    return 0;
}

Money operator+(const Money &a, const Money &b)
{
    Money sum;
    sum.hrn = a.hrn + b.hrn;
    sum.kop = a.kop + b.kop;
    if(sum.kop >= 100)
    {
        sum.kop -= 100;
        sum.hrn++;
    }
    return sum;
}
Money operator-(const Money &a, const Money &b)
{
    Money sum;
    sum.hrn = a.hrn - b.hrn;
    sum.kop = a.kop - b.kop;
    if(sum.kop < 0)
    {
        sum.kop += 100;
        sum.hrn--;
    }
    return sum;
}
Money operator*(const Money &a, int k)
{
    Money sum;
    sum.hrn = a.hrn * k;
    sum.kop = a.kop * k;
    while(sum.kop >= 100)
    {
        sum.kop -= 100;
        sum.hrn++;
    }
    return sum;
}
bool operator<(const Money &a, const Money &b)
{
    if(a.hrn == b.hrn)
    {
        return a.kop < b.kop;
    }
    return a.hrn < b.hrn;
}
std::ostream &operator<<(std::ostream &os, const Money &money)
{
    os << money.hrn << ".";
    if(money.kop < 10) os << '0';
    os << money.kop << " грн";
    return os;
}

OrderNode *findById(const OrderList &list, int id)
{
    OrderNode* ptr = list.head;
    while(ptr != nullptr)
    {
        if(ptr->data.id == id)
        {
            return ptr;
        }
        ptr = ptr->next;
    }
    return nullptr;
}

bool evalRPN(const char* expr, Money &res)
{
    if(expr == nullptr)
    {
        std::cout << "Помилка у виразі: порожній вираз.\n";
        return false;
    }

    char* copy = new char[strlen(expr) + 1];
    strcpy(copy, expr);
    NumStack stack;
    char* token = strtok(copy, " \t");

    if(token == nullptr)
    {
        std::cout << "Помилка у виразі: порожній вираз.\n";
        delete[] copy;
        return false;
    }

    while(token != nullptr)
    {
        if(strcmp(token, "+") == 0 ||
           strcmp(token, "-") == 0 ||
           strcmp(token, "*") == 0)
        {
            Money money1, money2, result;
            bool res1 = stack.Pop(money1);
            bool res2 = stack.Pop(money2);

            if(!(res1 && res2))
            {
                std::cout << "Помилка у виразі: для операції «" << token
                          << "» бракує чисел.\n";
                stack.Clear();
                delete[] copy;
                return false;
            }

            long long a = 1LL * money2.hrn * 100 + money2.kop;
            long long b = 1LL * money1.hrn * 100 + money1.kop;

            if(strcmp(token, "+") == 0)
            {
                if(a + b > 10000000LL)
                {
                    std::cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                    stack.Clear();
                    delete[] copy;
                    return false;
                }
                result = money2 + money1;
            }
            else if(strcmp(token, "-") == 0)
            {
                if(money2 < money1)
                {
                    std::cout << "Помилка у виразі: проміжний результат від'ємний.\n";
                    stack.Clear();
                    delete[] copy;
                    return false;
                }
                result = money2 - money1;
            }
            else
            {
                if(money1.kop != 0 || money1.hrn < 1 || money1.hrn > 100)
                {
                    std::cout << "Помилка у виразі: множник має бути цілим числом від 1 до 100.\n";
                    stack.Clear();
                    delete[] copy;
                    return false;
                }
                if(a * money1.hrn > 10000000LL)
                {
                    std::cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                    stack.Clear();
                    delete[] copy;
                    return false;
                }
                result = money2 * money1.hrn;
            }
            stack.Push(result);
        }
        else
        {
            Money number;
            if(!parseMoney(token, number))
            {
                std::cout << "Помилка у виразі: «" << token
                          << "» не є числом або операцією.\n";
                stack.Clear();
                delete[] copy;
                return false;
            }
            if(number.hrn > 100000 ||
               (number.hrn == 100000 && number.kop > 0))
            {
                std::cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                stack.Clear();
                delete[] copy;
                return false;
            }
            stack.Push(number);
        }
        token = strtok(nullptr, " \t");
    }

    if(stack.size != 1)
    {
        std::cout << "Помилка у виразі: у стеку залишилось чисел: "
                  << stack.size << ", а має бути одне.\n";
        stack.Clear();
        delete[] copy;
        return false;
    }

    if(stack.top->value.hrn == 0 && stack.top->value.kop == 0)
    {
        std::cout << "Помилка у виразі: кінцева вартість не може бути нульовою.\n";
        stack.Clear();
        delete[] copy;
        return false;
    }

    res = stack.top->value;
    stack.Clear();
    delete[] copy;
    return true;
}

bool parseMoney(const char* token, Money &value)
{
    if(token == nullptr || token[0] == '\0') return false;

    int i = 0;
    int hrn = 0;
    int kop = 0;
    int digits = 0;

    while(token[i] >= '0' && token[i] <= '9')
    {
        if(digits >= 6) return false;

        hrn = hrn * 10 + (token[i] - '0');
        digits++;
        i++;
    }

    if(digits == 0) return false;

    if(token[i] == '.')
    {
        i++;
        digits = 0;

        while(token[i] >= '0' && token[i] <= '9')
        {
            if(digits >= 2) return false;

            kop = kop * 10 + (token[i] - '0');
            digits++;
            i++;
        }

        if(digits == 0) return false;
        if(digits == 1) kop *= 10;
    }

    if(token[i] != '\0') return false;

    value.hrn = hrn;
    value.kop = kop;

    return true;
}

bool readLine(char* buffer, int capacity)
{
    if(std::cin.getline(buffer, capacity))
    {
        int len = strlen(buffer);
        if(len > 0 && buffer[len - 1] == '\r') buffer[len - 1] = '\0';
        return true;
    }
    if(std::cin.eof()) return false;

    std::cin.clear();
    char ch;
    while(std::cin.get(ch) && ch != '\n') {}
    std::cout << "Помилка: введений рядок надто довгий.\n";
    return false;
}

bool parseInt(const char* text, int &value)
{
    if(text == nullptr) return false;
    int i = 0;
    while(text[i] == ' ' || text[i] == '\t') i++;

    bool negative = false;
    if(text[i] == '+' || text[i] == '-')
    {
        negative = (text[i] == '-');
        i++;
    }
    if(text[i] < '0' || text[i] > '9') return false;

    long long result = 0;
    long long limit = negative ? 2147483648LL : 2147483647LL;
    while(text[i] >= '0' && text[i] <= '9')
    {
        int digit = text[i] - '0';
        if(result > (limit - digit) / 10) return false;
        result = result * 10 + digit;
        i++;
    }
    while(text[i] == ' ' || text[i] == '\t') i++;
    if(text[i] != '\0') return false;

    value = (int)(negative ? -result : result);
    return true;
}

bool validLatinName(const char* name, int maxLength)
{
    if(name == nullptr) return false;
    int len = strlen(name);
    if(len < 1 || len > maxLength) return false;
    for(int i = 0; i < len; i++)
    {
        if(!((name[i] >= 'A' && name[i] <= 'Z') ||
             (name[i] >= 'a' && name[i] <= 'z'))) return false;
    }
    return true;
}

bool validPhone(const char* phone)
{
    if(phone == nullptr || strlen(phone) != 10 || phone[0] != '0')
        return false;
    for(int i = 0; i < 10; i++)
        if(phone[i] < '0' || phone[i] > '9') return false;
    return true;
}

bool parseDate(const char* text, Date &date)
{
    if(text == nullptr || strlen(text) != 10 ||
       text[2] != '.' || text[5] != '.') return false;

    for(int i = 0; i < 10; i++)
    {
        if(i == 2 || i == 5) continue;
        if(text[i] < '0' || text[i] > '9') return false;
    }

    int day = (text[0] - '0') * 10 + (text[1] - '0');
    int month = (text[3] - '0') * 10 + (text[4] - '0');
    int year = (text[6] - '0') * 1000 + (text[7] - '0') * 100
             + (text[8] - '0') * 10 + (text[9] - '0');

    if(year < 2000 || year > 2099 || month < 1 || month > 12)
        return false;

    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool leap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    if(leap) days[1] = 29;
    if(day < 1 || day > days[month - 1]) return false;

    date.day = day;
    date.month = month;
    date.year = year;
    return true;
}

bool readMasters(MasterRing &masters)
{
    char line[256];
    std::cout << "Кількість майстрів (від 1 до 5): ";
    if(!readLine(line, sizeof(line))) return false;

    int n;
    if(!parseInt(line, n) || n < 1 || n > 5)
    {
        std::cout << "Помилка: кількість майстрів має бути від 1 до 5.\n";
        return false;
    }

    std::cout << "Імена майстрів через пробіл: ";
    if(!readLine(line, sizeof(line))) return false;

    int count = 0;
    char* name = strtok(line, " \t");
    while(name != nullptr)
    {
        if(count == n || !validLatinName(name, 23))
        {
            std::cout << "Помилка: кількість імен має дорівнювати " << n
                      << ", кожне ім'я з латинських літер, до 23 символів.\n";
            return false;
        }
        if(masters.FindByName(name) != nullptr)
        {
            std::cout << "Помилка: імена майстрів не повинні повторюватися.\n";
            return false;
        }
        masters.Add(name);
        count++;
        name = strtok(nullptr, " \t");
    }

    if(count != n)
    {
        std::cout << "Помилка: кількість імен має дорівнювати " << n
                  << ", кожне ім'я з латинських літер, до 23 символів.\n";
        return false;
    }
    return true;
}

bool readOrder(Order &order)
{
    char line[512];
    std::cout << "Ім'я клієнта: ";
    if(!readLine(line, sizeof(line))) return false;
    if(!validLatinName(line, 15))
    {
        std::cout << "Помилка: ім'я має містити від 1 до 15 латинських літер.\n";
        return false;
    }
    strcpy(order.client.name, line);

    std::cout << "Телефон (10 цифр): ";
    if(!readLine(line, sizeof(line))) return false;
    if(!validPhone(line))
    {
        std::cout << "Помилка: телефон має складатися з 10 цифр і починатися з 0.\n";
        return false;
    }
    strcpy(order.client.phone, line);

    std::cout << "Дата прийому (ДД.ММ.РРРР): ";
    if(!readLine(line, sizeof(line))) return false;
    if(!parseDate(line, order.date))
    {
        std::cout << "Помилка: некоректна дата.\n";
        return false;
    }

    std::cout << "Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ";
    if(!readLine(line, sizeof(line))) return false;
    int type;
    if(!parseInt(line, type) || type < 1 || type > 3)
    {
        std::cout << "Помилка: тип пристрою має бути 1, 2 або 3.\n";
        return false;
    }
    order.type = static_cast<DeviceType>(type);

    if(order.type == DeviceType::PHONE)
    {
        std::cout << "Останні 6 цифр IMEI: ";
        if(!readLine(line, sizeof(line))) return false;
        if(strlen(line) != 6)
        {
            std::cout << "Помилка: потрібно рівно 6 цифр.\n";
            return false;
        }
        int imei = 0;
        for(int i = 0; i < 6; i++)
        {
            if(line[i] < '0' || line[i] > '9')
            {
                std::cout << "Помилка: потрібно рівно 6 цифр.\n";
                return false;
            }
            imei = imei * 10 + (line[i] - '0');
        }
        order.info.imei = imei;
    }
    else if(order.type == DeviceType::LAPTOP)
    {
        std::cout << "Серійний номер: ";
        if(!readLine(line, sizeof(line))) return false;
        int len = strlen(line);
        if(len < 1 || len > 11)
        {
            std::cout << "Помилка: серійний номер має містити від 1 до 11 великих літер або цифр.\n";
            return false;
        }
        for(int i = 0; i < len; i++)
        {
            if(!((line[i] >= 'A' && line[i] <= 'Z') ||
                 (line[i] >= '0' && line[i] <= '9')))
            {
                std::cout << "Помилка: серійний номер має містити від 1 до 11 великих літер або цифр.\n";
                return false;
            }
        }
        strcpy(order.info.serial, line);
    }
    else
    {
        std::cout << "Діагональ (19–100 дюймів): ";
        if(!readLine(line, sizeof(line))) return false;
        int inches;
        if(!parseInt(line, inches) || inches < 19 || inches > 100)
        {
            std::cout << "Помилка: діагональ має бути від 19 до 100 дюймів.\n";
            return false;
        }
        order.info.inches = inches;
    }

    std::cout << "Опис несправності: ";
    if(!readLine(line, sizeof(line))) return false;
    if(strlen(line) < 1 || strlen(line) > 80)
    {
        std::cout << "Помилка: опис несправності має містити від 1 до 80 байтів.\n";
        return false;
    }
    strcpy(order.problem, line);

    std::cout << "Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ";
    if(!readLine(line, sizeof(line))) return false;
    if(!parseInt(line, order.priority) || order.priority < 1 || order.priority > 3)
    {
        std::cout << "Помилка: пріоритет має бути 1, 2 або 3.\n";
        return false;
    }

    std::cout << "Вартість (обернений польський запис): ";
    if(!readLine(line, sizeof(line))) return false;
    if(!evalRPN(line, order.price)) return false;

    order.status = Status::WAITING;
    order.master[0] = '\0';
    return true;
}

void addOrder(OrderList &list, PriorityQueue &queue, ActionStack &history, int &nextId)
{
    Order order = {};
    if(!readOrder(order)) return;

    order.id = nextId;
    nextId++;
    list.Append(order);
    Order* stored = &list.tail->data;
    queue.Enqueue(stored);
    history.Push(ActionType::ADD, *stored);

    std::cout << "Замовлення №" << order.id << " додано: вартість "
              << order.price << ", у черзі на ремонт: " << queue.size << ".\n";
}

std::ostream &operator<<(std::ostream &os, const Order &order)
{
    const char* type = order.type == DeviceType::PHONE ? "PHONE" :
                       order.type == DeviceType::LAPTOP ? "LAPTOP" : "TV";
    const char* status = order.status == Status::WAITING ? "WAITING" :
                         order.status == Status::REPAIR ? "REPAIR" : "DONE";

    char date[16];
    char details[24];
    char amount[20];
    snprintf(date, sizeof(date), "%02d.%02d.%04d", order.date.day, order.date.month, order.date.year);

    if(order.type == DeviceType::PHONE)
        snprintf(details, sizeof(details), "IMEI %06d", order.info.imei);
    else if(order.type == DeviceType::LAPTOP)
        snprintf(details, sizeof(details), "SN %s", order.info.serial);
    else
        snprintf(details, sizeof(details), "%d inch", order.info.inches);

    snprintf(amount, sizeof(amount), "%d.%02d", order.price.hrn, order.price.kop);

    os << "| " << std::right << std::setw(3) << order.id
       << " | " << std::left  << std::setw(15) << order.client.name
       << " | " << std::setw(10) << order.client.phone
       << " | " << std::setw(10) << date
       << " | " << std::setw(6) << type
       << " | " << std::setw(14) << details
       << " | " << std::right << std::setw(2) << order.priority
       << " | " << std::left  << std::setw(7) << status
       << " | " << std::right << std::setw(9) << amount << " |";
    return os;
}

void printJournal(const OrderList &list, const PriorityQueue &queue)
{
    if(list.head == nullptr)
    {
        std::cout << "Журнал порожній.\n";
        return;
    }

    const char* border = "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+";
    std::cout << border << '\n';
    std::cout << "|   № | Клієнт          | Телефон    | Дата       | Тип    | Деталі         | Пр | Статус  |  Вартість |\n";
    std::cout << border << '\n';
    OrderNode* ptr = list.head;
    while(ptr != nullptr)
    {
        std::cout << ptr->data << '\n';
        ptr = ptr->next;
    }
    std::cout << border << '\n';
    std::cout << "Усього замовлень: " << list.size
              << ", у черзі на ремонт: " << queue.size << '\n';
}

void reverseJournal(OrderList &list)
{
    if(list.head == nullptr)
    {
        std::cout << "Журнал порожній.\n";
        return;
    }
    list.Reverse();
    std::cout << "Журнал розвернуто: тепер першим іде замовлення №"
              << list.head->data.id << ", останнім №"
              << list.tail->data.id << ".\n";
}

void assignOrder(PriorityQueue &queue, MasterRing &masters)
{
    if(queue.head == nullptr)
    {
        std::cout << "Черга на ремонт порожня.\n";
        return;
    }

    Order* order = queue.Dequeue();
    Master* master = masters.TakeNext();
    if(master == nullptr)
    {
        queue.Enqueue(order);
        std::cout << "Помилка: немає жодного майстра.\n";
        return;
    }

    order->status = Status::REPAIR;
    strcpy(order->master, master->name);

    std::cout << "Замовлення №" << order->id << " (пріоритет " << order->priority
              << ") передано майстру " << master->name << ".\n";
    std::cout << "Несправність: " << order->problem << '\n';
    std::cout << "У черзі залишилось: " << queue.size << '\n';
}

bool readOrderId(int &id)
{
    char line[512];
    std::cout << "Номер замовлення: ";
    if(!readLine(line, sizeof(line))) return false;
    if(!parseInt(line, id))
    {
        std::cout << "Помилка: номер замовлення має бути цілим числом.\n";
        return false;
    }
    return true;
}

void finishRepair(OrderList &list, MasterRing &masters)
{
    int id;
    if(!readOrderId(id)) return;

    OrderNode* node = findById(list, id);
    if(node == nullptr)
    {
        std::cout << "Замовлення №" << id << " не знайдено.\n";
        return;
    }
    Order &order = node->data;
    if(order.status == Status::WAITING)
    {
        std::cout << "Замовлення №" << id << " ще не передано майстру.\n";
        return;
    }
    if(order.status == Status::DONE)
    {
        std::cout << "Замовлення №" << id << " уже завершено.\n";
        return;
    }

    Master* master = masters.FindByName(order.master);
    if(master == nullptr)
    {
        std::cout << "Помилка: майстра замовлення не знайдено.\n";
        return;
    }

    order.status = Status::DONE;
    master->completed++;
    master->earnings = master->earnings + order.price;

    std::cout << "Ремонт замовлення №" << id << " завершено. Майстер "
              << master->name << ": виконано " << master->completed
              << ", виручка " << master->earnings << ".\n";
}

void deleteOrder(OrderList &list, PriorityQueue &queue, ActionStack &history)
{
    int id;
    if(!readOrderId(id)) return;

    OrderNode* node = findById(list, id);
    if(node == nullptr)
    {
        std::cout << "Замовлення №" << id << " не знайдено.\n";
        return;
    }
    if(node->data.status != Status::WAITING)
    {
        std::cout << "Видалити можна лише замовлення, яке очікує в черзі.\n";
        return;
    }

    Order saved = node->data;
    queue.RemoveFromQueue(&node->data);
    list.Remove(node);
    history.Push(ActionType::REMOVE, saved);

    std::cout << "Замовлення №" << id << " видалено. У журналі: " << list.size
              << ", у черзі: " << queue.size << ".\n";
}

void undoAction(OrderList &list, PriorityQueue &queue, ActionStack &history)
{
    ActionType type;
    Order saved;
    if(!history.Pop(type, saved))
    {
        std::cout << "Немає дій для скасування.\n";
        return;
    }

    if(type == ActionType::ADD)
    {
        OrderNode* node = findById(list, saved.id);
        if(node == nullptr)
        {
            std::cout << "Додавання замовлення №" << saved.id
                      << " скасувати неможливо: замовлення відсутнє в журналі.\n";
            return;
        }
        if(node->data.status != Status::WAITING)
        {
            std::cout << "Додавання замовлення №" << saved.id
                      << " скасувати неможливо: його вже передано майстру.\n";
            return;
        }
        queue.RemoveFromQueue(&node->data);
        list.Remove(node);
        std::cout << "Скасовано додавання замовлення №" << saved.id << ".\n";
    }
    else
    {
        list.Append(saved);
        queue.Enqueue(&list.tail->data);
        std::cout << "Скасовано видалення замовлення №" << saved.id
                  << ": його повернуто в кінець журналу і в чергу.\n";
    }
}

Money revenue(const OrderNode *p)
{
    if(p == nullptr) return Money(0, 0);
    Money rest = revenue(p->next);
    if(p->data.status == Status::DONE) return p->data.price + rest;
    return rest;
}

bool beforeInReport(const Order* a, const Order* b)
{
    if(b->price < a->price) return true;
    if(a->price < b->price) return false;
    return a->id < b->id;
}

void quickSort(Order* arr[], int len)
{
    if(len <= 1)
    {
        return;
    }
    Order* pivot = arr[len - 1];
    int i = -1;
    int j = 0;
    while(j < len - 1)
    {
        if(beforeInReport(arr[j], pivot))
        {
            i++;
            Order* temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
        j++;
    }
    arr[len - 1] = arr[i + 1];
    arr[i + 1] = pivot;
    quickSort(arr, i + 1);
    quickSort(arr + i + 2, len - i - 2);
    return;
}

void printReport(const OrderList &list, const MasterRing &masters)
{
    std::cout << "Замовлення за вартістю:\n";
    if(list.size == 0)
    {
        std::cout << "Журнал порожній.\n";
    }
    else
    {
        Order** items = new Order*[list.size];
        OrderNode* ptr = list.head;
        for(int i = 0; i < list.size; i++)
        {
            items[i] = &ptr->data;
            ptr = ptr->next;
        }

        quickSort(items, list.size);

        for(int i = 0; i < list.size; i++)
        {
            const char* status = items[i]->status == Status::WAITING ? "WAITING" :
                                 items[i]->status == Status::REPAIR ? "REPAIR" : "DONE";
            char amount[20];
            snprintf(amount, sizeof(amount), "%d.%02d", items[i]->price.hrn, items[i]->price.kop);
            std::cout << "  №" << items[i]->id << " " << std::right << std::setw(9)
                      << amount << " грн " << status << '\n';
        }
        Money difference = items[0]->price - items[list.size - 1]->price;
        std::cout << "Різниця між найдорожчим і найдешевшим: "
                  << difference << '\n';
        delete[] items;
    }

    std::cout << "Виручка за завершеними ремонтами: " << revenue(list.head) << '\n';
    std::cout << "Майстри, починаючи з наступного в черзі:\n";
    if(masters.current != nullptr)
    {
        Master* ptr = masters.current;
        do
        {
            std::cout << "  " << std::left << std::setw(7) << ptr->name
                      << " виконано: " << ptr->completed
                      << ", виручка: " << ptr->earnings << '\n';
            ptr = ptr->next;
        }while(ptr != masters.current);
    }
}

void printMenu()
{
    std::cout << "+-------+------------------------------+\n";
    std::cout << "| Пункт |           Операція           |\n";
    std::cout << "+-------+------------------------------+\n";
    std::cout << "|   1   |       Додати замовлення      |\n";
    std::cout << "|   2   |       Журнал замовлень       |\n";
    std::cout << "|   3   |   Видати замовлення майстру  |\n";
    std::cout << "|   4   |       Завершити ремонт       |\n";
    std::cout << "|   5   |      Видалити замовлення     |\n";
    std::cout << "|   6   |     Скасувати останню дію    |\n";
    std::cout << "|   7   |             Звіт             |\n";
    std::cout << "|   8   |       Розвернути журнал      |\n";
    std::cout << "|   0   |             Вийти            |\n";
    std::cout << "+-------+------------------------------+\n";
    std::cout << "Ваш вибір: ";
}

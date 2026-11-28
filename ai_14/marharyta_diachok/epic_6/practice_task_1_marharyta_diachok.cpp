/*  
Задача: Class Practice Task. Задача: Сервісний центр: черга ремонтів. Варіант №3.  
Автор: Дячок Маргарита. 
Група: ШІ-14 
*/ 

#include <iostream>
#include <iomanip>
#include <cstdio> 
#include <cstring>
#include <cctype>

using namespace std;

enum class DeviceType {PHONE = 1, LAPTOP, TV};
enum class Status { WAITING, REPAIR, DONE};
enum class ActionType {ADD, REMOVE};
struct Money { int hrn; int kop;};
struct Client {char name[16]; char phone[11];};
struct Date {int day; int month; int year;};
union DeviceInfo { int imei; char serial[12]; int inches;};
struct Master {char name[24]; int done; Money revenue; Master *next;};
struct Order {int id; Client client; Date date; DeviceType type; DeviceInfo info; char problem[81]; int priority; Money price; Status status; char mname[24];};
struct OPZ {long long cent; OPZ *next;};
struct OrderNode {Order order; OrderNode *prev; OrderNode *next;};
struct OrderList {OrderNode *head = nullptr; OrderNode *tail = nullptr; int size = 0;};
struct QNode {Order *order; QNode *next;};
struct Action {ActionType type; Order order; Action *next;};



Master* createMastersRing(const char names[][24], int n) {
Master *first = nullptr;
Master *last = nullptr;

for (int i = 0; i < n; ++i) {
Master *m = new Master;
strcpy(m->name, names[i]);
m->done = 0;
m->revenue.hrn = 0;
m->revenue.kop = 0;
m->next = nullptr;

if (first == nullptr) first = m; 
else last->next = m;
    last = m;}

if (last != nullptr) last->next = first;

return first;}



void pushAction(Action *&top, ActionType type, const Order &o) {
Action *a = new Action;
a->type = type;
a->order = o;
a->next = top;
top = a;}

void clearActions(Action *&top) {
while (top != nullptr) {
Action *t = top;
top = t->next;
delete t;}}


void clearOrderList(OrderList &orderlist) {
while(orderlist.head != nullptr) {
    OrderNode *temp = orderlist.head;
    orderlist.head = temp->next;
    delete temp;}
    orderlist.tail = nullptr;
    orderlist.size = 0;}


void addToJournal(OrderList &list, Order const &o) {
    OrderNode *no = new OrderNode;
    no->order = o;
    no->next = nullptr;
    no->prev = list.tail;
    if(list.tail != nullptr) list.tail->next = no;
    else list.head = no;
    list.tail = no;
    list.size++;
}

//Однозвʼязний список
void enqueue(QNode *&head, Order *o) {
QNode *n = new QNode;
n->order = o;
if(head == nullptr || head->order->priority < o->priority) {
    n->next = head;
    head = n;
    return;}

QNode *cur = head;
while (cur->next != nullptr && cur->next->order->priority >= o->priority) cur = cur->next;
    n->next = cur->next;
    cur->next = n; 
    return;}


Order *dequeue(QNode *&head) {
if (head == nullptr) return nullptr;
    QNode *h = head;
    Order *o = h->order;
    head = h->next;
    delete h;
    return o;}

int queueSize(const QNode *head) {
    int c = 0;
    for (; head != nullptr; head = head->next) c++;
    return c;}

void clearQueue(QNode *&head) {
while (head != nullptr) {
     QNode *h = head;
        head = h->next;
        delete h;}}


ostream &operator<<(ostream &os, const Order &o) {
char date[16], details[32], price1[32], price[32];

sprintf(date, "%02d.%02d.%04d", o.date.day, o.date.month, o.date.year);
sprintf(price1, "%d.%02d", o.price.hrn, o.price.kop);
sprintf(price, "%9s", price1);

const char *type = "";

switch (o.type) {
    case DeviceType::PHONE:
        type = "PHONE";
        sprintf(details, "IMEI %06d", o.info.imei);
        break;
    case DeviceType::LAPTOP:
        type = "LAPTOP";
        sprintf(details, "SN %s", o.info.serial);
        break;
    case DeviceType::TV:
        type = "TV";
        sprintf(details, "%d inch", o.info.inches);
        break;}

const char *status = "";

switch (o.status) {
    case Status::WAITING: status = "WAITING"; break;
    case Status::REPAIR:  status = "REPAIR";  break;
    case Status::DONE:    status = "DONE";    break;}


return os << "| " << left << setw(3)  << o.id
          << " | " << setw(15) << o.client.name
          << " | " << setw(10) << o.client.phone
          << " | " << setw(10) << date
          << " | " << setw(6)  << type
          << " | " << setw(14) << details
          << " | " << setw(2)  << o.priority
          << " | " << setw(7)  << status
          << " | " << price
          << " |";}



bool readLine(char *buffer, int size) {
    cin.getline(buffer, size);
    if (!cin) return false;
    return true;}

Money convertMoney(long long cent) {Money money; money.hrn = cent / 100; money.kop = cent % 100; return money;}
ostream &operator<<(ostream &os, const Money &money) {
    return os << money.hrn << '.' << right << setfill('0') << setw(2) << money.kop << setfill(' ');}



void clearOPZ(OPZ *&head) {
    while (head != nullptr) { OPZ *t = head; head = head->next; delete t; }}

int rewriteCents(const char *s, long long &cent) {
if (!s) return 0;
int intcount = 0;
int fraccount = 0;
int i = 0;
long long intpart = 0;
long long fracpart = 0;

while(isdigit((unsigned char)s[i])) {
    if (intcount < 7) intpart = intpart * 10 + (s[i] - '0');
    intcount++;
    i++;}

if(intcount == 0) return 0;

if(s[i] == '.') {
i++;
while(isdigit((unsigned char)s[i])) {
if (fraccount < 2) fracpart = fracpart * 10 + (s[i] - '0');
    fraccount++;
    i++;}

if (fraccount == 0 || fraccount > 2) return 0; 
    if (fraccount == 1) {
    fracpart *= 10;}
} 
if(s[i] != '\0') return 0;
if(intcount > 6) return 2;
cent = intpart * 100 + fracpart;
return 1;}

long long toCent(const Money &m) {return (long long)m.hrn * 100 + m.kop;}
Money operator+(const Money &a, const Money &b) {return convertMoney(toCent(a) + toCent(b));}
Money operator-(const Money &a, const Money &b) {return convertMoney(toCent(a) - toCent(b));}
Money operator*(const Money &a, int k) {return convertMoney(toCent(a) * k);}
bool operator<(const Money &a, const Money &b) {return toCent(a) < toCent(b);}


bool evalRPN(const char *expr, Money &res) {
int count = 0;
long long result = 0;
const long long maxcent = 10000000;
char temp[256];
strncpy(temp, expr, 256);
temp[255] = '\0';

OPZ *head = nullptr;
char *token = strtok(temp, " ");
while (token != nullptr) {
    if(strlen(token) == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*')) {

    if (count < 2) {
        cout << "Помилка у виразі: для операції «" << token[0] << "» бракує чисел.\n";
        clearOPZ(head); return false;}
        OPZ *t = head; long long b = t->cent; head = t->next; delete t;
        t = head; long long a = t->cent; head = t->next; delete t;
        count -= 2;

        if (token[0] == '+') result = a + b;

        else if (token[0] == '-') {
                result = a - b;

        if (result < 0) {
        cout << "Помилка у виразі: проміжний результат від'ємний.\n";
        clearOPZ(head); return false;}}

        else { 
        if (b % 100 != 0 || b < 100 || b > 10000) {
cout << "Помилка у виразі: множник має бути цілим числом від 1 до 100.\n";
clearOPZ(head); return false;}
result = a * (b / 100);}}
            
else {
    long long cent = 0;
    int rC = rewriteCents(token, cent);
    if (rC == 0) {
        cout << "Помилка у виразі: «" << token << "» не є числом або операцією.\n";
        clearOPZ(head); return false;}
    if (rC == 2) result = maxcent + 1;
    else result = cent;}

if (result > maxcent) {
cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
clearOPZ(head); return false;}

    OPZ *x = new OPZ;
    x->cent = result;
    x->next = head;
    head = x;
    count++;
    token = strtok(nullptr, " ");}

if (count == 0) {cout << "Помилка у виразі: порожній вираз.\n"; return false;}
if (count > 1) {
    cout << "Помилка у виразі: у стеку залишилось чисел: " << count << ", а має бути одне.\n";
    clearOPZ(head); return false;}
    result = head->cent;
    clearOPZ(head);
if (result == 0) {cout << "Помилка у виразі: вартість не може дорівнювати 0.00.\n"; return false;}
    res = convertMoney(result);
    return true;}



void addOrder(Order &order, int &error) {
error = 0;
char buffer[256];
cout << "Ім'я клієнта: ";
if(!(readLine(buffer, 256))) {cout << "Помилка: ім'я має містити від 1 до 15 латинських літер.\n";error = 1; return;}
if(strlen(buffer) < 1 || strlen(buffer) > 15) {cout << "Помилка: ім'я має містити від 1 до 15 латинських літер.\n"; error = 1; return;}
for (int i = 0; buffer[i] != '\0'; ++i) {
    char c = buffer[i];
    if(!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {cout << "Помилка: ім'я має містити від 1 до 15 латинських літер."; error = 1; return;}}
strcpy(order.client.name, buffer);

cout << "Телефон (10 цифр): ";
if(!(readLine(buffer, 256))) {error = 1; return;}
if(strlen(buffer) != 10 || buffer[0] != '0') {cout << "Помилка: телефон має складатися з 10 цифр і починатися з 0.\n"; error = 1; return;}
for (int i = 0; i < 10; ++i)
    if(!isdigit((unsigned char)buffer[i])) {error = 1; return;}
strcpy(order.client.phone, buffer);

cout << "Дата прийому (ДД.ММ.РРРР): ";
char dt[256];
if(!(readLine(dt, 256))) {error = 1; return;}
if(strlen(dt) != 10 || dt[2] != '.' || dt[5] != '.') {cout << "Помилка: дата має бути у форматі ДД.ММ.РРРР.\n"; error = 1; return;}
for (int i = 0; i < 10; ++i)
    if(i != 2 && i != 5 && !isdigit((unsigned char)dt[i])) {cout << "Помилка: некоректна дата.\n"; error = 1; return;}
order.date.day = (dt[0] - '0') * 10 + (dt[1] - '0');
order.date.month = (dt[3] - '0') * 10 + (dt[4] - '0');
order.date.year = (dt[6] - '0') * 1000 + (dt[7] - '0') * 100 + (dt[8] - '0') * 10 + (dt[9] - '0');
if(order.date.year < 2000 || order.date.year > 2099) {cout << "Помилка: некоректна дата."; error = 1; return;}
if(order.date.month < 1 || order.date.month > 12) {cout << "Помилка: некоректна дата."; error = 1; return;}
if(order.date.day < 1) {cout << "Помилка: некоректна дата."; error = 1; return;}
if(order.date.month == 2) {
bool leap = (order.date.year % 4 == 0 && order.date.year % 100 != 0) || order.date.year % 400 == 0;
    if(leap) {
        if(order.date.day > 29) {cout << "Помилка: некоректна дата."; error = 1; return;}}
    else {
        if(order.date.day > 28) {cout << "Помилка: некоректна дата."; error = 1; return;}}}

else if(order.date.month == 4 || order.date.month == 6 || order.date.month == 9 || order.date.month == 11) {
    if(order.date.day > 30) {cout << "Помилка: некоректна дата."; error = 1; return;}}
    else if(order.date.day > 31) {cout << "Помилка: некоректна дата."; error = 1; return;}

cout << "Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ";
if(!(readLine(buffer, 256))) {error = 1; return;}
if (strlen(buffer) != 1 || buffer[0] < '1' || buffer[0] > '3') {cout << "Помилка: тип пристрою має бути 1, 2 або 3.\n"; error = 1; return;}
order.type = static_cast<DeviceType>(buffer[0] - '0');

switch(order.type) {
    case DeviceType::PHONE :
        cout << "Останні 6 цифр IMEI: ";
        if (!readLine(buffer, 256)) {error = 1; return;}
        if (strlen(buffer) != 6) {cout << "Помилка: потрібно рівно 6 цифр.\n"; error = 1; return;}
        order.info.imei = 0;
        for (int i = 0; i < 6; ++i) {
            if (!isdigit((unsigned char)buffer[i])) {cout << "Помилка: потрібно рівно 6 цифр.\n"; error = 1; return;}
            order.info.imei = order.info.imei * 10 + (buffer[i] - '0');}
        break;
    case DeviceType::LAPTOP :
        cout << "Серійний номер: ";
        if (!readLine(buffer, 256)) {error = 1; return;}
        if (strlen(buffer) < 1 || strlen(buffer) > 11) {cout << "Помилка: серійний номер має бути від 1 до 11 символів.\n"; error = 1; return;}
        for (int i = 0; buffer[i] != '\0'; ++i) {
            char inf = buffer[i];
            if(!((inf >= 'A' && inf <= 'Z') || (inf >= '0' && inf <= '9'))) {cout << "Помилка: некорректний ввід.\n"; error = 1; return;}}
        strcpy(order.info.serial, buffer);
        break;
    case DeviceType::TV :
        cout << "Діагональ: ";
        if(!readLine(buffer, 256)) {error = 1; return;}
        if(strlen(buffer) < 1 || strlen(buffer) > 3) {cout << "Помилка: діагональ має бути від 19 до 100.\n"; error = 1; return;}
        order.info.inches = 0;
        for (int i = 0; buffer[i] != '\0'; ++i) {
            if(!isdigit((unsigned char)buffer[i])) {cout << "Помилка: некорректний ввід.\n"; error = 1; return;}
            order.info.inches = order.info.inches * 10 + (buffer[i] - '0');}
        if (order.info.inches < 19 || order.info.inches > 100) {cout << "Помилка: діагональ має бути від 19 до 100.\n"; error = 1; return;}
    break;}

cout << "Опис несправності: ";
if (!readLine(buffer, 256)) {error = 1; return;}
if (strlen(buffer) < 1 || strlen(buffer) > 80) {
    cout << "Помилка: опис має містити від 1 до 80 байтів.\n"; error = 1; return;}
strcpy(order.problem, buffer);

cout << "Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ";
if (!readLine(buffer, 256)) {error = 1; return;}
if (strlen(buffer) != 1 || buffer[0] < '1' || buffer[0] > '3') {cout << "Помилка: пріоритет має бути 1, 2 або 3.\n"; error = 1; return;}
order.priority = buffer[0] - '0';

cout << "Вартість (обернений польський запис): ";
if(!readLine(buffer, 256)) {error = 1; return;}
if (!evalRPN(buffer, order.price)) {error = 1; return;}

order.status = Status::WAITING;
order.mname[0] = '\0';}




void showJournal(OrderList const &orderlist, QNode const *queuehead) {
    if(orderlist.head == nullptr) {cout << "Журнал порожній.\n"; return;}

cout << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+\n" <<
         "| №   | Клієнт          | Телефон    | Дата       | Тип    | Деталі         | Пр | Статус  | Вартість  |\n" 
       << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+\n";
    
for(const OrderNode *p = orderlist.head; p != nullptr; p = p->next) {
    cout << p->order << endl;}

cout << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+\n";

cout << "Усього замовлень: " << orderlist.size << ", у черзі на ремонт: " << queueSize(queuehead) << '\n';}



void assignOrder(QNode *&queuehead, Master *&nextMaster) {
if (queuehead == nullptr) {
    cout << "Черга на ремонт порожня.\n";
    return;}

Order *o = dequeue(queuehead);
Master *m = nextMaster;
nextMaster = nextMaster->next;

o->status = Status::REPAIR;
strcpy(o->mname, m->name);

cout << "Замовлення №" << o->id << " (пріоритет " << o->priority << ") передано майстру " << m->name << ".\n" << "Несправність: " << o->problem << '\n' << "У черзі залишилось: " << queueSize(queuehead) << '\n';
}

Master* findMasterByName(Master *firstMaster, const char *name) {
if (firstMaster == nullptr) return nullptr;
Master *m = firstMaster;
do {
    if (strcmp(m->name, name) == 0) return m;
    m = m->next;} 
while (m != firstMaster);
    return nullptr;
}


OrderNode *findById(const OrderList &list, int id) {
 for (OrderNode *p = list.head; p != nullptr; p = p->next) if (p->order.id == id) return p;
    return nullptr;}

void finishTheRepair(OrderList &journal, Master *firstMaster) {
char buf[256];
cout << "Номер замовлення: ";
if (!readLine(buf, 256)) return;

int len = strlen(buf);
if (len < 1) {
cout << "Помилка: номер замовлення має бути цілим числом.\n";
    return;}

for (int i = 0; i < len; ++i) {
if (!isdigit((unsigned char)buf[i])) {
cout << "Помилка: номер замовлення має бути цілим числом.\n";
    return;}}

if (len > 9) {
    cout << "Замовлення №" << buf << " не знайдено.\n";
    return;}

int id = 0;
for (int i = 0; i < len; ++i) {
id = id * 10 + (buf[i] - '0');}

OrderNode *node = findById(journal, id);
if (node == nullptr) {
cout << "Замовлення №" << id << " не знайдено.\n";
    return;}

if (node->order.status == Status::WAITING) {
cout << "Замовлення №" << id << " ще не передано майстру.\n";
    return;}

if (node->order.status == Status::DONE) {
cout << "Замовлення №" << id << " уже завершено.\n";
    return;}

Master *m = findMasterByName(firstMaster, node->order.mname);
if (m == nullptr) return;

node->order.status = Status::DONE;
m->done++;
m->revenue = m->revenue + node->order.price;

cout << "Ремонт замовлення №" << id << " завершено. Майстер " << m->name << ": виконано " << m->done << ", виручка " << m->revenue << " грн.\n";
}


void removeFromQueue(QNode *&head, const Order *o) { //Видалення вузла з пріоритетної черги
    if (head == nullptr) return;

    if (head->order == o) {
        QNode *t = head;
        head = t->next;
        delete t;
        return;
    }

    QNode *cur = head;
    while (cur->next != nullptr && cur->next->order != o) {
        cur = cur->next;
    }

    if (cur->next != nullptr) {
        QNode *t = cur->next;
        cur->next = t->next;
        delete t;
    }
}


void removeNode(OrderList &l, OrderNode *p) { //Видалення вузла з двозв'язного списку (журналу)
    if (p->prev != nullptr) p->prev->next = p->next;
    else l.head = p->next;

    if (p->next != nullptr) p->next->prev = p->prev;
    else l.tail = p->prev;

    delete p;
    l.size--;
}



void deleteOrder(OrderList &journal, QNode *&queuehead, Action *&actions) {
char buf[256];
cout << "Номер замовлення: ";
if (!readLine(buf, 256)) return;

int len = strlen(buf);
if (len < 1) {
cout << "Помилка: номер замовлення має бути цілим числом.\n";
    return;}

for (int i = 0; i < len; ++i) {
if (!isdigit((unsigned char)buf[i])) {
cout << "Помилка: номер замовлення має бути цілим числом.\n";
    return;}}

if (len > 9) {
cout << "Замовлення №" << buf << " не знайдено.\n";
    return;}

int id = 0;
for (int i = 0; i < len; ++i) {
id = id * 10 + (buf[i] - '0');}

OrderNode *node = findById(journal, id);
if (node == nullptr) {
cout << "Замовлення №" << id << " не знайдено.\n";
    return;}

if (node->order.status != Status::WAITING) {
cout << "Видалити можна лише замовлення, яке очікує в черзі.\n";
    return;}

pushAction(actions, ActionType::REMOVE, node->order);  
removeFromQueue(queuehead, &node->order);             
removeNode(journal, node);                          

cout << "Замовлення №" << id << " видалено. У журналі: " << journal.size << ", у черзі: " << queueSize(queuehead) << ".\n";
}

void undoAction(OrderList &journal, QNode *&queuehead, Action *&actions) {
if (actions == nullptr) {
    cout << "Немає дій для скасування.\n";
    return;}

Action *a = actions;
actions = a->next;          

if (a->type == ActionType::ADD) {
    OrderNode *node = findById(journal, a->order.id);
    if (node != nullptr && node->order.status == Status::WAITING) {
        int id = node->order.id;
        removeFromQueue(queuehead, &node->order);   
        removeNode(journal, node);                  
        cout << "Додавання замовлення №" << id << " скасовано.\n";} 

    else cout << "Додавання замовлення №" << a->order.id << " скасувати неможливо: його вже передано майстру.\n";} 
    
else {
    addToJournal(journal, a->order);
    enqueue(queuehead, &journal.tail->order);
    cout << "Скасовано видалення замовлення №" << a->order.id << ": його повернуто в кінець журналу і в чергу.\n";}

    delete a;}


void reverseJournal(OrderList &journal) {
if (journal.head == nullptr) {
    cout << "Журнал порожній.\n";
    return;}

OrderNode *cur = journal.head;
while (cur != nullptr) {
    OrderNode *nx = cur->next;   
    cur->next = cur->prev;
    cur->prev = nx;
    cur = nx;}

OrderNode *t = journal.head;
journal.head = journal.tail;
journal.tail = t;

cout << "Журнал розвернуто: тепер першим іде замовлення №" << journal.head->order.id << ", останнім №" << journal.tail->order.id << ".\n";
}



Money revenue(const OrderNode *p) {
if (p == nullptr) return Money{0, 0};      
Money rest = revenue(p->next);
if (p->order.status == Status::DONE) return rest + p->order.price;
return rest;}


const char *statusName(Status s) {
switch (s) {
    case Status::WAITING: return "WAITING";
    case Status::REPAIR:  return "REPAIR";
    case Status::DONE:    return "DONE";}

return "";}




bool comesBefore(const Order *a, const Order *b) {
if (b->price < a->price) return true;
if (a->price < b->price) return false;
return a->id < b->id;}


void report(const OrderList &journal, Master *nextMaster) {
if (journal.head == nullptr) {
    cout << "Журнал порожній.\n";
    return;}

int n = journal.size;
Order **arr = new Order*[n];
int i = 0;
for (OrderNode *p = journal.head; p != nullptr; p = p->next)
arr[i++] = &p->order;

for (int a = 0; a < n - 1; ++a)
    for (int b = 0; b < n - 1 - a; ++b)
        if (comesBefore(arr[b + 1], arr[b])) {
            Order *t = arr[b];
            arr[b] = arr[b + 1];
            arr[b + 1] = t;}

cout << "Замовлення за вартістю:\n";
for (int k = 0; k < n; ++k) {
cout << "№" << arr[k]->id << " " << arr[k]->price << " грн " << statusName(arr[k]->status) << '\n';}

cout << "Різниця між найдорожчим і найдешевшим: " << arr[0]->price - arr[n - 1]->price << " грн\n";

delete[] arr;

cout << "Виручка за завершеними ремонтами: " << revenue(journal.head) << " грн\n";

cout << "Майстри, починаючи з наступного в черзі:\n";
Master *m = nextMaster;
do {
    cout << m->name << " виконано: " << m->done << ", виручка: " << m->revenue << " грн\n";
    m = m->next;
    } while (m != nextMaster);
}

void addOrderFinal(OrderList &journal, QNode *&queuehead, Action *&actions, int &nextId) {
Order order;
int error = 0;

addOrder(order, error);
if (error == 1) return;

order.id = nextId++;
addToJournal(journal, order);
enqueue(queuehead, &journal.tail->order);
pushAction(actions, ActionType::ADD, order);

cout << "Замовлення №" << order.id << " додано: вартість " << order.price << " грн, у черзі на ремонт: " << queueSize(queuehead) << ".\n";
}


int main() {
char names[256];

cout << "Кількість майстрів (від 1 до 5): ";
if (!readLine(names, 256)) return 0;
if (strlen(names) != 1 || names[0] < '1' || names[0] > '5') {
    cout << "Помилка: кількість майстрів має бути цілим числом від 1 до 5.\n";
    return 0;}

int n = names[0] - '0';

cout << "Імена майстрів через пробіл: ";
if (!readLine(names, 256)) return 0;
char list[5][24];
int count_mnames = 0;
char *nm = strtok(names, " ");
while (nm) {
if (count_mnames >= n || strlen(nm) > 23) {
cout << "Помилка: кількість імен має дорівнювати " << n << ", кожне ім'я з латинських літер, до 23 символів.\n";
return 0;}

for (int i = 0; nm[i] != '\0'; ++i)
if (!isalpha((unsigned char)nm[i])) {
cout << "Помилка: кількість імен має дорівнювати " << n << ", кожне ім'я з латинських літер, до 23 символів.\n";
return 0;}

strcpy(list[count_mnames], nm);
count_mnames++;
nm = strtok(nullptr, " ");}
if (count_mnames != n) {
cout << "Помилка: кількість імен має дорівнювати " << n << ", кожне ім'я з латинських літер, до 23 символів.\n";
return 0;}

for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j)
        if (strcmp(list[i], list[j]) == 0) {
            cout << "Помилка: імена майстрів не повинні повторюватися.\n";
            return 0;}

Master *firstMaster = createMastersRing(list, n);
Master *nextMaster = firstMaster;

OrderList journal;
int nextId = 101;
QNode *queuehead = nullptr;   
Action *actions = nullptr;

int menu = -1;
do {
    cout << "\n1. Додати замовлення\n" 
         << "2. Журнал замовлень\n"
         << "3. Видати замовлення майстру\n"
         << "4. Завершити ремонт\n"
         << "5. Видалити замовлення\n"
         << "6. Скасувати останню дію\n"
         << "7. Звіт\n"
         << "8. Розвернути журнал\n"
         << "0. Вийти\n";

cout << "Ваш вибір: ";
char menu_option[256];
if (!readLine(menu_option, 256)) break;

if (strlen(menu_option) != 1 || !isdigit((unsigned char)menu_option[0])) {
    cout << "Помилка: введіть номер пункту меню.\n";
    menu = -1; continue;}

menu = menu_option[0] - '0';
if (menu > 8) {
cout << "Помилка: пункту " << menu << " немає в меню.\n";
menu = -1; continue;}

switch(menu) {
    case 1 : addOrderFinal(journal, queuehead, actions, nextId); break;
    case 2 : showJournal(journal, queuehead); break;
    case 3 : assignOrder(queuehead, nextMaster); break;
    case 4 : finishTheRepair(journal, firstMaster); break;
    case 5 : deleteOrder(journal, queuehead, actions); break;
    case 6 : undoAction(journal, queuehead, actions); break;
    case 7 : report(journal, nextMaster); break;
    case 8 : reverseJournal(journal); break;
    break;
    }
}
while (menu != 0);

Master *last = firstMaster;
while (last->next != firstMaster) last = last->next;
last->next = nullptr;

while (firstMaster != nullptr) {
    Master *t = firstMaster;
    firstMaster = t->next;
    delete t;
}
clearQueue(queuehead);
clearOrderList(journal);
clearActions(actions);
    return 0;
}
/*
Сервісний центр: черга ремонтів
Зубак Тетяна
ШІ-12
*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;
//організація
 //структури і тд
 enum class DeviceType{PHONE = 1, LAPTOP, TV};
 enum class Status{WAITING, REPAIR, DONE};
 enum class ActionType{ADD, REMOVE};

 struct Money{int hrn; int kop;};
 struct Date{int day; int month; int year;};
 struct Client{char name[16]; char phone[11];};
 union DeviceInfo{int imei; char serial[12]; int inches;};
 struct Order{int id; Client client; Date date; DeviceType type; DeviceInfo info; char problem[81]; int priority; Money price; Status status; char master[24];};
 struct OrderNode{Order order; OrderNode *prev; OrderNode *next;};
 struct OrderList{OrderNode *head; OrderNode *tail; int size;};
 struct QNode{Order *order; QNode *next;};
 struct Master{char name[24]; int done; Money sum; Master *next;};
 struct Action{ActionType type; Order order; Action *next;};
 struct Number{Money value; Number *next;};

 //константи
 const int max_line = 256;
 const int max_masters = 5;
 const int max_master_name = 23;
 const int max_client_name = 15;
 const int max_problem = 80;
 const int max_serial = 11;
 const Money max_price = {100000, 0};

 //ввід+валідація
 bool readLine(char *text, int size){
    cin.getline(text, size);
    if(cin.eof() && text[0] == '\0') return false;
    if(cin.fail() && !cin.eof()){
        cin.clear();
        cin.ignore(100000, '\n');
        text[0] = '\0';
    }
    return true;
 }

 bool allDigits(const char *text){
    for(const char *p = text; *p != '\0'; p++){
        if(*p < '0' || *p > '9') return false;
    }
    return true;
 }

 bool parseInt(const char *text, int &value){
    int len = strlen(text);
    if(len < 1 || len > 9 || !allDigits(text)) return false;

    value = 0;
    for(int i = 0; i < len; i++) value = value * 10 + (text[i] - '0');
    return true;
 }

 bool isLetter(char c){
    return (unsigned char)c < 128 && isalpha((unsigned char)c);
 }

 bool validName(const char *text, int max){
    int len = strlen(text);
    if(len < 1 || len > max) return false;
    for(int i = 0; i < len; i++){
        if(!isLetter(text[i])) return false;
    }
    return true;
 }

 //гроші
 Money operator+(const Money &a, const Money &b){
    int k = a.kop + b.kop;
    return {a.hrn + b.hrn + k / 100, k % 100};
 }

 Money operator-(const Money &a, const Money &b){
    int k = (a.hrn - b.hrn) * 100 + a.kop - b.kop;
    return {k / 100, k % 100};
 }

 Money operator*(const Money &a, int n){
    long long k = ((long long)a.hrn * 100 + a.kop) * n;
    return {(int)(k / 100), (int)(k % 100)};
 }

 bool operator<(const Money &a, const Money &b){
    if(a.hrn != b.hrn) return a.hrn < b.hrn;
    return a.kop < b.kop;
 }

 void moneyStr(const Money &m, char *text){
    sprintf(text, "%d.%02d", m.hrn, m.kop);
 }

 ostream &operator<<(ostream &os, const Money &m){
    char text[16];
    moneyStr(m, text);
    return os << text;
 }

 //замовлення
 const char *typeName(DeviceType type){
    if(type == DeviceType::PHONE) return "PHONE";
    if(type == DeviceType::LAPTOP) return "LAPTOP";
    return "TV";
 }

 const char *statusName(Status status){
    if(status == Status::WAITING) return "WAITING";
    if(status == Status::REPAIR) return "REPAIR";
    return "DONE";
 }

 ostream &operator<<(ostream &os, const Order &o){
    char date[16], details[32], price[16];
    sprintf(date, "%02d.%02d.%04d", o.date.day, o.date.month, o.date.year);
    if(o.type == DeviceType::PHONE) sprintf(details, "IMEI %06d", o.info.imei);
    else if(o.type == DeviceType::LAPTOP) sprintf(details, "SN %s", o.info.serial);
    else sprintf(details, "%d inch", o.info.inches);
    moneyStr(o.price, price);

    os << "│ " << right << setw(3) << o.id << " │ " << left << setw(15) << o.client.name;
    os << " │ " << setw(10) << o.client.phone << " │ " << setw(10) << date;
    os << " │ " << setw(6) << typeName(o.type) << " │ " << setw(14) << details;
    os << " │ " << right << setw(2) << o.priority << " │ " << left << setw(7) << statusName(o.status);
    os << " │ " << right << setw(9) << price << " │";
    return os;
 }

 //журнал
 OrderNode *addLast(OrderList &list, const Order &o){
    OrderNode *p = new OrderNode{o, list.tail, nullptr};
    if(list.tail != nullptr) list.tail->next = p;
    else list.head = p;
    list.tail = p;
    list.size++;
    return p;
 }

 OrderNode *findById(const OrderList &list, int id){
    for(OrderNode *p = list.head; p != nullptr; p = p->next){
        if(p->order.id == id) return p;
    }
    return nullptr;
 }

 void removeNode(OrderList &list, OrderNode *p){
    if(p->prev != nullptr) p->prev->next = p->next;
    else list.head = p->next;
    if(p->next != nullptr) p->next->prev = p->prev;
    else list.tail = p->prev;
    delete p;
    list.size--;
 }

 Money revenue(const OrderNode *p){
    if(p == nullptr) return {0, 0};
    Money res = revenue(p->next);
    if(p->order.status == Status::DONE) res = res + p->order.price;
    return res;
 }

 void freeList(OrderList &list){
    while(list.head != nullptr){
        OrderNode *p = list.head->next;
        delete list.head;
        list.head = p;
    }
    list.tail = nullptr;
    list.size = 0;
 }

 //черга на ремонт
 void enqueue(QNode *&head, Order *o){
    QNode *q = new QNode{o, nullptr};
    if(head == nullptr || head->order->priority < o->priority){
        q->next = head;
        head = q;
        return;
    }

    QNode *p = head;
    while(p->next != nullptr && p->next->order->priority >= o->priority) p = p->next;
    q->next = p->next;
    p->next = q;
 }

 Order *dequeue(QNode *&head){
    QNode *p = head;
    Order *o = p->order;
    head = head->next;
    delete p;
    return o;
 }

 void removeFromQueue(QNode *&head, const Order *o){
    QNode *p = head;
    QNode *prev = nullptr;
    while(p != nullptr && p->order != o){
        prev = p;
        p = p->next;
    }
    if(p == nullptr) return;
    if(prev != nullptr) prev->next = p->next;
    else head = p->next;
    delete p;
 }

 int countQueue(const QNode *head){
    int count = 0;
    for(const QNode *p = head; p != nullptr; p = p->next) count++;
    return count;
 }

 void freeQueue(QNode *&head){
    while(head != nullptr){
        QNode *p = head->next;
        delete head;
        head = p;
    }
 }

 //стек дій
 void pushAction(Action *&top, ActionType type, const Order &o){
    top = new Action{type, o, top};
 }

 Action popAction(Action *&top){
    Action *p = top;
    Action res = *p;
    top = top->next;
    delete p;
    return res;
 }

 void freeActions(Action *&top){
    while(top != nullptr){
        Action *p = top->next;
        delete top;
        top = p;
    }
 }

 //майстри
 bool splitNames(char *line, int n, char **words){
    int count = 0;
    bool ok = true;

    char *t = strtok(line, " ");
    while(t != nullptr){
        if(count >= n || !validName(t, max_master_name)) ok = false;
        else words[count] = t;
        count++;
        t = strtok(nullptr, " ");
    }
    if(!ok || count != n){
        cout << "Помилка: кількість імен має дорівнювати " << n << ", кожне ім'я з латинських літер, до " << max_master_name << " символів." << endl;
        return false;
    }
    for(int i = 1; i < n; i++){
        for(int j = 0; j < i; j++){
            if(strcmp(words[i], words[j]) == 0){
                cout << "Помилка: імена майстрів не повинні повторюватися." << endl;
                return false;
            }
        }
    }
    return true;
 }

 Master *makeMasters(char **words, int n){
    Master *head = nullptr;
    Master *tail = nullptr;

    for(int i = 0; i < n; i++){
        Master *p = new Master{};
        strcpy(p->name, words[i]);
        if(head == nullptr) head = p;
        else tail->next = p;
        tail = p;
    }
    tail->next = head;
    return head;
 }

 Master *readMasters(){
    char line[max_line];
    char *words[max_masters];
    int n = 0;

    cout << "Кількість майстрів: ";
    if(!readLine(line, max_line)) return nullptr;
    if(!parseInt(line, n) || n < 1 || n > max_masters){
        cout << "Помилка: кількість майстрів має бути цілим числом від 1 до " << max_masters << "." << endl;
        return nullptr;
    }
    cout << "Імена майстрів через пробіл: ";
    if(!readLine(line, max_line)) return nullptr;
    if(!splitNames(line, n, words)) return nullptr;

    return makeMasters(words, n);
 }

 Master *findMaster(Master *turn, const char *name){
    Master *p = turn;
    do{
        if(strcmp(p->name, name) == 0) return p;
        p = p->next;
    } while(p != turn);
    return nullptr;
 }

 void freeMasters(Master *&turn){
    if(turn == nullptr) return;

    Master *p = turn->next;
    while(p != turn){
        Master *t = p->next;
        delete p;
        p = t;
    }
    delete turn;
    turn = nullptr;
 }

 //вираз вартості

 void pushNumber(Number *&top, const Money &m){
    top = new Number{m, top};
 }

 Money popNumber(Number *&top){
    Number *p = top;
    Money res = p->value;
    top = top->next;
    delete p;
    return res;
 }

 void freeNumbers(Number *&top){
    while(top != nullptr) popNumber(top);
 }

 bool rpnFail(Number *&top){
    freeNumbers(top);
    return false;
 }

 bool isOperation(const char *text){
    return strlen(text) == 1 && (text[0] == '+' || text[0] == '-' || text[0] == '*');
 }

 bool parseMoney(const char *text, Money &m){
    int hrn = 0, kop = 0;
    int pos = 0;

    while(text[pos] >= '0' && text[pos] <= '9'){
        hrn = hrn * 10 + (text[pos] - '0');
        pos++;
    }
    if(pos < 1 || pos > 6) return false;
    if(text[pos] == '.'){
        pos++;
        int start = pos;
        while(text[pos] >= '0' && text[pos] <= '9'){
            kop = kop * 10 + (text[pos] - '0');
            pos++;
        }
        if(pos - start < 1 || pos - start > 2) return false;
        if(pos - start == 1) kop *= 10;
    }
    if(text[pos] != '\0') return false;
    m = {hrn, kop};
    return true;
 }

 bool overLimit(const Money &m){
    if(max_price < m){
        cout << "Помилка у виразі: сума перевищує 100000.00 грн." << endl;
        return true;
    }
    return false;
 }

 bool applyOperation(char op, const Money &a, const Money &b, Money &res){
    if(op == '+') res = a + b;
    else if(op == '-'){
        if(a < b){
            cout << "Помилка у виразі: проміжний результат від'ємний." << endl;
            return false;
        }
        res = a - b;
    }
    else{
        if(b.kop != 0 || b.hrn < 1 || b.hrn > 100){
            cout << "Помилка у виразі: множник має бути цілим числом від 1 до 100." << endl;
            return false;
        }
        res = a * b.hrn;
    }
    return !overLimit(res);
 }

 bool evalRPN(const char *expr, Money &res){
    char buf[max_line];
    Number *top = nullptr;
    int count = 0;
    strcpy(buf, expr);

    char *t = strtok(buf, " ");
    if(t == nullptr){
        cout << "Помилка у виразі: порожній вираз." << endl;
        return false;
    }

    while(t != nullptr){
        Money m = {0, 0};
        if(isOperation(t)){
            if(count < 2){
                cout << "Помилка у виразі: для операції «" << t << "» бракує чисел." << endl;
                return rpnFail(top);
            }
            Money b = popNumber(top);
            Money a = popNumber(top);
            count -= 2;
            if(!applyOperation(t[0], a, b, m)) return rpnFail(top);
        }
        else if(parseMoney(t, m)){
            if(overLimit(m)) return rpnFail(top);
        }
        else{
            cout << "Помилка у виразі: «" << t << "» не є числом або операцією." << endl;
            return rpnFail(top);
        }
        pushNumber(top, m);
        count++;
        t = strtok(nullptr, " ");
    }

    if(count != 1){
        cout << "Помилка у виразі: у стеку залишилось чисел: " << count << ", а має бути одне." << endl;
        return rpnFail(top);
    }

    res = popNumber(top);
    if(res.hrn == 0 && res.kop == 0){
        cout << "Помилка у виразі: вартість має бути більшою за 0.00 грн." << endl;
        return false;
    }
    return true;
 }

//1. додати замовлення
 bool readName(char *name){
    char line[max_line];
    cout << "Ім'я клієнта: ";
    if(!readLine(line, max_line)) return false;
    if(!validName(line, max_client_name)){
        cout << "Помилка: ім'я має містити від 1 до " << max_client_name << " латинських літер." << endl;
        return false;
    }
    strcpy(name, line);
    return true;
 }

 bool readPhone(char *phone){
    char line[max_line];
    cout << "Телефон (10 цифр): ";
    if(!readLine(line, max_line)) return false;
    if(strlen(line) != 10 || !allDigits(line) || line[0] != '0'){
        cout << "Помилка: телефон має складатися з 10 цифр і починатися з 0." << endl;
        return false;
    }
    strcpy(phone, line);
    return true;
 }

 bool realDate(const Date &d){
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(d.year < 2000 || d.year > 2099 || d.month < 1 || d.month > 12) return false;
    if(d.year % 4 == 0) days[1] = 29;
    return d.day >= 1 && d.day <= days[d.month - 1];
 }

 bool readDate(Date &d){
    char line[max_line];
    cout << "Дата прийому (ДД.ММ.РРРР):  ";
    if(!readLine(line, max_line)) return false;

    bool format = (strlen(line) == 10 && line[2] == '.' && line[5] == '.');
    for(int i = 0; format && i < 10; i++){
        if(i != 2 && i != 5 && (line[i] < '0' || line[i] > '9')) format = false;
    }
    if(!format){
        cout << "Помилка: дата має бути у форматі ДД.ММ.РРРР." << endl;
        return false;
    }

    d.day = (line[0] - '0') * 10 + (line[1] - '0');
    d.month = (line[3] - '0') * 10 + (line[4] - '0');
    d.year = (line[6] - '0') * 1000 + (line[7] - '0') * 100 + (line[8] - '0') * 10 + (line[9] - '0');
    if(!realDate(d)){
        cout << "Помилка: некоректна дата." << endl;
        return false;
    }
    return true;
 }

 bool readType(DeviceType &type){
    char line[max_line];
    int num = 0;
    cout << "Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ";
    if(!readLine(line, max_line)) return false;
    if(!parseInt(line, num) || num < 1 || num > 3){
        cout << "Помилка: тип пристрою має бути 1, 2 або 3." << endl;
        return false;
    }
    type = (DeviceType)num;
    return true;
 }

 bool readInfo(DeviceType type, DeviceInfo &info){
    char line[max_line];
    int num = 0;

    if(type == DeviceType::PHONE){
        cout << "Останні 6 цифр IMEI: ";
        if(!readLine(line, max_line)) return false;
        if(strlen(line) != 6 || !allDigits(line)){
            cout << "Помилка: потрібно рівно 6 цифр." << endl;
            return false;
        }
        parseInt(line, info.imei);
    }
    else if(type == DeviceType::LAPTOP){
        cout << "Серійний номер: ";
        if(!readLine(line, max_line)) return false;
        int len = strlen(line);
        bool ok = (len >= 1 && len <= max_serial);
        for(int i = 0; ok && i < len; i++){
            if(!((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= '0' && line[i] <= '9'))) ok = false;
        }
        if(!ok){
            cout << "Помилка: серійний номер має містити від 1 до " << max_serial << " великих латинських літер і цифр." << endl;
            return false;
        }
        strcpy(info.serial, line);
    }
    else{
        cout << "Діагональ: ";
        if(!readLine(line, max_line)) return false;
        if(!parseInt(line, num) || num < 19 || num > 100){
            cout << "Помилка: діагональ має бути цілим числом від 19 до 100." << endl;
            return false;
        }
        info.inches = num;
    }
    return true;
 }

 bool readProblem(char *problem){
    char line[max_line];
    cout << "Опис несправності: ";
    if(!readLine(line, max_line)) return false;
    int len = strlen(line);
    if(len < 1 || len > max_problem){
        cout << "Помилка: опис має містити від 1 до " << max_problem << " байтів." << endl;
        return false;
    }
    strcpy(problem, line);
    return true;
 }

 bool readPriority(int &priority){
    char line[max_line];
    int num = 0;
    cout << "Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ";
    if(!readLine(line, max_line)) return false;
    if(!parseInt(line, num) || num < 1 || num > 3){
        cout << "Помилка: пріоритет має бути 1, 2 або 3." << endl;
        return false;
    }
    priority = num;
    return true;
 }

 bool readPrice(Money &price){
    char line[max_line];
    cout << "Вартість (обернений польський запис): ";
    if(!readLine(line, max_line)) return false;
    return evalRPN(line, price);
 }

 void addOrder(OrderList &list, QNode *&queue, Action *&stack, int &next_id){
    Order o = {};
    if(!readName(o.client.name)) return;
    if(!readPhone(o.client.phone)) return;
    if(!readDate(o.date)) return;
    if(!readType(o.type)) return;
    if(!readInfo(o.type, o.info)) return;
    if(!readProblem(o.problem)) return;
    if(!readPriority(o.priority)) return;
    if(!readPrice(o.price)) return;

    o.id = next_id;
    o.status = Status::WAITING;
    next_id++;
    OrderNode *p = addLast(list, o);
    enqueue(queue, &p->order);
    pushAction(stack, ActionType::ADD, o);

    cout << "Замовлення №" << o.id << " додано: вартість " << o.price << " грн, у черзі на ремонт: " << countQueue(queue) << "." << endl;
 }

//2. журнал замовлень
 void printLine(){
    cout << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+" << endl;
 }

 void showList(const OrderList &list, const QNode *queue){
    if(list.size == 0){
        cout << "Журнал порожній." << endl;
        return;
    }

    printLine();
    cout << "│   № │ Клієнт          │ Телефон    │ Дата       │ Тип    │ Деталі         │ Пр │ Статус  │  Вартість │" << endl;
    printLine();
    for(const OrderNode *p = list.head; p != nullptr; p = p->next) cout << p->order << endl;
    printLine();
    cout << "Усього замовлень: " << list.size << ", у черзі на ремонт: " << countQueue(queue) << endl;
 }

//3. видати замовлення майстру
 void giveOrder(QNode *&queue, Master *&turn){
    if(queue == nullptr){
        cout << "Черга на ремонт порожня." << endl;
        return;
    }

    Order *o = dequeue(queue);
    o->status = Status::REPAIR;
    strcpy(o->master, turn->name);
    turn = turn->next;

    cout << "Замовлення №" << o->id << " (пріоритет " << o->priority << ") передано майстру " << o->master << "." << endl;
    cout << "Несправність: " << o->problem << endl;
    cout << "У черзі залишилось: " << countQueue(queue) << endl;
 }

//4. завершити ремонт
 OrderNode *askOrder(const OrderList &list){
    char line[max_line];
    int id = 0;

    cout << "Номер замовлення: ";
    if(!readLine(line, max_line)) return nullptr;
    if(!parseInt(line, id)){
        cout << "Помилка: номер замовлення має бути цілим числом." << endl;
        return nullptr;
    }

    OrderNode *p = findById(list, id);
    if(p == nullptr) cout << "Замовлення №" << id << " не знайдено." << endl;
    return p;
 }

 void finishOrder(const OrderList &list, Master *turn){
    OrderNode *p = askOrder(list);
    if(p == nullptr) return;
    if(p->order.status == Status::WAITING){
        cout << "Замовлення №" << p->order.id << " ще не передано майстру." << endl;
        return;
    }
    if(p->order.status == Status::DONE){
        cout << "Замовлення №" << p->order.id << " уже завершено." << endl;
        return;
    }

    Master *m = findMaster(turn, p->order.master);
    p->order.status = Status::DONE;
    m->done++;
    m->sum = m->sum + p->order.price;

    cout << "Ремонт замовлення №" << p->order.id << " завершено. Майстер " << m->name << ": виконано " << m->done << ", виручка " << m->sum << " грн." << endl;
 }

//5. видалити замовлення 
 void removeOrder(OrderList &list, QNode *&queue, Action *&stack){
    OrderNode *p = askOrder(list);
    if(p == nullptr) return;
    if(p->order.status != Status::WAITING){
        cout << "Видалити можна лише замовлення, яке очікує в черзі." << endl;
        return;
    }

    int id = p->order.id;
    pushAction(stack, ActionType::REMOVE, p->order);
    removeFromQueue(queue, &p->order);
    removeNode(list, p);

    cout << "Замовлення №" << id << " видалено. У журналі: " << list.size << ", у черзі: " << countQueue(queue) << "." << endl;
 }

//6. скасувати останню дію
 void undo(OrderList &list, QNode *&queue, Action *&stack){
    if(stack == nullptr){
        cout << "Немає дій для скасування." << endl;
        return;
    }

    Action a = popAction(stack);
    if(a.type == ActionType::ADD){
        OrderNode *p = findById(list, a.order.id);
        if(p == nullptr || p->order.status != Status::WAITING){
            cout << "Додавання замовлення №" << a.order.id << " скасувати неможливо: його вже передано майстру." << endl;
            return;
        }
        removeFromQueue(queue, &p->order);
        removeNode(list, p);
        cout << "Скасовано додавання замовлення №" << a.order.id << ": його вилучено з журналу і з черги." << endl;
    }
    else{
        OrderNode *p = addLast(list, a.order);
        enqueue(queue, &p->order);
        cout << "Скасовано видалення замовлення №" << a.order.id << ": його повернуто в кінець журналу і в чергу." << endl;
    }
 }

//7. звіт
 void swapOrders(Order *&a, Order *&b){
    Order *t = a;
    a = b;
    b = t;
 }

 bool higher(const Order *a, const Order *b){
    if(a->price < b->price) return false;
    if(b->price < a->price) return true;
    return a->id < b->id;
 }

 void sortOrders(Order **arr, int count){
    for(int i = 1; i < count; i++){
        for(int j = 1; j < count; j++){
            if(higher(arr[j], arr[j - 1])) swapOrders(arr[j - 1], arr[j]);
        }
    }
 }

 void showMasters(Master *turn){
    cout << "Майстри, починаючи з наступного в черзі:" << endl;
    Master *m = turn;
    do{
        cout << "  " << left << setw(12) << m->name << " виконано: " << m->done << ", виручка: " << m->sum << " грн" << endl;
        m = m->next;
    } while(m != turn);
    cout << right;
 }

 void report(const OrderList &list, Master *turn){
    if(list.size == 0){
        cout << "Журнал порожній." << endl;
        return;
    }

    Order **arr = new Order*[list.size];
    int i = 0;
    for(OrderNode *p = list.head; p != nullptr; p = p->next){
        arr[i] = &p->order;
        i++;
    }
    sortOrders(arr, list.size);

    cout << "Замовлення за вартістю:" << endl;
    for(i = 0; i < list.size; i++){
        char price[16];
        moneyStr(arr[i]->price, price);
        cout << "  №" << arr[i]->id << "  " << setw(9) << price << " грн  " << statusName(arr[i]->status) << endl;
    }
    cout << "Різниця між найдорожчим і найдешевшим: " << arr[0]->price - arr[list.size - 1]->price << " грн" << endl;
    cout << "Виручка за завершеними ремонтами: " << revenue(list.head) << " грн" << endl;
    showMasters(turn);

    delete[] arr;
    arr = nullptr;
 }

//8. розвернути журнал
 void reverseList(OrderList &list){
    if(list.size == 0){
        cout << "Журнал порожній." << endl;
        return;
    }

    OrderNode *p = list.head;
    while(p != nullptr){
        OrderNode *next = p->next;
        p->next = p->prev;
        p->prev = next;
        p = next;
    }
    OrderNode *t = list.head;
    list.head = list.tail;
    list.tail = t;

    cout << "Журнал розвернуто: тепер першим іде замовлення №" << list.head->order.id << ", останнім №" << list.tail->order.id << "." << endl;
 }

//меню
 bool status(OrderList &list, QNode *&queue, Master *&turn, Action *&stack, int &next_id, int &def){
    char line[max_line];
    int menu = 0;

    cout << endl << "1 - Додати замовлення" << endl << "2 - Журнал замовлень" << endl << "3 - Видати замовлення майстру" << endl << "4 - Завершити ремонт" << endl << "5 - Видалити замовлення" << endl << "6 - Скасувати останню дію" << endl  << "7 - Звіт" << endl << "8 - Розвернути журнал" << endl << "0 - Вийти" << endl;
    cout << "Ваш вибір: ";
    if(!readLine(line, max_line)) return false;
    if(!parseInt(line, menu)){
        cout << "Помилка: введіть номер пункту меню." << endl;
        return true;
    }

    switch(menu){
        case 1:
            addOrder(list, queue, stack, next_id);
            break;
        case 2:
            showList(list, queue);
            break;
        case 3:
            giveOrder(queue, turn);
            break;
        case 4:
            finishOrder(list, turn);
            break;
        case 5:
            removeOrder(list, queue, stack);
            break;
        case 6:
            undo(list, queue, stack);
            break;
        case 7:
            report(list, turn);
            break;
        case 8:
            reverseList(list);
            break;
        case 0:
            def = 1;
            break;
        default:
            cout << "Помилка: пункту " << menu << " немає в меню." << endl;
    }
    if(cin.eof()) return false;
    return true;
 }

int main(){
    int def = 0;
    int next_id = 101;
    OrderList list = {nullptr, nullptr, 0};
    QNode *queue = nullptr;
    Action *stack = nullptr;
    Master *turn = readMasters();
    if(turn == nullptr) return 0;
    do{
        if(!status(list, queue, turn, stack, next_id, def)) break;
    } while(def != 1);

    freeList(list);
    freeQueue(queue);
    freeActions(stack);
    freeMasters(turn);
    return 0;
}
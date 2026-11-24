#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdio>
#include <iomanip>
using namespace std;

const int MAX_KOP = 10000000;    

enum class DeviceType {PHONE = 1, LAPTOP, TV};
enum class Status {WAITING, REPAIR, DONE};
enum class ActionType {ADD, REMOVE};


struct Money {
    int hrn;
    int kop;
};

struct Date {int day, month, year;};
struct Client {char name[16]; char phone[11];};
union DeviceInfo {int imei; char serial[12]; int inches;};

struct Order {
    int id;
    Client client;
    Date date;
    DeviceType type;
    DeviceInfo info;
    char problemDescription[81];
    int priority;
    Money price;
    Status status;
    char master[24];
};

struct OrderNode {
    Order data;
    OrderNode* prev = nullptr;
    OrderNode* next = nullptr;
};

struct OrderList{
    OrderNode* head = nullptr;
    OrderNode* tail = nullptr;
    int size = 0;

    ~OrderList();
};

struct QNode {
    Order* order;
    QNode* next;
};

struct PQueue {
    QNode* head = nullptr;
    int size = 0;

    ~PQueue();
};

struct Master{
    char name[24];
    int amountOfCompletedOrders = 0;
    Money revenue = {0, 0};
    Master* next = nullptr;
};

struct MasterRing{
    Master* cur = nullptr;

    ~MasterRing();
};

struct NumNode {
    Money value;
    NumNode* next;
};

struct NumStack{
    NumNode* top = nullptr;

    ~NumStack();
};

struct Action {
    ActionType type;
    Order copy;
    Action* next;
};

struct ActionStack {
    Action* top = nullptr;
    ~ActionStack();
};

struct ServiceCenter{
    MasterRing masters;
    OrderList journal;
    PQueue queue;
    ActionStack actions;
    int nextId = 101;
};

int toKop(const Money &money){
    return money.hrn * 100 + money.kop;
}

Money fromKop(int k){
    return {k / 100, k % 100};
}

Money operator+(const Money &moneyA, const Money &moneyB){
    return fromKop(toKop(moneyA) + toKop(moneyB));
}

Money operator-(const Money &moneyA, const Money &moneyB){
    return fromKop(toKop(moneyA) - toKop(moneyB));
}

Money operator*(const Money& a, int k) {
    return fromKop(toKop(a) * k);
}

bool operator<(const Money &moneyA, const Money &moneyB){
    return toKop(moneyA) < toKop(moneyB);
}

ostream &operator<<(ostream &os, const Money &money){
    return os << money.hrn << '.' << setw(2) << setfill('0') << money.kop << setfill(' ');
}

bool parseMoney(const char* token, Money &output){
    int hrn = 0;
    int kop = 0;

    int i = 0;
    int intDigits = 0;
    while(isdigit(token[i])){
        hrn = hrn * 10 + (token[i] - '0');
        i++;
        intDigits++;
    }
    if(intDigits < 1 || intDigits > 6){
        return false;
    }

    if(token[i] == '.'){
        i++;
        int fractionDigits = 0;
        while(isdigit(token[i])){
            kop = kop * 10 + (token[i] - '0');
            i++;
            fractionDigits++;
        }
        if(fractionDigits < 1 || fractionDigits > 2){
            return false;
        }
        if(fractionDigits == 1){
            kop *= 10;
        }
    }

    if(token[i] != '\0'){
        return false;
    }

    output = {hrn, kop};
    return true;
}

void numPush(NumStack& stack, const Money& value){
    stack.top = new NumNode{value, stack.top};
}

bool numPop(NumStack& stack, Money& value){
    if(stack.top == nullptr){
        return false;
    }
    NumNode* temp = stack.top;
    value = temp->value;
    stack.top = temp->next;
    delete temp;
    return true;
}

void numClear(NumStack& stack){
    while(stack.top != nullptr){
        NumNode* temp = stack.top;
        stack.top = stack.top->next;
        delete temp;
    }
}

NumStack::~NumStack(){
    numClear(*this);
}

int numCount(const NumStack& stack){
    int count = 0;
    for(const NumNode* p = stack.top; p != nullptr; p = p->next){
        count++;
    }
    return count;
}

bool evalRPN(const char* expression, Money& result){
    char buf[256];
    strcpy(buf, expression);

    NumStack stack;
    int tokens = 0;

    for(char* token = strtok(buf, " "); token != nullptr; token = strtok(nullptr, " ")){
        tokens++;
        Money value;
        bool isOperation = strlen(token) == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*');

        if(isOperation){
            Money a, b;
            if(!numPop(stack, b) || !numPop(stack, a)){
                cout << "Помилка у виразі: для операції «" << token[0] << "» бракує чисел" << endl;
                return false;
            }
            if(token[0] == '+'){
                value = a + b;
            }
            else if(token[0] == '-'){
                if(a < b){
                    cout << "Помилка у виразі: проміжний результат від'ємний" << endl;
                    return false;
                }
                value = a - b;
            }
            else {
                if(b.kop != 0 || b.hrn < 1 || b.hrn > 100){
                    cout << "Помилка у виразі: множник має бути цілим числом від 1 до 100" << endl;
                    return false;
                }
                value = a * b.hrn;
            }
        }
        else if(!parseMoney(token, value)){
            cout << "Помилка у виразі: «" << token << "» не є числом або операцією" << endl;
            return false;
        }

        if(toKop(value) > MAX_KOP){
            cout << "Помилка у виразі: сума перевищує 100000.00 грн" << endl;
            return false;
        }
        numPush(stack, value);
    }

    if(tokens == 0){
        cout << "Помилка у виразі: порожній вираз" << endl;
        return false;
    }
    int leftNumbers = numCount(stack);
    if(leftNumbers != 1){
        cout << "Помилка у виразі: у стеку залишилось чисел: " << leftNumbers << ", а має бути одне" << endl;
        return false;
    }
    numPop(stack, result);
    if(toKop(result) == 0){
        cout << "Помилка у виразі: вартість має бути більшою за 0.00 грн" << endl;
        return false;
    }
    return true;
}

bool readLine(const char* prompt, char* buffer, int size){
    cout << prompt;
    if(cin.getline(buffer, size)){
        return true;
    }
    if(cin.eof()){
        return false;
    }
    cin.clear();
    cin.ignore(100000, '\n');
    buffer[0] = '\0';
    return true;
}

bool isLatinWord(const char* word, int minLength, int maxLength){
    int length = strlen(word);
    if(length < minLength || length > maxLength){
        return false;
    }
    for(int i = 0; i < length; i++){
        if(!isalpha(word[i])){
            return false;
        }
    }
    return true;
}

bool allDigits(const char* text, int requiredLength){
    if((int)strlen(text) != requiredLength){
        return false;
    }
    for(int i = 0; i < requiredLength; i++){
        if(!isdigit(text[i])){
            return false;
        }
    }
    return true;
}

bool isValidPhone(const char* phone){
    return allDigits(phone, 10) && phone[0] == '0';
}

bool isValidSerial(const char* serial){
    int length = strlen(serial);
    if(length < 1 || length > 11){
        return false;
    }
    for(int i = 0; i < length; i++){
        bool isUpperLetter = serial[i] >= 'A' && serial[i] <= 'Z';
        bool isDigit = isdigit(serial[i]);
        if(!isUpperLetter && !isDigit){
            return false;
        }
    }
    return true;
}

bool parseIntRange(const char* text, int minValue, int maxValue, int& result){
    int length = strlen(text);
    if(length < 1 || length > 9){
        return false;
    }
    int value = 0;
    for(int i = 0; i < length; i++){
        if(!isdigit(text[i])){
            return false;
        }
        value = value * 10 + (text[i] - '0');
    }
    if(value < minValue || value > maxValue){
        return false;
    }
    result = value;
    return true;
}

int daysInMonth(int month, int year){
    const int daysPerMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(month == 2 && year % 4 == 0){
        return 29;
    }
    return daysPerMonth[month - 1];
}

int parseDate(const char* text, Date& date){
    if(strlen(text) != 10 || text[2] != '.' || text[5] != '.'){
        return 1;
    }
    for(int i = 0; i < 10; i++){
        if(i != 2 && i != 5 && !isdigit(text[i])){
            return 1;
        }
    }
    int day = (text[0] - '0') * 10 + (text[1] - '0');
    int month = (text[3] - '0') * 10 + (text[4] - '0');
    int year = (text[6] - '0') * 1000 + (text[7] - '0') * 100 + (text[8] - '0') * 10 + (text[9] - '0');

    if(year < 2000 || year > 2099 || month < 1 || month > 12){
        return 2;
    }
    if(day < 1 || day > daysInMonth(month, year)){
        return 2;
    }
    date = {day, month, year};
    return 0;
}

MasterRing::~MasterRing(){
    if(cur == nullptr){
        return;
    }
    Master* p = cur->next;
    cur->next = nullptr;
    while(p != nullptr){
        Master* t = p;
        p = p->next;
        delete t;
    }
    cur = nullptr;
}

bool equalWords(const char* a, const char* b){
    int i = 0;
    while(a[i] != '\0' && b[i] != '\0'){
        if(tolower(a[i]) != tolower(b[i])){
            return false;
        }
        i++;
    }
    return a[i] == b[i];
}

void buildRing(char names[][24], int n, MasterRing &ring){
    Master* first = nullptr;
    Master* last = nullptr;
    for(int i = 0; i < n; i++){
        Master* master = new Master;
        strcpy(master->name, names[i]);
        if(first == nullptr){
            first = master;
        }
        else {
            last->next = master;
        }
        last = master;
    }
    last->next = first;
    ring.cur = first;
}

bool readMasters(int n, MasterRing &ring){
    char line[256];
    if(!readLine("Імена майстрів через пробіл: ", line, 256)){
        return false;
    }

    char names[5][24];
    int count = 0;
    for(char* t = strtok(line, " "); t != nullptr; t = strtok(nullptr, " ")){
        if(count == n){
            cout << "Помилка: Кількість введених імен майстрів не може перевищувати задану вами кількість!" << endl;
            return false;
        }
        if(!isLatinWord(t, 1, 23)){
            cout << "Помилка: ім'я майстра має містити від 1 до 23 латинських літер!" << endl;
            return false;
        }
        strcpy(names[count], t);
        count++;
    }

    if(count != n){
        cout << "Помилка: Кількість введених імен майстрів не відповідає заданій кількості!" << endl;
        return false;
    }

    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(equalWords(names[i], names[j])){
                cout << "Помилка: Імена майстрів не можуть повторюватись!" << endl;
                return false;
            }
        }
    }

    buildRing(names, n, ring);
    return true;
}

Master* takeMaster(MasterRing& masterRing){
    Master* master = masterRing.cur;
    masterRing.cur = masterRing.cur->next;
    return master;
}

Master* findMaster(const MasterRing& masterRing, const char* name){
    Master* master = masterRing.cur;
    do{
        if(strcmp(master->name, name) == 0){
            return master;
        }
        master = master->next;
    } 
    while(master != masterRing.cur);
    return nullptr;
}

void printMasters(const MasterRing& masterRing){
    Master* master = masterRing.cur;
    do{
        cout << "  " << left << setw(12) << master->name << right << " виконано: " << master->amountOfCompletedOrders 
            << ", виручка: " << master->revenue << " грн" << endl;
        master = master->next;
    }while(master != masterRing.cur);
}

void clearOrderList(OrderList& orderList){
    while(orderList.head != nullptr){
        OrderNode* temp = orderList.head;
        orderList.head = orderList.head->next;
        delete temp;
    }
    orderList.tail = nullptr;
    orderList.size = 0;
}

OrderList::~OrderList(){
    clearOrderList(*this);
}

OrderNode* listPushBack(OrderList& orderList, const Order& order){
    OrderNode* newOrder = new OrderNode{order, orderList.tail, nullptr};
    if(orderList.tail){
        orderList.tail->next = newOrder;
    }
    else{
        orderList.head = newOrder;
    }
    orderList.tail = newOrder;
    orderList.size++;
    return newOrder;
}

OrderNode* findById(const OrderList& list, int id){
    OrderNode* order = list.head;
    while(order != nullptr){
        if(order->data.id == id){
            return order;
        }
        order = order->next;
    }
    return nullptr;
}

void listUnlink(OrderList& list, OrderNode* node){
    if(node->prev != nullptr){
        node->prev->next = node->next;
    }
    else{
        list.head = node->next;
    }

    if(node->next != nullptr){
        node->next->prev = node->prev;
    }
    else{
        list.tail = node->prev;
    }
    list.size--;
}

void listReverse(OrderList& list){
    OrderNode* cur = list.head;
    
    while(cur != nullptr){
        OrderNode* temp = cur->prev;
        cur->prev = cur->next;
        cur->next = temp;
        cur = cur->prev;
    }
    OrderNode* temp = list.head;
    list.head = list.tail;
    list.tail = temp;
}

Money revenue(const OrderNode* node){
    if(node == nullptr){
        return {0, 0};
    }
    Money rest = revenue(node->next);
    if(node->data.status == Status::DONE){
        return rest + node->data.price;
    }
    return rest;
}

void pqPush(PQueue& queue, Order* order){
    QNode* newOrder = new QNode{order, nullptr};
    if(queue.head == nullptr || order->priority > queue.head->order->priority){
        newOrder->next = queue.head;
        queue.head = newOrder;
    }
    else{
        QNode* cur = queue.head;
        while(cur->next != nullptr && cur->next->order->priority >= order->priority){
            cur = cur->next;
        }
        newOrder->next = cur->next;
        cur->next = newOrder;
    }
    queue.size++;
}

Order* pqPop(PQueue& queue){
    if(queue.head == nullptr){
        return nullptr;
    }
    QNode* temp = queue.head;
    Order* order = temp->order;
    queue.head = temp->next;
    delete temp;
    queue.size--;
    return order;
}

void pqClear(PQueue& queue){
    while(pqPop(queue) != nullptr){}
}

PQueue::~PQueue(){
    pqClear(*this);
}

bool pqRemove(PQueue& queue, Order* order){
    QNode* prev = nullptr;
    QNode* cur = queue.head;

    while(cur != nullptr){
        if(cur->order == order){
            if(prev == nullptr){
                queue.head = cur->next;
            }
            else{
                prev->next = cur->next;
            }
            delete cur;
            queue.size--;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

void pushAction(ActionStack& stack, ActionType type, const Order& order){
    stack.top = new Action{type, order, stack.top};
}

bool popAction(ActionStack& stack, Action& action){
    if(stack.top == nullptr){
        return false;
    }
    Action *temp = stack.top;
    action = *temp;
    stack.top = temp->next;
    delete temp;
    return true;
}

void clearActions(ActionStack& stack){
    while(stack.top != nullptr){
        Action* temp = stack.top;
        stack.top = stack.top->next;
        delete temp;
    }
}

ActionStack::~ActionStack(){
    clearActions(*this);
}

const char* typeName(DeviceType type){
    switch(type){
        case DeviceType::PHONE:
            return "PHONE";
        case DeviceType::LAPTOP:
            return "LAPTOP";
        case DeviceType::TV:
            return "TV";
    }
    return "";
}

const char* statusName(Status status){
    switch(status){
        case Status::WAITING:
            return "WAITING";
        case Status::REPAIR:
            return "REPAIR";
        case Status::DONE:
            return "DONE";
    }
    return "";
}

ostream& operator<<(ostream& os, const Order& order){
    char date[11];
    snprintf(date, sizeof(date), "%02d.%02d.%04d", order.date.day, order.date.month, order.date.year);

    char details[20];
    switch(order.type){
        case DeviceType::PHONE:
            snprintf(details, sizeof(details), "IMEI %06d", order.info.imei);
            break;
        case DeviceType::LAPTOP:
            snprintf(details, sizeof(details), "SN %s", order.info.serial);
            break;
        case DeviceType::TV:
            snprintf(details, sizeof(details), "%d inch", order.info.inches);
            break;
    }

    char price[16];
    snprintf(price, sizeof(price), "%d.%02d", order.price.hrn, order.price.kop);

    return os << "| " << right << setw(3) << order.id
              << " | " << left << setw(15) << order.client.name
              << " | " << setw(10) << order.client.phone
              << " | " << setw(10) << date
              << " | " << setw(6) << typeName(order.type)
              << " | " << setw(14) << details
              << " | " << right << setw(2) << order.priority
              << " | " << left << setw(7) << statusName(order.status)
              << " | " << right << setw(9) << price
              << " |";
}

void menuAdd(ServiceCenter& serviceCenter){
    Order order;
    char line[256];

    if(!readLine("Ім'я клієнта: ", line, 256)){
        return;
    }
    if(!isLatinWord(line, 1, 15)){
        cout << "Помилка: ім'я має містити від 1 до 15 латинських літер!" << endl;
        return;
    }
    strcpy(order.client.name, line);

    if(!readLine("Телефон (10 цифр): ", line, 256)){
        return;
    }
    if(!isValidPhone(line)){
        cout << "Помилка: телефон має складатися з 10 цифр і починатися з 0!" << endl;
        return;
    }
    strcpy(order.client.phone, line);

    if(!readLine("Дата прийому (ДД.ММ.РРРР): ", line, 256)){
        return;
    }
    int result = parseDate(line, order.date);
    if(result == 1){
        cout << "Помилка: дата має бути у форматі ДД.ММ.РРРР!" << endl;
        return;
    }
    if(result == 2){
        cout << "Помилка: некоректна дата!" << endl;
        return;
    }

    if(!readLine("Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ", line, 256)){
        return;
    }
    int type;
    if(!parseIntRange(line, 1, 3, type)){
        cout << "Помилка: тип пристрою має бути 1, 2 або 3!" << endl;
        return;
    }
    order.type = (DeviceType)type;

    switch(order.type){
        case DeviceType::PHONE:
            if(!readLine("Останні 6 цифр IMEI: ", line, 256)){
                return;
            }
            if(!allDigits(line, 6)){
                cout << "Помилка: потрібно рівно 6 цифр!" << endl;
                return;
            }
            parseIntRange(line, 0, 999999, order.info.imei);
            break;

        case DeviceType::LAPTOP:
            if(!readLine("Серійний номер: ", line, 256)){
                return;
            }
            if(!isValidSerial(line)){
                cout << "Помилка: серійний номер має містити від 1 до 11 великих латинських літер і цифр!" << endl;
                return;
            }
            strcpy(order.info.serial, line);
            break;

        case DeviceType::TV:
            if(!readLine("Діагональ (дюймів): ", line, 256)){
                return;
            }
            if(!parseIntRange(line, 19, 100, order.info.inches)){
                cout << "Помилка: діагональ має бути цілим числом від 19 до 100!" << endl;
                return;
            }
            break;
    }

    if(!readLine("Опис несправності: ", line, 256)){
        return;
    }
    int length = strlen(line);
    if(length < 1 || length > 80){
        cout << "Помилка: опис несправності має містити від 1 до 80 байтів!" << endl;
        return;
    }
    strcpy(order.problemDescription, line);

    if(!readLine("Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ", line, 256)){
        return;
    }
    if(!parseIntRange(line, 1, 3, order.priority)){
        cout << "Помилка: пріоритет має бути 1, 2 або 3!" << endl;
        return;
    }

    if(!readLine("Вартість (обернений польський запис): ", line, 256)){
        return;
    }
    if(!evalRPN(line, order.price)){
        return;
    }

    order.id = serviceCenter.nextId++;
    order.status = Status::WAITING;
    order.master[0] = '\0';
    OrderNode* newNode = listPushBack(serviceCenter.journal, order);
    pqPush(serviceCenter.queue, &newNode->data);
    pushAction(serviceCenter.actions, ActionType::ADD, newNode->data);

    cout << "Замовлення №" << order.id << " додано: вартість " << order.price
         << " грн, у черзі на ремонт: " << serviceCenter.queue.size << "." << endl;
}

void menuJournal(const ServiceCenter& center){
    if(center.journal.size == 0){
        cout << "Журнал порожній." << endl;
        return;
    }

    const char* border = "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+";
    cout << border << endl;
    cout << "|   № | Клієнт          | Телефон    | Дата       | Тип    | Деталі         | Пр | Статус  |  Вартість |" << endl;
    cout << border << endl;

    for(const OrderNode* node = center.journal.head; node != nullptr; node = node->next){
        cout << node->data << endl;
    }

    cout << border << endl;
    cout << "Усього замовлень: " << center.journal.size
         << ", у черзі на ремонт: " << center.queue.size << endl;
}

void menuGive(ServiceCenter& center){
    Order* order = pqPop(center.queue);
    if(order == nullptr){
        cout << "Черга на ремонт порожня." << endl;
        return;
    }

    Master* master = takeMaster(center.masters);
    order->status = Status::REPAIR;
    strcpy(order->master, master->name);

    cout << "Замовлення №" << order->id << " (пріоритет " << order->priority << ") передано майстру " << master->name << "." << endl;
    cout << "Несправність: " << order->problemDescription << endl;
    cout << "У черзі залишилось: " << center.queue.size << endl;
}

void menuFinish(ServiceCenter& serviceCenter){
    char line[256];
    if(!readLine("Номер замовлення: ", line, 256)){
        return;
    }
    int id;
    if(!parseIntRange(line, 0, 999999999, id)){
        cout << "Помилка: номер замовлення має бути цілим числом!" << endl;
        return;
    }
    OrderNode* node = findById(serviceCenter.journal, id);
    if(node == nullptr){
        cout << "Замовлення №" << id << " не знайдено" << endl;
        return;
    }
    Order& order = node->data;
    if(order.status == Status::WAITING){
        cout << "Замовлення №" << id << " ще не передано майстру." << endl;
        return;
    }
    if(order.status == Status::DONE){
        cout << "Замовлення №" << id << " уже завершено." << endl;
        return;
    }

    order.status = Status::DONE;
    Master* master = findMaster(serviceCenter.masters, order.master);
    master->amountOfCompletedOrders++;
    master->revenue = master->revenue + order.price;

    cout << "Ремонт замовлення №" << id << " завершено. Майстер " << master->name 
        << ": виконано " << master->amountOfCompletedOrders
        << ", виручка " << master->revenue << " грн." << endl;
}

void menuDelete(ServiceCenter& serviceCenter){
    char line[256];
    if(!readLine("Номер замовлення: ", line, 256)){
        return;
    }
    int id;
    if(!parseIntRange(line, 0, 999999999, id)){
        cout << "Помилка: номер замовлення має бути цілим числом!" << endl;
        return;
    }
    OrderNode* node = findById(serviceCenter.journal, id);
    if(node == nullptr){
        cout << "Замовлення №" << id << " не знайдено" << endl;
        return;
    }
    Order& order = node->data;
    if(order.status != Status::WAITING){
        cout << "Видалити можна лише замовлення, яке очікує в черзі" << endl;
        return;
    }
    pqRemove(serviceCenter.queue, &order);
    listUnlink(serviceCenter.journal, node);
    pushAction(serviceCenter.actions, ActionType::REMOVE, order);
    cout << "Замовлення №" << id << " видалено. У журналі: " << serviceCenter.journal.size << " , у черзі: " << serviceCenter.queue.size << endl;
    delete node;
}

void menuUndo(ServiceCenter& serviceCenter){
    Action action;
    if(!popAction(serviceCenter.actions, action)){
        cout << "Немає дій для скасування" << endl;
        return;
    }
    int id = action.copy.id;

    if(action.type == ActionType::ADD){
        OrderNode* node = findById(serviceCenter.journal, id);
        if(node == nullptr || node->data.status != Status::WAITING){
            cout << "Додавання замовлення №" << id << " скасувати неможливо: його вже передано майстру" << endl;
            return;
        }
        pqRemove(serviceCenter.queue, &node->data);
        listUnlink(serviceCenter.journal, node);
        delete node;
        cout << "Скасовано додавання замовлення №" << id << ": його вилучено з журналу і черги" << endl;
    }
    else{
        OrderNode* node = listPushBack(serviceCenter.journal, action.copy);
        pqPush(serviceCenter.queue, &node->data);
        cout << "Скасовано видалення замовлення №" << id << ": його повернуто в кінець журналу і в чергу" << endl;
    }      
}

void menuReport(const ServiceCenter& serviceCenter){
    int size = serviceCenter.journal.size;
    if(size == 0){
        cout << "Журнал порожній" << endl;
    }
    else{
        const Order** orders = new const Order*[size];
        OrderNode* cur = serviceCenter.journal.head;
        for(int i = 0; i < size; i++){
            orders[i] = &cur->data;
            cur = cur->next;
        }

        for(int i = 0; i < size; i++){
            for(int j = 0; j < size - 1 - i; j++){
                const Order* a = orders[j];
                const Order* b = orders[j+1];
                bool swap = a->price < b->price || (!(b->price < a->price) && a->id > b->id);
                if(swap){
                    orders[j] = b;
                    orders[j+1] = a;
                } 
            }
        }

        cout << "Замовлення за вартістю: " << endl;
        for(int i = 0; i < size; i++){
            char price[16];
            snprintf(price, sizeof(price), "%d.%02d", orders[i]->price.hrn, orders[i]->price.kop);
            cout << " №" << orders[i]->id << right << setw(11) << price << " грн " << statusName(orders[i]->status) << endl;
        }
        cout << "Різниця між найдорожчим і найдешевшим: " << orders[0]->price - orders[size-1]->price << " грн" << endl;
        delete[] orders;
    }
    cout << "Виручка за завершеними ремонтами: " << revenue(serviceCenter.journal.head) << " грн" << endl;
    cout << "Майстри, починаючи з наступного в черзі: " << endl;
    printMasters(serviceCenter.masters);
}

void menuReverse(ServiceCenter& serviceCenter){
    if(serviceCenter.journal.size == 0){
        cout << "Журнал порожній" << endl;
        return;
    }
    listReverse(serviceCenter.journal);
    cout << "Журнал розвернуто: тепер першим іде замовлення №" << serviceCenter.journal.head->data.id
         << ", останнім №"  << serviceCenter.journal.tail->data.id << endl;
}

void printMenu(){
    cout << endl
         << "1. Додати замовлення" << endl
         << "2. Журнал замовлень" << endl
         << "3. Видати замовлення майстру" << endl
         << "4. Завершити ремонт" << endl   
         << "5. Видалити замовлення" << endl
         << "6. Скасувати останню дію" << endl
         << "7. Звіт" << endl
         << "8. Розвернути журнал" << endl
         << "0. Вийти" << endl;
}

int main() {
    char line[256];
    if(!readLine("Кількість майстрів (від 1 до 5): ", line, 256)){
        return 0;
    }
    if(strlen(line) != 1 || line[0] < '1' || line[0] > '5'){
        cout << "Помилка: кількість майстрів має бути від 1 до 5!" << endl;
        return 0;
    }
    int n = line[0] - '0';

    ServiceCenter serviceCenter;
    if(!readMasters(n, serviceCenter.masters)){
        return 0;
    }

    while(true){
        printMenu();
        if(!readLine("Ваш вибір: ", line, 256)){
            break;
        }
        int choice;
        if(!parseIntRange(line, 0, 999999, choice)){
            cout << "Помилка: введіть номер пункту меню!" << endl;
            continue;
        }
        if(choice > 8){
            cout << "Помилка: пункту " << choice << " немає в меню!" << endl;
            continue;
        }
        if(choice == 0){
            break;
        }

        switch(choice){
            case 1:
                menuAdd(serviceCenter);
                break;
            case 2:
                menuJournal(serviceCenter);
                break;
            case 3:
                menuGive(serviceCenter);
                break;
            case 4:
                menuFinish(serviceCenter);
                break;
            case 5:
                menuDelete(serviceCenter);
                break;
            case 6:
                menuUndo(serviceCenter);
                break;
            case 7:
                menuReport(serviceCenter);
                break;
            case 8:
                menuReverse(serviceCenter);
                break;
        }
    }

    return 0;
}
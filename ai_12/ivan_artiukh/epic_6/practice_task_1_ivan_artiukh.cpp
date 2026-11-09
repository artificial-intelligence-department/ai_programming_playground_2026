#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

enum class DeviceType { PHONE = 1, LAPTOP, TV };

enum class Status { WAITING, REPAIR, DONE };

union DeviceInfo {
    int imei;
    char serial[12];
    int inches;
};

struct Money {
    int hrn = 0;
    int kop = 0;
    Money& operator=(const Money& other) {
        if (this != &other) {
            hrn = other.hrn;
            kop = other.kop;
        }
        return *this;
    }
};

struct Date {
    int day;
    int month;
    int year;
};

struct Client {
    char name[16];
    char phone[11];
};

struct Master {
    char name[24] = "";
    int completedCount = 0;
    Money revenue = {0, 0};
    Master* next = nullptr;
};

struct Order {
    int id;
    Client client;
    Date orderDate;
    DeviceType deviceType;
    DeviceInfo info;
    char problem[81];
    int priority;
    Money cost;
    Status status;
    char masterName[24];
};

struct OrderNode {
    Order data;
    OrderNode* prev;
    OrderNode* next;
};

struct OrderList {
    OrderNode* head = nullptr;
    OrderNode* tail = nullptr;
    int size = 0;
};

struct QNode {
    Order* order;
    QNode* next;
};

struct PriorityQueue {
    QNode* head = nullptr;
    int size = 0;
};

enum class ActionType { ADD, REMOVE };

struct Action {
    ActionType type;
    Order orderCopy;
    Action* next = nullptr;
};

OrderNode* appendOrder(OrderList& list, const Order& order) {
    OrderNode* node = new OrderNode;
    node->data = order;
    node->prev = list.tail;
    node->next = nullptr;

    if (list.tail) {
        list.tail->next = node;
    } else {
        list.head = node;
    }

    list.tail = node;
    list.size++;
    return node;
}

ostream& operator<<(ostream& os, const Money& m) {
    char buf[32];
    sprintf(buf, "%d.%02d", m.hrn, m.kop);
    os << buf;
    return os;
}

ostream& operator<<(ostream& os, const Date& d) {
    char buf[32];
    sprintf(buf, "%d.%d.%d", d.day, d.month, d.year);
    os << buf;
    return os;
}

ostream& operator<<(std::ostream& os, Status s) {
    switch (s) {
        case Status::WAITING: return os << "WAITING";
        case Status::REPAIR:  return os << "REPAIR";
        case Status::DONE:    return os << "DONE";
    }
    return os << "UNKNOWN";
}

Money operator+(const Money& a, const Money& b) {
    int totalKop = a.kop + b.kop;
    Money res;
    res.hrn = a.hrn + b.hrn + totalKop / 100;
    res.kop = totalKop % 100;
    return res;
}

Money operator-(const Money& a, const Money& b) {
    int totalKop = a.kop - b.kop;
    Money res;
    if(totalKop >= 0){
        res.hrn = a.hrn - b.hrn;
        res.kop = totalKop;
    }
    else if(totalKop < 0){
        res.hrn = a.hrn - b.hrn;
        res.kop = totalKop + 100;
    }
    return res;
}

bool operator>(const Money& a, const Money& b) {
    if (a.hrn != b.hrn) {
        return a.hrn > b.hrn;
    }
    return a.kop > b.kop;
}

bool operator==(const Money& a, const Money& b) {
    return a.hrn == b.hrn && a.kop == b.kop;
}

void enqueueOrder(PriorityQueue& pq, Order* order) {
    QNode* node = new QNode;
    node->order = order;
    node->next = nullptr;

    if (!pq.head || order->priority > pq.head->order->priority) {
        node->next = pq.head;
        pq.head = node;
    } else {
        QNode* curr = pq.head;
        while (curr->next && curr->next->order->priority >= order->priority) {
            curr = curr->next;
        }
        node->next = curr->next;
        curr->next = node;
    }
    pq.size++;
}

void pushUndo(Action*& top, ActionType type, const Order& order) {
    Action* act = new Action;
    act->type = type;
    act->orderCopy = order;
    act->next = top;
    top = act;
}

bool readLine(int maxSize, char* buf){
    if (!cin.getline(buf, maxSize)) {
        if (cin.eof()) return false;
        cin.clear();
        char ch;
        while (cin.get(ch) && ch != '\n') {}
        return false; 
    }
    return true;
}

bool readValidDate(Date &res){
    char buf[16];
    printf("Введіь дату подачі:\n");
    if(!readLine(sizeof(buf), buf) || strlen(buf) != 10 || buf[2]!= '.' || buf[5] != '.'){
        printf("Помилка: некоректна дата подачі!\n");
        return false;
    }
    for(int i = 0; i < 10; i++){
        if(i == 2 || i == 5){
            continue;
        }
        else if(buf[i] > '9' || buf[i] < '0'){
            printf("Помилка: некоректна дата подачі!\n");
            return false;
        }
    }
    int day = (buf[0] - '0') * 10 + (buf[1] - '0');
    int month = (buf[3] - '0') * 10 + (buf[4] - '0');
    int year = (buf[6] - '0') * 1000 + (buf[7] - '0') * 100 + (buf[8] - '0') * 10 + (buf[9] - '0');
    if(year < 2000 || year > 2099){
        printf("Помилка: некоректна дата подачі!\n");
        return false;
    }
    if(month > 12 || month < 1){
        printf("Помилка: некоректна дата подачі!\n");
        return false;
    }
    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(year%400 == 0 || (year%100 != 0 && year%4 == 0)) daysInMonth[1] = 29;
    if(day > daysInMonth[month-1] || day < 1){
        printf("Помилка: некоректна дата подачі!\n");
        return false;
    }
    res.day = day;
    res.month = month;
    res.year = year;
    return true;
}

bool readValidPhone(char phone[], const int size){
    printf("Номер телефону клієнта: ");
    if (!readLine(size, phone)) {
        printf("Помилка: невалідний номер телефону.\n");
        return false;
    }

    int len = strlen(phone);
    if (len != 10 || phone[0] != '0') {
    printf("Помилка: телефон має складатися з 10 цифр і починатися з 0.\n");
    return false;
}

    for (char* p = phone; *p != '\0'; p++) {
        if (!((*p >= '0' && *p <= '9'))) {
            printf("Помилка: невалідний номер телефону.\n");
            return false;
        }
    }

    return true;
}

bool readValidName(char name[], const int size) {
    printf("Ім'я клієнта: ");
    if (!readLine(size, name)) {
        printf("Помилка: ім'я має містити від 1 до 15 латинських літер.\n");
        return false;
    }

    int len = strlen(name);
    if (len < 1 || len > 15) {
        printf("Помилка: ім'я має містити від 1 до 15 латинських літер.\n");
        return false;
    }

    for (char* p = name; *p != '\0'; p++) {
        if (!((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z'))) {
            printf("Помилка: ім'я має містити від 1 до 15 латинських літер.\n");
            return false;
        }
    }

    return true;
}

bool readDeviceType(DeviceType &type) {
    char buf[16];
    cout << "Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ";
    if (!readLine(sizeof(buf), buf)) {
        cout << "Помилка: некоректний тип пристрою.\n";
        return false;
    }

    if (strlen(buf) != 1 || buf[0] < '1' || buf[0] > '3') {
        cout << "Помилка: некоректний тип пристрою.\n";
        return false;
    }

    type = static_cast<DeviceType>(buf[0] - '0');
    return true;
}

bool readDeviceInfo(DeviceType type, DeviceInfo &info) {
    char buf[32];

    switch (type) {
        case DeviceType::PHONE: {
            cout << "Останні 6 цифр IMEI: ";
            if (!readLine(sizeof(buf), buf) || strlen(buf) != 6) {
                cout << "Помилка: потрібно рівно 6 цифр.\n";
                return false;
            }
            int val = 0;
            for (int i = 0; i < 6; i++) {
                if (!isdigit(static_cast<unsigned char>(buf[i]))) {
                    cout << "Помилка: потрібно рівно 6 цифр.\n";
                    return false;
                }
                val = val * 10 + (buf[i] - '0');
            }
            info.imei = val;
            return true;
        }

        case DeviceType::LAPTOP: {
            cout << "Серійний номер: ";
            if (!readLine(12, info.serial)) { 
                cout << "Помилка: некоректний серійний номер.\n";
                return false;
            }
            int len = strlen(info.serial);
            if (len < 1 || len > 11) {
                cout << "Помилка: некоректний серійний номер.\n";
                return false;
            }
            for (int i = 0; i < len; i++) {
                unsigned char c = static_cast<unsigned char>(info.serial[i]);
                if (!isupper(c) && !isdigit(c)) {
                    cout << "Помилка: некоректний серійний номер.\n";
                    return false;
                }
            }
            return true;
        }

        case DeviceType::TV: {
            cout << "Діагональ (19-100): ";
            if (!readLine(sizeof(buf), buf)) {
                cout << "Помилка: некоректна діагональ.\n";
                return false;
            }
            int len = strlen(buf);
            if (len < 2 || len > 3) {
                cout << "Помилка: некоректна діагональ.\n";
                return false;
            }
            int diag = 0;
            for (int i = 0; i < len; i++) {
                if (!isdigit(static_cast<unsigned char>(buf[i]))) {
                    cout << "Помилка: некоректна діагональ.\n";
                    return false;
                }
                diag = diag * 10 + (buf[i] - '0');
            }
            if (diag < 19 || diag > 100) {
                cout << "Помилка: некоректна діагональ.\n";
                return false;
            }
            info.inches = diag;
            return true;
        }
    }
    return false;
}

bool readProblem(char problem[81]) {
    cout << "Опис несправності: ";
    if (!readLine(81, problem)) {
        cout << "Помилка: опис несправності має містити від 1 до 80 байтів.\n";
        return false;
    }

    int len = strlen(problem);
    if (len < 1 || len > 80) {
        cout << "Помилка: опис несправності має містити від 1 до 80 байтів.\n";
        return false;
    }

    return true;
}

bool readPriority(int &priority){
    printf("Пріоритет (1 звичайний, 2 підвищений, 3 терміновий):\n");
    char buf[16];
    if (!readLine(sizeof(buf), buf)) {
        cout << "Помилка: некоректна пріоритетність.\n";
        return false;
    }

    if (strlen(buf) != 1 || buf[0] < '1' || buf[0] > '3') {
        cout << "Помилка: некоректна пріоритетність.\n";
        return false;
    }

    priority = static_cast<int>(buf[0] - '0');
    return true;
}

struct NumNode {
    long long val;
    NumNode *next;
};

void pushNum(NumNode*& top, long long val) {
    NumNode* node = new NumNode;
    node->val = val;
    node->next = top;
    top = node;
}

bool popNum(NumNode *&top, long long &val){
    if (!top) return false;
    NumNode* temp = top;
    val = temp->val;
    top = top->next;
    delete temp;
    return true;
}

void clearNumStack(NumNode*& top) {
    while (top) {
        NumNode* temp = top;
        top = top->next;
        delete temp;
    }
}

int parseMoneyToken(const char* tok, long long& kopiyki) {
    int i = 0;
    long long hrn = 0;
    int intDigits = 0;

    while (isdigit(static_cast<char>(tok[i]))) {
        hrn = hrn * 10 + (tok[i] - '0');
        intDigits++;
        if (intDigits > 6) return 0;
        i++;
    }

    if (intDigits == 0) return 0; 

    long long kop = 0;
    if (tok[i] == '.') {
        i++;
        int fracDigits = 0;
        while (isdigit(static_cast<char>(tok[i]))) {
            if (fracDigits == 0) kop += (tok[i] - '0') * 10;
            else if (fracDigits == 1) kop += (tok[i] - '0');
            else return 0;
            fracDigits++;
            i++;
        }
        if (fracDigits == 0) return 0;
    }

    if (tok[i] != '\0') return 0; 

    kopiyki = hrn * 100 + kop;
    if (kopiyki > 10000000LL) return -1;

    return 1;
}

bool evalRPN(const char* expr, Money& res) {
    NumNode* top = nullptr;
    int i = 0;
    int tokenCount = 0;

    while (expr[i] != '\0') {
        while (expr[i] == ' ') i++;
        if (expr[i] == '\0') break;

        char token[32];
        int len = 0;
        while(expr[i] != '\0' && expr[i] != ' '){
            if(len < 31){
                token[len] = expr[i];
                len++;
                i++;
            }
            else{
                while (expr[i] != '\0' && expr[i] != ' ') i++;
                token[len] = '\0';
                cout << "Помилка у виразі: «" << token << "...» не є числом або операцією.\n";
                clearNumStack(top);
                return false;
            }
        }
        token[len] = '\0';
        tokenCount++;
        if (len == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*')){
            long long first = 0, second = 0;
            if(!popNum(top, first) || !popNum(top, second)){
                cout << "Помилка у виразі: для операції «" << token[0] << "» бракує чисел.\n";
                clearNumStack(top);
                return false;
            }
            long long val = 0;
            switch (token[0])
            {
            case '+':
                val = first + second;
                break;
            case '-':
                val = second - first;
                if (val < 0) {
                    cout << "Помилка у виразі: проміжний результат від'ємний.\n";
                    clearNumStack(top);
                    return false;
                }
                break;
            case '*':{
                if (first > 10000 || first < 100) {
                    cout << "Помилка у виразі: множник має бути цілим числом від 1 до 100.\n";
                    clearNumStack(top);
                    return false;
                }
                long long tmp = second /= 100;
                val = tmp * first;
                break;  
            }      
            default:
                cout << "Помилка у виразі: для операції «" << token[0] << endl;
                break;
            }
            if(val > 10000000){
                cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                clearNumStack(top);
                return false;
            }
            pushNum(top, val);
        }
        else{
            long long val = 0;
            int status = parseMoneyToken(token, val);
            if(status == -1){
                cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                clearNumStack(top);
                return false;
            }
            else if(status == 0){
                cout << "Помилка у виразі: «" << token << "» не є числом або операцією.\n";
                clearNumStack(top);
                return false;
            }
            pushNum(top, val);
        }
    }
     if (tokenCount == 0) {
        cout << "Помилка у виразі: порожній вираз.\n";
        return false;
    }
    int remaining = 0;
    for (NumNode* p = top; p != nullptr; p = p->next) {
        remaining++;
    }

    if (remaining > 1) {
        cout << "Помилка у виразі: у стеку залишилось чисел: " << remaining << ", а має бути одне.\n";
        clearNumStack(top);
        return false;
    }

    long long kopiyki = 0;
    popNum(top, kopiyki);
    if(kopiyki == 0){
        cout << "Помилка у виразі: вартість не може дорівнювати 0.00 грн.\n";
        return false;
    }
    res.hrn = static_cast<int>(kopiyki / 100);
    res.kop = static_cast<int>(kopiyki % 100);
    return true;

}

void addOrder(OrderList& list, PriorityQueue& pq, Action*& undoTop, int& nextId) {
    Order newOrder;
    char name[16];
    if(!readValidName(name, 16)) return;
    strcpy(newOrder.client.name, name);
    char phone[11];
    if (!readValidPhone(phone, sizeof(phone))) return;
    strcpy(newOrder.client.phone, phone);
    Date date;
    if(!readValidDate(date)) return;
    newOrder.orderDate = date;
    DeviceType type;
    if(!readDeviceType(type)) return;
    newOrder.deviceType = type;
    DeviceInfo info;
    if(!readDeviceInfo(type, info)) return;
    newOrder.info = info;
    char problem[81];
    if(!readProblem(problem)) return;
    strcpy(newOrder.problem, problem);
    int priority;
    if(!readPriority(priority)) return;
    newOrder.priority = priority;
    char buf[256];
    cout << "Вартість (обернений польський запис): ";
    if(!cin.getline(buf, sizeof(buf))) return;
    if(!evalRPN(buf, newOrder.cost)) {
        return;
    }
    newOrder.id = nextId++;
    newOrder.status = Status::WAITING;
    newOrder.masterName[0] = '\0';

    OrderNode* node = appendOrder(list, newOrder);

    enqueueOrder(pq, &node->data);

    pushUndo(undoTop, ActionType::ADD, newOrder);

    cout << "Замовлення №" << newOrder.id << " додано: вартість " << newOrder.cost << " грн, у черзі на ремонт: " << pq.size << ".\n";
}

void displayOrders(const OrderList& list){
    cout << "+-----+-----------------+------------+------------+--------+-----------------------+--------------------------------------------------------------+----+---------+-----------+\n";
    cout << "|   № | Клієнт          | Телефон    | Дата       | Тип    | Пристрій              | Деталі                                                       | Пр | Статус  | Вартість  |\n";
    cout << "+-----+-----------------+------------+------------+--------+-----------------------+--------------------------------------------------------------+----+---------+-----------+\n";
    const OrderNode *p = list.head;
    for(int i = 0; i < list.size; i++){
        cout << "| " << left << setw(3) << p->data.id 
             << " | " << left  << setw(15) << p->data.client.name 
             << " | " << left  << setw(10) << p->data.client.phone 
             << " | " << left  << setw(10) << p->data.orderDate
             << " | ";
        int deviceTypeInt = static_cast<int>(p->data.deviceType);
        switch (deviceTypeInt)
        {
            case 1: {
                char imeiBuf[8];
                sprintf(imeiBuf, "%06d", p->data.info.imei);
                cout << left << setw(6) << "PHONE" << " | " << setw(21) << imeiBuf;
                break;
            }
            case 2:
                cout << left  << setw(6) << "LAPTOP" << " | " << setw(21) << p->data.info.serial;
                break;
            case 3:
                cout << left  << setw(6) << "TV" << " | " << setw(21) << p->data.info.inches;
                break;
            default:
                cout << left  << setw(6) << "N/A" << " | " << setw(21) << "-";
                break;
        }
        cout << " | " << left  << setw(60) << p->data.problem 
             << " | " << right  << setw(2) << p->data.priority 
             << " | " << left  << setw(7) << p->data.status 
             << " | " << right << setw(9) << p->data.cost << " |\n";
        cout << "+-----+-----------------+------------+------------+--------+-----------------------+--------------------------------------------------------------+----+---------+-----------+\n";
        p = p->next;
    }

}

bool popOrder(PriorityQueue &pq, Order *&order){
    if(pq.size <= 0) return false;
    QNode *tmp = pq.head;
    order = tmp->order;
    pq.head = pq.head->next;
    pq.size --;
    delete tmp;
    return true;

}

void shipOrder(PriorityQueue &pq, Master *&currMaster){
    Order *currOrder = nullptr;
    if(!popOrder(pq, currOrder)){
        cout << "Черга на ремонт порожня.\n";
        return;
    }
    currOrder->status = Status::REPAIR;
    strcpy(currOrder->masterName, currMaster->name);

    cout << "Замовлення №" << currOrder->id << " (пріоритет " << currOrder->priority
         << ") передано майстру " << currMaster->name << ".\n"
         << "Несправність: " << currOrder->problem << "\n"
         << "У черзі залишилось: " << pq.size << "\n";

    currMaster = currMaster->next;
}

OrderNode *findById(const OrderList &list, int id){
    if(list.head == nullptr) return nullptr;
    OrderNode *curr = list.head;
    while(curr!= nullptr){
        if(curr->data.id == id){
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

void finishRepair(OrderList& list, Master *currMaster){
    cout << "Введіть Id замовлення: ";
    char line[256];
    cin.getline(line, 256);
    bool isNum = true;
    int len = strlen(line);
    for(int i = 0; i < len; i++){
        if(!isdigit(line[i])){
            isNum = false;
            break;
        }
    }
    if(!(len >= 3 && isNum)){
        cout << "Помилка: id - ціле число від 101.\n";
        return; 
    }
    int id = 0;
    for(int i = 0; i < len; i++){
        int pow = 1;
        for(int j = len - 1; j > i; j--){
            pow *= 10;
        }
        id += (line[i] - '0') * pow;
    }
    OrderNode *desirableOrder = findById(list, id);
    if(desirableOrder == nullptr){
        cout << "Замовлення №" << id << " не знайдено.\n";
        return;
    }
    if(desirableOrder->data.status == Status::WAITING){
        cout << "Замовлення №" << id << " ще не передано майстру.\n";
        return;
    }
    if(desirableOrder->data.status == Status::DONE){
        cout << "Замовлення №" << id << " уже завершено.\n";
        return;
    }
    desirableOrder->data.status = Status::DONE;
    Master *tmp = currMaster;
    bool isFound = false;
    do{
        if(strcmp(tmp->name, desirableOrder->data.masterName) == 0){
            isFound = true;
            break;
        }
        tmp = tmp->next;
    }while(tmp != currMaster);
    if(!isFound){
        return;
    }
    tmp->completedCount++;
    tmp->revenue = tmp->revenue + desirableOrder->data.cost;
    cout << "Ремонт замовлення №" << id << " завершено. Майстер " << tmp->name
         << ": виконано " << tmp->completedCount
         << ", виручка " << tmp->revenue << " грн.\n";

}

void removeOrder(OrderList& list, Action *&undoTop,PriorityQueue &pq){
    cout << "Введіть Id замовлення: ";
    char line[256];
    cin.getline(line, 256);
    bool isNum = true;
    int len = strlen(line);
    for(int i = 0; i < len; i++){
        if(!isdigit(line[i])){
            isNum = false;
            break;
        }
    }
    if(!(len >= 3 && isNum)){
        cout << "Помилка: id - ціле число від 101.\n";
        return; 
    }
    int id = 0;
    for(int i = 0; i < len; i++){
        int pow = 1;
        for(int j = len - 1; j > i; j--){
            pow *= 10;
        }
        id += (line[i] - '0') * pow;
    }
    OrderNode *desirableOrder = findById(list, id);
    if(desirableOrder == nullptr){
        cout << "Замовлення №" << id << " не знайдено.\n";
        return;
    }
    if(desirableOrder->data.status == Status::REPAIR){
        cout << "Замовлення №" << id << " вже передано майстру.\n";
        return;
    }
    if(desirableOrder->data.status == Status::DONE){
        cout << "Замовлення №" << id << " уже завершено.\n";
        return;
    }
    QNode *tmp = pq.head;
    if(pq.head->order->id == desirableOrder->data.id){
        pq.head = pq.head->next;
        delete tmp;
        pq.size--;
    }
    else if(pq.head){
        while(tmp->next != nullptr){
            if(tmp->next->order->id == desirableOrder->data.id){
                QNode *toDelete = tmp->next;
                tmp->next = toDelete->next;
                delete toDelete;
                pq.size--;
                break;
            }
            tmp = tmp->next;
        }
    }
    Action* actTmp = new Action;
    actTmp->type = ActionType::REMOVE;
    actTmp->orderCopy = desirableOrder->data;
    actTmp->next = undoTop;
    undoTop = actTmp;

    if(list.size == 1 && list.head == desirableOrder){
        list.head = nullptr;
        list.tail = nullptr;
        list.size = 0;
        delete desirableOrder;
    }
    else if(list.head == desirableOrder){
        list.head = list.head->next;
        list.head->prev = nullptr;
        delete desirableOrder;
        list.size--;
    }
    else if(list.tail == desirableOrder){
        list.tail = list.tail->prev;
        list.tail->next=nullptr;
        delete desirableOrder;
        list.size--;
    }
    else{
        desirableOrder->prev->next = desirableOrder->next;
        desirableOrder->next->prev = desirableOrder->prev;
        delete desirableOrder;
        list.size--;
    }
    cout << "Замовлення №" << id <<" успішно видалено.\n";
}

void undoLast(Action *&undoTop, OrderList& list, PriorityQueue& pq){
    if(!undoTop){
        return;
    }
    if(undoTop->type == ActionType::REMOVE){
    Order newOrder = undoTop->orderCopy;
    int id = undoTop->orderCopy.id;
        OrderNode* node = appendOrder(list, newOrder);

        enqueueOrder(pq, &node->data);

        
        Action *tmp = undoTop;
        undoTop = undoTop->next;
        delete tmp;
        cout << "Скасовано видалення замовлення №" << id << ".\n";
    }
    else if(undoTop->type == ActionType::ADD){
        int id = undoTop->orderCopy.id;
        OrderNode* target = findById(list, id);

        if (target == nullptr || target->data.status != Status::WAITING) {
            cout << "Неможливо скасувати додавання замовлення №" << id
                << ": воно вже в роботі або виконане.\n";
            return;
        }
        QNode *tmp = pq.head;
        if(pq.head->order->id == target->data.id){
            pq.head = pq.head->next;
            delete tmp;
            pq.size--;
        }
        else if(pq.head){
            while(tmp->next != nullptr){
                if(tmp->next->order->id == target->data.id){
                    QNode *toDelete = tmp->next;
                    tmp->next = toDelete->next;
                    delete toDelete;
                    pq.size--;
                    break;
                }
                tmp = tmp->next;
            }
        }
        if(list.size == 1 && list.head == target){
        list.head = nullptr;
        list.tail = nullptr;
        list.size = 0;
        delete target;
        }
        else if(list.head == target){
            list.head = list.head->next;
            list.head->prev = nullptr;
            delete target;
            list.size--;
        }
        else if(list.tail == target){
            list.tail = list.tail->prev;
            list.tail->next=nullptr;
            delete target;
            list.size--;
        }
        else{
            target->prev->next = target->next;
            target->next->prev = target->prev;
            delete target;
            list.size--;
        }

        Action* tmpAct = undoTop;
        undoTop = undoTop->next;
        delete tmpAct;

        cout << "Скасовано додавання замовлення №" << id << ".\n";
        
    }

}

Money calculateRevenue(const OrderNode* p){
    if (p == nullptr) {
        return Money{0, 0};
    }

    Money rest = calculateRevenue(p->next);
    if (p->data.status == Status::DONE) {
        return p->data.cost + rest;
    }
    return rest;
}

void generateReport(const OrderList& list, Master *listMasters){
    Order** arr = new Order*[list.size];
    OrderNode* curr = list.head;
    int len = 0;
    for (int i = 0; i < list.size; i++) {
        arr[i] = &curr->data;
        curr = curr->next;
        len++;
    }
    for(int i = 0; i < list.size - 1; i++){
        bool swapped = false;
        for(int j = 0; j < list.size - 1 - i; j++){
            bool needSwap = false;
            if (arr[j + 1]->cost > arr[j]->cost) {
                needSwap = true;
            }
            else if (arr[j + 1]->cost == arr[j]->cost && arr[j + 1]->id < arr[j]->id) {
                    needSwap = true;
            }

            if (needSwap) {
                Order* tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                swapped = true;
            }
        }
        if(!swapped){
            break;
        }
    }
    cout<<"Замовлення за вартістю:\n";
    for(int i = 0; i < len; i++){
        cout << "№ " << setw(5) << left << arr[i]->id << " " << setw(8) << right << arr[i]->cost << " грн " << setw(6) << arr[i]->status << endl;

    }
    Money revenue ;
    revenue = calculateRevenue(list.head);
    Money diff = arr[0]->cost - arr[len-1]->cost;
    delete[] arr;
    cout << "Різниця між найдорожчим і найдешевшим: "<< diff<< "грн\n";
    cout << "Виручка за завершеними ремонтами: "<< revenue<< "грн\n";
    cout << "Майстри, починаючи з наступного в черзі:\n";
    Master *tmp = listMasters;
    bool isFound = false;
    do{
        cout << "    "<< tmp->name <<" виконано: " << tmp->completedCount << ", виручка: " << tmp->revenue << "грн\n";
        tmp = tmp->next;
    }while(tmp != listMasters);

}

void reverseList(OrderList &list){
    if (list.size == 0) {
        cout << "Журнал порожній.\n";
    }
    OrderNode* curr = list.head;
    while (curr != nullptr) {
        OrderNode* temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev; 
    }
    
    OrderNode* tempHead = list.head;
    list.head = list.tail;
    list.tail = tempHead;
    
    cout << "Журнал інвертовано.\n";
}

void freeMasters(Master*& head) {
    if (!head) return;

    Master* curr = head->next;
    while (curr != head) {
        Master* nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
    delete head;
    head = nullptr;
}

bool readMasters(Master *&head, int n){
    char namesLine[256];
    cin.getline(namesLine, 256);
    int idx = 0;
    Master *tmp = head;
    for (int i = 0; i < n; i++) {
        if(i==0){
            head = new Master;
            head->next = head;
            tmp = head;
        }
        else if(i != 0){
            (*tmp).next = new Master;
            tmp = (*tmp).next;
            (*tmp).next = head;
        }
        while (namesLine[idx] == ' ') idx++;
        int j = 0;
        while (namesLine[idx] != '\0' && namesLine[idx] != ' ' && j < 23 ) {
            if(!((namesLine[idx] >= 'A' && namesLine[idx] <= 'Z') || (namesLine[idx] >= 'a' && namesLine[idx] <= 'z'))){
                freeMasters(head);
                cout << "Помилка: кількість імен має дорівнювати " << n <<", кожне ім'я з латинських літер, до 23 символів.\n";
                return false;
            }
            (*tmp).name[j++] = namesLine[idx++];
        }
        if(namesLine[idx] != ' ' && namesLine[idx] != '\0'){
            freeMasters(head);
            cout << "Помилка: кількість імен має дорівнювати " << n << ", кожне ім'я з латинських літер, до 23 символів.\n";
            return false;
        }
        (*tmp).name[j] = '\0';
        if(strcmp((*tmp).name, "") == 0){
            freeMasters(head);
            cout << "Помилка: кількість імен має дорівнювати " << n <<", кожне ім'я з латинських літер, до 23 символів.\n";
            return false;
        }
        for (Master* check = head; check != tmp; check = check->next) {
            if (strcmp(check->name, tmp->name) == 0) {
                cout << "Помилка: імена майстрів не повинні повторюватися.\n";
                freeMasters(head);
                return false;
            }
    }
    }
    while (namesLine[idx] == ' ') idx++;
    if (namesLine[idx] != '\0') {
        freeMasters(head);
        cout << "Помилка: кількість імен має дорівнювати " << n << ", кожне ім'я з латинських літер, до 23 символів.\n";
        return false;
    }
    return true;
}

int main() {
    cout << "Введіть кількість майстрів: ";
    char line[256];
    cin.getline(line, 256);
    if (!(strlen(line) == 1 && line[0] >= '1' && line[0] <= '5')) {
        cout << "Помилка: кількість майстрів має бути цілим числом від 1 до 5.\n";
        return 1; 
    }
    int n = line[0] - '0';
    cout << "Імена майстрів через пробіл: ";

    Master *listOfMasters = nullptr;
    if(!readMasters(listOfMasters, n)){
        return 1;
    }

    OrderList list;
    PriorityQueue pq;
    Action* undoTop = nullptr;
    int nextId = 101;
    char menu_buf[32];
    char menu_option = ' ';

    do {
        cout << "\n1. Додати замовлення\n"
            << "2. Журнал замовлень\n"
            << "3. Видати замовлення майстру\n"
            << "4. Завершити ремонт\n"
            << "5. Видалити замовлення\n"
            << "6. Скасувати останню дію\n"
            << "7. Звіт\n"
            << "8. Розвернути журнал\n"
            << "0. Вийти\n"
            << "Ваш вибір: ";
        if (!cin.getline(menu_buf, 32)) break;
        menu_option = menu_buf[0];

        if (strlen(menu_buf) != 1 || !(menu_option >= '0' && menu_option <= '8')) {
            cout << "Помилка: неправильний пункт меню.\n";
            continue;
        }

        switch (menu_option) {
        case '1': {
            addOrder(list, pq, undoTop, nextId);
            break;
        }

        case '2': {
            displayOrders(list);
            break;
        }

        case '3': {
            shipOrder(pq, listOfMasters);
            break;
        }

        case '4': {
            finishRepair(list, listOfMasters);
            break;
        }

        case '5': {
            removeOrder(list, undoTop, pq);
            break;
        }

        case '6': {
            undoLast(undoTop, list, pq);
            break;
        }

        case '7': {
            generateReport(list, listOfMasters);
            break;
        }

        case '8': {
            reverseList(list);
            break;
        }
        case '0': {
            cout << "Вихід із програми...\n";
            break;
        }

        default:
            cout << "Неочікувана помилка. Спробуйте ще раз.\n";
            break;
        }

    }while (menu_option != '0');

    freeMasters(listOfMasters);

    while (list.head) {
    OrderNode* tmp = list.head;
    list.head = list.head->next;
    delete tmp;
    }

    while (pq.head) {
        QNode* tmp = pq.head;
        pq.head = pq.head->next;
        delete tmp;
    }

    while (undoTop) {
        Action* tmp = undoTop;
        undoTop = undoTop->next;
        delete tmp;
    }
    
    return 0;
}
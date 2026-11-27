/*
Епік 6. Практичне завдання: Сервісний центр: черга ремонтів
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

struct Money {
    int hrn = 0;
    int kop = 0;
};

struct Master {
    char name[24] = "";
    int completed = 0;
    Money income;
    Master* next = nullptr;
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

enum class DeviceType { PHONE = 1, LAPTOP, TV };
enum class Status { WAITING, REPAIR, DONE };
enum class ActionType { ADD, DELETE };

union DeviceInfo {
    int imei;
    char serial[12];
    int inches;
};

struct Order {
    Client client;
    int id;
    Date date;
    DeviceType type;
    DeviceInfo info;
    char master[24] = "";
    Money price;
    char problem[81];
    Status status = Status::WAITING;
    int priority;
};

struct QNode {
    Order* order = nullptr;
    QNode* next = nullptr;
};

struct OrderNode {
    Order order {};
    OrderNode* next = nullptr;
    OrderNode* prev = nullptr;
};

struct OrderList {
    OrderNode* head = nullptr;
    OrderNode* tail = nullptr;
    int size = 0;
};

struct Action {
    ActionType type;
    Order order;
    Action* next = nullptr;
};

struct MoneyNode {
    Money value;
    MoneyNode* next = nullptr;
};

long long toKop(const Money& money) { return money.hrn * 100LL + money.kop; }

Money fromKop(long long kop) {
    Money result;
    result.hrn = kop / 100;
    result.kop = kop % 100;
    return result;
}

Money operator+(const Money& a, const Money& b) { return fromKop(toKop(a) + toKop(b)); }
Money operator-(const Money& a, const Money& b) { return fromKop(toKop(a) - toKop(b)); }
Money operator*(const Money& a, int n) { return fromKop(toKop(a) * n); }
bool operator<(const Money& a, const Money& b) { return toKop(a) < toKop(b); }

ostream& operator<<(ostream& out, const Money& money) {
    out << money.hrn << ".";
    if (money.kop < 10) out << "0";
    out << money.kop;
    return out;
}

bool addOrder(OrderList& list, QNode*& qHead, Action*& actionTop, int& nextId);
bool deleteOrder(OrderList& list, QNode*& qHead, Action*& actionTop);
bool undoAction(OrderList& list, QNode*& qHead, Action*& actionTop);
bool validName(const char* name, int maxLen);
void addMaster(Master*& head, Master*& tail, const char* name);
void deleteMasters(Master*& head, Master*& tail);
bool validPhone(const char* phone);
bool validDate(const char* str, Date& date);
bool validIMEI(const char* imei);
bool validSerial(const char* serial);
bool validInches(const char* str, int& inches);
void push(MoneyNode*& top, const Money& value);
bool pop(MoneyNode*& top, Money& value);
void deleteStack(MoneyNode*& top);
bool parseMoney(const char* str, Money& money);
bool evalRPN(const char* expr, Money& res);
bool readOrder(Order& order);
OrderNode* appendOrder(OrderList& list, const Order& order);
OrderNode* findById(const OrderList& list, int id);
void enqueue(QNode*& head, Order* order);
void pushAction(Action*& top, ActionType type, const Order& order);
int queueSize(const QNode* head);
bool readId(int& id);
Master* findMaster(Master* head, const char* name);
bool removeFromQueue(QNode*& head, const Order* order);
void removeOrderNode(OrderList& list, OrderNode* node);
ostream& operator<<(ostream& out, const Order& order);
void printOrders(const OrderList& list, const QNode* qHead);
bool giveOrder(QNode*& qHead, Master*& current);
bool finishRepair(OrderList& list, Master* head);
Money revenue(const OrderNode* node);
void printReport(const OrderList& list, Master* current);
void reverseOrders(OrderList& list);
void deleteQueue(QNode*& head);
void deleteActions(Action*& top);
void deleteOrders(OrderList& list);

int main() {
    char n[256];
    cout << "Кількість майстрів (від 1 до 5): ";
    if (!cin.getline(n, sizeof(n)) || strlen(n) != 1 || n[0] < '1' || n[0] > '5') {
        cout << "Помилка: кількість майстрів має бути цілим числом від 1 до 5.\n";
        return 1;
    }

    int howMany = n[0] - '0';
    char names[256];
    cout << "Імена майстрів через пробіл: ";
    if (!cin.getline(names, sizeof(names))) {
        cout << "Помилка: некоректний список імен майстрів.\n";
        return 1;
    }

    char* portion = strtok(names, " ");
    char masterNames[5][24];
    int actualCount = 0;

    while (portion != nullptr) {

        if (!validName(portion, 23)) {
            cout << "Помилка: кожне ім'я майстра має містити лише латинські літери (до 23 символів).\n";
            return 1;
        }

        for (int i = 0; i < actualCount; i++) {
            if (strcmp(masterNames[i], portion) == 0) {
                cout << "Помилка: імена майстрів не повинні повторюватися.\n";
                return 1;
            }
        }

        if (actualCount >= howMany) {
            cout << "Помилка: кількість імен має дорівнювати " << howMany << ".\n";
            return 1;
        }

        strcpy(masterNames[actualCount++], portion);
        portion = strtok(nullptr, " ");
    }

    if (actualCount != howMany) {
        cout << "Помилка: кількість імен має дорівнювати " << howMany << ", кожне ім'я з латинських літер, до 23 символів.\n";
        return 1;
    }

    Master* head = nullptr;
    Master* tail = nullptr;

    for (int i = 0; i < howMany; i++) addMaster(head, tail, masterNames[i]);

    Master* current = head;
    OrderList list;
    QNode* qHead = nullptr;
    Action* actionTop = nullptr;

    int nextId = 101;
    bool menuIsAlive = true;
    char choice[256];

    do {
        cout << "\n=========== Меню ===========\n";
        cout << "1    Додати замовлення\n";
        cout << "2    Журнал замовлень\n";
        cout << "3    Видати замовлення майстру\n";
        cout << "4    Завершити ремонт\n";
        cout << "5    Видалити замовлення\n";
        cout << "6    Скасувати останню дію\n";
        cout << "7    Звіт\n";
        cout << "8    Розвернути журнал\n";
        cout << "0    Вийти\n";
        cout << "Ваш вибір: ";

        if (!cin.getline(choice, sizeof(choice))) {
            if (cin.eof()) {
                menuIsAlive = false;
                break;
            }
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка: введіть номер пункту меню.\n";
            continue;
        }

        if (strlen(choice) != 1 || choice[0] < '0' || choice[0] > '9') {
            cout << "Помилка: введіть номер пункту меню.\n";
            continue;
        }

        if (choice[0] > '8') {
            cout << "Помилка: пункту " << choice[0] << " немає в меню.\n";
            continue;
        }

        switch (choice[0]) {
            case '0': {
                menuIsAlive = false;
                break;
            }
            case '1': {
                addOrder(list, qHead, actionTop, nextId);
                break;
            }
            case '2': {
                printOrders(list, qHead);
                break;
            }
            case '3': {
                giveOrder(qHead, current);
                break;
            }
            case '4': {
                finishRepair(list, head);
                break;
            }
            case '5': {
                deleteOrder(list, qHead, actionTop);
                break;
            }
            case '6': {
                undoAction(list, qHead, actionTop);
                break;
            }
            case '7': {
                printReport(list, current);
                break;
            }
            case '8': {
                reverseOrders(list);
                break;
            }
        }
    } while (menuIsAlive);

    deleteQueue(qHead);
    deleteOrders(list);
    deleteActions(actionTop);
    deleteMasters(head, tail);

    return 0;
}

bool validName(const char* name, int maxLen) {

    int len = strlen(name);
    if (len < 1 || len > maxLen) return false;

    for (int i = 0; i < len; i++) {
        if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z'))) return false;
    }
    return true;
}

void addMaster(Master*& head, Master*& tail, const char* name) {

    Master* node = new Master;
    strcpy(node->name, name);

    if (head == nullptr) head = node;
    else tail->next = node;

    tail = node;
    tail->next = head;
}

void deleteMasters(Master*& head, Master*& tail) {

    if (head == nullptr) return;
    tail->next = nullptr;

    while (head != nullptr) {
        Master* temp = head;
        head = head->next;
        delete temp;
    }

    tail = nullptr;
}

bool validPhone(const char* phone) {

    if (strlen(phone) != 10 || phone[0] != '0') return false;

    for (int i = 0; phone[i] != '\0'; i++) {
        if (!isdigit(static_cast<unsigned char>(phone[i]))) return false;
    }

    return true;
}

bool validDate(const char* str, Date& date) {

    if (strlen(str) != 10 || str[2] != '.' || str[5] != '.') return false;

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(static_cast<unsigned char>(str[i]))) return false;
    }

    Date temp;

    if (sscanf(str, "%d.%d.%d", &temp.day, &temp.month, &temp.year) != 3) return false;
    if (temp.year < 2000 || temp.year > 2099 || temp.month < 1 || temp.month > 12) return false;

    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool leap = temp.year % 400 == 0 || (temp.year % 4 == 0 && temp.year % 100 != 0);
    int maxDay = temp.month == 2 && leap ? 29 : daysInMonth[temp.month - 1];

    if (temp.day < 1 || temp.day > maxDay) return false;

    date = temp;
    return true;
}

bool validIMEI(const char* imei) {

    if (strlen(imei) != 6) return false;

    for (int i = 0; i < 6; i++) if (imei[i] < '0' || imei[i] > '9') {
        return false;
    }

    return true;
}

bool validSerial(const char* serial) {

    int len = strlen(serial);
    if (len < 1 || len > 11) return false;

    for (int i = 0; i < len; i++) {
        if (!((serial[i] >= 'A' && serial[i] <= 'Z') || (serial[i] >= '0' && serial[i] <= '9'))) return false;
    }

    return true;
}

bool validInches(const char* str, int& inches) {

    int len = strlen(str);

    if (len < 2 || len > 3) return false;
    for (int i = 0; i < len; i++) {
        if (str[i] < '0' || str[i] > '9') return false;
    }
    
    int value;

    if (sscanf(str, "%d", &value) != 1 || value < 19 || value > 100) return false;

    inches = value;

    return true;
}

void push(MoneyNode*& top, const Money& value) {

    MoneyNode* node = new MoneyNode;

    node->value = value;
    node->next = top;

    top = node;
}

bool pop(MoneyNode*& top, Money& value) {

    if (top == nullptr) return false;

    MoneyNode* node = top;

    value = node->value;
    top = top->next;

    delete node;

    return true;
}

void deleteStack(MoneyNode*& top) {
    while (top != nullptr) {
        MoneyNode* temp = top;
        top = top->next;
        delete temp;
    }
}

bool parseMoney(const char* str, Money& money) {

    Money temp;

    int i = 0;
    int digits = 0;

    while (str[i] >= '0' && str[i] <= '9') {
        if (digits == 6) return false;
        temp.hrn = temp.hrn * 10 + str[i] - '0';
        digits++;
        i++;
    }

    if (digits == 0) return false;

    if (str[i] == '.') {
        i++;
        digits = 0;

        while (str[i] >= '0' && str[i] <= '9') {
            if (digits == 2) return false;
            temp.kop = temp.kop * 10 + str[i] - '0';

            digits++;
            i++;
        }

        if (digits == 0) return false;
        if (digits == 1) temp.kop *= 10;
    }

    if (str[i] != '\0') return false;
    money = temp;
    return true;
}

bool evalRPN(const char* expr, Money& res) {

    MoneyNode* top = nullptr;

    const Money limit = {100000, 0};

    char copy[1024];

    if (strlen(expr) >= sizeof(copy)) {
        cout << "Помилка у виразі: вираз задовгий.\n";
        return false;
    }

    strcpy(copy, expr);

    char* portion = strtok(copy, " ");

    if (portion == nullptr) {
        cout << "Помилка у виразі: порожній вираз.\n";
        return false;
    }

    while (portion != nullptr) {

        if (strcmp(portion, "+") == 0 || strcmp(portion, "-") == 0 || strcmp(portion, "*") == 0) {
            Money a, b, result;
            char operation = portion[0];

            if (!pop(top, b) || !pop(top, a)) {
                cout << "Помилка у виразі: для операції «" << operation << "» бракує чисел.\n";
                deleteStack(top);
                return false;
            }

            if (operation == '+') result = a + b;

            else if (operation == '-') {
                if (a < b) {
                    cout << "Помилка у виразі: проміжний результат від'ємний.\n";
                    deleteStack(top);
                    return false;
                }
                result = a - b;
            }

            else {
                if (b.kop != 0 || b.hrn < 1 || b.hrn > 100) {
                    cout << "Помилка у виразі: множник має бути цілим числом від 1 до 100.\n";
                    deleteStack(top);
                    return false;
                }
                result = a * b.hrn;
            }

            if (limit < result) {
                cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                deleteStack(top);
                return false;
            }

            
            push(top, result);
        }
        else {
            Money number;

            if (!parseMoney(portion, number)) {
                cout << "Помилка у виразі: «" << portion << "» не є числом або операцією.\n";
                deleteStack(top);
                return false;
            }

            if (limit < number) {
                cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                deleteStack(top);
                return false;
            }

            push(top, number);
        }
        portion = strtok(nullptr, " ");
    }

    int numbersLeft = 0;

    for (MoneyNode* p = top; p != nullptr; p = p->next) numbersLeft++;

    if (numbersLeft != 1) {
        cout << "Помилка у виразі: у стеку залишилось чисел: " << numbersLeft << ", а має бути одне.\n";
        deleteStack(top);
        return false;
    }

    Money result;
    pop(top, result);

    if (result.hrn == 0 && result.kop == 0) {
        cout << "Помилка у виразі: кінцева вартість дорівнює 0.00 грн.\n";
        return false;
    }

    res = result;

    return true;
}

bool readOrder(Order& order) {

    char name[16];
    cout << "Ім'я клієнта: ";
    if (!cin.getline(name, sizeof(name)) || !validName(name, 15)) {
        cout << "Помилка: ім'я має містити від 1 до 15 латинських літер.\n";
        return false;
    }

    strcpy(order.client.name, name);

    char phone[11];
    cout << "Телефон (10 цифр): ";

    if (!cin.getline(phone, sizeof(phone)) || !validPhone(phone)) {
        cout << "Помилка: телефон має складатися з 10 цифр і починатися з 0.\n";
        return false;
    }

    strcpy(order.client.phone, phone);

    char date[11];
    cout << "Дата прийому (ДД.ММ.РРРР): ";

    if (!cin.getline(date, sizeof(date)) || !validDate(date, order.date)) {
        cout << "Помилка: некоректна дата.\n";
        return false;
    }

    char type[16];
    cout << "Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ";
    if (!cin.getline(type, sizeof(type)) || strlen(type) != 1 || type[0] < '1' || type[0] > '3') {
        cout << "Помилка: тип пристрою має бути 1, 2 або 3.\n";
        return false;
    }
    
    order.type = static_cast<DeviceType>(type[0] - '0');

    switch (order.type) {
        case DeviceType::PHONE: {

            char imei[16];
            cout << "Останні 6 цифр IMEI: ";

            if (!cin.getline(imei, sizeof(imei)) || !validIMEI(imei)) {
                cout << "Помилка: потрібно рівно 6 цифр.\n";
                return false;
            }

            sscanf(imei, "%d", &order.info.imei);
            break;
        }
        case DeviceType::LAPTOP: {
            char serial[16];
            cout << "Серійний номер: ";

            if (!cin.getline(serial, sizeof(serial)) || !validSerial(serial)) {
                cout << "Помилка: серійний номер має містити від 1 до 11 великих латинських літер або цифр.\n";
                return false;
            }

            strcpy(order.info.serial, serial);
            break;
        }
        case DeviceType::TV: {
            char inches[16];
            int value;

            cout << "Діагональ телевізора: ";
            if (!cin.getline(inches, sizeof(inches)) || !validInches(inches, value)) {
                cout << "Помилка: діагональ має бути цілим числом від 19 до 100.\n";
                return false;
            }

            order.info.inches = value;
            break;
        }
    }

    char problem[81];
    cout << "Опис несправності: ";
    if (!cin.getline(problem, sizeof(problem)) || strlen(problem) < 1) {
        cout << "Помилка: опис має містити від 1 до 80 байтів.\n";
        return false;
    }

    strcpy(order.problem, problem);

    char priority[16];
    cout << "Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ";
    if (!cin.getline(priority, sizeof(priority)) || strlen(priority) != 1 || priority[0] < '1' || priority[0] > '3') {
        cout << "Помилка: пріоритет має бути 1, 2 або 3.\n";
        return false;
    }

    order.priority = priority[0] - '0';

    char price[1024];
    cout << "Вартість (обернений польський запис): ";
    if (!cin.getline(price, sizeof(price))) {
        cout << "Помилка: некоректне введення вартості.\n";
        return false;
    }

    return evalRPN(price, order.price);
}

OrderNode* appendOrder(OrderList& list, const Order& order) {

    OrderNode* node = new OrderNode;

    node->order = order;
    node->prev = list.tail;

    if (list.head == nullptr) list.head = node;
    else list.tail->next = node;

    list.tail = node;
    list.size++;

    return node;
}

OrderNode* findById(const OrderList& list, int id) {

    OrderNode* current = list.head;

    while (current != nullptr && current->order.id != id) {
        current = current->next;
    }

    return current;
}

void enqueue(QNode*& head, Order* order) {

    QNode* node = new QNode;

    node->order = order;

    if (head == nullptr || order->priority > head->order->priority) {
        node->next = head;
        head = node;
        return;
    }

    QNode* current = head;

    while (current->next != nullptr && current->next->order->priority >= order->priority) {
        current = current->next;
    }

    node->next = current->next;
    current->next = node;
}

void pushAction(Action*& top, ActionType type, const Order& order) {

    Action* node = new Action;

    node->type = type;
    node->order = order;
    node->next = top;
    top = node;
}

int queueSize(const QNode* head) {
    int count = 0;

    while (head != nullptr) {
        count++;
        head = head->next;
    }

    return count;
}

bool readId(int& id) {
    char input[32];

    if (!cin.getline(input, sizeof(input))) {
        cout << "Помилка: номер замовлення має бути цілим числом.\n";
        return false;
    }

    if (input[0] == '\0') {
        cout << "Помилка: номер замовлення має бути цілим числом.\n";
        return false;
    }

    id = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] < '0' || input[i] > '9') {
            cout << "Помилка: номер замовлення має бути цілим числом.\n";
            return false;
        }

        int digit = input[i] - '0';
        if (id > (2147483647 - digit) / 10) {
            cout << "Помилка: номер замовлення завеликий.\n";
            return false;
        }
        id = id * 10 + digit;
    }

    return true;
}

Master* findMaster(Master* head, const char* name) {

    if (head == nullptr) return nullptr;

    Master* current = head;

    do {
        if (strcmp(current->name, name) == 0) return current;
        current = current->next;
    } while (current != head);

    return nullptr;
}

bool removeFromQueue(QNode*& head, const Order* order) {

    QNode* current = head;
    QNode* previous = nullptr;

    while (current != nullptr && current->order != order) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) return false;
    if (previous == nullptr) head = current->next;
    else previous->next = current->next;
    delete current;

    return true;
}

void removeOrderNode(OrderList& list, OrderNode* node) {

    if (node->prev != nullptr) node->prev->next = node->next;
    else list.head = node->next;

    if (node->next != nullptr) node->next->prev = node->prev;
    else list.tail = node->prev;

    delete node;
    list.size--;
}

bool addOrder(OrderList& list, QNode*& qHead, Action*& actionTop, int& nextId) {

    Order order{};

    if (!readOrder(order)) return false;

    order.id = nextId++;
    OrderNode* node = appendOrder(list, order);

    enqueue(qHead, &node->order);
    pushAction(actionTop, ActionType::ADD, order);

    cout << "Замовлення №" << order.id << " додано: вартість " << order.price << " грн, у черзі на ремонт: " << queueSize(qHead) << ".\n";

    return true;
}

ostream& operator<<(ostream& out, const Order& order) {
    char date[11], details[20], price[16], type[8], status[8];

    snprintf(date, sizeof(date), "%02d.%02d.%04d", order.date.day, order.date.month, order.date.year);
    snprintf(price, sizeof(price), "%d.%02d", order.price.hrn, order.price.kop);

    switch (order.type) {
        case DeviceType::PHONE: {
            strcpy(type, "PHONE");
            snprintf(details, sizeof(details), "IMEI %06d", order.info.imei);
            break;
        }
        case DeviceType::LAPTOP: {
            strcpy(type, "LAPTOP");
            snprintf(details, sizeof(details), "SN %s", order.info.serial);
            break;
        }
        case DeviceType::TV: {
            strcpy(type, "TV");
            snprintf(details, sizeof(details), "%d inch", order.info.inches);
            break;
        }
    }

    switch (order.status) {
        case Status::WAITING: {
            strcpy(status, "WAITING");
            break;
        }
        case Status::REPAIR: {
            strcpy(status, "REPAIR");
            break;
        }
        case Status::DONE: {
            strcpy(status, "DONE");
            break;
        }
    }

    ios::fmtflags oldFlags = out.flags();
    char oldFill = out.fill();

    out << "| " << left << setw(4) << order.id << " | " << setw(15) << order.client.name  << " | " << setw(10) << order.client.phone << " | " << setw(10) << date << " | " << setw(6) << type << " | " << setw(14) << details << " | " << setw(2) << order.priority << " | " << setw(7) << status << " | " << right << setw(9) << price << " |\n";

    out.flags(oldFlags);
    out.fill(oldFill);

    return out;
}

void printOrders(const OrderList& list, const QNode* qHead) {

    if (list.head == nullptr) {
        cout << "Журнал порожній.\n";
        return;
    }
    cout << "+------+-----------------+------------+------------+--------+----------------+----+---------+-----------+\n";
    cout << "| №    | Клієнт          | Телефон    | Дата       | Тип    | Деталі         | Пр | Статус  | Вартість  |\n";
    cout << "+------+-----------------+------------+------------+--------+----------------+----+---------+-----------+\n";

    for (OrderNode* current = list.head; current != nullptr; current = current->next) cout << current->order;

    cout << "+------+-----------------+------------+------------+--------+----------------+----+---------+-----------+\n";

    cout << "Усього замовлень: " << list.size << ", у черзі на ремонт: " << queueSize(qHead) << "\n";
}

bool giveOrder(QNode*& qHead, Master*& current) {

    if (qHead == nullptr) {
        cout << "Черга на ремонт порожня.\n";
        return false;
    }

    QNode* node = qHead;
    Order* order = node->order;
    qHead = qHead->next;

    delete node;

    strcpy(order->master, current->name);
    order->status = Status::REPAIR;

    cout << "Замовлення №" << order->id << " (пріоритет " << order->priority << ") передано майстру " << current->name << ".\n";
    cout << "Несправність: " << order->problem << "\n";
    current = current->next;

    cout << "У черзі залишилось: " << queueSize(qHead) << "\n";

    return true;
}

bool finishRepair(OrderList& list, Master* head) {
    int id;
    cout << "Номер замовлення: ";
    if (!readId(id)) return false;

    OrderNode* node = findById(list, id);

    if (node == nullptr) {
        cout << "Замовлення №" << id << " не знайдено.\n";
        return false;
    }

    Order* order = &node->order;

    if (order->status == Status::WAITING) {
        cout << "Замовлення №" << id << " ще не передано майстру.\n";
        return false;
    }

    if (order->status == Status::DONE) {
        cout << "Замовлення №" << id << " уже завершено.\n";
        return false;
    }

    Master* master = findMaster(head, order->master);

    if (master == nullptr) {
        cout << "Помилка: майстра не знайдено.\n";
        return false;
    }

    order->status = Status::DONE;
    master->completed++;
    master->income = master->income + order->price;

    cout << "Ремонт замовлення №" << id << " завершено. Майстер " << master->name << ": виконано " << master->completed << ", виручка " << master->income << " грн.\n";

    return true;
}

bool deleteOrder(OrderList& list, QNode*& qHead, Action*& actionTop) {
    int id;
    cout << "Номер замовлення: ";

    if (!readId(id)) return false;

    OrderNode* node = findById(list, id);

    if (node == nullptr) {
        cout << "Замовлення №" << id << " не знайдено.\n";
        return false;
    }

    if (node->order.status != Status::WAITING) {
        cout << "Видалити можна лише замовлення, яке очікує в черзі.\n";
        return false;
    }

    if (!removeFromQueue(qHead, &node->order)) {
        cout << "Помилка: замовлення відсутнє в черзі.\n";
        return false;
    }

    Order order = node->order;
    pushAction(actionTop, ActionType::DELETE, order);
    removeOrderNode(list, node);

    cout << "Замовлення №" << id << " видалено. У журналі: " << list.size << ", у черзі: " << queueSize(qHead) << ".\n";

    return true;
}

bool undoAction(OrderList& list, QNode*& qHead, Action*& actionTop) {
    if (actionTop == nullptr) {
        cout << "Немає дій для скасування.\n";
        return false;
    }

    Action* action = actionTop;
    bool success = true;

    if (action->type == ActionType::ADD) {
        OrderNode* node = findById(list, action->order.id);

        if (node == nullptr) {
            cout << "Помилка: замовлення не знайдено.\n";
            success = false;
        }

        else if (node->order.status != Status::WAITING) {
            cout << "Додавання замовлення №" << node->order.id << " скасувати неможливо: його вже передано майстру.\n";
            success = false;
        }
        
        else if (!removeFromQueue(qHead, &node->order)) {
            cout << "Помилка: замовлення відсутнє в черзі.\n";
            success = false;
        }
        
        else {
            removeOrderNode(list, node);
            cout << "Додавання замовлення №" << action->order.id << " скасовано.\n";
        }

    }

    else {
        OrderNode* node = appendOrder(list, action->order);
        enqueue(qHead, &node->order);
        cout << "Скасовано видалення замовлення №" << node->order.id << ": його повернуто в кінець журналу і в чергу.\n";
    }

    actionTop = action->next;
    delete action;
    return success;
}

Money revenue(const OrderNode* node) {

    if (node == nullptr) return Money{};

    Money total = revenue(node->next);
    
    if (node->order.status == Status::DONE) total = node->order.price + total;
    
    return total;
}

void printReport(const OrderList& list, Master* current) {
    cout << "\n========== ЗВІТ ==========\n";
    int count = list.size;

    if (count == 0) {
        cout << "Журнал порожній.\n";
        cout << "Виручка за завершеними ремонтами: 0.00 грн\n";
    } 
    
    else {
        Order** orders = new Order*[count];
        OrderNode* node = list.head;
        
        for (int i = 0; i < count; i++) {
            orders[i] = &node->order;
            node = node->next;
        }

        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                bool swapNeeded = orders[j]->price < orders[j + 1]->price;

                if (!(orders[j]->price < orders[j + 1]->price) &&
                    !(orders[j + 1]->price < orders[j]->price) && orders[j]->id > orders[j + 1]->id) {
                    swapNeeded = true;
                }

                if (swapNeeded) {
                    Order* temp = orders[j];
                    orders[j] = orders[j + 1];
                    orders[j + 1] = temp;
                }
            }
        }

        cout << "Замовлення за вартістю:\n";

        for (int i = 0; i < count; i++) {
            const char* status = orders[i]->status == Status::WAITING ? "WAITING" : orders[i]->status == Status::REPAIR ? "REPAIR" : "DONE";
            cout << " №" << orders[i]->id << " " << orders[i]->price << " грн " << status << "\n";
        }

        Money difference = orders[0]->price - orders[count - 1]->price;

        cout << "Різниця між найдорожчим і найдешевшим: " << difference << " грн\n";

        delete[] orders;

        cout << "Виручка за завершеними ремонтами: " << revenue(list.head) << " грн\n";
    }

    if (current != nullptr) {

        cout << "Майстри, починаючи з наступного в черзі:\n";
        Master* start = current;

        do {
            cout << " " << current->name << "   виконано: " << current->completed << ", виручка: " << current->income << " грн\n";
            current = current->next;
        } while (current != start);
    }

    cout << "========== КІНЕЦЬ ЗВІТУ ==========\n";
}

void reverseOrders(OrderList& list) {
    if (list.head == nullptr) {
        cout << "Журнал порожній.\n";
        return;
    }

    OrderNode* current = list.head;

    while (current != nullptr) {
        OrderNode* next = current->next;
        current->next = current->prev;
        current->prev = next;
        current = next;
    }

    OrderNode* temp = list.head;
    list.head = list.tail;
    list.tail = temp;

    cout << "Журнал розвернуто: тепер першим іде замовлення №" << list.head->order.id << ", останнім №" << list.tail->order.id << ".\n";
}

void deleteQueue(QNode*& head) {
    while (head != nullptr) {
        QNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void deleteOrders(OrderList& list) {
    OrderNode* current = list.head;

    while (current != nullptr) {
        OrderNode* temp = current;
        current = current->next;
        delete temp;
    }

    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

void deleteActions(Action*& top) {
    while (top != nullptr) {
        Action* temp = top;
        top = top->next;
        delete temp;
    }
}

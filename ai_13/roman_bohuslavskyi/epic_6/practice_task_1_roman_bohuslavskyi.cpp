/*
Задача:  Сервісний центр: черга ремонтів
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>

using namespace std;

const int INPUT_SIZE = 2048;
const int MAX_PRICE = 10000000;

enum class DeviceType {
    PHONE = 1,
    LAPTOP,
    TV
};

enum class Status {
    WAITING,
    REPAIR,
    DONE
};

enum class ActionType {
    ADD,
    REMOVE
};

struct Money {
    int hrn;
    int kop;
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

union DeviceInfo {
    int imei;
    char serial[12];
    int inches;
};

struct Order {
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

struct OrderNode {
    Order order;
    OrderNode* prev;
    OrderNode* next;
};

struct OrderList {
    OrderNode* head;
    OrderNode* tail;
    int size;
};

struct QNode {
    Order* order;
    QNode* next;
};

struct Master {
    char name[24];
    int completed;
    Money earned;
    Master* next;
};

struct Action {
    ActionType type;
    Order order;
    Action* next;
};

struct NumberNode {
    Money value;
    NumberNode* next;
};

int kopecks(const Money& value);
Money moneyFrom(int value);
Money operator+(const Money& a, const Money& b);
Money operator-(const Money& a, const Money& b);
Money operator*(const Money& a, int count);
bool operator<(const Money& a, const Money& b);
ostream& operator<<(ostream& os, const Money& value);
const char* statusName(Status status);
bool readLine(const char* prompt, char* text, int capacity);
bool parseInt(char* text, int& value);
bool latinWord(char* text, int maximum);
bool digits(char* text, int length);
bool parseDate(char* text, Date& date);
void clearNumbers(NumberNode*& top);
Money popNumber(NumberNode*& top);
bool parseMoney(char* token, Money& result);
bool evalRPN(const char* expr, Money& res);
OrderNode* appendOrder(OrderList& list, const Order& order);
OrderNode* findById(const OrderList& list, int id);
void removeOrder(OrderList& list, OrderNode* node);
void enqueue(QNode*& head, Order* order);
void removeFromQueue(QNode*& head, int id);
int queueSize(const QNode* head);
void pushAction(Action*& top, ActionType type, const Order& order);
void clearActions(Action*& top);
void clearMasters(Master*& first);
bool readMasters(Master*& first);
bool inputField(const char* prompt, char* text);
bool readOrder(Order& order);
void addOrder(OrderList& list, QNode*& queue, Action*& actions, int& nextId);
ostream& operator<<(ostream& os, const Order& order);
void showJournal(const OrderList& list, const QNode* queue);
void assignOrder(QNode*& queue, Master*& nextMaster);
OrderNode* requestOrder(const OrderList& list);
void completeRepair(const OrderList& list, Master* masters);
void deleteOrder(OrderList& list, QNode*& queue, Action*& actions);
void undoAction(OrderList& list, QNode*& queue, Action*& actions);
Money revenue(const OrderNode* p);
void sortOrders(Order** orders, int count);
void showReport(const OrderList& list, Master* nextMaster);
void reverseJournal(OrderList& list);
void freeMemory(OrderList& list, QNode*& queue, Action*& actions, Master*& masters);
void showMenu();

int main() {
    OrderList list{nullptr, nullptr, 0};
    QNode* queue = nullptr;
    Action* actions = nullptr;
    Master* masters = nullptr;
    if (!readMasters(masters)) {
        return 0;
    }
    Master* nextMaster = masters;
    int nextId = 101;
    char text[INPUT_SIZE];
    while (true) {
        showMenu();
        int choice;
        bool validLine = readLine("Ваш вибір: ", text, INPUT_SIZE);
        if (!validLine && cin.eof()) {
            break;
        }
        if (!validLine || !parseInt(text, choice)) {
            cout << "Помилка: введіть номер пункту меню.\n";
            continue;
        }
        if (choice == 0) {
            break;
        }
        cout << '\n';
        switch (choice) {
        case 1:
            addOrder(list, queue, actions, nextId);
            break;
        case 2:
            showJournal(list, queue);
            break;
        case 3:
            assignOrder(queue, nextMaster);
            break;
        case 4:
            completeRepair(list, masters);
            break;
        case 5:
            deleteOrder(list, queue, actions);
            break;
        case 6:
            undoAction(list, queue, actions);
            break;
        case 7:
            showReport(list, nextMaster);
            break;
        case 8:
            reverseJournal(list);
            break;
        default:
            cout << "Помилка: пункту " << choice << " немає в меню.\n";
        }
    }
    freeMemory(list, queue, actions, masters);
    return 0;
}

int kopecks(const Money& value) {
    return value.hrn * 100 + value.kop;
}

Money moneyFrom(int value) {
    return {value / 100, value % 100};
}

Money operator+(const Money& a, const Money& b) {
    return moneyFrom(kopecks(a) + kopecks(b));
}

Money operator-(const Money& a, const Money& b) {
    return moneyFrom(kopecks(a) - kopecks(b));
}

Money operator*(const Money& a, int count) {
    return moneyFrom(kopecks(a) * count);
}

bool operator<(const Money& a, const Money& b) {
    return kopecks(a) < kopecks(b);
}

ostream& operator<<(ostream& os, const Money& value) {
    char text[32];
    sprintf(text, "%d.%02d", value.hrn, value.kop);
    os << text;
    return os;
}

const char* statusName(Status status) {
    if (status == Status::WAITING) {
        return "WAITING";
    }
    if (status == Status::REPAIR) {
        return "REPAIR";
    }
    return "DONE";
}

bool readLine(const char* prompt, char* text, int capacity) {
    cout << prompt;
    if (cin.getline(text, capacity)) {
        return true;
    }
    if (cin.eof()) {
        return false;
    }
    cin.clear();
    cin.ignore(100000, '\n');
    text[0] = '\0';
    return false;
}

bool parseInt(char* text, int& value) {
    if (text[0] == '\0' || strlen(text) > 9) {
        return false;
    }
    int result = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] < '0' || text[i] > '9') {
            return false;
        }
        result = result * 10 + (text[i] - '0');
    }
    value = result;
    return true;
}

bool latinWord(char* text, int maximum) {
    int length = strlen(text);
    if (length < 1 || length > maximum) {
        return false;
    }
    for (int i = 0; i < length; i++) {
        if (!((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))) {
            return false;
        }
    }
    return true;
}

bool digits(char* text, int length) {
    if (static_cast<int>(strlen(text)) != length) {
        return false;
    }
    for (int i = 0; i < length; i++) {
        if (text[i] < '0' || text[i] > '9') {
            return false;
        }
    }
    return true;
}

bool parseDate(char* text, Date& date) {
    if (strlen(text) != 10 || text[2] != '.' || text[5] != '.') {
        return false;
    }
    for (int i = 0; i < 10; i++) {
        if (i != 2 && i != 5 && (text[i] < '0' || text[i] > '9')) {
            return false;
        }
    }
    date.day = (text[0] - '0') * 10 + (text[1] - '0');
    date.month = (text[3] - '0') * 10 + (text[4] - '0');
    date.year = (text[6] - '0') * 1000 + (text[7] - '0') * 100 + (text[8] - '0') * 10 + (text[9] - '0');
    if (date.year < 2000 || date.year > 2099 || date.month < 1 || date.month > 12) {
        return false;
    }
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (date.year % 4 == 0) {
        days[1] = 29;
    }
    return date.day >= 1 && date.day <= days[date.month - 1];
}

void clearNumbers(NumberNode*& top) {
    while (top) {
        NumberNode* old = top;
        top = top->next;
        delete old;
    }
}

Money popNumber(NumberNode*& top) {
    NumberNode* old = top;
    Money value = old->value;
    top = top->next;
    delete old;
    return value;
}

bool parseMoney(char* token, Money& result) {
    int i = 0;
    int hrn = 0;
    int kop = 0;
    while (token[i] >= '0' && token[i] <= '9') {
        if (i == 6) {
            return false;
        }
        hrn = hrn * 10 + (token[i] - '0');
        i++;
    }
    if (i == 0) {
        return false;
    }
    if (token[i] == '.') {
        i++;
        if (token[i] < '0' || token[i] > '9') {
            return false;
        }
        kop = (token[i] - '0') * 10;
        i++;
        if (token[i] >= '0' && token[i] <= '9') {
            kop += token[i] - '0';
            i++;
        }
    }
    if (token[i]) {
        return false;
    }
    result = {hrn, kop};
    return true;
}

bool evalRPN(const char* expr, Money& res) {
    char buffer[INPUT_SIZE];
    strcpy(buffer, expr);
    const char* separators = " \t\n\r\f\v";
    NumberNode* top = nullptr;
    int count = 0;
    const char* error = nullptr;
    for (char* token = strtok(buffer, separators); token && !error; token = strtok(nullptr, separators)) {
        Money value{};
        if (token[1] == '\0' && (token[0] == '+' || token[0] == '-' || token[0] == '*')) {
            if (count < 2) {
                cout << "Помилка у виразі: для операції «" << token << "» бракує чисел.\n";
                clearNumbers(top);
                return false;
            }
            Money b = popNumber(top);
            Money a = popNumber(top);
            count -= 2;
            if (token[0] == '+') {
                value = a + b;
            }
            else if (token[0] == '-') {
                if (a < b) {
                    error = "проміжний результат від'ємний.";
                }
                else {
                    value = a - b;
                }
            }
            else {
                if (b.kop != 0 || b.hrn < 1 || b.hrn > 100) {
                    error = "множник має бути цілим числом від 1 до 100.";
                }
                else {
                    value = a * b.hrn;
                }
            }
        }
        else if (!parseMoney(token, value)) {
            cout << "Помилка у виразі: «" << token << "» не є числом або операцією.\n";
            clearNumbers(top);
            return false;
        }
        if (!error && kopecks(value) > MAX_PRICE) {
            error = "сума перевищує 100000.00 грн.";
        }
        if (!error) {
            top = new NumberNode{value, top};
            count++;
        }
    }
    if (!error && count == 0) {
        error = "порожній вираз.";
    }
    if (!error && count != 1) {
        cout << "Помилка у виразі: у стеку залишилось чисел: " << count << ", а має бути одне.\n";
        clearNumbers(top);
        return false;
    }
    if (!error && kopecks(top->value) == 0) {
        error = "кінцевий результат має бути більшим за 0.00 грн.";
    }
    if (error) {
        cout << "Помилка у виразі: " << error << '\n';
    }
    else {
        res = top->value;
    }
    clearNumbers(top);
    return error == nullptr;
}

OrderNode* appendOrder(OrderList& list, const Order& order) {
    OrderNode* node = new OrderNode{order, list.tail, nullptr};
    if (list.tail) {
        list.tail->next = node;
    }
    else {
        list.head = node;
    }
    list.tail = node;
    list.size++;
    return node;
}

OrderNode* findById(const OrderList& list, int id) {
    for (OrderNode* p = list.head; p; p = p->next) {
        if (p->order.id == id) {
            return p;
        }
    }
    return nullptr;
}

void removeOrder(OrderList& list, OrderNode* node) {
    if (node->prev) {
        node->prev->next = node->next;
    }
    else {
        list.head = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    else {
        list.tail = node->prev;
    }
    delete node;
    --list.size;
}

void enqueue(QNode*& head, Order* order) {
    QNode* previous = nullptr;
    QNode* current = head;
    while (current && current->order->priority >= order->priority) {
        previous = current;
        current = current->next;
    }
    QNode* node = new QNode{order, current};
    if (previous) {
        previous->next = node;
    }
    else {
        head = node;
    }
}

void removeFromQueue(QNode*& head, int id) {
    QNode* previous = nullptr;
    QNode* current = head;
    while (current && current->order->id != id) {
        previous = current;
        current = current->next;
    }
    if (!current) {
        return;
    }
    if (previous) {
        previous->next = current->next;
    }
    else {
        head = current->next;
    }
    delete current;
}

int queueSize(const QNode* head) {
    int count = 0;
    for (; head; head = head->next) {
        count++;
    }
    return count;
}


void pushAction(Action*& top, ActionType type, const Order& order) {
    top = new Action{type, order, top};
}

void clearActions(Action*& top) {
    while (top) {
        Action* old = top;
        top = top->next;
        delete old;
    }
}

void clearMasters(Master*& first) {
    if (!first) {
        return;
    }
    Master* p = first->next;
    while (p != first) {
        Master* old = p;
        p = p->next;
        delete old;
    }
    delete first;
    first = nullptr;
}

bool readMasters(Master*& first) {
    char text[INPUT_SIZE];
    char* names[5];
    int count;
    if (!readLine("Кількість майстрів (від 1 до 5): ", text, INPUT_SIZE) || !parseInt(text, count) || count < 1 || count > 5) {
        cout << "Помилка: кількість майстрів має бути цілим числом від 1 до 5.\n";
        return false;
    }
    char* token = nullptr;
    if (readLine("Імена майстрів через пробіл: ", text, INPUT_SIZE)) {
        token = strtok(text, " ");
    }
    int found = 0;
    while (token && found < count && latinWord(token, 23)) {
        names[found] = token;
        found++;
        token = strtok(nullptr, " ");
    }
    if (found != count || token) {
        cout << "Помилка: кількість імен має дорівнювати " << count << ", кожне ім'я з латинських літер, до 23 символів.\n";
        return false;
    }
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(names[i], names[j]) == 0) {
                cout << "Помилка: імена майстрів не повинні повторюватися.\n";
                return false;
            }
        }
    }
    Master* tail = nullptr;
    for (int i = 0; i < count; i++) {
        Master* node = new Master{};
        strcpy(node->name, names[i]);
        if (!first) {
            first = node;
        }
        else {
            tail->next = node;
        }
        tail = node;
    }
    tail->next = first;
    return true;
}

bool inputField(const char* prompt, char* text) {
    if (readLine(prompt, text, INPUT_SIZE)) {
        return true;
    }
    if (!cin.eof()) {
        cout << "Помилка: введений рядок надто довгий.\n";
    }
    return false;
}

bool readOrder(Order& order) {
    char text[INPUT_SIZE];
    int value;
    if (!inputField("Ім'я клієнта: ", text)) {
        return false;
    }
    if (!latinWord(text, 15)) {
        cout << "Помилка: ім'я має містити від 1 до 15 латинських літер.\n";
        return false;
    }
    strcpy(order.client.name, text);
    if (!inputField("Телефон (10 цифр): ", text)) {
        return false;
    }
    if (!digits(text, 10) || text[0] != '0') {
        cout << "Помилка: телефон має складатися з 10 цифр і починатися з 0.\n";
        return false;
    }
    strcpy(order.client.phone, text);
    if (!inputField("Дата прийому (ДД.ММ.РРРР): ", text)) {
        return false;
    }
    if (!parseDate(text, order.date)) {
        cout << "Помилка: некоректна дата.\n";
        return false;
    }
    if (!inputField("Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ", text)) {
        return false;
    }
    if (!parseInt(text, value) || value < 1 || value > 3) {
        cout << "Помилка: тип пристрою має бути 1, 2 або 3.\n";
        return false;
    }
    order.type = static_cast<DeviceType>(value);
    if (order.type == DeviceType::PHONE) {
        if (!inputField("Останні 6 цифр IMEI: ", text)) {
            return false;
        }
        if (!digits(text, 6)) {
            cout << "Помилка: потрібно рівно 6 цифр.\n";
            return false;
        }
        parseInt(text, order.info.imei);
    }
    else if (order.type == DeviceType::LAPTOP) {
        if (!inputField("Серійний номер: ", text)) {
            return false;
        }
        bool valid = strlen(text) >= 1 && strlen(text) <= 11;
        for (int i = 0; text[i]; i++) {
            if (!((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= '0' && text[i] <= '9'))) {
                valid = false;
            }
        }
        if (!valid) {
            cout << "Помилка: серійний номер має містити від 1 до 11 великих латинських літер і цифр.\n";
            return false;
        }
        strcpy(order.info.serial, text);
    }
    else {
        if (!inputField("Діагональ (від 19 до 100 дюймів): ", text)) {
            return false;
        }
        if (!parseInt(text, value) || value < 19 || value > 100) {
            cout << "Помилка: діагональ має бути від 19 до 100 дюймів.\n";
            return false;
        }
        order.info.inches = value;
    }
    if (!inputField("Опис несправності: ", text)) {
        return false;
    }
    if (strlen(text) < 1 || strlen(text) > 80) {
        cout << "Помилка: опис має містити від 1 до 80 байтів.\n";
        return false;
    }
    strcpy(order.problem, text);
    if (!inputField("Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ", text)) {
        return false;
    }
    if (!parseInt(text, value) || value < 1 || value > 3) {
        cout << "Помилка: пріоритет має бути 1, 2 або 3.\n";
        return false;
    }
    order.priority = value;
    if (!inputField("Вартість (обернений польський запис): ", text)) {
        return false;
    }
    return evalRPN(text, order.price);
}

void addOrder(OrderList& list, QNode*& queue, Action*& actions, int& nextId) {
    Order order{};
    if (!readOrder(order)) {
        return;
    }
    order.id = nextId++;
    order.status = Status::WAITING;
    OrderNode* node = appendOrder(list, order);
    enqueue(queue, &node->order);
    pushAction(actions, ActionType::ADD, order);
    cout << "Замовлення №" << order.id << " додано: вартість " << order.price << " грн, у черзі на ремонт: " << queueSize(queue) << ".\n";
}

ostream& operator<<(ostream& os, const Order& order) {
    char details[32], price[32], date[40];
    const char* type;
    if (order.type == DeviceType::PHONE) {
        type = "PHONE";
        sprintf(details, "IMEI %06d", order.info.imei);
    }
    else if (order.type == DeviceType::LAPTOP) {
        type = "LAPTOP";
        sprintf(details, "SN %s", order.info.serial);
    }
    else {
        type = "TV";
        sprintf(details, "%d inch", order.info.inches);
    }

    sprintf(date, "%02d.%02d.%04d", order.date.day, order.date.month, order.date.year);
    sprintf(price, "%d.%02d", order.price.hrn, order.price.kop);

    char row[256];
    sprintf(row, "| %10d | %-15s | %-10s | %-10s | %-6s | %-14s | %2d | %-7s | %9s |\n", order.id, order.client.name, order.client.phone, date, type, details, order.priority, statusName(order.status), price);
    os << row;
    return os;
}

void showJournal(const OrderList& list, const QNode* queue) {
    if (!list.head) {
        cout << "Журнал порожній.\n";
        return;
    }
    const char* border = "+------------+-----------------+------------+------------+--------+----------------+----+---------+-----------+\n";
    cout << border;
    cout << "|          № | Клієнт          | Телефон    | Дата       | Тип    | Деталі         | Пр | Статус  |  Вартість |\n";
    cout << border;
    for (OrderNode* p = list.head; p; p = p->next) {
        cout << p->order;
    }
    cout << border;
    cout << "Усього замовлень: " << list.size << ", у черзі на ремонт: " << queueSize(queue) << '\n';
}

void assignOrder(QNode*& queue, Master*& nextMaster) {
    if (!queue) {
        cout << "Черга на ремонт порожня.\n";
        return;
    }
    QNode* old = queue;
    Order& order = *old->order;
    queue = old->next;
    delete old;
    order.status = Status::REPAIR;
    strcpy(order.master, nextMaster->name);
    cout << "Замовлення №" << order.id << " (пріоритет " << order.priority << ") передано майстру " << nextMaster->name << ".\n";
    cout << "Несправність: " << order.problem << '\n';
    cout << "У черзі залишилось: " << queueSize(queue) << '\n';
    nextMaster = nextMaster->next;
}

OrderNode* requestOrder(const OrderList& list) {
    char text[INPUT_SIZE];
    int id;
    if (!inputField("Номер замовлення: ", text)) {
        return nullptr;
    }
    if (!parseInt(text, id)) {
        cout << "Помилка: номер замовлення має бути цілим числом.\n";
        return nullptr;
    }
    OrderNode* node = findById(list, id);
    if (!node) {
        cout << "Замовлення №" << id << " не знайдено.\n";
    }
    return node;
}

void completeRepair(const OrderList& list, Master* masters) {
    OrderNode* node = requestOrder(list);
    if (!node) {
        return;
    }
    Order& order = node->order;
    if (order.status == Status::WAITING) {
        cout << "Замовлення №" << order.id << " ще не передано майстру.\n";
        return;
    }
    if (order.status == Status::DONE) {
        cout << "Замовлення №" << order.id << " уже завершено.\n";
        return;
    }
    Master* master = masters;
    do {
        if (strcmp(master->name, order.master) == 0) {
            break;
        }
        master = master->next;
    } while (master != masters);
    order.status = Status::DONE;
    master->completed++;
    master->earned = master->earned + order.price;
    cout << "Ремонт замовлення №" << order.id << " завершено. Майстер " << master->name << ": виконано " << master->completed << ", виручка " << master->earned << " грн.\n";
}

void deleteOrder(OrderList& list, QNode*& queue, Action*& actions) {
    OrderNode* node = requestOrder(list);
    if (!node) {
        return;
    }
    if (node->order.status != Status::WAITING) {
        cout << "Видалити можна лише замовлення, яке очікує в черзі.\n";
        return;
    }
    int id = node->order.id;
    pushAction(actions, ActionType::REMOVE, node->order);
    removeFromQueue(queue, id);
    removeOrder(list, node);
    cout << "Замовлення №" << id << " видалено. У журналі: " << list.size << ", у черзі: " << queueSize(queue) << ".\n";
}

void undoAction(OrderList& list, QNode*& queue, Action*& actions) {
    if (!actions) {
        cout << "Немає дій для скасування.\n";
        return;
    }
    Action* old = actions;
    actions = old->next;
    int id = old->order.id;
    if (old->type == ActionType::REMOVE) {
        OrderNode* node = appendOrder(list, old->order);
        enqueue(queue, &node->order);
        cout << "Скасовано видалення замовлення №" << id << ": його повернуто в кінець журналу і в чергу.\n";
    }
    else {
        OrderNode* node = findById(list, id);
        if (node && node->order.status == Status::WAITING) {
            removeFromQueue(queue, id);
            removeOrder(list, node);
            cout << "Скасовано додавання замовлення №" << id << ".\n";
        }
        else {
            cout << "Додавання замовлення №" << id << " скасувати неможливо: його вже передано майстру.\n";
        }
    }
    delete old;
}

Money revenue(const OrderNode* p) {
    if (!p) {
        return {0, 0};
    }
    Money rest = revenue(p->next);
    return p->order.status == Status::DONE ? p->order.price + rest : rest;
}

void sortOrders(Order** orders, int count) {
    for (int i = 1; i < count; i++) {
        Order* value = orders[i];
        int j = i - 1;
        while (j >= 0 && (orders[j]->price < value->price || (kopecks(orders[j]->price) == kopecks(value->price) && orders[j]->id > value->id))) {
            orders[j + 1] = orders[j];
            --j;
        }
        orders[j + 1] = value;
    }
}

void showReport(const OrderList& list, Master* nextMaster) {
    if (!list.head) {
        cout << "Журнал порожній.\n";
    }
    else {
        Order** orders = new Order*[list.size];
        int i = 0;
        for (OrderNode* p = list.head; p; p = p->next) {
            orders[i++] = &p->order;
        }
        sortOrders(orders, list.size);
        cout << "Замовлення за вартістю:\n";
        for (i = 0; i < list.size; i++) {
            cout << "  №" << orders[i]->id << "  " << right << setw(9) << orders[i]->price << " грн  " << statusName(orders[i]->status) << '\n';
        }
        cout << "Різниця між найдорожчим і найдешевшим: " << orders[0]->price - orders[list.size - 1]->price << " грн\n";
        delete[] orders;
    }
    cout << "Виручка за завершеними ремонтами: " << revenue(list.head) << " грн\n";
    cout << "Майстри, починаючи з наступного в черзі:\n";
    Master* master = nextMaster;
    do {
        cout << "  " << left << setw(12) << master->name << " виконано: " << master->completed << ", виручка: " << master->earned << " грн\n";
        master = master->next;
    } while (master != nextMaster);
    cout << right;
}

void reverseJournal(OrderList& list) {
    if (!list.head) {
        cout << "Журнал порожній.\n";
        return;
    }
    OrderNode* p = list.head;
    while (p) {
        OrderNode* next = p->next;
        p->next = p->prev;
        p->prev = next;
        p = next;
    }
    OrderNode* oldHead = list.head;
    list.head = list.tail;
    list.tail = oldHead;
    cout << "Журнал розвернуто: тепер першим іде замовлення №" << list.head->order.id << ", останнім №" << list.tail->order.id << ".\n";
}

void freeMemory(OrderList& list, QNode*& queue, Action*& actions, Master*& masters) {
    while (queue) {
        QNode* old = queue;
        queue = queue->next;
        delete old;
    }
    clearActions(actions);
    while (list.head) {
        removeOrder(list, list.head);
    }
    clearMasters(masters);
}

void showMenu() {
    cout << "\nОберіть пункт:\n";
    cout << "1. Додати замовлення\n";
    cout << "2. Журнал замовлень\n";
    cout << "3. Видати замовлення майстру\n";
    cout << "4. Завершити ремонт\n";
    cout << "5. Видалити замовлення\n";
    cout << "6. Скасувати останню дію\n";
    cout << "7. Звіт\n";
    cout << "8. Розвернути журнал\n";
    cout << "0. Вийти\n";
}

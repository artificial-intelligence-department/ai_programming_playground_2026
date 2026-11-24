/*
 * Практична робота (Epic 6): Сервісний центр - черга ремонтів
 * Ткач Артем Ігорович, ШІ-13
 */

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

const int LINE = 256;
const int MAX_MASTERS = 5;
const int MAX_KOP = 10000000;
const int CHOICE_EOF = -1;
const int CHOICE_BAD = -2;

enum class DeviceType { PHONE = 1, LAPTOP, TV };
enum class Status { WAITING, REPAIR, DONE };
enum class ActionKind { ADDED, REMOVED };

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
    OrderNode *prev;
    OrderNode *next;
};

struct OrderList {
    OrderNode *head;
    OrderNode *tail;
    int size;
};

struct QNode {
    Order *order;
    QNode *next;
};

struct Master {
    char name[24];
    int repairs;
    Money revenue;
    Master *next;
};

struct Action {
    ActionKind kind;
    Order order;
    Action *next;
};

struct NumNode {
    Money value;
    NumNode *next;
};

struct Service {
    OrderList list;
    QNode *queueHead;
    int queueSize;
    Master *firstMaster;
    Master *nextMaster;
    Action *historyTop;
    int nextId;
};

// ---------------------------------------------------------------- Money

Money makeMoney(int kop) {
    Money result;
    result.hrn = kop / 100;
    result.kop = kop % 100;
    return result;
}

int toKop(const Money &money) {
    return money.hrn * 100 + money.kop;
}

Money operator+(const Money &a, const Money &b) {
    int total = toKop(a) + toKop(b);
    Money result = makeMoney(total);
    return result;
}

Money operator-(const Money &a, const Money &b) {
    int total = toKop(a) - toKop(b);
    Money result = makeMoney(total);
    return result;
}

Money operator*(const Money &a, int times) {
    int total = toKop(a) * times;
    Money result = makeMoney(total);
    return result;
}

bool operator<(const Money &a, const Money &b) {
    int first = toKop(a);
    int second = toKop(b);
    return first < second;
}

ostream &operator<<(ostream &os, const Money &money) {
    os << money.hrn << '.' << setfill('0') << setw(2) << money.kop << setfill(' ');
    return os;
}

void formatMoney(const Money &money, char *text) {
    snprintf(text, 16, "%d.%02d", money.hrn, money.kop);
}

// ------------------------------------------------------- Назви та вивід

const char *typeName(DeviceType type) {
    if (type == DeviceType::PHONE) {
        return "PHONE";
    } else if (type == DeviceType::LAPTOP) {
        return "LAPTOP";
    }
    return "TV";
}

const char *statusName(Status status) {
    if (status == Status::WAITING) {
        return "WAITING";
    } else if (status == Status::REPAIR) {
        return "REPAIR";
    }
    return "DONE";
}

void formatDetails(const Order &order, char *text) {
    if (order.type == DeviceType::PHONE) {
        snprintf(text, 24, "IMEI %06d", order.info.imei);
    } else if (order.type == DeviceType::LAPTOP) {
        snprintf(text, 24, "SN %s", order.info.serial);
    } else {
        snprintf(text, 24, "%d inch", order.info.inches);
    }
}

ostream &operator<<(ostream &os, const Order &order) {
    char details[24];
    char price[16];
    char row[200];
    formatDetails(order, details);
    formatMoney(order.price, price);
    snprintf(row, 200, "| %3d | %-15s | %-10s | %02d.%02d.%04d | %-6s | %-14s | %2d | %-7s | %9s |", order.id, order.client.name, order.client.phone, order.date.day, order.date.month, order.date.year, typeName(order.type), details, order.priority, statusName(order.status), price);
    os << row;
    return os;
}

// ------------------------------------------------------------ Введення

int readLine(char *buffer, int size) {
    cin.getline(buffer, size);
    bool ended = cin.eof();
    bool failed = cin.fail();
    if (failed && ended) {
        return 0;
    }
    if (failed) {
        cin.clear();
        cin.ignore(1000000, '\n');
        cout << "Помилка: рядок занадто довгий." << endl;
        return -1;
    }
    int length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\r') {
        buffer[length - 1] = '\0';
    }
    return 1;
}

bool isDigitChar(char c) {
    return c >= '0' && c <= '9';
}

bool isLatinLetter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool isUpperOrDigit(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

bool parseInt(const char *text, int &value) {
    while (*text == ' ') {
        ++text;
    }
    int length = 0;
    int result = 0;
    while (*text >= '0' && *text <= '9') {
        if (length < 9) {
            result = result * 10 + (*text - '0');
        }
        ++length;
        ++text;
    }
    while (*text == ' ') {
        ++text;
    }
    if (length == 0 || length > 9 || *text != '\0') {
        return false;
    }
    value = result;
    return true;
}

int numberAt(const char *text, int start, int count) {
    int value = 0;
    for (int i = 0; i < count; ++i) {
        char c = text[start + i];
        bool digit = isDigitChar(c);
        if (!digit) {
            return -1;
        }
        value = value * 10 + (c - '0');
    }
    return value;
}

bool isValidName(const char *text, int maxLength) {
    int length = strlen(text);
    if (length < 1 || length > maxLength) {
        return false;
    }
    for (int i = 0; i < length; ++i) {
        bool letter = isLatinLetter(text[i]);
        if (!letter) {
            return false;
        }
    }
    return true;
}

bool isValidPhone(const char *text) {
    int length = strlen(text);
    if (length != 10 || text[0] != '0') {
        return false;
    }
    int number = numberAt(text, 1, 9);
    return number >= 0;
}

bool isValidSerial(const char *text) {
    int length = strlen(text);
    if (length < 1 || length > 11) {
        return false;
    }
    for (int i = 0; i < length; ++i) {
        bool good = isUpperOrDigit(text[i]);
        if (!good) {
            return false;
        }
    }
    return true;
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int daysInMonth(int month, int year) {
    const int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool leap = isLeapYear(year);
    if (month == 2 && leap) {
        return 29;
    }
    return days[month];
}

int parseDate(const char *text, Date &date) {
    int length = strlen(text);
    if (length != 10 || text[2] != '.' || text[5] != '.') {
        return 1;
    }
    int day = numberAt(text, 0, 2);
    int month = numberAt(text, 3, 2);
    int year = numberAt(text, 6, 4);
    if (day < 0 || month < 0 || year < 0) {
        return 1;
    }
    if (month < 1 || month > 12 || year < 2000 || year > 2099) {
        return 2;
    }
    int limit = daysInMonth(month, year);
    if (day < 1 || day > limit) {
        return 2;
    }
    date.day = day;
    date.month = month;
    date.year = year;
    return 0;
}

// ----------------------------------------- Вираз вартості (стек чисел)

void pushNum(NumNode *&top, const Money &value) {
    NumNode *node = new NumNode;
    node->value = value;
    node->next = top;
    top = node;
}

void popNum(NumNode *&top, Money &value) {
    NumNode *node = top;
    value = node->value;
    top = node->next;
    delete node;
}

void freeNums(NumNode *&top) {
    while (top != nullptr) {
        NumNode *next = top->next;
        delete top;
        top = next;
    }
}

int parseNumber(const char *token, Money &value) {
    int intDigits = 0;
    int intPart = 0;
    while (*token >= '0' && *token <= '9') {
        if (intDigits < 7) {
            intPart = intPart * 10 + (*token - '0');
        }
        ++intDigits;
        ++token;
    }
    if (intDigits == 0) {
        return 1;
    }
    int fracDigits = 0;
    int fracPart = 0;
    if (*token == '.') {
        ++token;
        while (*token >= '0' && *token <= '9') {
            if (fracDigits < 2) {
                fracPart = fracPart * 10 + (*token - '0');
            }
            ++fracDigits;
            ++token;
        }
        if (fracDigits == 1) {
            fracPart = fracPart * 10;
        }
        if (fracDigits == 0 || fracDigits > 2) {
            return 1;
        }
    }
    if (*token != '\0') {
        return 1;
    }
    if (intDigits > 6) {
        return 2;
    }
    value.hrn = intPart;
    value.kop = fracPart;
    return 0;
}

bool computeOperation(char op, const Money &leftValue, const Money &rightValue, Money &result) {
    if (op == '+') {
        result = leftValue + rightValue;
    } else if (op == '-') {
        bool negative = leftValue < rightValue;
        if (negative) {
            cout << "Помилка у виразі: проміжний результат від'ємний." << endl;
            return false;
        }
        result = leftValue - rightValue;
    } else {
        bool badMultiplier = rightValue.kop != 0 || rightValue.hrn < 1 || rightValue.hrn > 100;
        if (badMultiplier) {
            cout << "Помилка у виразі: множник має бути цілим числом від 1 до 100." << endl;
            return false;
        }
        result = leftValue * rightValue.hrn;
    }
    int total = toKop(result);
    if (total > MAX_KOP) {
        cout << "Помилка у виразі: сума перевищує 100000.00 грн." << endl;
        return false;
    }
    return true;
}

bool applyOperator(char op, NumNode *&top, int &count) {
    if (count < 2) {
        cout << "Помилка у виразі: для операції «" << op << "» бракує чисел." << endl;
        return false;
    }
    Money rightValue;
    Money leftValue;
    Money result;
    popNum(top, rightValue);
    popNum(top, leftValue);
    count = count - 2;
    bool ok = computeOperation(op, leftValue, rightValue, result);
    if (!ok) {
        return false;
    }
    pushNum(top, result);
    ++count;
    return true;
}

bool processToken(const char *token, NumNode *&top, int &count) {
    char first = token[0];
    char second = token[1];
    bool isOperator = (first == '+' || first == '-' || first == '*') && second == '\0';
    if (isOperator) {
        bool ok = applyOperator(first, top, count);
        return ok;
    }
    Money value;
    int status = parseNumber(token, value);
    if (status == 1) {
        cout << "Помилка у виразі: «" << token << "» не є числом або операцією." << endl;
        return false;
    }
    int total = toKop(value);
    if (status == 2 || total > MAX_KOP) {
        cout << "Помилка у виразі: сума перевищує 100000.00 грн." << endl;
        return false;
    }
    pushNum(top, value);
    ++count;
    return true;
}

bool evalRPN(const char *expr, Money &res) {
    char buffer[LINE];
    strcpy(buffer, expr);
    NumNode *top = nullptr;
    int count = 0;
    bool ok = true;
    char *token = strtok(buffer, " \t");
    while (token != nullptr && ok) {
        ok = processToken(token, top, count);
        if (ok) {
            token = strtok(nullptr, " \t");
        }
    }
    if (ok && count == 0) {
        cout << "Помилка у виразі: порожній вираз." << endl;
        ok = false;
    }
    if (ok && count != 1) {
        cout << "Помилка у виразі: у стеку залишилось чисел: " << count << ", а має бути одне." << endl;
        ok = false;
    }
    if (ok) {
        popNum(top, res);
        int total = toKop(res);
        if (total == 0) {
            cout << "Помилка у виразі: вартість має бути більшою за 0.00 грн." << endl;
            ok = false;
        }
    }
    freeNums(top);
    return ok;
}

// ------------------------------------------- Читання полів замовлення

bool readClientName(char *name) {
    char line[LINE];
    cout << "Ім'я клієнта: ";
    int status = readLine(line, LINE);
    if (status != 1) {
        return false;
    }
    bool valid = isValidName(line, 15);
    if (!valid) {
        cout << "Помилка: ім'я має містити від 1 до 15 латинських літер." << endl;
        return false;
    }
    strcpy(name, line);
    return true;
}

bool readPhone(char *phone) {
    char line[LINE];
    cout << "Телефон (10 цифр): ";
    int status = readLine(line, LINE);
    if (status != 1) {
        return false;
    }
    bool valid = isValidPhone(line);
    if (!valid) {
        cout << "Помилка: телефон має складатися з 10 цифр і починатися з 0." << endl;
        return false;
    }
    strcpy(phone, line);
    return true;
}

bool readDate(Date &date) {
    char line[LINE];
    cout << "Дата прийому (ДД.ММ.РРРР): ";
    int status = readLine(line, LINE);
    if (status != 1) {
        return false;
    }
    int code = parseDate(line, date);
    if (code == 1) {
        cout << "Помилка: дата має бути у форматі ДД.ММ.РРРР." << endl;
        return false;
    }
    if (code == 2) {
        cout << "Помилка: некоректна дата." << endl;
        return false;
    }
    return true;
}

bool readDeviceType(DeviceType &type) {
    char line[LINE];
    cout << "Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ";
    int status = readLine(line, LINE);
    if (status != 1) {
        return false;
    }
    int value = 0;
    bool ok = parseInt(line, value);
    if (!ok || value < 1 || value > 3) {
        cout << "Помилка: тип пристрою має бути 1, 2 або 3." << endl;
        return false;
    }
    type = static_cast<DeviceType>(value);
    return true;
}

bool readImei(DeviceInfo &info) {
    char line[LINE];
    cout << "Останні 6 цифр IMEI: ";
    int status = readLine(line, LINE);
    if (status != 1) {
        return false;
    }
    int length = strlen(line);
    int number = numberAt(line, 0, 6);
    if (length != 6 || number < 0) {
        cout << "Помилка: потрібно рівно 6 цифр." << endl;
        return false;
    }
    info.imei = number;
    return true;
}

bool readSerial(DeviceInfo &info) {
    char line[LINE];
    cout << "Серійний номер (1-11 великих латинських літер і цифр): ";
    int status = readLine(line, LINE);
    if (status != 1) {
        return false;
    }
    bool valid = isValidSerial(line);
    if (!valid) {
        cout << "Помилка: серійний номер має складатися з 1-11 великих латинських літер і цифр." << endl;
        return false;
    }
    strcpy(info.serial, line);
    return true;
}

bool readInches(DeviceInfo &info) {
    char line[LINE];
    cout << "Діагональ у дюймах (від 19 до 100): ";
    int status = readLine(line, LINE);
    if (status != 1) {
        return false;
    }
    int value = 0;
    bool ok = parseInt(line, value);
    if (!ok || value < 19 || value > 100) {
        cout << "Помилка: діагональ має бути цілим числом від 19 до 100." << endl;
        return false;
    }
    info.inches = value;
    return true;
}

bool readDeviceInfo(DeviceType type, DeviceInfo &info) {
    bool ok = false;
    if (type == DeviceType::PHONE) {
        ok = readImei(info);
    } else if (type == DeviceType::LAPTOP) {
        ok = readSerial(info);
    } else {
        ok = readInches(info);
    }
    return ok;
}

bool readProblem(char *problem) {
    char line[LINE];
    cout << "Опис несправності: ";
    int status = readLine(line, LINE);
    if (status != 1) {
        return false;
    }
    int length = strlen(line);
    if (length < 1 || length > 80) {
        cout << "Помилка: опис має містити від 1 до 80 байтів." << endl;
        return false;
    }
    strcpy(problem, line);
    return true;
}

bool readPriority(int &priority) {
    char line[LINE];
    cout << "Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ";
    int status = readLine(line, LINE);
    if (status != 1) {
        return false;
    }
    int value = 0;
    bool ok = parseInt(line, value);
    if (!ok || value < 1 || value > 3) {
        cout << "Помилка: пріоритет має бути 1, 2 або 3." << endl;
        return false;
    }
    priority = value;
    return true;
}

bool readPrice(Money &price) {
    char line[LINE];
    cout << "Вартість (обернений польський запис): ";
    int status = readLine(line, LINE);
    if (status != 1) {
        return false;
    }
    bool ok = evalRPN(line, price);
    return ok;
}

bool readOrderId(int &id) {
    char line[LINE];
    cout << "Номер замовлення: ";
    int status = readLine(line, LINE);
    if (status != 1) {
        return false;
    }
    bool ok = parseInt(line, id);
    if (!ok) {
        cout << "Помилка: номер замовлення має бути цілим числом." << endl;
        return false;
    }
    return true;
}

bool readOrder(Order &order) {
    bool ok = readClientName(order.client.name);
    if (!ok) {
        return false;
    }
    ok = readPhone(order.client.phone);
    if (!ok) {
        return false;
    }
    ok = readDate(order.date);
    if (!ok) {
        return false;
    }
    ok = readDeviceType(order.type);
    if (!ok) {
        return false;
    }
    ok = readDeviceInfo(order.type, order.info);
    if (!ok) {
        return false;
    }
    ok = readProblem(order.problem);
    if (!ok) {
        return false;
    }
    ok = readPriority(order.priority);
    if (!ok) {
        return false;
    }
    ok = readPrice(order.price);
    return ok;
}

// ----------------------------------------- Двозв'язний список (журнал)

OrderNode *appendOrder(OrderList &list, const Order &order) {
    OrderNode *node = new OrderNode;
    node->order = order;
    node->prev = list.tail;
    node->next = nullptr;
    if (list.tail != nullptr) {
        list.tail->next = node;
    } else {
        list.head = node;
    }
    list.tail = node;
    ++list.size;
    return node;
}

OrderNode *findById(const OrderList &list, int id) {
    OrderNode *p = list.head;
    while (p != nullptr && p->order.id != id) {
        p = p->next;
    }
    return p;
}

void removeNode(OrderList &list, OrderNode *node) {
    if (node->prev != nullptr) {
        node->prev->next = node->next;
    } else {
        list.head = node->next;
    }
    if (node->next != nullptr) {
        node->next->prev = node->prev;
    } else {
        list.tail = node->prev;
    }
    delete node;
    --list.size;
}

void reverseList(OrderList &list) {
    OrderNode *p = list.head;
    while (p != nullptr) {
        OrderNode *oldNext = p->next;
        p->next = p->prev;
        p->prev = oldNext;
        p = oldNext;
    }
    OrderNode *oldHead = list.head;
    list.head = list.tail;
    list.tail = oldHead;
}

void freeList(OrderList &list) {
    OrderNode *p = list.head;
    while (p != nullptr) {
        OrderNode *next = p->next;
        delete p;
        p = next;
    }
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

Money revenue(const OrderNode *p) {
    if (p == nullptr) {
        Money zero = makeMoney(0);
        return zero;
    }
    Money rest = revenue(p->next);
    if (p->order.status == Status::DONE) {
        Money sum = rest + p->order.price;
        return sum;
    }
    return rest;
}

// ---------------------------------------------------- Пріоритетна черга

void enqueue(Service &s, Order *order) {
    QNode *node = new QNode;
    node->order = order;
    node->next = nullptr;
    if (s.queueHead == nullptr || s.queueHead->order->priority < order->priority) {
        node->next = s.queueHead;
        s.queueHead = node;
    } else {
        QNode *p = s.queueHead;
        while (p->next != nullptr && p->next->order->priority >= order->priority) {
            p = p->next;
        }
        node->next = p->next;
        p->next = node;
    }
    ++s.queueSize;
}

Order *dequeue(Service &s) {
    QNode *node = s.queueHead;
    Order *order = node->order;
    s.queueHead = node->next;
    delete node;
    --s.queueSize;
    return order;
}

void removeFromQueue(Service &s, const Order *order) {
    QNode *prev = nullptr;
    QNode *p = s.queueHead;
    while (p != nullptr && p->order != order) {
        prev = p;
        p = p->next;
    }
    if (p == nullptr) {
        return;
    }
    if (prev == nullptr) {
        s.queueHead = p->next;
    } else {
        prev->next = p->next;
    }
    delete p;
    --s.queueSize;
}

void freeQueue(Service &s) {
    while (s.queueHead != nullptr) {
        QNode *next = s.queueHead->next;
        delete s.queueHead;
        s.queueHead = next;
    }
    s.queueSize = 0;
}

// ------------------------------------------------------ Стек дій

void pushAction(Service &s, ActionKind kind, const Order &order) {
    Action *action = new Action;
    action->kind = kind;
    action->order = order;
    action->next = s.historyTop;
    s.historyTop = action;
}

Action *popAction(Service &s) {
    Action *action = s.historyTop;
    s.historyTop = action->next;
    action->next = nullptr;
    return action;
}

void freeHistory(Service &s) {
    while (s.historyTop != nullptr) {
        Action *next = s.historyTop->next;
        delete s.historyTop;
        s.historyTop = next;
    }
}

// ------------------------------------------------ Кільце майстрів

bool parseMasterNames(const char *line, int expected, char names[][24]) {
    char buffer[LINE];
    strcpy(buffer, line);
    int count = 0;
    bool valid = true;
    char *token = strtok(buffer, " \t");
    while (token != nullptr) {
        bool good = isValidName(token, 23);
        if (!good) {
            valid = false;
        }
        if (good && count < MAX_MASTERS) {
            strcpy(names[count], token);
        }
        ++count;
        token = strtok(nullptr, " \t");
    }
    if (!valid || count != expected) {
        cout << "Помилка: кількість імен має дорівнювати " << expected << ", кожне ім'я з латинських літер, до 23 символів." << endl;
        return false;
    }
    for (int i = 0; i < count; ++i) {
        for (int j = i + 1; j < count; ++j) {
            int same = strcmp(names[i], names[j]);
            if (same == 0) {
                cout << "Помилка: імена майстрів не повинні повторюватися." << endl;
                return false;
            }
        }
    }
    return true;
}

void buildRing(Service &s, int count, char names[][24]) {
    Master *last = nullptr;
    for (int i = 0; i < count; ++i) {
        Master *master = new Master;
        strcpy(master->name, names[i]);
        master->repairs = 0;
        master->revenue = makeMoney(0);
        master->next = nullptr;
        if (last == nullptr) {
            s.firstMaster = master;
        } else {
            last->next = master;
        }
        last = master;
    }
    last->next = s.firstMaster;
    s.nextMaster = s.firstMaster;
}

bool readMasters(Service &s) {
    char line[LINE];
    cout << "Кількість майстрів (від 1 до 5): ";
    int status = readLine(line, LINE);
    if (status != 1) {
        return false;
    }
    int count = 0;
    bool ok = parseInt(line, count);
    if (!ok || count < 1 || count > MAX_MASTERS) {
        cout << "Помилка: кількість майстрів має бути цілим числом від 1 до 5." << endl;
        return false;
    }
    cout << "Імена майстрів через пробіл: ";
    status = readLine(line, LINE);
    if (status != 1) {
        return false;
    }
    char names[MAX_MASTERS][24];
    ok = parseMasterNames(line, count, names);
    if (!ok) {
        return false;
    }
    buildRing(s, count, names);
    return true;
}

Master *findMaster(const Service &s, const char *name) {
    Master *p = s.firstMaster;
    int same = strcmp(p->name, name);
    while (same != 0) {
        p = p->next;
        same = strcmp(p->name, name);
    }
    return p;
}

void freeMasters(Service &s) {
    if (s.firstMaster == nullptr) {
        return;
    }
    Master *p = s.firstMaster->next;
    s.firstMaster->next = nullptr;
    while (p != nullptr) {
        Master *next = p->next;
        delete p;
        p = next;
    }
    s.firstMaster = nullptr;
    s.nextMaster = nullptr;
}

// -------------------------------------------------------- Пункти меню

void addOrder(Service &s) {
    Order order;
    memset(&order, 0, sizeof(order));
    bool ok = readOrder(order);
    if (!ok) {
        return;
    }
    order.id = s.nextId;
    ++s.nextId;
    order.status = Status::WAITING;
    OrderNode *node = appendOrder(s.list, order);
    enqueue(s, &node->order);
    pushAction(s, ActionKind::ADDED, order);
    cout << "Замовлення №" << order.id << " додано: вартість " << order.price << " грн, у черзі на ремонт: " << s.queueSize << "." << endl;
}

void showLog(const Service &s) {
    if (s.list.size == 0) {
        cout << "Журнал порожній." << endl;
        return;
    }
    cout << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+" << endl;
    cout << "|   № | Клієнт          | Телефон    | Дата       | Тип    | Деталі         | Пр | Статус  |  Вартість |" << endl;
    cout << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+" << endl;
    const OrderNode *p = s.list.head;
    while (p != nullptr) {
        cout << p->order << endl;
        p = p->next;
    }
    cout << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+" << endl;
    cout << "Усього замовлень: " << s.list.size << ", у черзі на ремонт: " << s.queueSize << endl;
}

void dispatchOrder(Service &s) {
    if (s.queueHead == nullptr) {
        cout << "Черга на ремонт порожня." << endl;
        return;
    }
    Order *order = dequeue(s);
    Master *master = s.nextMaster;
    order->status = Status::REPAIR;
    strcpy(order->master, master->name);
    s.nextMaster = master->next;
    cout << "Замовлення №" << order->id << " (пріоритет " << order->priority << ") передано майстру " << master->name << "." << endl;
    cout << "Несправність: " << order->problem << endl;
    cout << "У черзі залишилось: " << s.queueSize << endl;
}

void finishRepair(Service &s) {
    int id = 0;
    bool ok = readOrderId(id);
    if (!ok) {
        return;
    }
    OrderNode *node = findById(s.list, id);
    if (node == nullptr) {
        cout << "Замовлення №" << id << " не знайдено." << endl;
        return;
    }
    if (node->order.status == Status::WAITING) {
        cout << "Замовлення №" << id << " ще не передано майстру." << endl;
        return;
    }
    if (node->order.status == Status::DONE) {
        cout << "Замовлення №" << id << " уже завершено." << endl;
        return;
    }
    Master *master = findMaster(s, node->order.master);
    node->order.status = Status::DONE;
    ++master->repairs;
    master->revenue = master->revenue + node->order.price;
    cout << "Ремонт замовлення №" << id << " завершено. Майстер " << master->name << ": виконано " << master->repairs << ", виручка " << master->revenue << " грн." << endl;
}

void deleteOrder(Service &s) {
    int id = 0;
    bool ok = readOrderId(id);
    if (!ok) {
        return;
    }
    OrderNode *node = findById(s.list, id);
    if (node == nullptr) {
        cout << "Замовлення №" << id << " не знайдено." << endl;
        return;
    }
    if (node->order.status != Status::WAITING) {
        cout << "Видалити можна лише замовлення, яке очікує в черзі." << endl;
        return;
    }
    Order copy = node->order;
    removeFromQueue(s, &node->order);
    removeNode(s.list, node);
    pushAction(s, ActionKind::REMOVED, copy);
    cout << "Замовлення №" << id << " видалено. У журналі: " << s.list.size << ", у черзі: " << s.queueSize << "." << endl;
}

void undoAdded(Service &s, const Order &order) {
    OrderNode *node = findById(s.list, order.id);
    if (node == nullptr) {
        cout << "Замовлення №" << order.id << " не знайдено, скасувати додавання неможливо." << endl;
        return;
    }
    if (node->order.status != Status::WAITING) {
        cout << "Додавання замовлення №" << order.id << " скасувати неможливо: його вже передано майстру." << endl;
        return;
    }
    removeFromQueue(s, &node->order);
    removeNode(s.list, node);
    cout << "Додавання замовлення №" << order.id << " скасовано." << endl;
}

void undoRemoved(Service &s, const Order &order) {
    OrderNode *node = appendOrder(s.list, order);
    enqueue(s, &node->order);
    cout << "Скасовано видалення замовлення №" << order.id << ": його повернуто в кінець журналу і в чергу." << endl;
}

void undoLastAction(Service &s) {
    if (s.historyTop == nullptr) {
        cout << "Немає дій для скасування." << endl;
        return;
    }
    Action *action = popAction(s);
    if (action->kind == ActionKind::ADDED) {
        undoAdded(s, action->order);
    } else {
        undoRemoved(s, action->order);
    }
    delete action;
}

bool goesBefore(const Order *a, const Order *b) {
    bool cheaper = b->price < a->price;
    if (cheaper) {
        return true;
    }
    bool dearer = a->price < b->price;
    if (dearer) {
        return false;
    }
    return a->id < b->id;
}

void sortByPrice(Order **orders, int count) {
    for (int i = 0; i < count; ++i) {
        for (int j = i + 1; j < count; ++j) {
            bool swapNeeded = goesBefore(orders[j], orders[i]);
            if (swapNeeded) {
                Order *temporary = orders[i];
                orders[i] = orders[j];
                orders[j] = temporary;
            }
        }
    }
}

void showSortedOrders(Service &s) {
    int count = s.list.size;
    Order **orders = new Order *[count];
    OrderNode *p = s.list.head;
    int index = 0;
    while (p != nullptr) {
        orders[index] = &p->order;
        ++index;
        p = p->next;
    }
    sortByPrice(orders, count);
    cout << "Замовлення за вартістю:" << endl;
    for (int i = 0; i < count; ++i) {
        char price[16];
        formatMoney(orders[i]->price, price);
        cout << "  №" << orders[i]->id << setw(11) << price << " грн  " << statusName(orders[i]->status) << endl;
    }
    Money difference = orders[0]->price - orders[count - 1]->price;
    cout << "Різниця між найдорожчим і найдешевшим: " << difference << " грн" << endl;
    delete[] orders;
}

void showMasters(const Service &s) {
    cout << "Майстри, починаючи з наступного в черзі:" << endl;
    const Master *p = s.nextMaster;
    do {
        cout << "  " << left << setw(12) << p->name << right << " виконано: " << p->repairs << ", виручка: " << p->revenue << " грн" << endl;
        p = p->next;
    } while (p != s.nextMaster);
}

void showReport(Service &s) {
    if (s.list.size == 0) {
        cout << "Журнал порожній." << endl;
    } else {
        showSortedOrders(s);
    }
    Money total = revenue(s.list.head);
    cout << "Виручка за завершеними ремонтами: " << total << " грн" << endl;
    showMasters(s);
}

void reverseLog(Service &s) {
    if (s.list.size == 0) {
        cout << "Журнал порожній." << endl;
        return;
    }
    reverseList(s.list);
    cout << "Журнал розвернуто: тепер першим іде замовлення №" << s.list.head->order.id << ", останнім №" << s.list.tail->order.id << "." << endl;
}

// ------------------------------------------------------ Меню і main

void showMenu() {
    cout << endl;
    cout << "Меню:" << endl;
    cout << "1 - Додати замовлення" << endl;
    cout << "2 - Журнал замовлень" << endl;
    cout << "3 - Видати замовлення майстру" << endl;
    cout << "4 - Завершити ремонт" << endl;
    cout << "5 - Видалити замовлення" << endl;
    cout << "6 - Скасувати останню дію" << endl;
    cout << "7 - Звіт" << endl;
    cout << "8 - Розвернути журнал" << endl;
    cout << "0 - Вийти" << endl;
}

int readChoice() {
    char line[LINE];
    cout << "Ваш вибір: ";
    int status = readLine(line, LINE);
    if (status == 0) {
        return CHOICE_EOF;
    }
    if (status == -1) {
        return CHOICE_BAD;
    }
    int choice = 0;
    bool ok = parseInt(line, choice);
    if (!ok) {
        cout << "Помилка: введіть номер пункту меню." << endl;
        return CHOICE_BAD;
    }
    if (choice > 8) {
        cout << "Помилка: пункту " << choice << " немає в меню." << endl;
        return CHOICE_BAD;
    }
    return choice;
}

void processChoice(Service &s, int choice) {
    if (choice == 1) {
        addOrder(s);
    } else if (choice == 2) {
        showLog(s);
    } else if (choice == 3) {
        dispatchOrder(s);
    } else if (choice == 4) {
        finishRepair(s);
    } else if (choice == 5) {
        deleteOrder(s);
    } else if (choice == 6) {
        undoLastAction(s);
    } else if (choice == 7) {
        showReport(s);
    } else if (choice == 8) {
        reverseLog(s);
    } else if (choice == 0) {
        cout << "Вихід з програми." << endl;
    }
}

void initService(Service &s) {
    s.list.head = nullptr;
    s.list.tail = nullptr;
    s.list.size = 0;
    s.queueHead = nullptr;
    s.queueSize = 0;
    s.firstMaster = nullptr;
    s.nextMaster = nullptr;
    s.historyTop = nullptr;
    s.nextId = 101;
}

void freeService(Service &s) {
    freeList(s.list);
    freeQueue(s);
    freeHistory(s);
    freeMasters(s);
}

int main() {
    Service service;
    initService(service);
    bool ok = readMasters(service);
    if (!ok) {
        freeService(service);
        return 1;
    }
    int choice = 0;
    do {
        showMenu();
        choice = readChoice();
        processChoice(service, choice);
    } while (choice != 0 && choice != CHOICE_EOF);
    freeService(service);
    return 0;
}

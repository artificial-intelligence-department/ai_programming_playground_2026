#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

struct Money {
    int hrn;
    int kop;
};

enum class DeviceType {
    PHONE = 1,
    LAPTOP,
    TV
};

enum class Status {
    WAITING = 1,
    REPAIR,
    DONE
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
    int phone;
    char laptop[12];
    int tv;
};
struct Order {
    int number;
    Client client;
    Date date;
    DeviceType devicetype;
    DeviceInfo deviceinfo;
    char problem[81];
    int priority;
    Money cost;
    Status status;
    char master[24];
};

struct OrderNode {
    Order key;
    OrderNode *prev = nullptr;
    OrderNode *next = nullptr;
};

struct OrderList {
    OrderNode *head = nullptr;   
    OrderNode *tail = nullptr;   
    int size = 0;
};

struct Master {
    char name[24];
    int tasks = 0;
    Money earned{0, 0};
    Master* next = nullptr;
};

struct QNode {
    Order *key;
    QNode *next = nullptr;
};

struct OrderQueue {
    QNode *head = nullptr;
    int size = 0;
};

enum class ActionType {
    ADD,
    REMOVE
};

struct Action {
    ActionType type;
    Order order;          // копія замовлення для можливого відновлення
    Action* next = nullptr;
};

void pushAction(Action*& top, ActionType type, const Order& order) {
    top = new Action{type, order, top};
}

bool popAction(Action*& top, ActionType& type, Order& order) {
    if (top == nullptr) return false;
    Action* old = top;
    type = old->type;
    order = old->order;
    top = old->next;
    delete old;
    return true;
}

void clearActions(Action*& top) {
    while (top != nullptr) {
        Action* old = top;
        top = old->next;
        delete old;
    }
}

OrderNode* appendOrder(OrderList& list, const Order& order) {
    OrderNode *new_node = new OrderNode{order, list.tail, nullptr};
    if (list.tail) {
        list.tail->next = new_node;
    }
    else {
        list.head = new_node;
    }
    list.tail = new_node;
    list.size++;
    return new_node;
}

void removeOrderNode(OrderList& list, OrderNode* node) {
    if (node == nullptr) return;

    if (node->prev != nullptr) node->prev->next = node->next;
    else list.head = node->next;

    if (node->next != nullptr) node->next->prev = node->prev;
    else list.tail = node->prev;

    delete node;
    list.size--;
}

void clearOrders(OrderList& list) {
    OrderNode* p = list.head;
    while (p != nullptr) {
        OrderNode* next = p->next;
        delete p;
        p = next;
    }
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

void enqueue(OrderQueue& queue, Order* order) {
    if (order == nullptr) return;
    QNode *node = new QNode{order, nullptr};

    if (queue.head == nullptr || queue.head->key->priority < order->priority) {
        node->next = queue.head;
        queue.head = node;
    } else {
        QNode *p = queue.head;
        while (p->next != nullptr && p->next->key->priority >= order->priority) {
            p = p->next;
        }
        node->next = p->next;
        p->next = node;
    }
    queue.size++;
}

Order* dequeue(OrderQueue& queue) {
    if (queue.head == nullptr) return nullptr;
    QNode *old = queue.head;
    queue.head = old->next;
    Order *order = old->key;
    delete old;
    queue.size--;
    return order;
}

bool removeFromQueue(OrderQueue& queue, const Order* order) {
    QNode *previous = nullptr;
    QNode *p = queue.head;
    while (p != nullptr && p->key != order) {
        previous = p;
        p = p->next;
    }
    if (p == nullptr) return false;

    if (previous == nullptr) queue.head = p->next;
    else previous->next = p->next;
    delete p;
    queue.size--;
    return true;
}

void clearQueue(OrderQueue& queue) {
    while (queue.head != nullptr) {
        QNode *old = queue.head;
        queue.head = old->next;
        delete old;
    }
    queue.size = 0;
}

ostream& operator<<(ostream& os, const Money& amount) {
    os << amount.hrn << "."
       << setw(2) << setfill('0') << amount.kop
       << setfill(' ');
    return os;
}

ostream& operator<<(ostream& os, const Order& order) {
    char dateText[11];
    snprintf(dateText, sizeof(dateText), "%02d.%02d.%04d",
             order.date.day, order.date.month, order.date.year);

    const char *typeText = "";
    char details[32];
    if (order.devicetype == DeviceType::PHONE) {
        typeText = "PHONE";
        snprintf(details, sizeof(details), "IMEI %06d", order.deviceinfo.phone);
    } else if (order.devicetype == DeviceType::LAPTOP) {
        typeText = "LAPTOP";
        snprintf(details, sizeof(details), "SN %s", order.deviceinfo.laptop);
    } else {
        typeText = "TV";
        snprintf(details, sizeof(details), "%d inch", order.deviceinfo.tv);
    }

    const char *statusText = "";
    if (order.status == Status::WAITING) statusText = "WAITING";
    else if (order.status == Status::REPAIR) statusText = "REPAIR";
    else if (order.status == Status::DONE) statusText = "DONE";

    char priceText[16];
    snprintf(priceText, sizeof(priceText), "%d.%02d", order.cost.hrn, order.cost.kop);

    ios_base::fmtflags oldFlags = os.flags();
    char oldFill = os.fill();
    os << setfill(' ')
       << "| " << right << setw(3) << order.number
       << " | " << left << setw(15) << order.client.name
       << " | " << setw(10) << order.client.phone
       << " | " << setw(10) << dateText
       << " | " << setw(6) << typeText
       << " | " << setw(14) << details
       << " | " << right << setw(2) << order.priority
       << " | " << left << setw(7) << statusText
       << " | " << right << setw(9) << priceText << " |";
    os.flags(oldFlags);
    os.fill(oldFill);
    return os;
}

bool operator<(const Money& a, const Money& b) {
    if (a.hrn != b.hrn) return a.hrn < b.hrn;
    return a.kop < b.kop;
}

Money operator+(const Money& a, const Money& b) {
    Money result;
    result.hrn = a.hrn + b.hrn;
    result.kop = a.kop + b.kop;
    if (result.kop >= 100) {
        result.kop -= 100;
        result.hrn++;
    }
    return result;
}

// Викликати лише коли a не менше за b.
Money operator-(const Money& a, const Money& b) {
    Money result;
    result.hrn = a.hrn - b.hrn;
    result.kop = a.kop - b.kop;
    if (result.kop < 0) {
        result.kop += 100;
        result.hrn--;
    }
    return result;
}

Money operator*(const Money& amount, int count) {
    long long totalKop = (static_cast<long long>(amount.hrn) * 100 + amount.kop) * count;
    Money result;
    result.hrn = static_cast<int>(totalKop / 100);
    result.kop = static_cast<int>(totalKop % 100);
    return result;
}

struct PriceNode {
    Money value;
    PriceNode *next = nullptr;
};

void pushPrice(PriceNode*& top, const Money& value) {
    top = new PriceNode{value, top};
}

bool popPrice(PriceNode*& top, Money& value) {
    if (top == nullptr) return false;
    PriceNode *old = top;
    value = old->value;
    top = old->next;
    delete old;
    return true;
}

void clearPrice(PriceNode*& top) {
    while (top != nullptr) {
        PriceNode *old = top;
        top = top->next;
        delete old;
    }
}

bool parseMoneyToken(const char* begin, const char* end, Money& value) {
    const char *p = begin;
    int hrn = 0;
    int integerDigits = 0;
    while (p < end && isdigit(static_cast<unsigned char>(*p))) {
        if (++integerDigits > 6) return false;
        hrn = hrn * 10 + (*p - '0');
        p++;
    }
    if (integerDigits == 0) return false;

    int kop = 0;
    if (p < end && *p == '.') {
        p++;
        int fractionalDigits = 0;
        while (p < end && isdigit(static_cast<unsigned char>(*p))) {
            if (++fractionalDigits > 2) return false;
            kop = kop * 10 + (*p - '0');
            p++;
        }
        if (fractionalDigits == 0) return false;
        if (fractionalDigits == 1) kop *= 10;
    }

    if (p != end || hrn > 100000 || (hrn == 100000 && kop > 0)) return false;
    value = Money{hrn, kop};
    return true;
}

bool evalRPN(const char* expr, Money& res) {
    if (expr == nullptr) return false;
    const long long maxKop = 10000000;
    PriceNode *top = nullptr;
    const char *p = expr;

    while (*p != '\0') {
        while (isspace(static_cast<unsigned char>(*p))) p++;
        if (*p == '\0') break;

        const char *begin = p;
        while (*p != '\0' && !isspace(static_cast<unsigned char>(*p))) p++;
        const char *end = p;

        if (end - begin == 1 && (*begin == '+' || *begin == '-' || *begin == '*')) {
            Money right, left;
            if (!popPrice(top, right) || !popPrice(top, left)) {
                clearPrice(top);
                return false;
            }

            long long leftKop = static_cast<long long>(left.hrn) * 100 + left.kop;
            long long rightKop = static_cast<long long>(right.hrn) * 100 + right.kop;
            Money answer;
            if (*begin == '+') {
                if (leftKop + rightKop > maxKop) {
                    clearPrice(top);
                    return false;
                }
                answer = left + right;
            } else if (*begin == '-') {
                if (left < right) {
                    clearPrice(top);
                    return false;
                }
                answer = left - right;
            } else {
                if (right.kop != 0 || right.hrn < 1 || right.hrn > 100 ||
                    leftKop * right.hrn > maxKop) {
                    clearPrice(top);
                    return false;
                }
                answer = left * right.hrn;
            }
            pushPrice(top, answer);
        } else {
            Money number;
            if (!parseMoneyToken(begin, end, number)) {
                clearPrice(top);
                return false;
            }
            pushPrice(top, number);
        }
    }

    if (top == nullptr || top->next != nullptr ||
        (top->value.hrn == 0 && top->value.kop == 0)) {
        clearPrice(top);
        return false;
    }
    res = top->value;
    clearPrice(top);
    return true;
}


OrderNode* findById(const OrderList& list, int id) {
    OrderNode *p = list.head;
    while (p && p->key.number != id) {
        p = p->next;
    }
    if (p != nullptr) return p;
    return nullptr;
}
struct MasterRing {
    Master* head = nullptr;
    Master* nextToAssign = nullptr;
    int size = 0;
};

bool addMaster(MasterRing& ring, const char* name) {
    if (name == nullptr || strlen(name) == 0 || strlen(name) > 23 || ring.size >= 5) {
        return false;
    }
    for (const char* c = name; *c != '\0'; c++) {
        if (!((*c >= 'A' && *c <= 'Z') || (*c >= 'a' && *c <= 'z'))) return false;
    }

    Master* p = ring.head;
    for (int i = 0; i < ring.size; i++) {
        if (strcmp(p->name, name) == 0) return false;
        p = p->next;
    }

    Master* newMaster = new Master{};
    strcpy(newMaster->name, name);
    if (ring.head == nullptr) {
        ring.head = newMaster;
        newMaster->next = newMaster;
        ring.nextToAssign = newMaster;
    } else {
        Master* last = ring.head;
        while (last->next != ring.head) last = last->next;
        last->next = newMaster;
        newMaster->next = ring.head;
    }
    ring.size++;
    return true;
}

Master* takeNextMaster(MasterRing& ring) {
    if (ring.nextToAssign == nullptr) return nullptr;
    Master *result = ring.nextToAssign;
    ring.nextToAssign = result->next;
    return result;
}

Master* findMasterByName(const MasterRing& ring, const char* name) {
    if (ring.head == nullptr) return nullptr;
    Master* p = ring.head;
    do {
        if (strcmp(p->name, name) == 0) return p;
        p = p->next;
    } while (p != ring.head);
    return nullptr;
}

void printMasterReport(const MasterRing& ring) {
    if (ring.nextToAssign == nullptr) return;
    Master* p = ring.nextToAssign;
    do {
        cout << p->name << " (" << p->tasks << ", " << p->earned << " грн)\n";
        p = p->next;
    } while (p != ring.nextToAssign);
}

void clearMasters(MasterRing& ring) {
    if (ring.head == nullptr) return;

    Master* last = ring.head;
    while (last->next != ring.head) last = last->next;
    last->next = nullptr;

    Master* p = ring.head;
    while (p != nullptr) {
        Master* next = p->next;
        delete p;
        p = next;
    }
    ring.head = nullptr;
    ring.nextToAssign = nullptr;
    ring.size = 0;
}

bool readMasters(MasterRing& ring) {
    char countLine[64];
    cout << "Введіть кількість майстрів (від 1 до 5):\n";
    if (!cin.getline(countLine, sizeof(countLine))) {
        cout << "Некоректна кількість майстрів.\n";
        clearMasters(ring);
        return false;
    }

    const char* p = countLine;
    while (*p == ' ' || *p == '\t') p++;
    if (*p < '1' || *p > '5') {
        cout << "Кількість майстрів має бути цілим числом від 1 до 5.\n";
        clearMasters(ring);
        return false;
    }
    int count = *p - '0';
    p++;
    while (*p == ' ' || *p == '\t') p++;
    if (*p != '\0') {
        cout << "Некоректна кількість майстрів.\n";
        clearMasters(ring);
        return false;
    }

    char namesLine[256];
    cout << "Введіть " << count << " різних імен майстрів латиницею через пробіл:\n";
    if (!cin.getline(namesLine, sizeof(namesLine))) {
        cout << "Некоректний рядок з іменами майстрів.\n";
        clearMasters(ring);
        return false;
    }

    char* name = strtok(namesLine, " \t");
    for (int i = 0; i < count; i++) {
        if (name == nullptr || !addMaster(ring, name)) {
            cout << "Некоректне або повторене ім'я майстра.\n";
            clearMasters(ring);
            return false;
        }
        name = strtok(nullptr, " \t");
    }
    if (name != nullptr) {
        cout << "Введено забагато імен майстрів.\n";
        clearMasters(ring);
        return false;
    }
    return true;
}

bool readInputLine(char* buffer, int capacity) {
    if (cin.getline(buffer, capacity)) return true;
    if (cin.eof()) return false;
    cin.clear();
    char ch;
    while (cin.get(ch) && ch != '\n') {}
    return false;
}

bool parseNumber(const char* text, int minimum, int maximum, int& result) {
    if (*text == '\0') return false;
    int value = 0;
    for (const char* p = text; *p != '\0'; p++) {
        if (*p < '0' || *p > '9') return false;
        int digit = *p - '0';
        if (digit > maximum || value > (maximum - digit) / 10) return false;
        value = value * 10 + digit;
    }
    if (value < minimum) return false;
    result = value;
    return true;
}

bool parseInteger(const char* text, int& result) {
    const char* p = text;
    bool negative = false;
    if (*p == '-' || *p == '+') {
        negative = *p == '-';
        p++;
    }
    if (*p == '\0') return false;

    long long value = 0;
    const long long limit = negative ? 2147483648LL : 2147483647LL;
    for (; *p != '\0'; p++) {
        if (*p < '0' || *p > '9') return false;
        int digit = *p - '0';
        if (value > (limit - digit) / 10) return false;
        value = value * 10 + digit;
    }
    if (negative && value == 2147483648LL) result = -2147483647 - 1;
    else result = negative ? -static_cast<int>(value) : static_cast<int>(value);
    return true;
}

bool validClientName(const char* name) {
    int length = static_cast<int>(strlen(name));
    if (length < 1 || length > 15) return false;
    for (int i = 0; i < length; i++) {
        if (!((name[i] >= 'A' && name[i] <= 'Z') ||
              (name[i] >= 'a' && name[i] <= 'z'))) return false;
    }
    return true;
}

bool validPhone(const char* phone) {
    if (strlen(phone) != 10 || phone[0] != '0') return false;
    for (int i = 0; i < 10; i++) {
        if (phone[i] < '0' || phone[i] > '9') return false;
    }
    return true;
}

bool parseDate(const char* text, Date& date) {
    if (strlen(text) != 10 || text[2] != '.' || text[5] != '.') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (text[i] < '0' || text[i] > '9') return false;
    }
    int day = (text[0] - '0') * 10 + (text[1] - '0');
    int month = (text[3] - '0') * 10 + (text[4] - '0');
    int year = (text[6] - '0') * 1000 + (text[7] - '0') * 100 +
               (text[8] - '0') * 10 + (text[9] - '0');
    if (year < 2000 || year > 2099 || month < 1 || month > 12) return false;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool leap = year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
    if (leap) daysInMonth[1] = 29;
    if (day < 1 || day > daysInMonth[month - 1]) return false;
    date = Date{day, month, year};
    return true;
}

bool validSerial(const char* serial) {
    int length = static_cast<int>(strlen(serial));
    if (length < 1 || length > 11) return false;
    for (int i = 0; i < length; i++) {
        if (!((serial[i] >= 'A' && serial[i] <= 'Z') ||
              (serial[i] >= '0' && serial[i] <= '9'))) return false;
    }
    return true;
}

// Для виразу вартості умова не задає максимальної довжини рядка.
bool readPriceLine(char*& expression) {
    int capacity = 256;
    int length = 0;
    expression = new char[capacity];
    expression[0] = '\0';
    char chunk[256];
    while (true) {
        cin.getline(chunk, sizeof(chunk));
        if (cin.bad()) {
            delete[] expression;
            expression = nullptr;
            return false;
        }
        if (cin.fail() && cin.eof()) {
            if (length > 0) return true;
            delete[] expression;
            expression = nullptr;
            return false;
        }
        int partLength = static_cast<int>(strlen(chunk));
        while (length + partLength + 1 > capacity) {
            int newCapacity = capacity * 2;
            char* bigger = new char[newCapacity];
            memcpy(bigger, expression, length + 1);
            delete[] expression;
            expression = bigger;
            capacity = newCapacity;
        }
        memcpy(expression + length, chunk, partLength + 1);
        length += partLength;
        if (!cin.fail()) return true;
        cin.clear();
    }
}

bool readOrder(Order& order) {
    Order draft{};
    char line[256];

    cout << "Введіть ім'я клієнта (1–15 латинських літер):\n";
    if (!readInputLine(line, sizeof(line)) || !validClientName(line)) {
        cout << "Некоректне ім'я клієнта.\n";
        return false;
    }
    strcpy(draft.client.name, line);

    cout << "Введіть телефон (10 цифр, перша 0):\n";
    if (!readInputLine(line, sizeof(line)) || !validPhone(line)) {
        cout << "Некоректний телефон.\n";
        return false;
    }
    strcpy(draft.client.phone, line);

    cout << "Введіть дату прийому (ДД.ММ.РРРР):\n";
    if (!readInputLine(line, sizeof(line)) || !parseDate(line, draft.date)) {
        cout << "Некоректна дата.\n";
        return false;
    }

    int number;
    cout << "Введіть тип пристрою (1 телефон, 2 ноутбук, 3 телевізор):\n";
    if (!readInputLine(line, sizeof(line)) || !parseNumber(line, 1, 3, number)) {
        cout << "Некоректний тип пристрою.\n";
        return false;
    }
    draft.devicetype = static_cast<DeviceType>(number);

    if (draft.devicetype == DeviceType::PHONE) {
        cout << "Введіть останні 6 цифр IMEI:\n";
        if (!readInputLine(line, sizeof(line)) || strlen(line) != 6) {
            cout << "IMEI має містити рівно 6 цифр.\n";
            return false;
        }
        for (int i = 0; i < 6; i++) {
            if (line[i] < '0' || line[i] > '9') {
                cout << "IMEI має містити лише цифри.\n";
                return false;
            }
        }
        parseNumber(line, 0, 999999, draft.deviceinfo.phone);
    } else if (draft.devicetype == DeviceType::LAPTOP) {
        cout << "Введіть серійний номер (1–11 великих латинських літер або цифр):\n";
        if (!readInputLine(line, sizeof(line)) || !validSerial(line)) {
            cout << "Некоректний серійний номер.\n";
            return false;
        }
        strcpy(draft.deviceinfo.laptop, line);
    } else {
        cout << "Введіть діагональ телевізора (19–100 дюймів):\n";
        if (!readInputLine(line, sizeof(line)) ||
            !parseNumber(line, 19, 100, draft.deviceinfo.tv)) {
            cout << "Некоректна діагональ.\n";
            return false;
        }
    }

    cout << "Введіть опис несправності (1–80 байтів):\n";
    if (!readInputLine(line, sizeof(line)) || strlen(line) < 1 || strlen(line) > 80) {
        cout << "Опис несправності має містити від 1 до 80 байтів.\n";
        return false;
    }
    strcpy(draft.problem, line);

    cout << "Введіть пріоритет (1 звичайний, 2 підвищений, 3 терміновий):\n";
    if (!readInputLine(line, sizeof(line)) || !parseNumber(line, 1, 3, draft.priority)) {
        cout << "Некоректний пріоритет.\n";
        return false;
    }

    cout << "Введіть вартість у зворотному польському записі:\n";
    char* expression = nullptr;
    if (!readPriceLine(expression)) {
        cout << "Не вдалося прочитати вираз вартості.\n";
        return false;
    }
    bool correctPrice = evalRPN(expression, draft.cost);
    delete[] expression;
    if (!correctPrice) {
        cout << "Некоректний вираз вартості.\n";
        return false;
    }

    draft.status = Status::WAITING;
    draft.master[0] = '\0';
    order = draft;
    return true;
}

void addOrderFromInput(OrderList& journal, OrderQueue& queue,
                       Action*& history, int& nextId) {
    Order order{};
    if (!readOrder(order)) return;

    order.number = nextId;
    OrderNode* node = appendOrder(journal, order);
    enqueue(queue, &node->key);
    pushAction(history, ActionType::ADD, node->key);
    nextId++;

    cout << "Замовлення №" << node->key.number << " додано: вартість "
         << node->key.cost << " грн, у черзі на ремонт: " << queue.size << ".\n";
}

void printMenu() {
    cout << "\nМеню сервісного центру:\n"
         << "1. Додати замовлення\n"
         << "2. Журнал замовлень\n"
         << "3. Видати замовлення майстру\n"
         << "4. Завершити ремонт\n"
         << "5. Видалити замовлення\n"
         << "6. Скасувати останню дію\n"
         << "7. Звіт\n"
         << "8. Розвернути журнал\n"
         << "0. Вийти\n"
         << "Введіть номер пункту меню:\n";
}

void showJournal(const OrderList& journal, const OrderQueue& queue) {
    if (journal.head == nullptr) {
        cout << "Журнал замовлень порожній.\n";
    } else {
        const char* border =
            "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+";
        cout << border << '\n'
             << "|   № | Клієнт          | Телефон    | Дата       | Тип    | Деталі         | Пр | Статус  |  Вартість |\n"
             << border << '\n';

        for (OrderNode* p = journal.head; p != nullptr; p = p->next) {
            cout << p->key << '\n';
        }
        cout << border << '\n';
    }
    cout << "Усього замовлень: " << journal.size
         << ", у черзі на ремонт: " << queue.size << '\n';
}

void assignOrderToMaster(OrderQueue& queue, MasterRing& masters) {
    if (queue.head == nullptr) {
        cout << "Черга на ремонт порожня.\n";
        return;
    }
    if (masters.nextToAssign == nullptr) {
        cout << "Немає майстра для виконання замовлення.\n";
        return;
    }

    Order* order = dequeue(queue);
    Master* master = takeNextMaster(masters);
    order->status = Status::REPAIR;
    strcpy(order->master, master->name);

    cout << "Замовлення №" << order->number << " (пріоритет " << order->priority
         << ") передано майстру " << master->name << ".\n"
         << "Несправність: " << order->problem << '\n'
         << "У черзі залишилось: " << queue.size << '\n';
}

void completeRepair(OrderList& journal, MasterRing& masters) {
    cout << "Введіть номер замовлення для завершення ремонту:\n";
    char line[64];
    int id;
    if (!readInputLine(line, sizeof(line))) {
        if (!cin.eof()) cout << "Номер замовлення має бути цілим числом.\n";
        return;
    }
    if (!parseInteger(line, id)) {
        cout << "Номер замовлення має бути цілим числом.\n";
        return;
    }

    OrderNode* node = findById(journal, id);
    if (node == nullptr) {
        cout << "Замовлення №" << id << " не знайдено.\n";
        return;
    }
    if (node->key.status == Status::WAITING) {
        cout << "Замовлення №" << id << " ще не передано майстру.\n";
        return;
    }
    if (node->key.status == Status::DONE) {
        cout << "Замовлення №" << id << " уже завершено.\n";
        return;
    }

    Master* master = findMasterByName(masters, node->key.master);
    if (master == nullptr) {
        cout << "Призначеного майстра не знайдено.\n";
        return;
    }
    node->key.status = Status::DONE;
    master->tasks++;
    master->earned = master->earned + node->key.cost;
    cout << "Ремонт замовлення №" << id << " завершено. Майстер " << master->name
         << ": виконано " << master->tasks << ", виручка " << master->earned << " грн.\n";
}

void deleteWaitingOrder(OrderList& journal, OrderQueue& queue, Action*& history) {
    cout << "Введіть номер замовлення для видалення:\n";
    char line[64];
    int id;
    if (!readInputLine(line, sizeof(line))) {
        if (!cin.eof()) cout << "Номер замовлення має бути цілим числом.\n";
        return;
    }
    if (!parseInteger(line, id)) {
        cout << "Номер замовлення має бути цілим числом.\n";
        return;
    }

    OrderNode* node = findById(journal, id);
    if (node == nullptr) {
        cout << "Замовлення №" << id << " не знайдено.\n";
        return;
    }
    if (node->key.status == Status::REPAIR) {
        cout << "Замовлення №" << id << " уже передано майстру, видалити його не можна.\n";
        return;
    }
    if (node->key.status == Status::DONE) {
        cout << "Замовлення №" << id << " уже завершено, видалити його не можна.\n";
        return;
    }

    Order saved = node->key;
    if (!removeFromQueue(queue, &node->key)) {
        cout << "Замовлення не знайдено в черзі; журнал не змінено.\n";
        return;
    }
    removeOrderNode(journal, node);
    pushAction(history, ActionType::REMOVE, saved);
    cout << "Замовлення №" << id << " видалено. У журналі: " << journal.size
         << ", у черзі: " << queue.size << ".\n";
}

void undoLastAction(OrderList& journal, OrderQueue& queue, Action*& history) {
    ActionType type;
    Order saved{};
    if (!popAction(history, type, saved)) {
        cout << "Немає дії для скасування.\n";
        return;
    }

    if (type == ActionType::ADD) {
        OrderNode* node = findById(journal, saved.number);
        if (node == nullptr) {
            cout << "Додане замовлення №" << saved.number << " не знайдено.\n";
            return;
        }
        if (node->key.status != Status::WAITING) {
            cout << "Додавання замовлення №" << saved.number
                 << " не можна скасувати: його вже передано майстру.\n";
            return;
        }
        if (!removeFromQueue(queue, &node->key)) {
            cout << "Замовлення не знайдено в черзі; журнал не змінено.\n";
            return;
        }
        removeOrderNode(journal, node);
        cout << "Скасовано додавання замовлення №" << saved.number << ".\n";
    } else {
        OrderNode* node = appendOrder(journal, saved);
        enqueue(queue, &node->key);
        cout << "Скасовано видалення замовлення №" << saved.number
             << ": його повернуто в кінець журналу і в чергу.\n";
    }
}

Money revenue(const OrderNode* p) {
    if (p == nullptr) return Money{0, 0};
    Money rest = revenue(p->next);
    if (p->key.status == Status::DONE) return p->key.cost + rest;
    return rest;
}

bool comesBeforeInReport(const Order* a, const Order* b) {
    if (b->cost < a->cost) return true;
    if (a->cost < b->cost) return false;
    return a->number < b->number;
}

const char* statusName(Status status) {
    if (status == Status::WAITING) return "WAITING";
    if (status == Status::REPAIR) return "REPAIR";
    return "DONE";
}

void showReport(const OrderList& journal, const MasterRing& masters) {
    cout << "Замовлення за вартістю:\n";
    if (journal.size == 0) {
        cout << "Журнал порожній.\n";
    } else {
        Order** sorted = new Order*[journal.size];
        int count = 0;
        for (OrderNode* p = journal.head; p != nullptr; p = p->next) {
            sorted[count++] = &p->key;
        }

        // Сортування вставками: спадання ціни, за рівної ціни — зростання номера.
        for (int i = 1; i < count; i++) {
            Order* current = sorted[i];
            int j = i - 1;
            while (j >= 0 && comesBeforeInReport(current, sorted[j])) {
                sorted[j + 1] = sorted[j];
                j--;
            }
            sorted[j + 1] = current;
        }

        for (int i = 0; i < count; i++) {
            cout << "  №" << sorted[i]->number << " " << sorted[i]->cost
                 << " грн  " << statusName(sorted[i]->status) << '\n';
        }
        Money difference = sorted[0]->cost - sorted[count - 1]->cost;
        cout << "Різниця між найдорожчим і найдешевшим: " << difference << " грн.\n";
        delete[] sorted;
    }

    cout << "Виручка за завершеними ремонтами: " << revenue(journal.head) << " грн.\n";
    cout << "Майстри, починаючи з наступного для видачі замовлення:\n";
    printMasterReport(masters);
}

void reverseJournal(OrderList& journal) {
    if (journal.head == nullptr) {
        cout << "Журнал порожній, розвертати нічого.\n";
        return;
    }

    OrderNode* p = journal.head;
    while (p != nullptr) {
        OrderNode* next = p->next;
        p->next = p->prev;
        p->prev = next;
        p = next;
    }

    OrderNode* oldHead = journal.head;
    journal.head = journal.tail;
    journal.tail = oldHead;
    cout << "Журнал розвернуто. Перше замовлення: №" << journal.head->key.number
         << ", останнє: №" << journal.tail->key.number << ".\n";
}

int main() {
    MasterRing masters;
    if (!readMasters(masters)) return 0;

    OrderList journal;
    OrderQueue queue;
    Action* history = nullptr;
    int nextId = 101;

    while (true) {
        printMenu();
        char line[64];
        if (!readInputLine(line, sizeof(line))) {
            if (cin.eof()) break;
            cout << "Некоректний пункт меню.\n";
            continue;
        }
        int choice;
        if (!parseNumber(line, 0, 8, choice)) {
            cout << "Некоректний пункт меню.\n";
            continue;
        }
        if (choice == 0) break;
        if (choice == 1) addOrderFromInput(journal, queue, history, nextId);
        else if (choice == 2) showJournal(journal, queue);
        else if (choice == 3) assignOrderToMaster(queue, masters);
        else if (choice == 4) completeRepair(journal, masters);
        else if (choice == 5) deleteWaitingOrder(journal, queue, history);
        else if (choice == 6) undoLastAction(journal, queue, history);
        else if (choice == 7) showReport(journal, masters);
        else if (choice == 8) reverseJournal(journal);
        if (cin.eof()) break;
    }

    clearActions(history);
    clearQueue(queue);
    clearOrders(journal);
    clearMasters(masters);
    return 0;
}

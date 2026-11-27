/*
Назва задачі: Сервісний центр: черга ремонтів
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>

using namespace std;

enum class DeviceType { PHONE = 1, LAPTOP, TV };
enum class Status { WAITING, REPAIR, DONE };
enum class ActionType { ADD, REMOVE };

struct Money {
    int hrn;
    int kop;
};

long long kopecks(const Money &money) {
    return 100LL * money.hrn + money.kop;
}

Money fromKopecks(long long value) {
    return Money{static_cast<int>(value / 100), static_cast<int>(value % 100)};
}

Money operator+(const Money &a, const Money &b) {
    return fromKopecks(kopecks(a) + kopecks(b));
}

Money operator-(const Money &a, const Money &b) {
    return fromKopecks(kopecks(a) - kopecks(b));
}

Money operator*(const Money &money, int count) {
    return fromKopecks(kopecks(money) * count);
}

bool operator<(const Money &a, const Money &b) {
    return kopecks(a) < kopecks(b);
}

ostream &operator<<(ostream &os, const Money &money) {
    char text[40];
    long long value = kopecks(money);

    sprintf(text, "%lld.%02lld", value / 100, value % 100);
    return os << text;
}

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
    OrderNode* head = nullptr;
    OrderNode* tail = nullptr;
    int size = 0;
};

struct QNode {
    Order* order;
    QNode* next;
};

struct Master {
    char name[24];
    int count;
    Money revenue;
    Master* next;
};

struct Action {
    ActionType type;
    Order order;
    Action* next;
};

struct MoneyNode {
    Money value;
    MoneyNode* next;
};

bool readLine(char* text, int capacity) {
    cin.getline(text, capacity);

    if (!cin.fail()) {
        return true;
    }

    cin.clear();

    char ch;
    while (cin.get(ch)) {
        if (ch == '\n') {
            break;
        }
    }

    return false;
}

bool readInt(int& value) {
    char text[128];
    long long number;
    char extra;

    if (!readLine(text, sizeof text)) {
        return false;
    }

    if (sscanf(text, "%11lld %c", &number, &extra) != 1 || number < -2147483648 || number > 2147483647) {
        return false;
    }

    value = number;
    return true;
}

bool validName(char* name, int maxLength) {
    int length = strlen(name);

    if (length < 1 || length > maxLength) {
        return false;
    }

    for (int i = 0; i < length; i++) {
        char ch = name[i];

        if (!(ch >= 'A' && ch <= 'Z') && !(ch >= 'a' && ch <= 'z')) {
            return false;
        }
    }

    return true;
}

bool digitsOnly(char* text) {
    if (*text == '\0') {
        return false;
    }

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] < '0' || text[i] > '9') {
            return false;
        }
    }

    return true;
}

bool parseDate(char* text, Date &date) {
    if (strlen(text) != 10 || text[2] != '.' || text[5] != '.') {
        return false;
    }

    for (int i = 0; i < 10; i++) {
        if (i != 2 && i != 5 && (text[i] < '0' || text[i] > '9')) {
            return false;
        }
    }

    date.day = (text[0] - '0') * 10 + text[1] - '0';
    date.month = (text[3] - '0') * 10 + text[4] - '0';
    date.year = (text[6] - '0') * 1000 + (text[7] - '0') * 100 + (text[8] - '0') * 10 + text[9] - '0';

    if (date.year < 2000 || date.year > 2099 || date.month < 1 || date.month > 12) {
        return false;
    }

    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (date.year % 400 == 0 || (date.year % 4 == 0 && date.year % 100 != 0)) {
        days[1] = 29;
    }

    return date.day >= 1 && date.day <= days[date.month - 1];
}

void pushMoney(MoneyNode*& top, const Money &value) {
    top = new MoneyNode{value, top};
}

Money popMoney(MoneyNode*& top) {
    MoneyNode* node = top;
    Money value = node->value;

    top = node->next;
    delete node;

    return value;
}

void clearMoney(MoneyNode*& top) {
    while (top != nullptr) {
        popMoney(top);
    }
}

bool rpnError(MoneyNode*& top, const char* message) {
    cout << "Помилка у виразі: " << message << '\n';
    clearMoney(top);
    return false;
}

bool parseMoney(char* token, Money &money) {
    int i = 0;
    int hrn = 0;

    while (token[i] >= '0' && token[i] <= '9') {
        if (i == 6) {
            return false;
        }

        hrn = hrn * 10 + token[i] - '0';
        i++;
    }

    if (i == 0) {
        return false;
    }

    int kop = 0;

    if (token[i] == '.') {
        i++;
        int count = 0;

        while (token[i] >= '0' && token[i] <= '9') {
            if (count == 2) {
                return false;
            }

            kop = kop * 10 + token[i] - '0';
            count++;
            i++;
        }

        if (count == 0) {
            return false;
        }

        if (count == 1) {
            kop *= 10;
        }
    }

    money = Money{hrn, kop};
    return token[i] == '\0';
}

bool evalRPN(const char* expr, Money &res) {
    MoneyNode* top = nullptr;
    const char* p = expr;

    while (*p != '\0') {
        while (*p == ' ') {
            p++;
        }

        if (*p == '\0') {
            break;
        }

        const char* start = p;

        while (*p != '\0' && *p != ' ') {
            p++;
        }

        int length = p - start;
        char* token = new char[length + 1];

        memcpy(token, start, length);
        token[length] = '\0';

        bool operation = length == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*');

        if (operation) {
            char op = token[0];
            delete[] token;

            if (top == nullptr || top->next == nullptr) {
                cout << "Помилка у виразі: для операції «" << op << "» бракує чисел.\n";

                clearMoney(top);
                return false;
            }

            Money right = popMoney(top);
            Money left = popMoney(top);
            Money result{};

            if (op == '+') {
                result = left + right;
            } else if (op == '-') {
                if (left < right) {
                    return rpnError(top, "проміжний результат від'ємний.");
                }

                result = left - right;
            } else {
                if (right.kop != 0 || right.hrn < 1 || right.hrn > 100) {
                    return rpnError(top, "множник має бути цілим числом від 1 до 100.");
                }

                if (kopecks(left) > 10000000 / right.hrn) {
                    return rpnError(top, "сума перевищує 100000.00 грн.");
                }

                result = left * right.hrn;
            }

            if (kopecks(result) > 10000000) {
                return rpnError(top, "сума перевищує 100000.00 грн.");
            }

            pushMoney(top, result);
        } else {
            Money value{};
            bool valid = parseMoney(token, value);

            if (!valid) {
                cout << "Помилка у виразі: «" << token << "» не є числом або операцією.\n";

                delete[] token;
                clearMoney(top);
                return false;
            }

            delete[] token;

            if (kopecks(value) > 10000000) {
                return rpnError(top, "сума перевищує 100000.00 грн.");
            }

            pushMoney(top, value);
        }
    }

    if (top == nullptr) {
        return rpnError(top, "порожній вираз.");
    }

    if (top->next != nullptr) {
        int count = 0;

        for (MoneyNode* p = top; p != nullptr; p = p->next) {
            count++;
        }

        cout << "Помилка у виразі: у стеку залишилось чисел: " << count << ", а має бути одне.\n";

        clearMoney(top);
        return false;
    }

    Money value = popMoney(top);

    if (kopecks(value) == 0) {
        return rpnError(top, "кінцева вартість має бути більшою за 0.00 грн.");
    }

    res = value;
    return true;
}

OrderNode* appendOrder(OrderList &list, const Order &order) {
    OrderNode* node = new OrderNode{order, list.tail, nullptr};

    if (list.tail != nullptr) {
        list.tail->next = node;
    } else {
        list.head = node;
    }

    list.tail = node;
    list.size++;

    return node;
}

OrderNode* findById(const OrderList &list, int id) {
    for (OrderNode* p = list.head; p != nullptr; p = p->next) {
        if (p->order.id == id) {
            return p;
        }
    }

    return nullptr;
}

void eraseOrder(OrderList &list, OrderNode* node) {
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
    list.size--;
}

void enqueue(QNode*& head, Order* order) {
    QNode* newNode = new QNode{order, nullptr};

    if (head == nullptr || order->priority > head->order->priority) {
        newNode->next = head;
        head = newNode;
        return;
    }

    QNode* current = head;

    while (current->next != nullptr && current->next->order->priority >= order->priority) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void removeQueued(QNode*& head, int id) {
    QNode** place = &head;

    while (*place != nullptr && (*place)->order->id != id) {
        place = &(*place)->next;
    }

    if (*place != nullptr) {
        QNode* node = *place;
        *place = node->next;
        delete node;
    }
}

int queueSize(QNode* head) {
    int count = 0;

    while (head != nullptr) {
        count++;
        head = head->next;
    }

    return count;
}

void pushAction(Action*& top, ActionType type, const Order &order) {
    top = new Action{type, order, top};
}

void clearMasters(Master*& head) {
    if (head == nullptr) {
        return;
    }

    Master* p = head->next;

    while (p != head) {
        Master* next = p->next;
        delete p;
        p = next;
    }

    delete head;
    head = nullptr;
}

bool readMasters(Master*& head) {
    int count;

    cout << "Кількість майстрів (від 1 до 5): ";

    if (!readInt(count) || count < 1 || count > 5) {
        cout << "Помилка: кількість майстрів має бути цілим числом від 1 до 5.\n";
        return false;
    }

    char text[256];
    char names[5][24]{};

    cout << "Імена майстрів через пробіл: ";

    if (!readLine(text, sizeof text)) {
        cout << "Помилка: некоректний рядок імен майстрів.\n";
        return false;
    }

    int size = 0;
    char* name = strtok(text, " ");

    while (name != nullptr) {
        if (size >= count || !validName(name, 23)) {
            break;
        }

        for (int i = 0; i < size; i++) {
            if (strcmp(names[i], name) == 0) {
                cout << "Помилка: імена майстрів не повинні повторюватися.\n";
                return false;
            }
        }

        strcpy(names[size], name);
        size++;
        name = strtok(nullptr, " ");
    }

    if (name != nullptr || size != count) {
        cout << "Помилка: кількість імен має дорівнювати " << count << ", кожне ім'я з латинських літер, до 23 символів.\n";
        return false;
    }

    Master* tail = nullptr;

    for (int i = 0; i < count; i++) {
        Master* node = new Master{};
        strcpy(node->name, names[i]);

        if (head == nullptr) {
            head = node;
        } else {
            tail->next = node;
        }

        tail = node;
        tail->next = head;
    }

    return true;
}

bool readOrder(Order &order) {
    cout << "Ім'я клієнта: ";

    if (!readLine(order.client.name, sizeof order.client.name) || !validName(order.client.name, 15)) {
        cout << "Помилка: ім'я має містити від 1 до 15 латинських літер.\n";
        return false;
    }

    cout << "Телефон (10 цифр): ";

    if (!readLine(order.client.phone, sizeof order.client.phone) || strlen(order.client.phone) != 10 || order.client.phone[0] != '0' || !digitsOnly(order.client.phone)) {
        cout << "Помилка: телефон має складатися з 10 цифр і починатися з 0.\n";
        return false;
    }

    char text[128];

    cout << "Дата прийому (ДД.ММ.РРРР): ";

    if (!readLine(text, sizeof text) || !parseDate(text, order.date)) {
        cout << "Помилка: некоректна дата.\n";
        return false;
    }

    int type;

    cout << "Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ";

    if (!readInt(type) || type < 1 || type > 3) {
        cout << "Помилка: тип пристрою має бути 1, 2 або 3.\n";
        return false;
    }

    order.type = static_cast<DeviceType>(type);

    if (order.type == DeviceType::PHONE) {
        cout << "Останні 6 цифр IMEI: ";

        if (!readLine(text, sizeof text) || strlen(text) != 6 || !digitsOnly(text)) {
            cout << "Помилка: потрібно рівно 6 цифр.\n";
            return false;
        }

        int imei = 0;

        for (int i = 0; i < 6; i++) {
            imei = imei * 10 + (text[i] - '0');
        }

        order.info.imei = imei;
    } else if (order.type == DeviceType::LAPTOP) {
        cout << "Серійний номер: ";
        order.info.serial[0] = '\0';

        if (!readLine(order.info.serial, sizeof order.info.serial) || order.info.serial[0] == '\0') {
            cout << "Помилка: серійний номер має містити від 1 до 11 великих латинських літер і цифр.\n";
            return false;
        }

        for (int i = 0; order.info.serial[i] != '\0'; i++) {
            char ch = order.info.serial[i];

            if (!(ch >= 'A' && ch <= 'Z') && !(ch >= '0' && ch <= '9')) {
                cout << "Помилка: серійний номер має містити лише великі латинські літери і цифри.\n";
                return false;
            }
        }
    } else {
        cout << "Діагональ (від 19 до 100 дюймів): ";
        int inches;

        if (!readInt(inches) || inches < 19 || inches > 100) {
            cout << "Помилка: діагональ має бути цілим числом від 19 до 100.\n";
            return false;
        }

        order.info.inches = inches;
    }

    cout << "Опис несправності: ";

    if (!readLine(order.problem, sizeof order.problem) || order.problem[0] == '\0') {
        cout << "Помилка: опис має містити від 1 до 80 байтів.\n";
        return false;
    }

    cout << "Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ";

    if (!readInt(order.priority) || order.priority < 1 || order.priority > 3) {
        cout << "Помилка: пріоритет має бути 1, 2 або 3.\n";
        return false;
    }

    char expr[1024];

    cout << "Вартість (обернений польський запис): ";

    if (!readLine(expr, sizeof expr)) {
        cout << "Помилка: вираз задовгий або не вдалося його прочитати.\n";
        return false;
    }

    return evalRPN(expr, order.price);
}

void addOrder(OrderList &list, QNode*& queue, Action*& history, int &nextId) {
    Order order{};

    if (!readOrder(order)) {
        return;
    }

    order.id = nextId++;
    order.status = Status::WAITING;

    OrderNode* node = appendOrder(list, order);

    enqueue(queue, &node->order);
    pushAction(history, ActionType::ADD, order);

    cout << "Замовлення №" << order.id << " додано: вартість " << order.price << " грн, у черзі на ремонт: " << queueSize(queue) << ".\n";
}

ostream& operator<<(ostream& os, const Order& order) {
    char date[16];
    char details[32];
    char price[40];
    char row[256];

    sprintf(date, "%02d.%02d.%04d",
            order.date.day, order.date.month, order.date.year);

    const char* type = "TV";

    if (order.type == DeviceType::PHONE) {
        type = "PHONE";
        sprintf(details, "IMEI %06d", order.info.imei);
    } else if (order.type == DeviceType::LAPTOP) {
        type = "LAPTOP";
        sprintf(details, "SN %s", order.info.serial);
    } else {
        sprintf(details, "%d inch", order.info.inches);
    }

    const char* status = "DONE";

    if (order.status == Status::WAITING) {
        status = "WAITING";
    } else if (order.status == Status::REPAIR) {
        status = "REPAIR";
    }

    sprintf(price, "%d.%02d", order.price.hrn, order.price.kop);

    snprintf(row, sizeof(row),
             "| %3d | %-15s | %-10s | %-10s | %-6s | %-14s | %2d | %-7s | %9s |\n",
             order.id, order.client.name, order.client.phone,
             date, type, details, order.priority, status, price);

    return os << row;
}

void tableBorder() {
    cout << "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+\n";
}

void tableHeader() {
    tableBorder();

    cout << "|   № | Клієнт          | Телефон    | Дата       | Тип    | Деталі         | Пр | Статус  |  Вартість |\n";

    tableBorder();
}

void showJournal(const OrderList &list, QNode* queue) {
    if (list.head == nullptr) {
        cout << "Журнал порожній.\n";
    } else {
        tableHeader();

        for (OrderNode* p = list.head; p != nullptr; p = p->next) {
            cout << p->order;
        }

        tableBorder();
    }

    cout << "Усього замовлень: " << list.size << ", у черзі на ремонт: " << queueSize(queue) << '\n';
}

void assignOrder(QNode*& queue, Master*& nextMaster) {
    if (queue == nullptr) {
        cout << "Черга на ремонт порожня.\n";
        return;
    }

    QNode* node = queue;
    Order &order = *node->order;

    queue = node->next;
    delete node;

    order.status = Status::REPAIR;
    strcpy(order.master, nextMaster->name);

    cout << "Замовлення №" << order.id << " (пріоритет " << order.priority << ") передано майстру " << nextMaster->name << ".\nНесправність: " << order.problem << "\nУ черзі залишилось: " << queueSize(queue) << '\n';

    nextMaster = nextMaster->next;
}

OrderNode* readOrderId(const OrderList &list) {
    int id;

    cout << "Номер замовлення: ";

    if (!readInt(id)) {
        cout << "Помилка: номер замовлення має бути цілим числом.\n";
        return nullptr;
    }

    OrderNode* node = findById(list, id);

    if (node == nullptr) {
        cout << "Замовлення №" << id << " не знайдено.\n";
    }

    return node;
}

void finishRepair(OrderList &list, Master* masters) {
    OrderNode* node = readOrderId(list);

    if (node == nullptr) {
        return;
    }

    Order &order = node->order;

    if (order.status == Status::WAITING) {
        cout << "Замовлення №" << order.id << " ще не передано майстру.\n";
        return;
    }

    if (order.status == Status::DONE) {
        cout << "Замовлення №" << order.id << " уже завершено.\n";
        return;
    }

    Master* p = masters;

    do {
        if (strcmp(p->name, order.master) == 0) {
            order.status = Status::DONE;
            p->count++;
            p->revenue = p->revenue + order.price;

            cout << "Ремонт замовлення №" << order.id << " завершено. Майстер " << p->name << ": виконано " << p->count << ", виручка " << p->revenue << " грн.\n";

            return;
        }

        p = p->next;
    } while (p != masters);
}

void deleteOrder(OrderList &list, QNode*& queue, Action*& history) {
    OrderNode* node = readOrderId(list);

    if (node == nullptr) {
        return;
    }

    if (node->order.status != Status::WAITING) {
        cout << "Видалити можна лише замовлення, яке очікує в черзі.\n";
        return;
    }

    int id = node->order.id;

    pushAction(history, ActionType::REMOVE, node->order);
    removeQueued(queue, id);
    eraseOrder(list, node);

    cout << "Замовлення №" << id << " видалено. У журналі: " << list.size << ", у черзі: " << queueSize(queue) << ".\n";
}

void undoAction(OrderList &list, QNode*& queue, Action*& history) {
    if (history == nullptr) {
        cout << "Немає дій для скасування.\n";
        return;
    }

    Action* action = history;
    history = action->next;

    int id = action->order.id;

    if (action->type == ActionType::REMOVE) {
        OrderNode* node = appendOrder(list, action->order);
        enqueue(queue, &node->order);

        cout << "Скасовано видалення замовлення №" << id << ": його повернуто в кінець журналу і в чергу.\n";
    } else {
        OrderNode* node = findById(list, id);

        if (node != nullptr && node->order.status == Status::WAITING) {
            removeQueued(queue, id);
            eraseOrder(list, node);

            cout << "Скасовано додавання замовлення №" << id << ".\n";
        } else {
            cout << "Додавання замовлення №" << id << " скасувати неможливо: його вже передано майстру.\n";
        }
    }

    delete action;
}

Money revenue(const OrderNode* p) {
    if (p == nullptr) {
        return Money{0, 0};
    }

    Money current = p->order.status == Status::DONE ? p->order.price : Money{0, 0};

    return current + revenue(p->next);
}

void sortOrders(Order** orders, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            bool equal = !(orders[j]->price < orders[j + 1]->price) && !(orders[j + 1]->price < orders[j]->price);

            if (orders[j]->price < orders[j + 1]->price || (equal && orders[j]->id > orders[j + 1]->id)) {
                Order* temp = orders[j];
                orders[j] = orders[j + 1];
                orders[j + 1] = temp;
            }
        }
    }
}

void showReport(const OrderList& list, Master* nextMaster) {
    if (list.size == 0) {
        cout << "Журнал порожній.\n";
        cout << "Різниця між найдорожчим і найдешевшим: "
             << Money{0, 0} << " грн\n";
    } else {
        Order** orders = new Order*[list.size];
        int i = 0;

        for (OrderNode* p = list.head; p != nullptr; p = p->next) {
            orders[i++] = &p->order;
        }

        sortOrders(orders, list.size);

        cout << "Замовлення за вартістю:\n";

        for (int j = 0; j < list.size; j++) {
            const char* status = "DONE";

            if (orders[j]->status == Status::WAITING) {
                status = "WAITING";
            } else if (orders[j]->status == Status::REPAIR) {
                status = "REPAIR";
            }

            char price[40];
            sprintf(price, "%d.%02d", orders[j]->price.hrn, orders[j]->price.kop);
            printf("  №%-5d%9s грн  %s\n", orders[j]->id, price, status);
        }

        cout << "Різниця між найдорожчим і найдешевшим: "
             << orders[0]->price - orders[list.size - 1]->price << " грн\n";

        delete[] orders;
    }

    cout << "Виручка за завершеними ремонтами: "
         << revenue(list.head) << " грн\n";

    cout << "Майстри, починаючи з наступного в черзі:\n";

    Master* p = nextMaster;

    do {
        printf("  %-12s виконано: %d, виручка: ", p->name, p->count);
        cout << p->revenue << " грн\n";

        p = p->next;
    } while (p != nextMaster);
}

void reverseJournal(OrderList &list) {
    if (list.head == nullptr) {
        cout << "Журнал порожній.\n";
        return;
    }

    OrderNode* p = list.head;

    while (p != nullptr) {
        OrderNode* next = p->next;
        p->next = p->prev;
        p->prev = next;
        p = next;
    }

    OrderNode* temp = list.head;
    list.head = list.tail;
    list.tail = temp;

    cout << "Журнал розвернуто: тепер першим іде замовлення №" << list.head->order.id << ", останнім №" << list.tail->order.id << ".\n";
}

void clearQueue(QNode*& head) {
    while (head != nullptr) {
        QNode* next = head->next;
        delete head;
        head = next;
    }
}

void clearHistory(Action*& top) {
    while (top != nullptr) {
        Action* next = top->next;
        delete top;
        top = next;
    }
}

void clearJournal(OrderList &list) {
    while (list.head != nullptr) {
        eraseOrder(list, list.head);
    }
}

void showMenu() {
    cout << "\nВведіть пункт меню:\n";
    cout << "1. Додати замовлення\n";
    cout << "2. Журнал замовлень\n";
    cout << "3. Видати замовлення майстру\n";
    cout << "4. Завершити ремонт\n";
    cout << "5. Видалити замовлення\n";
    cout << "6. Скасувати останню дію\n";
    cout << "7. Звіт\n";
    cout << "8. Розвернути журнал\n";
    cout << "0. Вийти\nВаш вибір: ";
}

int main() {
    Master* masters = nullptr;

    if (!readMasters(masters)) {
        clearMasters(masters);
        return 1;
    }

    Master* nextMaster = masters;
    OrderList list;

    QNode* queue = nullptr;
    Action* history = nullptr;

    int nextId = 101;
    int choice = 0;

    do {
    menuInput:
        showMenu();

        if (!readInt(choice)) {
            if (cin.fail()) {
                break;
            }

            cout << "Помилка: введіть номер пункту меню.\n";
            goto menuInput;
        }

        if (choice < 0 || choice > 8) {
            cout << "Помилка: пункту " << choice << " немає в меню.\n";
            goto menuInput;
        }

        switch (choice) {
            case 0:
                break;

            case 1:
                addOrder(list, queue, history, nextId);
                break;

            case 2:
                showJournal(list, queue);
                break;

            case 3:
                assignOrder(queue, nextMaster);
                break;

            case 4:
                finishRepair(list, masters);
                break;

            case 5:
                deleteOrder(list, queue, history);
                break;

            case 6:
                undoAction(list, queue, history);
                break;

            case 7:
                showReport(list, nextMaster);
                break;

            case 8:
                reverseJournal(list);
                break;
        }

        if (cin.fail()) {
            break;
        }
    } while (choice != 0);

    clearQueue(queue);
    clearHistory(history);
    clearJournal(list);
    clearMasters(masters);

    return 0;
}
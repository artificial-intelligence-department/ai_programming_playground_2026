/*
    Задача: “Сервісний центр: черга ремонтів”
    Михайловська Анна
    ШІ-14
*/

#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdio>
using namespace std;

//Оголошення всіх необхідних структур
enum class DeviceType { PHONE = 1, LAPTOP, TV };
enum class Status { WAITING, REPAIR, DONE };
enum class ActionType {ADD, REMOVE};

struct Money { int hrn; int kop;};

struct MoneyNode {Money value; MoneyNode * next;};

struct Date {int day, month, year; };

struct Client{char name[16],  phone[11]; };

union DeviceInfo { int imei; char serial[12]; int inches; };

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
    char masterName[24];};

struct OrderNode {Order order; OrderNode * prev; OrderNode * next;};

struct OrderList {OrderNode * head; OrderNode * tail; int size;};

struct QNode {Order * order; QNode * next;};

struct Master {char name[24]; int doneOrder; Money revenue; Master * next;};

struct Action {ActionType type; Order order; Action *next;};

//Прототипи функцій
Money operator+(const Money& a, const Money& b);
Money operator-(const Money& a, const Money& b);
Money operator*(const Money& money, int count);
bool operator<(const Money& a, const Money& b);
ostream& operator<<(ostream& os, const Money& money);
ostream& operator<<(ostream& os, const Order& order);

OrderNode* findById(const OrderList& list, int id);
void appendOrder(OrderList& list, const Order& order);
void enqueue(QNode*& head, Order* order);
void pushAction(Action*& top, ActionType type, const Order& order);
bool popAction(Action*& top, ActionType& type, Order& order);
void pushMoney(MoneyNode*& top, const Money& value);
bool popMoney(MoneyNode*& top, Money& value);
bool parseMoney(const char* text, Money& result);
void clearMoneyStack(MoneyNode*& top);
bool evalRPN(const char* expr, Money& res);
bool parseDate(const char* text, Date& result);
bool isValidClientName(const char* name);
bool isValidPhone(const char* phone);
bool isValidIMEI(const char* text);
bool isValidSerial(const char* text);
bool readLine(char* input, int capacity);
Order* dequeue(QNode*& head);
Master* findMaster(Master* start, const char* name);
void removeFromQueue(QNode*& head, int id);
void removeOrderNode(OrderList& list, OrderNode* node);
Money revenue(const OrderNode* p);


void addOrder(OrderList& list, QNode*& queueHead, Action*& actionTop, int& nextId);
void showJournal(const OrderList& list, const QNode* queueHead);
void assignOrder(QNode*& queueHead, Master*& nextMaster);
void finishRepair(OrderList& list, Master* nextMaster);
void deleteOrder(OrderList& list, QNode*& queueHead, Action*& actionTop);
void undoAction(OrderList& list, QNode*& queueHead, Action*& actionTop);
void showReport(const OrderList& list, const Master* nextMaster);
void reverseJournal(OrderList& list);
void clearAll(OrderList& list, QNode*& queueHead, Action*& actionTop, Master*& nextMaster);

int main(){

    OrderList journal{nullptr, nullptr, 0};

    QNode* queueHead = nullptr;

    Action* actionTop = nullptr;

    Master* nextMaster = nullptr;

    int nextId = 101;

    //Ввід користувачем кількості майстів та його валідація
    char input[2];
    cout << "Кількість майстрів (від 1 до 5): ";

    if (!cin.getline(input, 2)) {
        cout << "Помилка: введено неправильну кількість майстрів.\n";
        return 1;
    }
    if (input[0] < '1' || input[0] > '5' || input[1] != '\0') {
        cout << "Помилка: кількість майстрів має бути від 1 до 5.\n";
        return 1;
    }
    int masterCount = input[0] - '0';

    //Ввід користувачем імен майстрів та його валідація
    char masterNameLine[256];
    char masterNames[5][24];
    int countNames = 0;

    cout << "Введіть імена майстрів через пробіл: ";

    if (!cin.getline(masterNameLine, 256)) {
        cout << "Помилка: введені неправильні імена майстрів.\n";
        return 1;
    }

    //Розділення рядка на оеремі імена
    int i = 0;
    while (masterNameLine[i] != '\0') {
        while (masterNameLine[i] == ' ') 
            i++;
        
        if (masterNameLine[i] == '\0') {
            break;
        }

        if (countNames >= masterCount) {
            cout << "Помилка: введено забагато імен.\n";
            return 1;
        }

        int j = 0;
        while (masterNameLine[i] != ' ' && masterNameLine[i] != '\0') {
            char letter = masterNameLine[i];

            bool isLatin = (letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z');

            if (!isLatin || j >= 23) {
                cout << "Помилка: ім'я має містити від 1 до 23 латинських літер.\n";
                return 1;
            }

            masterNames[countNames][j] = letter;
            i++;
            j++;
        }

        masterNames[countNames][j] = '\0';

        //Перевірка чи імена не однакові
        for (int k = 0; k < countNames; k++) {
            if (strcmp(masterNames[k], masterNames[countNames]) == 0) {
                cout << "Помилка: імена майстрів не мають повторюватися.\n";
                return 1;
            }
        }
        countNames++;
    }

    if (countNames != masterCount) {
        cout << "Помилка: кількість імен має дорівнювати " << masterCount << ".\n";
        return 1;
    }

    //Створення кільця майстрів
    Master* firstMaster = nullptr;
    Master* lastMaster = nullptr;

    for (int i = 0; i < masterCount; i++) {
        Master* current = new Master;

        strcpy(current->name, masterNames[i]);
        current->doneOrder = 0;
        current->revenue = Money{0, 0};
        current->next = nullptr;

        if (firstMaster == nullptr) 
            firstMaster = current;
        else 
            lastMaster->next = current;
        
        lastMaster = current;
    }

    lastMaster->next = firstMaster;
    nextMaster = firstMaster;

    //Виведення меню
    int choice = -1;
    while (choice != 0) {
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

        //Перевірка некоректного вводу користувча
        char menuInput[256];
        if (!readLine(menuInput, 256)) {
            if (cin.eof())
                break;
            continue;
        }
        if (menuInput[0] < '0' || menuInput[0] > '9' ||  menuInput[1] != '\0') {
            cout << "Помилка: введіть номер пункту меню\n";
            continue;
        }

        choice = menuInput[0] - '0';
        switch (choice) {
            case 0:
                break;
            case 1:
                addOrder(journal, queueHead, actionTop, nextId);
                break;
            case 2:
                showJournal(journal, queueHead);
                break;
            case 3:
                assignOrder(queueHead, nextMaster);
                break;
            case 4:
                finishRepair(journal, nextMaster);
                break;
            case 5:
                deleteOrder(journal, queueHead, actionTop);
                break;
            case 6:
                undoAction(journal, queueHead, actionTop);
                break;
            case 7:
                showReport(journal, nextMaster);
                break;
            case 8:
                reverseJournal(journal);
                break;
            default:
                cout << "Помилка: пункту " << choice << " немає в меню.\n";
                break;
        }
    }

    clearAll(journal, queueHead, actionTop, nextMaster);

    return 0;
}


//Функція перевантаження оператора +
Money operator+(const Money& a, const Money& b) {
    int total = (a.hrn * 100 + a.kop) + (b.hrn * 100 + b.kop);
    Money result;
    result.hrn = total / 100;
    result.kop = total % 100;

    return result;
}

//Функція перевантаження оператора -
Money operator-(const Money& a, const Money& b) {
    int total = (a.hrn * 100 + a.kop) - (b.hrn * 100 + b.kop);
    Money result;  
    result.hrn = total / 100;
    result.kop = total % 100;

    return result;
}

//Функція перевантаження оператора *
Money operator*(const Money& money, int count) {
    int total = (money.hrn * 100 + money.kop) * count;
    Money result;
    result.hrn = total / 100;
    result.kop = total % 100;

    return result;
}

//Функція перевантаження оператора <
bool operator<(const Money& a, const Money& b) {
    if (a.hrn != b.hrn) 
        return a.hrn < b.hrn;

    return a.kop < b.kop;
}

//Функція перевантаження оператора << для виведення вартості
ostream& operator<<(ostream& os, const Money& money) {
    os << money.hrn << '.';

    if (money.kop < 10) 
        os << '0';

    os << money.kop;
    return os;
}

//Функція, яка переглядає журнал та шукає потрібний номер
OrderNode* findById(const OrderList& list, int id) {
    OrderNode* current = list.head;

    while (current != nullptr) {
        if (current->order.id == id) 
            return current;
        current = current->next;
    }

    return nullptr;
}

//Функція,яка додає замовлення в кінець журналу
void appendOrder(OrderList& list, const Order& order) {
    OrderNode* newNode = new OrderNode;
    newNode->order = order;
    newNode->prev = list.tail;
    newNode->next = nullptr;

    if (list.head == nullptr) 
        list.head = newNode;
    else 
        list.tail->next = newNode;
    
    list.tail = newNode;
    list.size++;
}

//Функція,яка додає замовлення в пріорітетну чергу
void enqueue(QNode*& head, Order* order) {
    QNode* newNode = new QNode;
    newNode->order = order;
    newNode->next = nullptr;

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

//Функція, яка додає запис останньої дії на вершину стеку 
void pushAction(Action*& top, ActionType type, const Order& order){
    Action * newAction = new Action;
    newAction->type = type;
    newAction->order = order;
    newAction->next = top;
    top = newAction;
}

//Функція, що запам’ятовує число для подальшого обчислення вартості
void pushMoney(MoneyNode*& top, const Money& value){
    MoneyNode * newMoneyNode = new MoneyNode;
    newMoneyNode->value = value;
    newMoneyNode->next = top;
    top = newMoneyNode;
}

//Функція, що забирає останнє збережене число для обчислення вартості
bool popMoney(MoneyNode*& top, Money& value){
    if (top == nullptr)
        return false;

    MoneyNode * temp = top;
    value = temp->value;
    top = temp->next;
    delete temp;

    return true;
}

//Функція, яка перевіряє запис введеного числа та перетворює його на гривні і копійки
bool parseMoney(const char* text, Money& result) {
    int position = 0;
    int hrn = 0;
    int kop = 0;
    int hrnDigits = 0;

    while (text[position] >= '0' && text[position] <= '9') {
        if (hrnDigits == 6) 
            return false;

        hrn = hrn * 10 + (text[position] - '0');
        hrnDigits++;
        position++;
    }

    if (hrnDigits == 0) 
        return false;
    
    if (text[position] == '.') {
        position++;

        int kopDigits = 0;
        while (text[position] >= '0' && text[position] <= '9') {
            if (kopDigits == 2) 
                return false;

            kop = kop * 10 + (text[position] - '0');
            kopDigits++;
            position++;
        }
        if (kopDigits == 0) 
            return false;

        if (kopDigits == 1) 
            kop *= 10; 
    }

    if (text[position] != '\0') 
        return false;
    
    result.hrn = hrn;
    result.kop = kop;

    return true;
}

//Функція, яка видаляє числа в стеку при неправильному вводу вартості ремонту
void clearMoneyStack(MoneyNode*& top){
    Money temp;
    while(popMoney(top, temp));
}

//Функція для підрахунку вартості в оберененому польському записі
bool evalRPN(const char* expr, Money& res){
    MoneyNode* top = nullptr;
    Money limit{100000, 0};
    char number[20];

    //Читання наступного числа або знака операції
    int i = 0;
    while (expr[i] != '\0') {
        while (expr[i] == ' ')
            i++;

        if (expr[i] == '\0')
            break;

        int j = 0;
        while (expr[i] != ' ' && expr[i] != '\0') {
            if (j >= 19) {
                cout << "Помилка у виразі: надто довгий токен.\n";
                clearMoneyStack(top);
                return false;
            }

            number[j] = expr[i];
            i++;
            j++;
        }
        number[j] = '\0';

        bool isOperation = number[1] == '\0' &&
            (number[0] == '+' || number[0] == '-' || number[0] == '*');

        //Якщо це операція, забираємо два числа та обчислюємо результат
        if (isOperation) {
            Money a;
            Money b;
            Money result;

            if (!popMoney(top, b) || !popMoney(top, a)) {
                cout << "Помилка у виразі: для операції «" << number[0] << "» бракує чисел.\n";
                clearMoneyStack(top);
                return false;
            }

            if (number[0] == '+') {
                result = a + b;

                if (limit < result) {
                    cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                    clearMoneyStack(top);
                    return false;
                }
            }
            else if (number[0] == '-') {
                if (a < b) {
                    cout << "Помилка у виразі: проміжний результат від'ємний.\n";
                    clearMoneyStack(top);
                    return false;
                }

                result = a - b;
            }
            
            else {
                if (b.kop != 0 || b.hrn < 1 || b.hrn > 100) {
                    cout << "Помилка у виразі: множник має бути цілим числом від 1 до 100.\n";
                    clearMoneyStack(top);
                    return false;
                }

                int totalKop = a.hrn * 100 + a.kop;

                if (totalKop > 10000000 / b.hrn) {
                    cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                    clearMoneyStack(top);
                    return false;
                }

                result = a * b.hrn;
            }

            pushMoney(top, result);

        //Якщо це число, перевіряємо його та зберігаємо для подальшого обчислення
        } else {
            Money value;

            if (!parseMoney(number, value)) {
                cout << "Помилка у виразі: «" << number << "» не є числом або операцією.\n";
                clearMoneyStack(top);
                return false;
            }

            if (limit < value) {
                cout << "Помилка у виразі: сума перевищує 100000.00 грн.\n";
                clearMoneyStack(top);
                return false;
            }

            pushMoney(top, value);
        }
    }

    //Після обчислення має залишитися одне число, більше за нуль
    if (top == nullptr) {
        cout << "Помилка у виразі: порожній вираз.\n";
        return false;
    }

    int count = 0;
    MoneyNode* current = top;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    if (count != 1) {
        cout << "Помилка у виразі: у стеку залишилось чисел: " << count << ", а має бути одне.\n";
        clearMoneyStack(top);
        return false;
    }

    Money finalResult;
    popMoney(top, finalResult);

    if (finalResult.hrn == 0 && finalResult.kop == 0) {
        cout << "Помилка у виразі: кінцевий результат дорівнює 0.00 грн.\n";
        return false;
    }

    res = finalResult;
    return true;
}

//Функція, яка перевіряє правильність запису дати
bool parseDate(const char* text, Date& result) {
    if (strlen(text) != 10)
        return false;

    if (text[2] != '.' || text[5] != '.')
        return false;

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5)
            continue;

        if (text[i] < '0' || text[i] > '9')
            return false;
    }

    int day = (text[0] - '0') * 10 + (text[1] - '0');
    int month = (text[3] - '0') * 10 + (text[4] - '0');
    int year = (text[6] - '0') * 1000 + (text[7] - '0') * 100 + (text[8] - '0') * 10 + (text[9] - '0');

    if (year < 2000 || year > 2099)
        return false;

    if (month < 1 || month > 12)
        return false;

    //Перевірка чи у конкретному місяці дійсно стільки днів
    int daysInMonth = 31;
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        daysInMonth = 30;
    }
    else if (month == 2) {
        bool leapYear = year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
        daysInMonth = leapYear ? 29 : 28;
    }

    if (day < 1 || day > daysInMonth)
        return false;

    result.day = day;
    result.month = month;
    result.year = year;

    return true;
}

//Функція, яка перевіряє чи коректно введено ім'я клієнта
bool isValidClientName(const char* name) {
    int length = strlen(name);

    if (length < 1 || length > 15)
        return false;

    for (int i = 0; i < length; i++) {
        bool isLatin = (name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z');

        if (!isLatin)
            return false;
    }
    return true;
}

//Функція, яка перевіряє чи коректно введено телефон клієнта
bool isValidPhone(const char* phone) {
    if (strlen(phone) != 10)
        return false;

    if (phone[0] != '0')
        return false;

    for (int i = 0; i < 10; i++) {
        if (phone[i] < '0' || phone[i] > '9')
            return false;
    }
    return true;
}

//Функція, яка первіряє чи введено рівно 6 цифр IMEI
bool isValidIMEI(const char* text) {
    if (strlen(text) != 6)
        return false;

    for (int i = 0; i < 6; i++) {
        if (text[i] < '0' || text[i] > '9')
            return false;
    }
    return true;
}

//Функція, яка перевіряє коректність вводу серійнийного номеру
bool isValidSerial(const char* text) {
    int length = strlen(text);

    if (length < 1 || length > 11)
        return false;

    for (int i = 0; i < length; i++) {
        bool isUpper = text[i] >= 'A' && text[i] <= 'Z';
        bool isDigit = text[i] >= '0' && text[i] <= '9';

        if (!isUpper && !isDigit)
            return false;
    }
    return true;
}

//Функція, яка читає введений рядок і повідомляє, якшо він дуже довгий
bool readLine(char* input, int capacity) {
    if (cin.getline(input, capacity))
        return true;

    if (!cin.eof()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка: надто довгий рядок.\n";
    }
    return false;
}

//Функція, яка додає нове замовлення в журнал (пункт 1)
void addOrder(OrderList& list, QNode*& queueHead, Action*& actionTop, int& nextId) {
    Order order{};
    char input[256];

    //Додавання імені клієнта до замовлення та перевірка вводу
    cout << "Ім'я клієнта: ";

    if (!readLine(input, 256))
        return;

    if (!isValidClientName(input)) {
        cout << "Помилка: ім'я має містити від 1 до 15 латинських літер.\n";
        return;
    }
    strcpy(order.client.name, input);

    //Додавання телефону клієнта до замовлення та перевірка вводу
    cout << "Телефон (10 цифр): ";

    if (!readLine(input, 256))
        return;

    if (!isValidPhone(input)) {
        cout << "Помилка: телефон має складатися з 10 цифр і починатися з 0.\n";
        return;
    }
    strcpy(order.client.phone, input);

    //Додавання дати прийому до замовлення та перевірка вводу
    cout << "Дата прийому (ДД.ММ.РРРР): ";

    if (!readLine(input, 256))
        return;

    if (!parseDate(input, order.date)) {
        cout << "Помилка: некоректна дата.\n";
        return;
    }

    //Додавання типу пристрою до замовлення та перевірка вводу
    cout << "Тип пристрою (1 телефон, 2 ноутбук, 3 телевізор): ";
    
    if (!readLine(input, 256))
        return;

    if (input[0] < '1' || input[0] > '3' || input[1] != '\0') {
        cout << "Помилка: тип пристрою має бути 1, 2 або 3.\n";
        return;
    }

    //Вибір пристрою
    if (input[0] == '1')
        order.type = DeviceType::PHONE;
    else if (input[0] == '2')
        order.type = DeviceType::LAPTOP;
    else
        order.type = DeviceType::TV;

    switch (order.type) {
        case DeviceType::PHONE: {
            cout << "Останні 6 цифр IMEI: ";
            
            if (!readLine(input, 256))
                return;

            if (!isValidIMEI(input)) {
                cout << "Помилка: потрібно рівно 6 цифр.\n";
                return;
            }

            int imei = 0;
            for (int i = 0; i < 6; i++) {
                imei = imei * 10 + (input[i] - '0');
            }
            order.info.imei = imei;
            break;
        }

        case DeviceType::LAPTOP: {
            cout << "Серійний номер: ";
            
            if (!readLine(input, 256))
                return;

            if (!isValidSerial(input)) {
                cout << "Помилка: серійний номер має містити від 1 до 11 великих латинських літер або цифр.\n";
                return;
            }
            strcpy(order.info.serial, input);
            break;
        }

        case DeviceType::TV: {
            cout << "Діагональ (від 19 до 100 дюймів): ";
            if (!readLine(input, 256))
                return;

            int length = strlen(input);
            if (length < 2 || length > 3) {
                cout << "Помилка: діагональ має бути цілим числом від 19 до 100.\n";
                return;
            }

            int inches = 0;
            for (int i = 0; i < length; i++) {
                if (input[i] < '0' || input[i] > '9') {
                    cout << "Помилка: діагональ має бути цілим числом від 19 до 100.\n";
                    return;
                }
                inches = inches * 10 + (input[i] - '0');
            }

            if (inches < 19 || inches > 100) {
                cout << "Помилка: діагональ має бути цілим числом від 19 до 100.\n";
                return;
            }
            order.info.inches = inches;
            break;
        }
    }

    //Додавання опису несправності до замовлення та перевірка вводу
    cout << "Опис несправності: ";
    
    if (!readLine(input, 256))
        return;

    if (strlen(input) < 1 || strlen(input) > 80) {
        cout << "Помилка: опис має бути до 80 байтів \n";
        return;
    }
    strcpy(order.problem, input);

    //Додавання пріорітету замовлення та перевірка вводу
    cout << "Пріоритет (1 звичайний, 2 підвищений, 3 терміновий): ";

    if (!readLine(input, 256))
        return;

    if (input[0] < '1' || input[0] > '3' || input[1] != '\0') {
        cout << "Помилка: пріорітет має бути 1, 2 або 3.\n";
        return;
    }
    order.priority = input[0] - '0';

    //Додавання вартості замовлення та перевірка вводу
    cout << "Вартість (обернений польський запис): ";

    if (!readLine(input, 256))
        return;

    if (!evalRPN(input, order.price))
        return;

    //Призначаємо номер і початковий стан замовлення
    order.id = nextId;
    order.status = Status::WAITING;
    order.masterName[0] = '\0';

    // Зберігаємо замовлення та запам'ятовуємо його додавання
    appendOrder(list, order);
    enqueue(queueHead, &list.tail->order);
    pushAction(actionTop, ActionType::ADD, order);

    nextId++;

    // Рахуємо замовлення, які очікують ремонту.
    int queueCount = 0;
    QNode* current = queueHead;

    while (current != nullptr) {
        queueCount++;
        current = current->next;
    }

    cout << "Замовлення №" << order.id << " додано: вартість " << order.price << " грн, у черзі на ремонт: " << queueCount << ".\n";
}

//Функція перевантаження оператора << для виведення одного замовлення
ostream& operator<<(ostream& os, const Order& order){
    char dateText[15];
    char typeText[10];
    char details[35];
    char statusText[10];
    char priceText[35];

    sprintf(dateText, "%02d.%02d.%04d", order.date.day, order.date.month, order.date.year);

    switch (order.type){
        case DeviceType::PHONE:
            strcpy(typeText, "PHONE");
            sprintf(details, "IMEI %06d", order.info.imei);
            break;

        case DeviceType:: LAPTOP:
            strcpy(typeText, "LAPTOP");
            sprintf(details, "SN %s", order.info.serial);
            break;

        case DeviceType:: TV:
            strcpy(typeText, "TV");
            sprintf(details, "%d inch", order.info.inches);
            break;
    }

    switch (order.status){
        case Status::WAITING:
            strcpy(statusText, "WAITING");
            break;

        case Status::REPAIR:
            strcpy(statusText, "REPAIR");
            break;

        case Status::DONE:
            strcpy(statusText, "DONE");
            break;
    }

    sprintf(priceText, "%d.%02d", order.price.hrn, order.price.kop);

    os << "| " << right << setw(3) << order.id << " | " << left << setw(15) << order.client.name
       << " | " << setw(10) << order.client.phone  << " | " << setw(10) << dateText 
       << " | " << setw(6) << typeText  << " | " << setw(14) << details << " | " << right << setw(2) << order.priority 
       << " | " << left << setw(7) << statusText << " | " << right << setw(9) << priceText << " |\n";
    
       return os;
}

//Функція яка показує таюлицю усіх замовлень (пункт 2)
void showJournal(const OrderList& list, const QNode* queueHead) {
    if (list.head == nullptr) {
        cout << "Журнал порожній\n";
        return;
    }

    const char* border = "+-----+-----------------+------------+------------+--------+----------------+----+---------+-----------+\n";
    cout << border;

    cout << "|  №  |      Клієнт     |  Телефон   |    Дата    |   Тип  |     Деталі     | Пр | Статус  |  Вартість |\n";
    cout << border;

    const OrderNode* current = list.head;
    while (current != nullptr) {
        cout << current->order;
        current = current->next;
    }
    cout << border;

    int queueCount = 0;
    const QNode* currentQueue = queueHead;
    while (currentQueue != nullptr) {
        queueCount++;
        currentQueue = currentQueue->next;
    }

    cout << "Усього замовлень: " << list.size << ", у черзі на ремонт: " << queueCount << '\n';
}

//Функція, яка забирає перше замовлення з черги, залишаючи його в журналі
Order* dequeue(QNode*& head) {
    if (head == nullptr)
        return nullptr;

    QNode* temp = head;
    Order* order = temp->order;
    head = temp->next;
    delete temp;

    return order;
}
//Функція, яка видає замовлення майстру (пункт 3)
void assignOrder(QNode*& queueHead, Master*& nextMaster){
    Order * order = dequeue(queueHead);

    if (order == nullptr){
        cout << "Черга на ремонт порожня";
        return;
    }

    order->status = Status::REPAIR;
    strcpy(order->masterName, nextMaster->name);

    int queueCount = 0;
    const QNode* currentQueue = queueHead;
    while (currentQueue != nullptr) {
        queueCount++;
        currentQueue = currentQueue->next;
    }

    cout << "Замовлення №" << order->id << " (пріоритет " << order->priority 
         << ") передано майстру " << order->masterName << ".\n";
    cout << "Несправність: " << order->problem << ".\n";
    cout << "У черзі залишилось : " << queueCount << ".\n";

    nextMaster = nextMaster->next;
}

//Фукція, яка знаходить майстра за заданим ім'ям
Master* findMaster(Master* start, const char* name) {
    if (start == nullptr)
        return nullptr;

    Master* current = start;
    do {
        if (strcmp(current->name, name) == 0)
            return current;

        current = current->next;
    } while (current != start);

    return nullptr;
}

//Фукція, яка завершує ремонт (пункт 4)
void finishRepair(OrderList& list, Master* nextMaster) {
    char input[256];
    cout << "Номер замовлення: ";
    if (!readLine(input, 256))
        return;

    if (input[0] == '\0') {
        cout << "Помилка: введіть номер замовлення\n";
        return;
    }

    int id = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] < '0' || input[i] > '9') {
            cout << "Помилка: номер замовлення має містити лише цифри\n";
            return;
        }
        id = id * 10 + (input[i] - '0');
    }

    OrderNode* node = findById(list, id);
    if (node == nullptr) {
        cout << "Замовлення №" << id << " не знайдено\n";
        return;
    }
    if (node->order.status == Status::WAITING) {
        cout << "Замовлення №" << id << " ще не передано майстру\n";
        return;
    }
    if (node->order.status == Status::DONE) {
        cout << "Замовлення №" << id << " уже завершено\n";
        return;
    }

    Master* master = findMaster(nextMaster, node->order.masterName);
    if (master == nullptr) {
        cout << "Помилка: майстра не знайдено\n";
        return;
    }

    node->order.status = Status::DONE;
    master->doneOrder++;
    master->revenue = master->revenue + node->order.price;
    cout << "Ремонт замовлення №" << id << " завершено. " << "Майстер " << master->name
         << ": виконано " << master->doneOrder << ", виручка " << master->revenue << " грн.\n";
}

//Функція, яка видаляє будь яке замовлення з черги
void removeFromQueue(QNode*& head, int id) {
    QNode* current = head;
    QNode* previous = nullptr;

    while (current != nullptr && current->order->id != id) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr)
        return;

    if (previous == nullptr)
        head = current->next;
    else
        previous->next = current->next;

    delete current;
}

//Функція, яка видаляє будь яке замовлення з журналу
void removeOrderNode(OrderList& list, OrderNode* node) {
    if (node == nullptr)
        return;

    if (node->prev != nullptr)
        node->prev->next = node->next;
    else
        list.head = node->next;

    if (node->next != nullptr)
        node->next->prev = node->prev;
    else
        list.tail = node->prev;

    delete node;
    list.size--;
}

//Функція видалення замовлення (пункт 5) 
void deleteOrder(OrderList& list, QNode*& queueHead, Action*& actionTop) {
    char input[256];
    cout << "Номер замовлення: ";
    if (!readLine(input, 256))
        return;

    if (input[0] == '\0') {
        cout << "Помилка: введіть номер замовлення\n";
        return;
    }

    int id = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] < '0' || input[i] > '9') {
            cout << "Помилка: номер замовлення має містити лише цифри.ʼ\n";
            return;
        }

        id = id * 10 + (input[i] - '0');
    }

    OrderNode* node = findById(list, id);
    if (node == nullptr) {
        cout << "Замовлення №" << id << " не знайдено\n";
        return;
    }

    if (node->order.status != Status::WAITING) {
        cout << "Видалити можна лише замовлення, яке очікує в черзі\n";
        return;
    }

    
    pushAction(actionTop, ActionType::REMOVE, node->order);
    removeFromQueue(queueHead, id);
    removeOrderNode(list, node);

    int queueCount = 0;
    const QNode* current = queueHead;
    while (current != nullptr) {
        queueCount++;
        current = current->next;
    }

    cout << "Замовлення №" << id << " видалено. " << "У журналі: " << list.size
         << ", у черзі: " << queueCount << ".\n";
}
//Функція, якк забирає останню записану дію та зберігає її дані
bool popAction(Action*& top, ActionType& type, Order& order) {
    if (top == nullptr)
        return false;

    Action* temp = top;
    type = temp->type;
    order = temp->order;

    top = temp->next;
    delete temp;

    return true;
}

//Функція, якк скасовує останню дію (пункт 6)
void undoAction(OrderList& list, QNode*& queueHead, Action*& actionTop) {
    ActionType type;
    Order order;

    if (!popAction(actionTop, type, order)) {
        cout << "Немає дій для скасування\n";
        return;
    }
    if (type == ActionType::ADD) {
        OrderNode* node = findById(list, order.id);

        if (node == nullptr) {
            cout << "Замовлення №" << order.id << " не знайдено\n";
            return;
        }
        if (node->order.status != Status::WAITING) {
            cout << "Додавання замовлення №" << order.id << " скасувати неможливо: його вже передано майстру\n";
            return;
        }

        removeFromQueue(queueHead, order.id);
        removeOrderNode(list, node);

        cout << "Скасовано додавання замовлення №" << order.id << ".\n";
    }
    else if (type == ActionType::REMOVE) {
        appendOrder(list, order);
        enqueue(queueHead, &list.tail->order);

        cout << "Скасовано видалення замовлення №" << order.id << ": його повернуто в кінець журналу і в чергу\n";
    }
}

//Функція, яка підраховує загальну вартість завершених ремонтів
Money revenue(const OrderNode* p) {
    if (p == nullptr)
        return Money{0, 0};

    if (p->order.status == Status::DONE)
        return p->order.price + revenue(p->next);

    return revenue(p->next);
}

//Функція, для показу звіту (пункт 7)
void showReport(const OrderList& list, const Master* nextMaster) {
    if (list.head == nullptr) {
        cout << "Журнал порожній.\n";
    }
    else {
        Order** orders = new Order*[list.size];
        OrderNode* current = list.head;
        int index = 0;
        while (current != nullptr) {
            orders[index] = &current->order;
            index++;
            current = current->next;
        }

        for (int i = 0; i < list.size - 1; i++) {
            int best = i;
            for (int j = i + 1; j < list.size; j++) {

                bool samePrice = orders[j]->price.hrn == orders[best]->price.hrn && orders[j]->price.kop == orders[best]->price.kop;

                if (orders[best]->price < orders[j]->price || (samePrice && orders[j]->id < orders[best]->id)) {
                    best = j;
                }
            }
            Order* temp = orders[i];
            orders[i] = orders[best];
            orders[best] = temp;
        }

        cout << "Замовлення за вартістю:\n";
        for (int i = 0; i < list.size; i++) {
            char priceText[32];
            char statusText[8];
            sprintf(priceText, "%d.%02d", orders[i]->price.hrn, orders[i]->price.kop);

            if (orders[i]->status == Status::WAITING)
                strcpy(statusText, "WAITING");
            else if (orders[i]->status == Status::REPAIR)
                strcpy(statusText, "REPAIR");
            else
                strcpy(statusText, "DONE");

            cout << "  №" << right << setw(3) << orders[i]->id << "  " << setw(9) << priceText
                 << " грн  " << statusText << '\n';
        }

        Money difference = orders[0]->price - orders[list.size - 1]->price;
        cout << "Різниця між найдорожчим і найдешевшим: " << difference << " грн\n";

        delete[] orders;
    }

    cout << "Виручка за завершеними ремонтами: " << revenue(list.head) << " грн\n";
    cout << "Майстри, починаючи з наступного в черзі:\n";

    if (nextMaster == nullptr) {
        cout << "Майстрів немає.\n";
        return;
    }

    const Master* currentMaster = nextMaster;
    do {
        cout << "  " << left << setw(23) << currentMaster->name  << " виконано: " << currentMaster->doneOrder
             << ", виручка: " << currentMaster->revenue << " грн\n";
        currentMaster = currentMaster->next;
    } while (currentMaster != nextMaster);
}
//Функція, яка розвертає журнал(пункт 8)
void reverseJournal(OrderList& list) {
    if (list.head == nullptr) {
        cout << "Журнал порожній\n";
        return;
    }

    OrderNode* current = list.head;
    while (current != nullptr) {
        OrderNode* oldNext = current->next;

        current->next = current->prev;
        current->prev = oldNext;
        current = oldNext;
    }

    OrderNode* temp = list.head;
    list.head = list.tail;
    list.tail = temp;

    cout << "Журнал розвернуто: тепер першим іде замовлення №" << list.head->order.id
         << ", останнім №" << list.tail->order.id << ".\n";
}

//Функція, яка звільняє усю пам'ять
void clearAll(OrderList& list, QNode*& queueHead, Action*& actionTop, Master*& nextMaster) {
    while (queueHead != nullptr) {
        QNode* temp = queueHead;
        queueHead = queueHead->next;
        delete temp;
    }

    while (list.head != nullptr) {
        OrderNode* temp = list.head;
        list.head = list.head->next;
        delete temp;
    }

    list.tail = nullptr;
    list.size = 0;

    ActionType type;
    Order order;

    while (popAction(actionTop, type, order)) {
    }
    
    if (nextMaster != nullptr) {
        Master* current = nextMaster->next;

        while (current != nextMaster) {
            Master* temp = current;
            current = current->next;
            delete temp;
        }
        delete nextMaster;
        nextMaster = nullptr;
    }
}

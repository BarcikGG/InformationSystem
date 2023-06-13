#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <filesystem>

using namespace std;

// Класс блюда
class Product {
public:
    int id; //id блюдв
    string name; //название блюда
    double price; //цена блюда

    //конструктор продукта
    Product(int _id, const string& _name, double _price) : id(_id), name(_name), price(_price) {}
};

// Класс блюда
class Dish {
public:
    int id; //id блюдв
    string name; //название блюда
    double price; //цена блюда
    int quantity; //кол-во блюд в наличии

    //конструктор продукта
    Dish(int _id, const string& _name, int _quantity, double _price) : id(_id), name(_name), quantity(_quantity), price(_price) {} 
};

// Класс ресторан
class Restaurant {
private:
    double balance; //баланс рестика

public:
    Restaurant(double initialBalance) : balance(initialBalance) {} //конструктор рестика

    //функция возвращающая баланс ресторана
    double getBalance() const {
        return balance;
    }

    //функция для пополнения баланса ресторана
    void deposit(double amount) {
        balance += amount; //пополняем баланс
    }

    //функция для списания средств со счета ресторана
    bool withdraw(double amount) {
        if (amount <= balance) { //проверяем, что списываем меньше или сумму баланса рестика
            balance -= amount; //списываем бабки
            return true;  // Успешное списание средств
        }
        return false;  // Недостаточно средств на балансе
    }
};


// Класс меню
class Menu {
private:
    vector<Dish> Dishs; //лист блюд для меню

public:
    //функция добавления блюда в меню
    void addToMenu(int id, const string& name, double price, int quantity) {
        Dishs.emplace_back(id, name, price, quantity); //добавление блюда
    }

    //функция проверки доступности блюда для заказа
    bool isAvailable(const string& name, int quantity) {
        for (const auto& Dish : Dishs) { //циклом проходимся по всем позициям меню
            //проверяем, что конкретное блюдо в количество больше или равно запрашиваемому количеству
            if (Dish.name == name && Dish.quantity >= quantity) {
                return true; //возвращаем true если блюдо есть
            }
        }
        return false; //блюд не хватает
    }
    
    //функция  вывода блюд меню
    void GetMenu() {
        for (const auto& Dish : Dishs) { //цикл проходящий по всем позициям меню
            cout << "ID: " << Dish.id << " | Блюдо: " << Dish.name << " Цена: " << Dish.price << "руб." << endl; //вывод блюда
        }
    }

    /*vector<Dish> GetDishs() {
        return Dishs;
    }*/

    //функция возвращающая название блюда
    string getMenuDishNameById(int id) {
        for (const auto& Dish : Dishs) { //цикл проходящий по всем позициям меню
            if (Dish.id == id) { //проверка соответствия id искомого блюда с текущим в цикле
                return Dish.name; //возвращаем название блюда
            }
        }
        return "Блюдо не найдено";  //возвращаем пустую строку, если продукт с указанным id не найден
    }

    //функция возвращающая цену блюда
    double GetPrice(int id) {
        for (const auto& Dish : Dishs) { //цикл проходящий по всем позициям меню
            if (Dish.id == id) { //проверка соответствия id искомого блюда с текущим в цикле
                return Dish.price; //возвращаем цену блюда
            }
        }
        return 0; // Возвращаем 0, если продукт не найден
    }

    //функция возвращающая кол-во конкретного блюда
    int GetQuantity(int id) {
        for (const auto& Dish : Dishs) { //цикл проходящий по всем позициям меню
            if (Dish.id == id) { //проверка соответствия id искомого блюда с текущим в цикле
                return Dish.quantity; //возвращаем кол-во конкретного блюда
            }
        }
        return 0; // Возвращаем 0, если продукт не найден
    }
};

// Класс корзины заказа гостя
class GuestOrderBasket {
private:
    vector<Dish> items; //лист с блюдами заказа

public:
    //функция добавления блюда в заказ
    void addItem(int id, string name, double price, int quantity) {
        items.emplace_back(id, name, price, quantity); //добавление блюда
    }

    //вывод корзины в консоль
    void printBasket() const {
        cout << "Ваш заказ: " << endl;
        for (const auto& item : items) { //цикл проходящий по всем позиция корзины
            cout << "Блюдо: " << item.name << ", Количество: " << item.quantity << endl; //вывод каждого блюда
        }
    }

    //функция для подсчета стоимости всего заказа
    double Amount() {
        double amount = 0; //обнуляем стоимость
        for (const auto& item : items) { //проходимся по всем пунктам заказа
            amount += item.price * item.quantity; //прибавляем к итоговой стоимости стоимость блюда умноженного на количество этого блюда
        }
        return amount; //возвращаем стоимость корзины
    }
};

// Класс заказа
class Order {
public:
    string status; //статус заказа

    Order() : status("Новый заказ!") {} //конструктор заказа

    void confirmOrder() {
        status = "Оплачен и передан на кухню";
        cout << "Статус изменен на:" << status << endl;
    }

    void CookingOrder() {
        status = "В процессе приготовления";
        cout << "Статус изменен на:" << status << endl;
    }

    void DeliveryOrder() {
        status = "Передан официанту";
        cout << "Статус изменен на:" << status << endl;
    }

    void CompleteOrder() {
        status = "Выдано";
        cout << "Статус изменен на:" << status << endl;
    }

    string GetStatus() {
        return status;
    }
};

// Класс сотрудника
class Employee {
public:
    string role;
    string lastName;
    string firstName;
    string patronymic;
    string username;
    string password;

    Employee(
        const string& _role,
        const string& _lastName,
        const string& _firstName,
        const string& _patronymic,
        const string& _username,
        const string& _password)
        : role(_role),
        lastName(_lastName),
        firstName(_firstName),
        patronymic(_patronymic),
        username(_username),
        password(_password) {}
};

// Класс системного администратора
class SystemAdministrator {
public:
    void editMenu() {
        // Логика редактирования меню
    }

    void editDishList(Menu& menu) {
        // Логика редактирования списка продуктов
    }

    void editEmployeeAccounts() {
        // Логика редактирования учетных записей сотрудников
    }

    void addEmployee(string role, string lastName, string firstName, string patronymic, string username, string password, string filename, vector<Employee> employees) {
        Employee employee{role, lastName, firstName, patronymic, username, password};
        
        ofstream outputFile(filename);
        employees.push_back(employee);

        if (outputFile.is_open()) {
            for (const auto& employee : employees) {
                outputFile 
                    << employee.role << " "
                    << employee.username << " "
                    << employee.firstName << " "
                    << employee.patronymic << " "
                    << employee.username << " "
                    << employee.password << " " << endl;
            }

            outputFile.close();
            cout << "Сотрудники успешно сохранены в файл." << endl;
        }
        else {
            cerr << "Не удалось открыть файл для записи." << endl;
        }
    }

    void getEmployees(vector<Employee> employees, string filename) {
        ifstream inputFile(filename);
        if (inputFile.is_open()) {
            string line;
            employees.clear();
            while (getline(inputFile, line)) {
                stringstream ss(line);
                string role, lastName, firstName, patronymic, username, password;
                if (ss >> role >> lastName >> firstName >> patronymic >> username >> password) {
                    employees.push_back({ role, lastName, firstName, patronymic, username, password });
                }
            }
            inputFile.close();
        }

        for (const auto& employee : employees) {
            cout << "------------------------\nРоль: " << employee.role << endl;
            cout << "Фамилия: " << employee.lastName << endl;
            cout << "Имя: " << employee.firstName << endl;
            cout << "Отчество: " << employee.patronymic << endl;
            cout << "Логин: " << employee.username << endl;
            cout << "Пароль: " << employee.password << endl;
            cout << endl;
        }
    }
};

// Класс журнала аудита
class AuditLog {
private:
    vector<string> entries;

public:
    void addEntry(const string& entry) {
        entries.push_back(entry);
    }

    void printEntries() const {
        for (const auto& entry : entries) {
            cout << entry << endl;
        }
    }
};

class DishRequest {
public:
    map<int, int> Dishs; // Ключ - идентификатор продукта, Значение - количество продукта
};

// Класс складского
class Storekeeper {
public:
    DishRequest createDishRequest(const Menu& menu) {
        DishRequest request;

        // Логика создания заявки на продукты

        return request;
    }

    void trackInventory(const Menu& menu) {
        // Логика отслеживания количества продуктов на складе
    }
};

// Класс поставщика
class Supplier {
public:
    void processDishRequest(const DishRequest& request, Menu& menu) {
        // Логика обработки заявки на продукты и отправки продуктов
    }
};

// Класс бухгалтера
class Accountant {
public:
    void viewDishRequests(const vector<DishRequest>& requests) {
        // Логика просмотра всех отправленных заявок на продукты
    }

    void viewDeliveries(const vector<DishRequest>& deliveries) {
        // Логика просмотра всех принятых поставок продуктов
    }

    void viewFinancialReports() {
        // Логика просмотра финансовой отчетности
    }
};

class Chef {
public:
    void viewOrders(const vector<Order>& orders) {
        // Логика просмотра всех заказов
    }

    void startPreparation(Order& order) {
        // Логика начала приготовления заказа
    }

    void prepareItem(Order& order, int menuItemIndex, const vector<int>& DishNumbers) {
        // Логика приготовления конкретного пункта заказа
    }
};

// Класс официанта
class Waiter {
public:
    void viewAvailableOrders(const vector<Order>& orders) {
        // Логика просмотра доступных для выдачи заказов
    }

    void changeOrderStatus(Order& order, int status) {
        switch (status)
        {
        case 1:
            order.CookingOrder();
            break;
        case 2:
            order.DeliveryOrder();
            break;
        case 3:
            order.CompleteOrder();
            break;
        default:
            cout << "Неверный номер" << endl;
            break;
        }
    }
};

//метод для очистки консоли
void clearConsole() {
    system("cls");
}

//метод для работы с гостем
int Guest(bool isLogin, Menu menu, Restaurant restaurant) {
    isLogin = true; //переменная для определения статуса пользователя и управления циклом
    char answer; //ответ гостя по заказа (да/нет)
    char action; //действие гостя (просмотр статуса или смена роли)
    int status = 0; //статус заказа
    double guest_amount; //сумма которую заплатил гость

    unique_ptr<GuestOrderBasket> backet = make_unique<GuestOrderBasket>(); // создание умного указателя корзины
    unique_ptr<Order> order = make_unique<Order>(); // создание умного указателя заказа

    clearConsole();
    menu.GetMenu(); //выводим меню для гостя
    int id = 0; //id для ввода номера заказа

    do {
        try {
            int quantity = 0;
            cout << "Для заказа блюда, введите его номер (0 - завершить): " << endl;
            cin >> id;

            string DishName = menu.getMenuDishNameById(id);
            int AvailableQuantity = menu.GetQuantity(id);

            if (menu.isAvailable(DishName, quantity)) {
                cout << "Количество: " << endl;
                cin >> quantity;

                if (AvailableQuantity < quantity) cout << "У нас всего: " << AvailableQuantity << "шт. " << DishName << endl;
                else backet->addItem(id, DishName, menu.GetPrice(id), quantity);
            }
            else cout << DishName << endl;
        }
        catch (exception) {}
    } while (id != 0);

    clearConsole();
    backet->printBasket();

    do {
        cout << "Подтвердить заказ? (y/n): ";
        cin >> answer;

        if (answer == 'y') {
            do {
                try {
                    cout << "К оплате: " << backet->Amount() << "\nВаша сумма: ";
                    cin >> guest_amount;

                    if (guest_amount >= backet->Amount()) {
                        clearConsole();
                        restaurant.deposit(guest_amount);
                        cout << "Статус: ";
                        order->confirmOrder();
                        cout << "Спасибо! Ваш заказ передан на кухню." << endl;
                        break;
                    }
                    else cout << "Недостаточно средств" << endl;
                }
                catch (exception) {}

            } while (guest_amount < backet->Amount());
            break;
        }
    } while (answer != 'y' || answer != 'n');

    do {
        cout << "s - статус заказа\nr - смена роли" << endl;
        cin >> action;

        if (action == 's') {
            clearConsole();
            cout << order->GetStatus() << endl;
        }
    } while (action != 'r');

    clearConsole();
    return 0;
}

int Admin_function(string filename, vector<Employee> emploees, AuditLog log)
{
    int action;
    unique_ptr<SystemAdministrator> adm = make_unique<SystemAdministrator>();

    string name;
    string surname;
    string patronymic;
    string role;
    string username;
    string password;

    do {
        clearConsole();
        cout << "1 - Добавить сотрудника\n2 - Добавить блюдо\n3 - Добавить продукт" << endl;
        cin >> action;

        if (action == 1) {
            adm->getEmployees(emploees, filename);
            cout << "Имя: ";
            cin >> name;
            cout << "Фамилия: ";
            cin >> surname;
            cout << "Отчество: ";
            cin >> patronymic;
            cout << "Роль: ";
            cin >> role;
            cout << "Логин: ";
            cin >> username;
            cout << "Пароль: ";
            cin >> password;

            adm->addEmployee(role, surname, name, patronymic, username, password, filename, emploees);
            log.addEntry("Админ добавил сотрудника");
        }

    } while (action != 0);

    return 0;
}

void CheckEmplFile(char* documentsPath, string filename, vector<Employee> employees) {
    if (documentsPath != nullptr) {
        // Проверка существования файла сотрудников
        ifstream file(filename);
        if (file.good()) {
            cout << "Файл сотрудников существует." << endl;

            //выгрузка сотрудников из файла в вектор
            ifstream inputFile(filename);
            if (inputFile.is_open()) {
                string line;
                while (getline(inputFile, line)) {
                    stringstream ss(line);
                    string role, lastName, firstName, patronymic, username, password;
                    if (ss >> role >> lastName >> firstName >> patronymic >> username >> password) {
                        employees.push_back({ role, lastName, firstName, patronymic, username, password });
                    }
                }
                inputFile.close();
            }
        }
        else {
            // Создание файла
            ofstream newFile(filename);
            if (newFile.is_open()) {
                newFile.close();
                cout << "Файл сотрудников создан." << endl;
                Employee admin{ "Admin", "Dergachev", "Daniil", "U", "fox", "fox" }; //добавляем админа 
                employees.push_back(admin); //добавляем в лист сотрудников
            }
            else {
                cout << "Не удалось создать файл" << endl;
            }
        }
    }
}

void CheckDishsFile(char* documentsPath, string filename, Menu menu) {
    if (documentsPath != nullptr) {
        // Проверка существования файла блюд
        ifstream file(filename);
        if (file.good()) {
            cout << "Файл блюд существует." << endl;

            //выгрузка блюд из файла в вектор
            ifstream inputFile(filename);
            if (inputFile.is_open()) {
                string line;
                while (getline(inputFile, line)) {
                    stringstream ss(line);
                    string id, name, price, quantity;
                    if (ss >> id >> name >> price >> quantity) {
                        menu.addToMenu(stoi(id), name, stod(price), stoi(quantity));
                    }
                }
                inputFile.close();
            }
        }
        else {
            // Создание файла
            ofstream newFile(filename);
            if (newFile.is_open()) {
                newFile.close();
                cout << "Файл блюд создан." << endl;
                
                menu.addToMenu(1, "Бургер", 499.99, 5);
                menu.addToMenu(2, "Пицца", 1200.99, 3);
                menu.addToMenu(3, "Салат", 399.99, 2);
                menu.addToMenu(4, "Суп", 350.99, 4);
                menu.addToMenu(5, "Стейк", 1200.99, 6);
                menu.addToMenu(6, "Рыба", 1500.99, 3);
                menu.addToMenu(7, "Паста", 850.99, 4);
                menu.addToMenu(8, "Картофель фри", 250.99, 5);
                menu.addToMenu(9, "Суши", 999.99, 7);
                menu.addToMenu(10, "Десерт", 450.99, 3);
            }
            else {
                cout << "Не удалось создать файл" << endl;
            }
        }
    }
}

int main()
{
    bool isLogin = false;
    setlocale(LC_ALL, "Russian");

    string role;
    string login;
    string password;

    Restaurant restaurant{1000000};
    
    Menu menu;
    AuditLog log;

    vector<Employee> employees;
    

    // Получение пути до папки "Документы" в Windows
    char* documentsPath;
    size_t len;
    _dupenv_s(&documentsPath, &len, "USERPROFILE");
    string filePath = documentsPath;
    
    filePath += "\\Documents\\employees.txt"; //добавляем к пути файл с сотрудниками
    CheckEmplFile(documentsPath, filePath, employees);

    filePath += "\\Documents\\dishes.txt"; //добавляем к пути файл с блюдами
    CheckDishsFile(documentsPath, filePath, menu);

    while (!isLogin) {
        cout << "Добро пожаловать в ресторан" << endl;
        cout << "Ваша роль: ";
        cin >> role;
        cout << "Ваш логин: ";
        cin >> login;
        cout << "Ваш пароль: ";
        cin >> password;

        if (login == "guest" && password == "guest") {
            Guest(isLogin, menu, restaurant);
            main();
        }
        else if (role == "admin") {
            for (const auto& employee : employees) {
                if (employee.username == login && employee.password == password) {
                    Admin_function(filePath, employees, log);
                    main();
                }
            }
        }
    }

    return 0;
}


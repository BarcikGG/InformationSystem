#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <filesystem>
#include <ctime>
#include "..\HashLib\HashPass.h"

using namespace std;

//метод для очистки консоли
void clearConsole() {
    system("cls");
}

// Класс блюда
class Product {
public:
    int id; //id продукта
    string name; //название продукта
    int price; //цена продукта (закупочная)

    //конструктор продукта
    Product(int _id, const string _name, int _price) : id(_id), name(_name), price(_price) {}
};

// Класс блюда
class Dish {
public:
    int id; //id блюда
    string name; //название блюда
    vector<string> craft; //рецепт
    int time; //время готовки
    int price; //цена блюда
    int quantity; //кол-во блюд в наличии

    //конструктор блюда
    Dish(int _id, const string _name, vector<string> _craft, int _time, int _quantity, int _price) : id(_id), name(_name), craft(_craft), time(_time), quantity(_quantity), price(_price) {}
};

// Класс ресторан
class Restaurant {
private:
    int balance; //баланс рестика

public:
    Restaurant(int initialBalance) : balance(initialBalance) {} //конструктор рестика

    //функция возвращающая баланс ресторана
    int getBalance() const {
        return balance;
    }

    //функция для пополнения баланса ресторана
    void deposit(int amount) {
        balance += amount; //пополняем баланс
    }

    //функция для списания средств со счета ресторана
    bool withdraw(int amount) {
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
    //конструктор меню
    Menu(vector<Dish> _dishs) : Dishs(_dishs) {}

    ////функция добавления блюда в меню
    //void addToMenu(int id, const string name, int price, int quantity) {
    //    //Dishs.emplace_back(id, name, price, quantity); //добавление блюда
    //}

    //функция проверки доступности блюда для заказа
    bool isAvailable(const string name, int quantity) {
        for (const auto& Dish : Dishs) { //циклом проходимся по всем позициям меню
            //проверяем, что конкретное блюдо в количество больше или равно запрашиваемому количеству
            if (Dish.name == name && Dish.quantity >= quantity) {
                return true; //возвращаем true если блюдо есть
            }
        }
        return false; //блюдо не доступно
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
    int GetPrice(int id) {
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
    void addItem(int id, string name, int price, int quantity) {
        //items.emplace_back(id, name, price, quantity); //добавление блюда
    }

    //вывод корзины в консоль
    void printBasket() const {
        cout << "Ваш заказ: " << endl;
        for (const auto& item : items) { //цикл проходящий по всем позиция корзины
            cout << "Блюдо: " << item.name << ", Количество: " << item.quantity << endl; //вывод каждого блюда
        }
    }

    //функция для подсчета стоимости всего заказа
    int Amount() {
        int amount = 0; //обнуляем стоимость
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
                    << employee.lastName << " "
                    << employee.firstName << " "
                    << employee.patronymic << " "
                    << employee.username << " "
                    << employee.password << " " << endl;
            }

            outputFile.close();
            cout << "Сотрудники успешно сохранены в файл." << endl;
        }
        else {
            cerr << "Не удалось открыть файл сотрудников для записи." << endl;
        }
    }

    void editEmployee(string username, string newRole, string newSurname, string newPassword, string filename, vector<Employee> employees) {
        bool found = false;

        // Найти сотрудника по имени пользователя
        for (auto& employee : employees) {
            if (employee.username == username) {
                // Обновить роль и пароль сотрудника
                employee.role = newRole;
                employee.lastName = newSurname;
                employee.password = newPassword;
                found = true;
                break;
            }
        }

        if (found) {
            ofstream outputFile(filename);

            if (outputFile.is_open()) {
                // Записать обновленные данные в файл
                for (const auto& employee : employees) {
                    outputFile
                        << employee.role << " "
                        << employee.lastName << " "
                        << employee.firstName << " "
                        << employee.patronymic << " "
                        << employee.username << " "
                        << employee.password << endl;
                }

                outputFile.close();
                cout << "Сотрудник успешно отредактирован и сохранен в файл" << endl;
            }
            else {
                cout << "Не удалось открыть файл сотрудников для записи" << endl;
            }
        }
        else {
            cout << "Сотрудник с логином " << username << " не найден" << endl;
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

    void addDish(vector<Dish>& dishes, Dish dish, string filename) {
        
        dishes.push_back(dish);

        ofstream outputFile(filename);
        if (outputFile.is_open()) {
            for (const auto& dish : dishes) {
                outputFile << dish.id << " "
                    << dish.name << " ";
                    
                    // Записываем вектор craft в файл
                    for (const auto& ingredient : dish.craft) {
                        outputFile << ingredient << " ";
                    }

                    outputFile << dish.time << " "
                    << dish.price << " "
                    << dish.quantity << endl;
            }
            outputFile.close();
            cout << "Блюдо успешно добавлено и сохранено в файл." << endl;

        }
        else {
            cout << "Не удалось открыть файл блюд для записи." << endl;
        }
    }

    void getDishes(vector<Dish> dishs, string filename) {
        ifstream inputFile(filename);
        if (inputFile.is_open()) {
            string line;
            while (getline(inputFile, line)) {
                stringstream ss(line);

                string id, name, time, price, quantity;
                if (ss >> id >> name) {
                    vector<string> craft;
                    string ingredient;
                    while (ss >> ingredient) {
                        craft.push_back(ingredient);
                    }
                    if (ss >> time >> price >> quantity) {
                        dishs.push_back({ stoi(id), name, craft, stoi(time), stoi(price), stoi(quantity) });
                    }
                }
            }
            inputFile.close();
        }
        else {
            cout << "Не удалось открыть файл блюд для чтения." << endl;
        }

        for (const auto& dish : dishs) {
            string ings;
            cout << "------------------------\n";
            cout << "ID: " << dish.id << endl;
            cout << "Название: " << dish.name << endl;

            for (const auto& ing : dish.craft) {
                ings += ing + ", ";
            }

            cout << "Рецепт: " << ings << endl;
            cout << "Время приготовления: " << dish.time << endl;
            cout << "Цена: " << dish.price << endl;
            cout << "Количество: " << dish.quantity << endl;
            cout << endl;
        }
    }

    void addProduct(int id, string name, int price, vector<Product> products, string filename) {
        Product product{ id, name, price };

        ofstream outputFile(filename);
        products.push_back(product);

        if (outputFile.is_open()) {
            for (const auto& product : products) {
                outputFile
                    << product.id << " "
                    << product.name << " "
                    << product.price << " " << endl;
            }

            outputFile.close();
            cout << "Продукты успешно сохранены в файл." << endl;
        }
        else {
            cerr << "Не удалось открыть файл продуктов для записи." << endl;
        }
    }

    void editProduct(string name, int newId, int newPrice, vector<Product> products, string fileProd) {
        bool found = false;

        // Найти продукт по ID
        for (auto& product : products) {
            if (product.name == name) {
                //обновляем id и цену продукта
                product.id = newId;
                product.price = newPrice;
                found = true;
                break;
            }
        }

        if (found) {
            ofstream outputFile(fileProd);

            if (outputFile.is_open()) {
                // Записать обновленные данные в файл
                for (const auto& product : products) {
                    outputFile
                        << product.id << " "
                        << product.name << " "
                        << product.price << endl;
                }

                outputFile.close();
                cout << "Продукт успешно отредактирован и сохранен в файл." << endl;
            }
            else {
                cout << "Не удалось открыть файл продуктов для записи." << endl;
            }
        }
        else {
            cout << "Продукт с названием: " << name << " не найден." << endl;
        }
    }

    void getProducts(vector<Product> products, string filename) {
        ifstream inputFile(filename);
        if (inputFile.is_open()) {
            string line;
            products.clear();
            while (getline(inputFile, line)) {
                stringstream ss(line);
                string id, name, price;
                if (ss >> id >> name >> price) {
                    products.push_back({ stoi(id), name, stoi(price) });
                }
            }
            inputFile.close();
        }
        cout << "Продукты" << endl;
        for (const auto& product : products) {
            cout << "------------------------\nID: " << product.id << endl;
            cout << "Название: " << product.name << endl;
            cout << "Цена: " << product.price << endl;
            cout << endl;
        }
    }

};

string currentDateTime() {
    time_t t = time(nullptr);
    tm now;
    localtime_s(&now, &t);

    char buffer[128];
    strftime(buffer, sizeof(buffer), "%m-%d-%Y %X", &now);
    return buffer;
}

// Класс журнала аудита
class AuditLog {
private:
    vector<string> entries;
    string pathLogs;

public:
    AuditLog(string _path) : pathLogs(_path) {}

    void addEntry(const string& entry) {
        string log = currentDateTime() + ": " + entry;
        entries.push_back(log);
        saveLogs(pathLogs);
    }

    void addOldLogs(const string& oldLog) {
        string log = oldLog;
        entries.push_back(log);
    }

    void printEntries() const {
        for (const auto& entry : entries) {
            cout << entry << endl;
        }
    }

    void saveLogs(string& filename) {
        ofstream outputFile(filename);

        if (outputFile.is_open()) {
            for (const auto& log : entries) {
                outputFile << log << " " << endl;
            }
            outputFile.close();
            cout << "Продукты успешно сохранены в файл." << endl;
        }
        else {
            cerr << "Не удалось открыть файл продуктов для записи." << endl;
        }
    }
};

class ProductRequest {
public:
    map<int, int> Product_map; // Ключ - идентификатор продукта, Значение - количество продукта
};

class ProductCraft {
public:
    map<int, vector<string>> Dish_craft; //map для приготовления блюда
};

// Класс складского
class Storekeeper {
    Product product;
    vector<Product> products;
public:
    Storekeeper(Product _product, vector<Product> _products) : product(_product), products(_products) {}

    ProductRequest createProductRequest(Restaurant& restaurant, ProductRequest request) {
        string name = "empty";
        int quantity = 0;

        cout << "Название продукта: ";
        cin >> name;

        for (const auto& product : products) 
        {
            if (product.name == name) {

                cout << "Кол-во продукта: ";
                cin >> quantity;

                if (product.price * quantity <= restaurant.getBalance()) {
                    restaurant.withdraw(product.price * quantity);
                    clearConsole();
                    //логика добавления в request.Product_map заказа (ключ - product.id, значение - quantity)
                    request.Product_map[product.id] = quantity;  // Добавляем заказ в Product_map
                    cout << "Заказ на " << product.name << " оформлен\nБаланс: " << restaurant.getBalance();
                }
                else {
                    clearConsole();
                    cout << "Недостаточно средств";
                }
            }
            else {
                cout << "Продукт не найден" << endl;
                cin >> name;
                //createProductRequest(restaurant);
            }
        }

        return request;
    }

    void trackInventory(const Menu& menu) {
        // Логика отслеживания количества продуктов на складе
    }
};

// Класс поставщика
class Supplier {
public:
    void processDishRequest(const ProductRequest& request, Menu& menu) {
        // Логика обработки заявки на продукты и отправки продуктов
    }
};

// Класс бухгалтера
class Accountant {
public:
    void viewDishRequests(const vector<ProductRequest>& requests) {
        // Логика просмотра всех отправленных заявок на продукты
    }

    void viewDeliveries(const vector<ProductRequest>& deliveries) {
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

//метод для работы с гостем
int Guest(Menu menu, Restaurant restaurant) {
    //isLogin = true; //переменная для определения статуса пользователя и управления циклом
    char answer; //ответ гостя по заказа (да/нет)
    char action; //действие гостя (просмотр статуса или смена роли)
    int status = 0; //статус заказа
    int guest_amount; //сумма которую заплатил гость

    unique_ptr<GuestOrderBasket> backet = make_unique<GuestOrderBasket>(); // создание умного указателя корзины
    unique_ptr<Order> order = make_unique<Order>(); // создание умного указателя заказа

    clearConsole();
    menu.GetMenu(); //выводим меню для гостя
    int id = 0; //id для ввода номера заказа

    do {
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

            cout << AvailableQuantity << endl;
        }
        else cout << DishName << endl;
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

int Admin_function(string& filename, string& fileDish, string& fileProd, vector<Employee>& employees, vector<Dish>& dishs, vector<Product>& products, AuditLog log)
{
    int action;
    unique_ptr<SystemAdministrator> adm = make_unique<SystemAdministrator>();

    string name;
    string surname;
    string patronymic;
    string role;
    string username;
    string password;

    int id, quantity, price, time;
    string ingredients;
    vector<string> craft;

    do {
        clearConsole();
        cout << "1 - Добавить сотрудника\n2 - Добавить блюдо\n3 - Добавить продукт" <<
            "\n5 - Изменить сотрудника\n6 - Изменить блюдо\n7 - Изменить продукт\n4 - Логи\n0 - Выход" << endl;
        cin >> action;

        if (action == 1) {
            adm->getEmployees(employees, filename);
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

            adm->addEmployee(role, surname, name, patronymic, username, HF(password), filename, employees);
            log.addEntry("Админ добавил сотрудника: " + surname + " " + name);
        }
        else if (action == 2) {
            adm->getDishes(dishs, fileDish);
            adm->getProducts(products, fileProd);
            cout << "Id: ";
            cin >> id;
            cout << "Название: ";
            cin >> name;
            cout << "Цена: ";
            cin >> price;
            cout << "Время готовки: ";
            cin >> time;
            cout << "Кол-во: ";
            cin >> quantity;
            
            cout << "Рецепт: ";
            cin.ignore(); // Очищаем символ новой строки из входного буфера
            getline(cin, ingredients);

            istringstream iss(ingredients); //поток ввода из строки (разделение строки на слова)
            string word; //инициализируем строку для занесения в нее слова

            while (iss >> word) {
                craft.push_back(word);
            }

            Dish new_dish{ id, name, craft, time, price, quantity };
            adm->addDish(dishs, new_dish, fileDish);
            log.addEntry("Админ добавил пункт меню: " + name);
        }
        else if (action == 3) {
            adm->getProducts(products, fileProd);
            cout << "ID: ";
            cin >> id;
            cout << "Название: ";
            cin >> name;
            cout << "Цена: ";
            cin >> price;

            adm->addProduct(id, name, price, products, fileProd);
            log.addEntry("Админ добавил продукт: " + name);
        }
        else if (action == 4) {
            string empty;
            log.printEntries();
            cout << "Введите любой символ для выхода" << endl;
            cin >> empty;
        }
        else if (action == 5) {
            adm->getEmployees(employees, filename);
            cout << "Введите логин сотрудника: " << endl;
            cin >> username;
            cout << "Новая роль: " << endl;
            cin >> role;
            cout << "Новая фамилия: " << endl;
            cin >> surname;
            cout << "Новый пароль: " << endl;
            cin >> password;

            adm->editEmployee(username, role, surname, HF(password), filename, employees);
            log.addEntry("Админ изменил сотрудника: " + surname);
        }
        else if (action == 6) {
            
        }
        else if (action == 7) {
            int newPrice;
            adm->getProducts(products, fileProd);
            cout << "Название продукта: " << endl;
            cin >> name;
            cout << "Новый id: " << endl;
            cin >> id;
            cout << "Новая цена: " << endl;
            cin >> newPrice;

            adm->editProduct(name, id, newPrice, products, fileProd);
            log.addEntry("Админ изменил продукт: " + name);
        }

    } while (action != 0);

    return 0;
}

vector<Employee> CheckEmplFile(char* documentsPath, string filename, vector<Employee> employees) {
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
            Employee admin{ "Admin", "Dergachev", "Daniil", "U", "fox", "fox" }; //добавляем админа 
            if (newFile.is_open()) {
                newFile << admin.role << " "
                    << admin.lastName << " "
                    << admin.firstName << " "
                    << admin.patronymic << " "
                    << admin.username << " "
                    << HF(admin.password) << " " << endl;
                newFile.close();
                cout << "Файл сотрудников создан." << endl;
                employees.push_back(admin); //добавляем в лист сотрудников
            }
            else {
                cout << "Не удалось создать файл" << endl;
            }
        }
    }
    return employees;
}

vector<Dish> CheckDishsFile(char* documentsPath, string filename, vector<Dish> dishs) {
    if (documentsPath != nullptr) {
        // Проверка существования файла блюд
        ifstream file(filename);
        if (file.good()) {
            cout << "Файл блюд существует." << endl;

            // выгрузка блюд из файла в вектор
            ifstream inputFile(filename);
            if (inputFile.is_open()) {
                string line;
                while (getline(inputFile, line)) {
                    stringstream ss(line);

                    string id, name, time, price, quantity;
                    if (ss >> id >> name) {
                        vector<string> craft;
                        string ingredient;
                        while (ss >> ingredient) {
                            craft.push_back(ingredient);
                        }
                        if (ss >> time >> price >> quantity) {
                            dishs.push_back({ stoi(id), name, craft, stoi(time), stoi(price), stoi(quantity) });
                        }
                    }
                }
                inputFile.close();
            }
        }
        else {
            // Создание файла
            ofstream newFile(filename);

            dishs.push_back({ 1, "Burger", {"bread", "cutlet", "sauce", "greens"}, 3, 499, 5});
            dishs.push_back({ 2, "Pizza", {"dough", "paste", "sausage", "cheese"}, 30, 1200, 3 });
            dishs.push_back({ 3, "Salat", {"greens", "meat", "tomato"}, 8, 399, 2 });
            
            if (newFile.is_open()) {
                for (const auto& dish : dishs) {
                    newFile << dish.id << " "
                        << dish.name << " ";

                    // Записываем вектор craft в файл
                    for (const auto& ingredient : dish.craft) {
                        newFile << ingredient << " ";
                    }

                    newFile << dish.time << " "
                        << dish.price << " "
                        << dish.quantity << endl;
                }
                newFile.close();
                cout << "Файл блюд создан." << endl;
            }
        }
    }
    return dishs;
}

vector<Product> CheckProductsFile(char* documentsPath, string filename, vector<Product> products) {
    if (documentsPath != nullptr) {
        // Проверка существования файла блюд
        ifstream file(filename);
        if (file.good()) {
            cout << "Файл продуктов существует." << endl;

            // выгрузка блюд из файла в вектор
            ifstream inputFile(filename);
            if (inputFile.is_open()) {
                string line;
                while (getline(inputFile, line)) {
                    stringstream ss(line);

                    string id, name, price;
                    if (ss >> id >> name) {
                        if (ss >> id >> name >> price) {
                            products.push_back({ stoi(id), name, stoi(price) });
                        }
                    }
                }
                inputFile.close();
            }
        }
        else {
            // Создание файла
            ofstream newFile(filename);

            products.push_back({ 1, "meat", 450});
            products.push_back({ 2, "ris", 50});
            products.push_back({ 3, "tomato", 180});

            if (newFile.is_open()) {
                for (const auto& product : products) {
                    newFile << product.id << " "
                        << product.name << " "
                        << product.price << endl;
                }
                newFile.close();
                cout << "Файл продуктов создан." << endl;
            }
        }
    }
    return products;
}

void CheckLogsFile(char* documentsPath, string filename, AuditLog log) {
    
    auto f = [&log](string oldLog) {
        log.addOldLogs(oldLog);
    };

    if (documentsPath != nullptr) {
        // Проверка существования файла логов
        ifstream file(filename);
        if (file.good()) {
            cout << "Файл логов существует." << endl;

            // выгрузка логов из файла в вектор
            ifstream inputFile(filename);
            if (inputFile.is_open()) {
                string line;
                while (getline(inputFile, line)) {
                    stringstream ss(line);

                    string current_log;
                    if (ss >> current_log) {
                        if (ss >> current_log) {
                            f(current_log);
                        }
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
                cout << "Файл логов создан." << endl;
            }
        }
    }
}

int checkRole(string role) {
    map<int, string> roles_map;

    roles_map.emplace(1, "Admin");
    roles_map.emplace(2, "Sklad");
    roles_map.emplace(3, "Seller");
    roles_map.emplace(4, "Buhgalter");
    roles_map.emplace(5, "Povar");
    roles_map.emplace(6, "Waiter");

    for (const auto& pair : roles_map) {
        if (pair.second == role) {
            return pair.first;  //возвращаем ключ, если значение совпадает
        }
    }

    return 0; //возвращаем 0, если роль не найдена
}

string Authorization(vector<Employee> employees, string& string_role) {
    clearConsole();

    string login;
    string password;

    cout << "Добро пожаловать в ресторан" << endl;
    cout << "Ваш логин: ";
    cin >> login;

    if (login == "guest") return "guest";
    else
    {
        cout << "Ваш пароль: ";
        cin >> password;
        string hashPass = HF(password);
        
        for (const auto& employee : employees) {
            if (employee.username == login && employee.password == hashPass) {
                string_role = employee.role;
                return "employee";
            }
        }
    }
}

int main()
{
    //bool isLogin = false;
    setlocale(LC_ALL, "Russian");

    Restaurant restaurant{1000000};

    vector<Employee> employees;
    vector<Dish> dishs;
    vector<Product> products;
    string string_role = "";

    // Получение пути до папки "Документы" в Windows
    char* documentsPath;
    size_t len;
    _dupenv_s(&documentsPath, &len, "USERPROFILE");
    string filePath = documentsPath;
    
    filePath += "\\Documents\\employees.txt"; //добавляем к пути файл с сотрудниками
    employees = CheckEmplFile(documentsPath, filePath, employees);

    string fileDish = documentsPath;
    fileDish += "\\Documents\\dishes.txt"; //добавляем к пути файл с блюдами
    dishs = CheckDishsFile(documentsPath, fileDish, dishs);

    string fileProd = documentsPath;
    fileProd += "\\Documents\\products.txt"; //добавляем к пути файл с продуктами
    products = CheckProductsFile(documentsPath, fileProd, products);

    string fileLog = documentsPath;
    fileLog += "\\Documents\\logs.txt"; //добавляем к пути файл с логами
    AuditLog log(fileLog);
    CheckLogsFile(documentsPath, fileLog, log);

    Menu menu(dishs);

    while (true) {
        if (Authorization(employees, string_role) == "guest") {
            Guest(menu, restaurant);
            Authorization(employees, string_role);
        }
        else {
            int role = checkRole(string_role);

            switch (role)
            {
            case 1:
                Admin_function(filePath, fileDish, fileProd, employees, dishs, products, log);
                Authorization(employees, string_role);
                break;
            case 2:
                //Admin_function(filePath, fileDish, fileProd, employees, dishs, products, log);
                Authorization(employees, string_role);
                break;
            default:
                cout << "Роль не найдена" << endl;
                break;
            }
        }
    }

    return 0;
}
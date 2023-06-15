#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <filesystem>
#include <ctime>

using namespace std;

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

public:
    void addEntry(const string& entry) {
        string log = currentDateTime() + entry;
        entries.push_back(log);
    }

    void printEntries() const {
        for (const auto& entry : entries) {
            cout << entry << endl;
        }
    }
};

class ProductRequest {
public:
    map<int, int> Dishs_map; // Ключ - идентификатор продукта, Значение - количество продукта
};

class ProductCraft {
public:
    map<int, vector<string>> Dish_craft; //map для приготовления блюда
};

// Класс складского
class Storekeeper {
public:
    ProductRequest createProductRequest(const Menu& menu) {
        ProductRequest request;

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
    int guest_amount; //сумма которую заплатил гость

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

int Admin_function(string filename, vector<Employee> emploees, vector<Dish> dishs, AuditLog log)
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
        cout << "1 - Добавить сотрудника\n2 - Добавить блюдо\n3 - Добавить продукт\n4 - Логи" << endl;
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
        else if (action == 2) {
            adm->getDishes(dishs, filename);
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
            adm->addDish(dishs, new_dish, filename);
            log.addEntry("Админ добавил пункт меню");
        }
        else if (action == 3) {
            
        }
        else if (action == 4) {
            log.printEntries();
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
                    << admin.password << " " << endl;
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

            dishs.push_back({ 1, "Бургер", {"булка", "котлета", "соус", "зелень"}, 3, 499, 5});
            dishs.push_back({ 2, "Пицца", {"тесто", "паста", "колбаса", "сыр"}, 30, 1200, 3 });
            dishs.push_back({ 3, "Салат", {"зелень", "мясо", "томаты"}, 8, 399, 2 });
            
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

int main()
{
    bool isLogin = false;
    setlocale(LC_ALL, "Russian");

    int role;
    string login;
    string password;

    Restaurant restaurant{1000000};
    
    AuditLog log;

    vector<Employee> employees;
    vector<Dish> dishs;

    // Получение пути до папки "Документы" в Windows
    char* documentsPath;
    size_t len;
    _dupenv_s(&documentsPath, &len, "USERPROFILE");
    string filePath = documentsPath;
    
    filePath += "\\Documents\\employees.txt"; //добавляем к пути файл с сотрудниками
    employees = CheckEmplFile(documentsPath, filePath, employees);

    filePath = documentsPath;
    filePath += "\\Documents\\dishes.txt"; //добавляем к пути файл с блюдами
    dishs = CheckDishsFile(documentsPath, filePath, dishs);

    Menu menu(dishs);

    while (!isLogin) {
        clearConsole();

        cout << "Добро пожаловать в ресторан" << endl;
        cout << "Ваш логин: ";
        cin >> login;
        cout << "Ваш пароль: ";
        cin >> password;

        if (login == "guest" && password == "guest") {
            Guest(isLogin, menu, restaurant);
            main();
        }
        else {
            for (const auto& employee : employees) {
                if (employee.username == login && employee.password == password) {
                    cout << "Ваша роль: \n1 - admin\n2 - sklad\n3 - povar\n4 - buhgalter\n5 - waiter\n6 - seller" << endl;
                    cin >> role;

                    switch (role)
                    {
                    case 1:
                        isLogin = true;
                        Admin_function(filePath, employees, dishs, log);
                        main();
                        break;
                    default:
                        cout << "Роль не найдена" << endl;
                        break;
                    }
                }
            }
        }
    }

    return 0;
}


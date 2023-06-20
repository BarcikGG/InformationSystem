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
    int craft; //рецепт
    int time; //время готовки
    int price; //цена блюда
    int quantity; //кол-во блюд в наличии

    //конструктор блюда
    Dish(int _id, const string _name, int _craft, int _time, int _price, int _quantity) : id(_id), name(_name), craft(_craft), time(_time), price(_price), quantity(_quantity) {}
};

class ProductRequest {
public:
    // Ключ - идентификатор продукта, Значение - количество продукта
    map<int, int> Product_map; 
};

class ProductStoreMap {
public:
    // Ключ - идентификатор продукта, Значение - количество продукта
    map<int, int> ProductStore_map; 
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

    //метод добавления блюд в вектор, сохранения их в файл и сохранения файла рецептов
    void addDish(vector<Dish>& dishs, Dish& dish, map<int, vector<string>>& Craft_map,string fileCraft, string filename) {
        
        dishs.push_back(dish);

        ofstream outputFile(filename);
        if (outputFile.is_open()) {
            for (const auto& dish : dishs) {
                outputFile << dish.id << " "
                    << dish.name << " "
                    << dish.craft << " "
                    << dish.time << " "
                    << dish.price << " "
                    << dish.quantity << endl;
            }
            outputFile.close();
            cout << "Блюдо успешно добавлено и сохранено в файл." << endl;
        }
        else {
            cout << "Не удалось открыть файл блюд для записи." << endl;
        }
        
        //добавление рецепта в файл рецептов
        ofstream outputFileCraft(fileCraft); // Открываем файл
        if (outputFileCraft.is_open()) {
            for (const auto& pair : Craft_map) {
                outputFileCraft << pair.first << " "; // Записываем ключ (число) в файл

                for (const auto& word : pair.second) {
                    outputFileCraft << word << " "; // Записываем каждое слово из вектора в файл
                }

                outputFileCraft << endl;
            }

            outputFileCraft.close();
            cout << "Данные успешно записаны в файл." << endl;
        }
        else {
            cout << "Не удалось открыть файл для записи." << endl;
        }
    }

    //метод изменения блюда
    void editDish(vector<Dish>& dishs, Dish& dish, map<int, vector<string>>& Craft_map, string fileCraft, string filename) {
        // Изменяем блюдо в векторе dishs
        for (auto& d : dishs) {
            if (d.id == dish.id) {
                d.name = dish.name;
                d.craft = dish.craft;
                d.time = dish.time;
                d.price = dish.price;
                d.quantity = dish.quantity;
                break;
            }
        }

        // Сохраняем изменения в файл блюд
        ofstream outputFile(filename);
        if (outputFile.is_open()) {
            for (const auto& d : dishs) {
                outputFile << d.id << " "
                    << d.name << " "
                    << d.craft << " "
                    << d.time << " "
                    << d.price << " "
                    << d.quantity << endl;
            }
            outputFile.close();
            cout << "Блюдо успешно изменено и сохранено в файл." << endl;
        }
        else {
            cout << "Не удалось открыть файл блюд для записи." << endl;
        }

        // Сохраняем изменения в файл рецептов
        ofstream outputFileCraft(fileCraft);
        if (outputFileCraft.is_open()) {
            for (const auto& pair : Craft_map) {
                outputFileCraft << pair.first << " ";

                for (const auto& word : pair.second) {
                    outputFileCraft << word << " ";
                }

                outputFileCraft << endl;
            }

            outputFileCraft.close();
            cout << "Рецепт успешно изменен и сохранен в файл." << endl;
        }
        else {
            cout << "Не удалось открыть файл рецептов для записи." << endl;
        }
    }

    void removeDish(int id, vector<Dish>& dishs, map<int, vector<string>>& Craft_map, string filename, string fileCraft) {
        // Удаляем блюдо из списка dishs
        for (auto dish = dishs.begin(); dish != dishs.end(); ) {
            if (dish->id == id) {
                dish = dishs.erase(dish);
            }
            else {
                dish++;
            }
        }

        // Удаляем рецепт из списка Craft_map
        Craft_map.erase(id);

        // Сохраняем изменения блюд в файл
        ofstream outputFile(filename);
        if (outputFile.is_open()) {
            for (const auto& dish : dishs) {
                outputFile << dish.id << " "
                    << dish.name << " "
                    << dish.craft << " "
                    << dish.time << " "
                    << dish.price << " "
                    << dish.quantity << endl;
            }
            outputFile.close();
            cout << "Блюдо успешно удалено из списка и сохранено в файл." << endl;
        }
        else {
            cout << "Не удалось открыть файл блюд для записи." << endl;
        }

        // Сохраняем изменения рецептов в файл
        ofstream outputFileCraft(fileCraft);
        if (outputFileCraft.is_open()) {
            for (const auto& pair : Craft_map) {
                outputFileCraft << pair.first << " "; // Записываем ключ в файл

                for (const auto& word : pair.second) {
                    outputFileCraft << word << " "; // Записываем каждое слово из вектора в файл
                }

                outputFileCraft << endl;
            }
            outputFileCraft.close();
            cout << "Рецепт успешно удален из списка и сохранен в файл" << endl;
        }
        else {
            cout << "Не удалось открыть файл рецептов для записи" << endl;
        }
    }

    void getDishes(vector<Dish>& dishs, string filename, map<int, vector<string>> Craft_map) {

        for (const auto& dish : dishs) {
            string ings;
            cout << "------------------------\n";
            cout << "ID: " << dish.id << endl;
            cout << "Название: " << dish.name << endl;


            for (const auto& ing : Craft_map[dish.id]) {
                ings += ing + ", ";
            }

            cout << "Рецепт: " << ings << endl;
            cout << "Время приготовления: " << dish.time << endl;
            cout << "Цена: " << dish.price << endl;
            cout << "Количество: " << dish.quantity << endl;
            cout << endl;
        }
    }

    void addProduct(int& id, string& name, int& price, vector<Product>& products, string filename) {
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

    void editProduct(Product& product, vector<Product>& products, string fileProd) {
        bool found = false;

        // Найти продукт по ID
        for (auto& p : products) {
            if (p.name == product.name) {
                //обновляем id и цену продукта
                p.id = product.id;
                p.price = product.price;
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
            cout << "Продукт с названием: " << product.name << " не найден." << endl;
        }
    }

    void removeProduct(int& id, vector<Product>& products, string filename) {
        // Удаляем продукт из вектора products
        for (auto check = products.begin(); check != products.end(); ) //проходимся по всему вектору.
        {
            if (check->id == id) { //сверяем найденный id с переданным id продукта.
                products.erase(check); //удаляем продукт
                break;
            }
            else {
                check++;
            }
        }

        // Сохраняем изменения в файл
        ofstream outputFile(filename);
        if (outputFile.is_open()) {
            for (const auto& product : products) {
                outputFile
                    << product.id << " "
                    << product.name << " "
                    << product.price << " " << endl;
            }

            outputFile.close();
            cout << "Продукт успешно удален и изменения сохранены в файл." << endl;
        }
        else {
            cerr << "Не удалось открыть файл продуктов для записи." << endl;
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
        cout << "-----------Продукты-----------" << endl;
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

// Класс складского
class Storekeeper {
public:
    int amount = 0;
    int amount_buy = 0;

    void getStore(vector<Product> products, string& fileStore)
    {
        ProductStoreMap product_map;
        ifstream file(fileStore);
        if (file.good()) {
            // выгрузка продуктов склада из файла в вектор
            ifstream inputFile(fileStore);
            if (inputFile.is_open()) {
                string line;
                while (getline(inputFile, line)) {
                    stringstream ss(line);

                    string id, quantity;
                    if (ss >> id >> quantity) {
                        product_map.ProductStore_map[stoi(id)] = { stoi(quantity) };
                    }
                }
                inputFile.close();
            }
        }

        for (const auto& pair : product_map.ProductStore_map) {
            int productId = pair.first;
            int quantity = pair.second;

            //поиск продукта по ID
            const auto& prod = find_if(products.begin(), products.end(), [productId](const Product& product) {
                return product.id == productId; //возвращает итератор, указывающий на найденный продукт или на конец вектора, если продукт не найден
            });

            // Проверка, найден ли продукт
            if (prod != products.end()) {
                const Product& product = *prod; //создаем объект продукта и передаем в него значение объекта
                cout << "Продукт: " << product.name << ", кол-во: " << quantity << endl;
            }
        }
    }

    //метод добавления заявки в файл
    void addToProductMapFile(string& fileRequest, map<int, int>& productMap) {
        ofstream outputFile(fileRequest, ios::app);  //открываем файл в режиме дополнения

        if (outputFile.is_open()) {
            for (const auto& pair : productMap) {
                outputFile << pair.first << " " << pair.second << endl;  // Записываем каждую пару Product_map в файл
            }

            outputFile.close();
            cout << "Новая пара Product_map успешно добавлена в файл" << endl;
        }
        else {
            cout << "Не удалось открыть файл для записи" << endl;
        }
    }


    void createProductRequest(vector<Product>& products, string& fileStore, ProductRequest& request, Restaurant& restaurant, AuditLog& log, string& fileRequest) {
        getStore(products, fileStore);
        string name;
        int quantity;
        amount = restaurant.getBalance();

        cout << "Название продукта: ";
        cin >> name;
        if (name != "exit") {

            for (const auto& product : products)
            {
                if (product.name == name) {

                    cout << "Кол-во продукта: ";
                    cin >> quantity;
                    
                    if (quantity > 0) {
                        amount_buy += product.price * quantity;
                        if (amount_buy <= amount) {
                            clearConsole();
                            //логика добавления в request.Product_map заказа (ключ - product.id, значение - quantity)
                            request.Product_map[product.id] = quantity;  // Добавляем заказ в Product_map
                            cout << "Заказ на " << product.name << " оформлен\nБаланс: " << amount << endl;
                            log.addEntry("Складовщик сделал заявку на закуп: " + product.name);
                            addToProductMapFile(fileRequest, request.Product_map);
                        }
                        else {
                            clearConsole();
                            cout << "Недостаточно средств";
                        }
                    }
                }
            }
        }
    }
};

// Класс поставщика
class Seller {
public:
    string answer;
    int amount = 0;

    void SendProducts(ProductStoreMap& productStore, ProductRequest& request, vector<Product>& products, Restaurant& restaurant, string& fileSent, string& fileStore, ProductStoreMap& product_map) {
        clearConsole();
        cout << "Ресторан заказывает: " << endl;

        for (const auto& pair : request.Product_map) {
            int productId = pair.first;
            int quantity = pair.second;

            //поиск продукта по ID
            const auto& prod = find_if(products.begin(), products.end(), [productId](const Product& product) {
                return product.id == productId; //возвращает итератор, указывающий на найденный продукт или на конец вектора, если продукт не найден
                });

            // Проверка, найден ли продукт
            if (prod != products.end()) {
                const Product& product = *prod; //создаем объект продукта и передаем в него значение объекта
                cout << "Продукт: " << product.name << ", кол-во: " << quantity << endl;
                amount += product.price * quantity;
            }
        }

        cout << "Подтверждаем отправку? y/n: ";
        cin >> answer;

        if (answer == "y")
        {
            restaurant.withdraw(amount);
            cout << "\nОплата прошла успешна" << endl;

            ofstream outputFile(fileSent, ios::app);  //открываем файл в режиме дополнения
            if (outputFile.is_open()) {
                for (const auto& pair : request.Product_map) {
                    outputFile << pair.first << " " << pair.second << endl;  // Записываем каждую пару Product_map в файл
                    
                    int previous = product_map.ProductStore_map[pair.first];
                    product_map.ProductStore_map[pair.first] = {previous + pair.second};
                }

                outputFile.close();
                cout << "Новая пара Product_map успешно добавлена в файл" << endl;
            }
            else {
                cout << "Не удалось открыть файл для записи" << endl;
            }

            ofstream outputFileProd(fileStore);  //открываем файл (store)
            if (outputFileProd.is_open()) {
                for (const auto& pair : productStore.ProductStore_map) {
                    outputFileProd << pair.first << " " << pair.second << endl;  // Записываем каждую пару Product_map в файл

                    int previous = productStore.ProductStore_map[pair.first];
                    productStore.ProductStore_map[pair.first] = { previous + pair.second };
                }

                outputFileProd.close();
            }
        }

    }
};

// Класс бухгалтера
class Accountant {
public:
    string exit;
    int allSellAmount = 0;
    int allOrdersAmount = 0;

    //вывод заказов за все время (получаем копию ProductRequest)
    void viewAllRequests(string& fileProdBuy, ProductRequest request, vector<Product>& products) {
        clearConsole();

        ifstream file(fileProdBuy);
        if (file.good()) {
            cout << "Файл продуктов на складе существует." << endl;

            // выгрузка блюд из файла в вектор
            ifstream inputFile(fileProdBuy);
            if (inputFile.is_open()) {
                string line;
                while (getline(inputFile, line)) {
                    stringstream ss(line);

                    string id, quantity;
                    if (ss >> id >> quantity) {
                        request.Product_map[stoi(id)] = { stoi(quantity) };
                    }
                }
                inputFile.close();
            }
        }

        cout << "Все заказы продуктов: " << endl;

        //циклом проходимся по копии map заказов
        for (const auto& pair : request.Product_map) {
            int productId = pair.first;
            int quantity = pair.second;

            //поиск продукта по ID
            const auto& prod = find_if(products.begin(), products.end(), [productId](const Product& product) {
                return product.id == productId; //возвращает итератор, указывающий на найденный продукт или на конец вектора, если продукт не найден
                });

            // Проверка, найден ли продукт
            if (prod != products.end()) {
                const Product& product = *prod; //создаем объект продукта и передаем в него значение объекта
                cout << "Продукт: " << product.name << ", кол-во: " << quantity << endl;
                allOrdersAmount += product.price * quantity;
            }
        }
        cout << "Всего заказано на: " << allOrdersAmount << endl;
    }

    void viewAllSends(string& fileSent, ProductRequest request, vector<Product>& products) {
        clearConsole();

        ifstream file(fileSent);
        if (file.good()) {
            cout << "Файл продуктов на складе существует." << endl;

            // выгрузка блюд из файла в вектор
            ifstream inputFile(fileSent);
            if (inputFile.is_open()) {
                string line;
                while (getline(inputFile, line)) {
                    stringstream ss(line);

                    string id, quantity;
                    if (ss >> id >> quantity) {
                        request.Product_map[stoi(id)] = { stoi(quantity) };
                    }
                }
                inputFile.close();
            }
        }

        cout << "Все заказы продуктов: " << endl;

        //циклом проходимся по копии map заказов
        for (const auto& pair : request.Product_map) {
            int productId = pair.first;
            int quantity = pair.second;

            //поиск продукта по ID
            const auto& prod = find_if(products.begin(), products.end(), [productId](const Product& product) {
                return product.id == productId; //возвращает итератор, указывающий на найденный продукт или на конец вектора, если продукт не найден
                });

            // Проверка, найден ли продукт
            if (prod != products.end()) {
                const Product& product = *prod; //создаем объект продукта и передаем в него значение объекта
                cout << "Продукт: " << product.name << ", кол-во: " << quantity << endl;
            }
        }
    }

    void viewFinReports(Restaurant& res) {
        int answer = 0;

        cout << "1 - Баланс рестика\n2 - Отчет продаж\n3 - Общие продажи " << endl;
        cin >> answer;

        switch (answer)
        {
        case 1:
            cout << "Баланс ресторана: " << res.getBalance() << endl;
            cout << "e - exit: ";
            cin >> exit;
            break;
        case 2:

            break;
        case 3:
            break;
        default:
            cout << "Неверное число" << endl;
            break;
        }
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

void Admin_function(string& filename, string& fileCraft, string& fileDish, string& fileProd, map<int, vector<string>> Craft_map, vector<Employee>& employees, vector<Dish>& dishs, vector<Product>& products, AuditLog& log, ProductStoreMap& storeMap)
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
            "\n5 - Изменить сотрудника\n6 - Изменить блюдо\n7 - Изменить продукт" <<
            "\n8 - удалить продукт\n4 - Логи\n0 - Выход" << endl;
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
            adm->getDishes(dishs, fileDish, Craft_map);
            cout << "Id: ";
            cin >> id;
            cout << "Название: ";
            cin.ignore();
            getline(cin, name);
            cout << "Цена: ";
            cin >> price;
            cout << "Время готовки: ";
            cin >> time;
            cout << "Кол-во: ";
            cin >> quantity;
            
            adm->getProducts(products, fileProd);
            cout << "Рецепт: ";
            cin.ignore(); // Очищаем символ новой строки из входного буфера
            getline(cin, ingredients);

            istringstream iss(ingredients); //поток ввода из строки (разделение строки на слова)
            string word; //инициализируем строку для занесения в нее слова

            while (iss >> word) {
                craft.push_back(word);
            }
            Craft_map[id] = craft;

            Dish new_dish{ id, name, id, time, price, quantity };
            adm->addDish(dishs, new_dish, Craft_map, fileCraft, fileDish);
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
            storeMap.ProductStore_map[id] = { 1 };
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
            vector<string> newCraft;
            adm->getDishes(dishs, fileDish, Craft_map);
            cout << "ID блюда: " << endl;
            cin >> id;
            cout << "Новое название: " << endl;
            cin >> name;
            cout << "Новая цена: " << endl;
            cin >> price;
            cout << "Новое время: " << endl;
            cin >> time;
            cout << "Новое кол-во: " << endl;
            cin >> quantity;

            adm->getProducts(products, fileProd);
            cout << "Новый рецепт: ";
            cin.ignore(); // Очищаем символ новой строки из входного буфера
            getline(cin, ingredients);

            istringstream iss(ingredients); //поток ввода из строки (разделение строки на слова)
            string word; //инициализируем строку для занесения в нее слова

            while (iss >> word) {
                newCraft.push_back(word);
            }

            Craft_map[id] = newCraft;

            Dish editedDish = {id, name, id, time, price, quantity};
            adm->editDish(dishs, editedDish, Craft_map, fileCraft, fileDish);
            log.addEntry("Админ изменил блюдо: " + name);
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

            Product editedProd = {id, name, newPrice};
            adm->editProduct(editedProd, products, fileProd);
            log.addEntry("Админ изменил продукт: " + name);
        }
        else if (action == 8) {
            string prodName;
            adm->getProducts(products, fileProd);
            cout << "ID продукта: ";
            cin >> id;

            for (const auto& prod : products) {
                if (prod.id == id) prodName = prod.name;
            }

            adm->removeProduct(id, products, fileProd);
            log.addEntry("Админ удалил продукт: " + prodName);
        }

    } while (action != 0);

}

void StoreKeeper_function(vector<Product>& products, string& fileStore, ProductRequest& request, Restaurant& restaurant, AuditLog& log, string fileRequest) 
{
    unique_ptr<Storekeeper> sklad = make_unique<Storekeeper>();
    int action;
    char empty;

    do 
    {
        clearConsole();
        cout << "1 - Посмотреть скалд\n2 - Добавить заявку" << endl;
        try {

            cin >> action;

            if (action == 1)
            {
                sklad->getStore(products, fileStore);
                cout << "\ne - для выхода" << endl;
                cin >> empty;

            }
            else if (action == 2)
            {
                sklad->createProductRequest(products, fileStore, request, restaurant, log, fileRequest);
                cout << "\ne - для выхода" << endl;
                cin >> empty;
            }
        }
        catch (exception ex) { cout << "Это не число" << endl; }

    } while (action != 0);
}

void Accountant_function(string& fileSells, string& fileProdBuys, ProductRequest request, vector<Product>& products, Restaurant restaurant) 
{
    unique_ptr<Accountant> acc = make_unique<Accountant>();
    int action;
    char empty;

    do
    {
        clearConsole();
        cout << "1 - Посмотреть все заявки\n2 - Посмотреть все поставки\n3 - Баланс" << endl;
        try {
            cin >> action;

            if (action == 1)
            {
                acc->viewAllRequests(fileProdBuys, request, products);
                cout << "\ne - для выхода" << endl;
                cin >> empty;

            }
            else if (action == 2)
            {
                acc->viewAllSends(fileSells, request, products);
                cout << "\ne - для выхода" << endl;
                cin >> empty;
            }
            else if (action == 3) 
            {
                acc->viewFinReports(restaurant);
            }
        }
        catch (exception ex) { cout << "Это не число" << endl; }
    } while (action != 0);
}

void CheckEmplFile(char* documentsPath, string filename, vector<Employee>& employees) {
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
}

void ReadCraft(const string& filename, map<int, vector<string>>& craft_map) {
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            stringstream ss(line);

            int number;
            ss >> number; // Считываем число из строки

            string word;
            vector<string> words;

            while (ss >> word) { // Считываем каждое слово из строки
                words.push_back(word);
            }

            craft_map[number] = words; // Добавляем пару (число, вектор слов) в map
        }

        inputFile.close();
        cout << "Данные успешно считаны из файла." << endl;
    }
    else {
        cout << "Не удалось открыть файл для чтения." << endl;
    }
}

void CheckDishsFile(char* documentsPath, string filename, string fileCraft, map<int, vector<string>>& craft_map, vector<Dish>& dishs) {
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

                    string id, name, id_craft, time, price, quantity;
                    if (ss >> id >> name >> id_craft >> time >> price >> quantity) {
                        dishs.push_back({ stoi(id), name, stoi(id_craft), stoi(time), stoi(price), stoi(quantity)});
                    }
                }
                inputFile.close();
            }
            ReadCraft(fileCraft, craft_map);
        }
        else {
            // Создание файла
            ofstream newFile(filename);

            dishs.push_back({ 1, "Burger", 1, 3, 499, 5});
            dishs.push_back({ 2, "Pizza", 2, 30, 1200, 3 });
            dishs.push_back({ 3, "Salat", 3, 8, 399, 2 });
            
            if (newFile.is_open()) {
                for (const auto& dish : dishs) {
                    newFile << dish.id << " "
                        << dish.name << " "
                        << dish.craft << " "
                        << dish.time << " "
                        << dish.price << " "
                        << dish.quantity << endl;
                }
                newFile.close();
                cout << "Файл блюд создан." << endl;
            }

            //запись в файл и map рецепта
            ofstream outputFile(fileCraft); // Открываем файл в режиме дополнения (append)
            craft_map[1] = {"Bread", "Meat", "Cheese", "Sauce", "Bread"};
            craft_map[2] = {"Dough", "Sausage", "Cheese", "Paste"};
            craft_map[3] = {"Tomato", "Meat", "Cheese", "Sauce"};

            if (outputFile.is_open()) {

                for (const auto& pair : craft_map) {
                    outputFile << pair.first << " "; // Записываем число в файл

                    for (const string& word : pair.second) {
                        outputFile << word << " " << endl; // Записываем каждое слово в файл, разделенное пробелом
                    }
                }

                outputFile << endl; // Переходим на новую строку
                outputFile.close();
                cout << "Данные успешно записаны в файл." << endl;
            }
        }
    }
}

void CheckProductsFile(char* documentsPath, string filename, vector<Product>& products) {
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
                    if (ss >> id >> name >> price) {
                        products.push_back({ stoi(id), name, stoi(price) });
                    }
                }
                inputFile.close();
            }
        }
        else {
            // Создание файла
            ofstream newFile(filename);

            products.push_back({ 1, "Meat", 450});
            products.push_back({ 2, "Ris", 50});
            products.push_back({ 3, "Tomato", 180});

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
}

void CheckLogsFile(char* documentsPath, string filename, AuditLog& log) {
    
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

void CheckProductsStoreFile(char* documentsPath, string filename, ProductStoreMap& storeMap) {
    if (documentsPath != nullptr) {
        // Проверка существования файла блюд
        ifstream file(filename);
        if (file.good()) {
            cout << "Файл продуктов на складе существует." << endl;

            // выгрузка блюд из файла в вектор
            ifstream inputFile(filename);
            if (inputFile.is_open()) {
                string line;
                while (getline(inputFile, line)) {
                    stringstream ss(line);

                    string id, quantity;
                    if (ss >> id >> quantity) {
                        storeMap.ProductStore_map[stoi(id)] = { stoi(quantity) };
                    }
                }
                inputFile.close();
            }
        }
        else {
            // Создание файла
            ofstream newFile(filename);

            storeMap.ProductStore_map[1] = {1};
            storeMap.ProductStore_map[2] = {1};
            storeMap.ProductStore_map[3] = {1};

            if (newFile.is_open()) {
                for (const auto& product : storeMap.ProductStore_map) {
                    newFile << product.first << " " << product.second << endl;
                }
                newFile.close();
                cout << "Файл продуктов создан." << endl;
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
        return "nobody";
    }
}

int main()
{
    //bool isLogin = false;
    setlocale(LC_ALL, "Russian");

    Restaurant restaurant{1000000};
    Seller seller;
    ProductRequest request;
    ProductStoreMap productStore;

    vector<Employee> employees;
    vector<Dish> dishs;
    vector<Product> products;
    string string_role = "";

    map<int, vector<string>> Dish_craft; //map для приготовления блюда

    // Получение пути до папки "Документы" в Windows
    char* documentsPath;
    size_t len;
    _dupenv_s(&documentsPath, &len, "USERPROFILE");
    string filePath = documentsPath;

    filePath += "\\Documents\\employees.txt"; //добавляем к пути файл с сотрудниками
    CheckEmplFile(documentsPath, filePath, employees);

    string fileDish = documentsPath; //полный путь к файлу блюд
    fileDish += "\\Documents\\dishes.txt"; //добавляем к пути файл с блюдами
    string fileCraft = documentsPath; //полный путь к файлу блюд
    fileCraft += "\\Documents\\crafts.txt"; //добавляем к пути файл с блюдами
    CheckDishsFile(documentsPath, fileDish, fileCraft, Dish_craft, dishs);

    string fileProd = documentsPath; //полный путь к файлу продуктов
    fileProd += "\\Documents\\products.txt"; //добавляем к пути файл с продуктами
    CheckProductsFile(documentsPath, fileProd, products);

    string fileLog = documentsPath; //полный путь к файлу логов
    fileLog += "\\Documents\\logs.txt"; //добавляем к пути файл с логами
    AuditLog log(fileLog);
    CheckLogsFile(documentsPath, fileLog, log);

    string fileRequest = documentsPath; //полный путь к файлу заявок
    fileRequest += "\\Documents\\product_buy.txt"; //добавляем к пути файл с заявками

    string fileSent = documentsPath; //полный путь к файлу отправленных продуктов
    fileSent += "\\Documents\\product_sent.txt"; //добавляем к пути файл с отправленными продуктами

    string fileStore = documentsPath; //полный путь к файлу склада
    fileStore += "\\Documents\\store.txt"; //добавляем к пути файл склада
    CheckProductsStoreFile(documentsPath, fileStore, productStore);

    Menu menu(dishs);

    while (true) {
        string authorization_result = Authorization(employees, string_role);
        if (authorization_result == "guest") {
            Guest(menu, restaurant);
            Authorization(employees, string_role);
        }
        else if (authorization_result == "employee") {
            int role = checkRole(string_role);

            switch (role)
            {
            case 1:
                Admin_function(filePath, fileCraft, fileDish, fileProd, Dish_craft, employees, dishs, products, log, productStore);
                Authorization(employees, string_role);
                break;
            case 2:
                StoreKeeper_function(products, fileStore, request, restaurant, log, fileRequest);
                Authorization(employees, string_role);
                break;
            case 3:
                seller.SendProducts(productStore, request, products, restaurant, fileSent, fileStore, productStore);
                Authorization(employees, string_role);
                break;
            case 4:
                Accountant_function(fileSent, fileRequest, request, products, restaurant);
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
#pragma once
class Restaurant {
private:
    int balance; //баланс ресторана

public:
    Restaurant(int _balance); //конструктор ресторана

    //функция возвращающая баланс ресторана
    int getBalance() const;

    //функция для пополнения баланса ресторана
    void deposit(int amount);

    //функция для списания средств со счета ресторана
    bool withdraw(int amount);
};



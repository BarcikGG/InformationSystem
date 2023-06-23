#include "Restaurant.h"

//определение конструктора ресторана
Restaurant::Restaurant(int _balance) : balance(_balance) {}

//определение функции возвращающей баланс ресторана
int Restaurant::getBalance() const {
    return balance;
}

//определение функции дл€ пополнени€ баланса ресторана
void Restaurant::deposit(int amount) {
    balance += amount; //пополн€ем баланс
}

//определение функции дл€ списани€ средств со счета ресторана
bool Restaurant::withdraw(int amount) {
    if (amount <= balance) { //провер€ем, что списываем меньше или сумму баланса ресторана
        balance -= amount; //списываем средства
        return true;  // ”спешное списание средств
    }
    return false;  // Ќедостаточно средств на балансе
}

#include "Restaurant.h"

//����������� ������������ ���������
Restaurant::Restaurant(int _balance) : balance(_balance) {}

//����������� ������� ������������ ������ ���������
int Restaurant::getBalance() const {
    return balance;
}

//����������� ������� ��� ���������� ������� ���������
void Restaurant::deposit(int amount) {
    balance += amount; //��������� ������
}

//����������� ������� ��� �������� ������� �� ����� ���������
bool Restaurant::withdraw(int amount) {
    if (amount <= balance) { //���������, ��� ��������� ������ ��� ����� ������� ���������
        balance -= amount; //��������� ��������
        return true;  // �������� �������� �������
    }
    return false;  // ������������ ������� �� �������
}

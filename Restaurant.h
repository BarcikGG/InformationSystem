#pragma once
class Restaurant {
private:
    int balance; //������ ���������

public:
    Restaurant(int _balance); //����������� ���������

    //������� ������������ ������ ���������
    int getBalance() const;

    //������� ��� ���������� ������� ���������
    void deposit(int amount);

    //������� ��� �������� ������� �� ����� ���������
    bool withdraw(int amount);
};



#include "account.h"
#include <iostream>
#include <locale>

void output(const Account& account)
{
	cout << "���: " << account.getPersonName() << endl;
	cout << "�����: " << account.getAddress() << endl;
	cout << "���������� ������: " << account.getPassportData() << endl;
	cout << "������: " << account.getBalance() << endl;
	cout << "���: " << account.getBIK() << endl;
	cout << "����� �����: " << account.getId() << endl;
	cout << "�����: " << account.getIncome() << endl;
	cout << "������: " << account.getExpenditure() << endl;

	switch (account.getStatus())
	{
	case Account::STATE::OK:
		cout << "���� ������������" << endl;
		break;
	case Account::STATE::FROZEN:
		cout << "���� ���������" << endl;
		break;
	case Account::STATE::CLOSED:
		cout << "���� ������" << endl;
		break;
	default:
		cout << "����������� ��������� �����" << endl;
		break;
	}

}

int main()
{
	setlocale(LC_ALL, "Russian");

	const string name = "�������� ������� �����������";
	const string address = "�������";
	const string passport = "32 28 1488; ������ �����-������ �������.";
	const unsigned int bik = 123456789;
	const unsigned int id = 54;

	cout << "�������� � ����� ������������� ��� � ����� �����" << endl;
	try {
		Account wrong_account = Account{ name, address, passport, -5, -9 };
	}
	catch (const invalid_argument& e) {
		cout << "������������ ��������: " << e.what() << endl;
	}

	try {
		Account test_account = Account{ name, address, passport, bik, id };
		output(test_account);
		cout << endl;

		test_account.deposit(10000);
		test_account.withdrawal(10);
		test_account.withdrawal(99999999);

		test_account.setPersonName("������ ����� ����������");
		test_account.setAddress("������");
		test_account.setPassportData("10 01 1337");
		output(test_account);

		Account test_account2(name, address, passport, 987654321, 45);

		test_account.transferTo(&test_account2, 300);
		test_account2.transferTo(&test_account, 250);

		cout << endl;
		output(test_account);
		cout << endl;
		output(test_account2);
	}
	catch (const invalid_argument& e) {
		cout << "��������� ������: " << e.what() << endl;
	}

	return 0;
}

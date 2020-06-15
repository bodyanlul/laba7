#pragma once

#include <string>
#include "revector.h"

using namespace std;

class Transaction;

class Account
{
public:
	Account(const string& _person, const string& _address, const string& _passport, int _bik, long long _id);

	/** ��������� ��� */
	void setPersonName(const string& new_name);

	/** ������� ��� */
	string getPersonName() const;

	/** ��������� ���������� ������ */
	void setPassportData(const string& new_passport);

	/** ������� ���������� ������ */
	string getPassportData() const;

	/** ��������� ������ */
	void setAddress(const string& new_address);

	/** ������� ������ */
	string getAddress() const;

	/** ������� ��������� */
	unsigned int getStatus() const;

	/** ������� ����� �������� (� ��������) */
	unsigned long long getIncome() const;

	/** ������� ����� �������� (� ��������) */
	unsigned long long getExpenditure() const;

	/** ������� ��� */
	unsigned int getBIK() const;

	/** ������� ������ ����� */
	unsigned long long getId() const;

	/** ������� �������� ������� ����� (� ��������) */
	unsigned long long getBalance() const;

	/** �������� ����������� ��������� �������� �� ������  */
	bool checkForActions() const;

	/** ���������� ���������
		  ����� ������ ���� � �������� */
	bool deposit(long long credit, bool create_transaction = true);

	/** ����� ��������
		  ����� ������ ���� � �������� */
	bool withdrawal(long long credit, bool create_transaction = true);

	ReVector<Transaction> getTransactions() const;

	void transferTo(Account* to, long long credit);

	enum STATE
	{
		OK,
		FROZEN,
		CLOSED
	};

private:
	string person,         // ���
		address,           // �����
		passport;          // ����������� ������
	unsigned int bik;      // ���
	unsigned long long id, // ����� �����
		income,            // ����� (� ��������)
		expenditure;       // ������ (� ��������)
	STATE status;          // ������. 0 - �����������, 1 - ���������, 2 - ������
	ReVector<Transaction> transactions;
};

class Transaction
{
public:
	Transaction(Account* to, long long credit);

	Transaction();

	enum TYPE
	{
		TRANSFER,
		WITHDRAWAL,
		DEPOSIT
	};

	Account* getDestination() const;

	long long getCredit() const;

	TYPE getType() const;

	bool checkSuccess() const;

private:
	Account* to{}, * from{};
	long long credit{};
	TYPE type;
	bool isSuccess{};
};
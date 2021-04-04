#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

enum AccountType
{
    Checking,
    Savings
};

class Account
{
public:
    Account(string cardNum, string pin, AccountType accountType, unsigned int newBalance)
        : _cardNum(cardNum), _pin(pin), _balances() 
    {
        _balances[accountType] = newBalance;
    }
    
    bool checkAccountTypeExists(AccountType accountType) const;
    bool updateBalance(AccountType accountType, unsigned int newBalance);
    unsigned getBalance(AccountType accountType) const;
    string getPin() const;

protected:
    string _cardNum;
    string _pin;
    unordered_map<AccountType, unsigned int, std::hash<int>> _balances; //Maps from account type (example checking, savings) to balance info
                                                        //For simplicity it is assumed that a account type doesnt exist if 
                                                        //it is not present in _balances 
};

class Bank
{
public:

    Bank() : _accounts() {}
    bool addAccount(string cardNum, string pin="1234", AccountType accountType=Checking, unsigned int balance=0);
    bool checkAccountExists(string cardNum);
    bool checkPinValid(string cardNum, string pin);
    bool checkAccountTypeExists(string cardNum, AccountType accountType);
    unsigned int getBalance(string cardNum, AccountType accountType);
    bool withdraw(string cardNum, AccountType accountType, unsigned int amount);
    bool deposit(string cardNum, AccountType accountType, unsigned int amount);

protected:
    unordered_map<string, Account> _accounts;//maps from card number to person's account  
};
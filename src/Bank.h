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

struct AccountInfo
{
    string accountNumber; //Not used for this exercise, but might be helpful in future
    AccountType accountType;
    unsigned int balance;
    unsigned int maxAllowedDeposit;

    void updateBalance(unsigned int newBalance) { balance = newBalance; }
};

struct Account
{
    string cardNum;
    string pin;
    unordered_map<AccountType, AccountInfo> _accounts; //Maps from account type (example checking, savings) to information about that account
                                                       //considering a person's account can have only one savings/checking account 
};

class Bank
{
public:
    bool addAccount(string cardNum, string pin="1234", AccountType accountType=Checking, unsigned int balance=0);
    bool updateAccount(string cardNum, string pin, AccountType accountType, unsigned int balance);

    bool checkAccountExists(string cardNum);
    bool checkPinValid(string cardNum, string pin);
    bool checkAccountTypeExists(string cardNum, AccountType accountType);
    unsigned int getBalance(string cardNum, AccountType accountType);
    bool withdraw(string cardNum, AccountType accountType, unsigned int amount);
    bool deposit(string cardNum, AccountType accountType, unsigned int amount);

    protected:
    unordered_map<string, Account> _accounts;//maps from card number to person's account  
};
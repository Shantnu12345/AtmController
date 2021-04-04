#pragma once
#include "Account.h"
#include <unordered_map>

//Fake Bank API that maintains all the accounts. The AtmController calls this API to validate if account/pin exists, update balance for withdraw/deposit, etc
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
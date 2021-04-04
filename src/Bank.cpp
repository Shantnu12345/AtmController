#include "Bank.h"

bool Bank::addAccount(string cardNum, string pin, AccountType accountType, unsigned int balance)
{
    if(_accounts.find(cardNum) == _accounts.end()) 
        _accounts.emplace(cardNum, Account(cardNum, pin)); //Make a new account if it doesnt exist before
    
    _accounts.at(cardNum).addAccountType(accountType, balance);
}

bool Bank::checkAccountExists(string cardNum)
{
    return _accounts.find(cardNum) != _accounts.end();
}

bool Bank::checkPinValid(string cardNum, string pin)
{
    return _accounts.at(cardNum).getPin() == pin;
}

bool Bank::checkAccountTypeExists(string cardNum, AccountType accountType)
{
    return _accounts.at(cardNum).checkAccountTypeExists(accountType); 
}

unsigned int Bank::getBalance(string cardNum, AccountType accountType)
{
    return _accounts.at(cardNum).getBalance(accountType);
}

bool Bank::withdraw(string cardNum, AccountType accountType, unsigned int amount)
{
    if(!_accounts.at(cardNum).checkAccountTypeExists(accountType))
        return false;

    unsigned int balance = _accounts.at(cardNum).getBalance(accountType);
    if(balance < amount)
        return false;

    _accounts.at(cardNum).updateBalance(accountType, balance - amount);
    return true;
}

bool Bank::deposit(string cardNum, AccountType accountType, unsigned int amount)
{
    cout<<"h1 ";
    if(!_accounts.at(cardNum).checkAccountTypeExists(accountType))
        return false;
    
    unsigned int balance = _accounts.at(cardNum).getBalance(accountType);
    cout<<balance;
    _accounts.at(cardNum).updateBalance(accountType, balance + amount);
    return true;
}

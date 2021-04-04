#include "Bank.h"

bool Account::updateBalance(AccountType accountType, unsigned int newBalance) 
{
    if(!checkAccountTypeExists(accountType))
        return false;

    _balances[accountType] = newBalance;
    return true;
}

bool Account::checkAccountTypeExists(AccountType accountType) const
{
    return _balances.find(accountType) != _balances.end();
}

unsigned int Account::getBalance(AccountType accountType) const
{
    return _balances[accountType];
}

string Account::getPin() const
{
    return _pin;
}

bool Bank::addAccount(string cardNum, string pin, AccountType accountType, unsigned int balance)
{
    _accounts[cardNum] = Account(cardNum, pin, accountType, balance);
}

bool Bank::checkAccountExists(string cardNum)
{
    return _accounts.find(cardNum) != _accounts.end();
}

bool Bank::checkPinValid(string cardNum, string pin)
{
    return _accounts[cardNum].getPin() == pin;
}

bool Bank::checkAccountTypeExists(string cardNum, AccountType accountType)
{
    return _accounts[cardNum].checkAccountTypeExists(accountType); 
}

unsigned int Bank::getBalance(string cardNum, AccountType accountType)
{
    return _accounts[cardNum].getBalance(accountType);
}

bool Bank::withdraw(string cardNum, AccountType accountType, unsigned int amount)
{
    if(!_accounts[cardNum].checkAccountTypeExists(accountType))
        return false;

    unsigned int balance = _accounts[cardNum].getBalance(accountType);
    if(balance < amount)
        return false;

    _accounts[cardNum].updateBalance(accountType, balance - amount);
    return true;
}

bool Bank::deposit(string cardNum, AccountType accountType, unsigned int amount)
{
    if(!_accounts[cardNum].checkAccountTypeExists(accountType))
        return false;
    
    unsigned int balance = _accounts[cardNum].getBalance(accountType);
    _accounts[cardNum].updateBalance(accountType, balance + amount);
    return true;
}

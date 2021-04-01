#include "Bank.h"

Bank::Bank() : _accounts() {}

bool Bank::checkAccount(string cardNum)
{
    return _accounts.find(cardNum) != _accounts.end();
}

bool Bank::addAccount(string cardNum, string pin, AccountType accountType, unsigned int balance)
{

}

bool Bank::updateAccount(string cardNum, string pin, AccountType accountType, unsigned int balance)
{

}

bool Bank::checkPin(string cardNum, string pin)
{

}

bool checkAccountType(string cardNum, AccountType accountType)
{

    return _accounts[cardNum]._accounts.find(accountType) != 
}

unsigned int Bank::getBalance(string cardNum, AccountType accountType)
{

}

bool Bank::withdraw(string cardNum, AccountType accountType, unsigned int amount)
{

}

bool Bank::deposit(string cardNum, AccountType accountType, unsigned int amount)
{

}

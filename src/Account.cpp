#include "Account.h"

inline string toString(AccountType accountType);

bool Account::addAccountType(AccountType accountType, unsigned int newBalance) 
{
    _balances[toString(accountType)] = newBalance;
    return true;
}

bool Account::checkAccountTypeExists(AccountType accountType) const
{
    return _balances.find(toString(accountType)) != _balances.end();
}

bool Account::updateBalance(AccountType accountType, unsigned int newBalance) 
{
  cout<<" h2 ";
    if(!checkAccountTypeExists(accountType))
        return false;

  cout<<newBalance;
    _balances[toString(accountType)] = newBalance;
  cout<<" h3 ";

    return true;
}

//Make sure to check account exists before calling this function
unsigned int Account::getBalance(AccountType accountType) const
{
    if(!checkAccountTypeExists(accountType))
        return 0;

    return _balances.at(toString(accountType));
}

string Account::getPin() const
{
    return _pin;
}

inline string toString(AccountType accountType)
{
  return accountType==Checking ? "Checking":"Savings";
}

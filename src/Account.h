#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

enum AccountType
{
    Checking,
    Savings
};


//Dummy Account class to store information about about the customer's account
class Account
{
public:
    Account(string cardNum, string pin) : _cardNum(cardNum), _pin(pin), _balances() {}
    bool addAccountType(AccountType accountType, unsigned int newBalance);
    bool checkAccountTypeExists(AccountType accountType) const;
    bool updateBalance(AccountType accountType, unsigned int newBalance);
    unsigned getBalance(AccountType accountType) const;
    string getPin() const;

protected:
    string _cardNum;
    string _pin;
    unordered_map<string, unsigned int> _balances; //Maps from account type (example checking, savings) to balance info
                                                   //For simplicity it is assumed that a account type doesnt exist if 
                                                   //it is not present in _balances
};

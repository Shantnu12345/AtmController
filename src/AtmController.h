#pragma once
#include <iostream>
#include <string>
#include "Bank.h"

using namespace std;

enum Action
{
    ViewBalance,
    Deposit,
    Withdraw,
    EndSession
};

struct CurrentSessionData
{
    string cardNum; 
    AccountType accountType;
    CurrentSessionData(string num="", AccountType type=Checking) //Account by default is checkin
        : cardNum(num), accountType(type) {}

    void clear() 
    {
        cardNum.clear();
        accountType = Checking; //reset to default
    }
};

struct Result
{
    string str;
    bool success;
    Result(string str="", bool success=false) : str(str), success(success) {}
};

class AtmController
{

public:
    AtmController(Bank const& bank);

    bool swipe(string cardNum);
    bool validatePin(string pin);
    bool selectAccount(AccountType accountType);
    Result accountAction(Action action, unsigned int amount=0); //Currently Supported actions: 
                                                                //ViewBalance, Deposit, Withdraw, End session

protected:
    Bank               _bank; 
    unsigned int       _cashBinAmount; //Current amount in the ATM
    CurrentSessionData _currSession;
};



#include "AtmController.h"

const unsigned int DEFAULT_CASH_BIN_AMOUNT = 100000; //dollars
const unsigned int MAX_WITHDRAW_LIMIT      = 2000;   //dollars
const unsigned int MAX_DEPOSIT_LIMIT       = 2000;   //dollars

AtmController::AtmController(Bank const& bank) 
    :_bank(bank), _cashBinAmount(DEFAULT_CASH_BIN_AMOUNT), _currSession() {}


bool AtmController::swipe(string cardNum)
{   
    if(_bank.checkAccountExists(cardNum))
    {
        _currSession.cardNum = cardNum;
        return true;
    }

    return false;
}

bool AtmController::validatePin(string pin)
{   
    if(_bank.checkPinValid(_currSession.cardNum, pin))
        return true;

    return false;
}

bool AtmController::selectAccount(AccountType accountType)
{
    if(_bank.checkAccountTypeExists(_currSession.cardNum, accountType))
    {
        _currSession.accountType = accountType;
        return true;
    }
    return false;
}

Result AtmController::accountAction(Action action, unsigned int amount)
{
    Result res;
    switch (action)
    {
    case ViewBalance:
        res.str = "Your balance is:" + to_string(_bank.getBalance(_currSession.cardNum, _currSession.accountType));
        res.success = true;
        break;

    case Withdraw:
        if(_bank.getBalance(_currSession.cardNum, _currSession.accountType) < amount)
        {
            res.str = "Insufficient account balance. Please enter a lower amount to withdraw";
            res.success = false;            
            break;
        }
        
        if(amount > _cashBinAmount)
        {
            res.str = "Insufficient cash in the atm's cash bin. Please enter a lower amount to withdraw";
            res.success = false;            
            break;
        }
        
        if(amount > MAX_WITHDRAW_LIMIT)
        {
            res.str = "Enter amount is greater than daily withdraw limit. Please enter a lower amount to withdraw";
            res.success = false;            
            break;
        }

        if(_bank.withdraw(_currSession.cardNum, _currSession.accountType, amount))
        {
            res.str = "Withdraw success. Please collect your cash. New amount in the account is " 
                + to_string(_bank.getBalance(_currSession.cardNum, _currSession.accountType));
            res.success = true;
        }
        else
        {
            res.str = "Withdraw Failure!!!"; 
            res.success = false;
        }
        

        break;

    case Deposit:
        if(amount > MAX_DEPOSIT_LIMIT)
        {
            res.str = "Amount is greater than the max deposit limit.";
            res.success = false;            
            break;
        }

        if(_bank.deposit(_currSession.cardNum, _currSession.accountType, amount))
        {
            res.str = "Deposit success. New amount in the account is " 
                + to_string(_bank.getBalance(_currSession.cardNum, _currSession.accountType));
            res.success = true;
        }
        else
        {
            res.str = "Deposit Failure!!!"; 
            res.success = false;
        }
        break;

    default:
        break;
    }

    return res;
}

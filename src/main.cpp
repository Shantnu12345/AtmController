#include <vector>
#include "AtmController.h"

struct ActionAmount
{
    Action action;
    unsigned int amount;
    ActionAmount(Action action, unsigned int amount=0)
        : action(action), amount(amount) {}
};

//Function to test the class functionality
void runSession(AtmController controller, 
                string cardNum, 
                string pin, 
                AccountType accountType, 
                vector<ActionAmount> const& actionsList)
{
    cout<<"Welcome dear customer. Please swipe your card."<<endl;
    bool success = controller.swipe(cardNum);
    if(!success)
    {
        cout<<"Invalid account number."<<endl;
        return;
    }

    cout<<"Swipe success. Please enter pin now."<<endl;
    success = controller.validatePin(pin);
    if(!success)
    {
        cout<<"Invalid pin. "<<endl;
        return;
    }

    cout<<"Pin success. Please select account type (Checking / Savings)"<<endl;
    success = controller.selectAccount(accountType);
    if(!success)
    {
        cout<<"Invalid account type selected."<<endl;
        return;
    }

    //Finally, perform all the actions from the action list: Checkbalance, Withdraw, Deposit, Exit session
    for(auto const& action:actionsList)
    {
        if(action.action==EndSession)
            break;

        Result res = controller.accountAction(action.action, action.amount);
        cout<<res.str<<endl;
    }

    cout<<"Thank you dear customer. Have a wonderful day"<<endl;

}

int main()
{
    //Test 1
    Bank emptyBank;
    AtmController emptyAtm(emptyBank);
    vector<ActionAmount> actionsList = {ViewBalance, EndSession};
    runSession(emptyAtm, "123456", "123", Savings, actionsList);

    //Test2
    
}
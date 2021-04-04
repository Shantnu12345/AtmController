#include <vector>
#include "AtmController.h"

// An action item is made of an action (example view balance, withdraw, 
// deposit, etc) and an associated amount (if any).
struct ActionItem
{
    Action action;
    unsigned int amount;
    ActionItem(Action action, unsigned int amount=0)
        : action(action), amount(amount) {}
};

//Function to test the class functionality
void runSession(AtmController controller, 
                string cardNum, 
                string pin, 
                AccountType accountType, 
                vector<ActionItem> const& actionsList)
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
    //Test 0
    cout<<"====================Test0========================"<<endl;
    Bank emptyBank;
    AtmController emptyAtm(emptyBank);
    vector<ActionItem> actionsList = { ActionItem(ViewBalance), ActionItem(EndSession) };
    runSession(emptyAtm, "123456", "123", Savings, actionsList);

    cout<<endl<<"====================Test1========================"<<endl;
    //Test1
    Bank testBank1;
    testBank1.addAccount("982567", "456", Checking, 10000);
    testBank1.addAccount("142567", "643", Checking, 20000);
    AtmController testAtm1(testBank1);
    actionsList = { ActionItem(ViewBalance), ActionItem(Deposit, 1000), ActionItem(EndSession) };
    runSession(testAtm1, "982567", "456", Checking, actionsList);
}
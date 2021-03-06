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
void runSession(AtmController & controller, 
                string cardNum, 
                string pin, 
                AccountType accountType, 
                vector<ActionItem> const& actionItems)
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
    for(auto const& action:actionItems)
    {
        Result res = controller.accountAction(action.action, action.amount);
        cout<<res.str<<endl;
        if(action.action==EndSession)
            break;
    }

}

int main()
{
    Bank testBank;
    testBank.addAccount("982567", "456", Checking, 10000);
    testBank.addAccount("142567", "643", Checking, 20000);
    AtmController testAtm(testBank);
    
    cout<<"====================Test0 - No account========================"<<endl;
    vector<ActionItem> actionItems = { ActionItem(ViewBalance), ActionItem(EndSession) };
    runSession(testAtm, "123456", "123", Savings, actionItems);

    cout<<endl<<"====================Test1 - Incorrect pin========================"<<endl;
    actionItems = { ActionItem(ViewBalance), ActionItem(EndSession) };
    runSession(testAtm, "982567", "454", Savings, actionItems);

    cout<<endl<<"====================Test2 - Incorrect account type chosen ========================"<<endl;
    actionItems = { ActionItem(ViewBalance), ActionItem(Deposit, 1000), ActionItem(EndSession) };
    runSession(testAtm, "982567", "456", Savings, actionItems);

    cout<<endl<<"====================Test3 - ViewBalance/Deposit========================"<<endl;
    actionItems = { ActionItem(ViewBalance), ActionItem(Deposit, 1000), ActionItem(EndSession) };
    runSession(testAtm, "142567", "643", Checking, actionItems);

    cout<<endl<<"====================Test4 - ViewBalance/Withdraw ========================"<<endl;
    actionItems = { ActionItem(ViewBalance), ActionItem(Withdraw, 2000), ActionItem(EndSession) };
    runSession(testAtm, "142567", "643", Checking, actionItems);


}
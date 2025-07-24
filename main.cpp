/*

--------------------------------------------------- 📄 ATM Project Description ---------------------------------------------------

- 📌 **Overview:**

This project is a console-based ATM system implemented in C++. It simulates basic ATM functionalities, allowing users to log in and perform standard banking operations.

- ✨ **Key Features:**

* **Login System:** Users must enter an account number and PIN to access the system.
* **Quick Withdraw:** Allows withdrawing fixed amounts quickly (e.g., 20, 50, 100, etc.).
* **Normal Withdraw:** Users can withdraw any custom amount that is a multiple of 5 and within their balance.
* **Deposit:** Users can deposit a custom amount into their account.
* **Check Balance:** Displays the current balance of the logged-in user.
* **Logout:** Option to securely log out from the system with confirmation.

- ⚙️ **Technical Details:**

* Uses `vector` to manage client data loaded from a text file (`Clients.txt`).
* Transactions update the client data and reflect changes in the file.
* Modular design with separate files and utility/helper functions to keep the code organized and clean.
* Enum-based menu options for better readability and maintainability.

- 📈 **Future Improvements:**

* Improve file management by using classes and serialization.
* Add logging to track user actions.
* Support multiple languages (localization).
* Enhance security by encrypting sensitive data like PINs.
* Add change client password feature to allow client change the current password.
* Use database to mange clients data inhsted of file.

- ✅ **Conclusion**:

The project demonstrates solid fundamentals in C++, good code organization, and practical handling of basic banking transactions. It’s a great foundation to build more advanced features in the future.

*/

#include"Utility.cpp"
#include"Features.h"
using namespace std;



Client mainClient;


const string clientsFilePath        = "Clients.txt";
const string delimiterInFile = "#//#";


vector<Client> mainClientsVector = Utility::loadClientsFileToVector(clientsFilePath , delimiterInFile);



enum MainMenuOptions 
{
    Quick_Withdraw    = 1 ,
    Normal_Withdraw       ,
    Deposit               ,
    Check_Balance         ,
    Update_My_Information ,
    Pay_To_Friend         ,
    Display_Transactions_History ,
    Display_Pays_History  ,
    Logout                  
};

MainMenuOptions mainOption;



void MainMenuFeatures::quickWithdraw()
{
    Utility::displayHeaderScreen("Quick Withdraw Screen");

    Utility::displayMenuList("\t\t\t\t\t[1] 20\t\t[2] 50\n\n\t\t\t\t\t[3] 100\t\t[4] 200\n\n\t\t\t\t\t[5] 400\t\t[6] 600\n\n\t\t\t\t\t[7] 800\t\t[8] 1000");

    Utility::displayClientBalance(mainClient);

    short quickAmounts[] = {20 , 50 , 100 , 200 , 400 , 600 , 800 , 1000};

    size_t size = sizeof(quickAmounts) / sizeof(short);

    short amountIndex = UserInput::readNumberInRange("\nChoose What Do You Want To Do? [1 to "+ to_string(size) + "]"  , 1 , 8);

    long double withdrawAmount = quickAmounts[amountIndex - 1];

    while (withdrawAmount > mainClient.balance)
    {
        cout << "\n\nCan NOT Perform This Transaction\n\n";
        amountIndex = UserInput::readNumberInRange("\nChoose What Do You Want To Do? [1 to "+ to_string(size) + "]"  , 1 , 8);
        withdrawAmount = quickAmounts[amountIndex - 1];
    }

    bool confirmWithdrawTransaction = UserInput::readYesNoAsBool("\nAre You Sure To Perform This Transaction?\n");

    if(confirmWithdrawTransaction)
    {
        if(Utility::performWithdrawDepositTransactionInClientsFile(mainClient , withdrawAmount , mainClientsVector , clientsFilePath , delimiterInFile , TransactionType::Withdraw_Transaction))   
        {
            TransactionStruct quickWithdrawTransaction{TransactionType::Withdraw_Transaction , withdrawAmount};
            Utility::loadTransactionRecordToFile(quickWithdrawTransaction , mainClient.accountNumber , delimiterInFile);
            cout << "\nTransaction Done Successifuly.\n";
        }
        else
            cout << "\nCan NOT Perform This Transaction\n\n";

        Utility::displayClientBalance(mainClient);
    }

}
void MainMenuFeatures::normalWithdraw()
{
    Utility::displayHeaderScreen("Normal Withdraw Screen");

    long double withdrawAmount = Utility::readTransactionAmount(mainClient , TransactionType::Withdraw_Transaction , "\nPlease Enter Withdraw Amount Multiple To 5's" , "\nError! You Enterd Invalid Withdraw Amount [The Amount Exceeds Your Balance].\n");

    bool confirmWithdrawTransaction = UserInput::readYesNoAsBool("\nAre You Sure To Perform This Transaction?\n");

    if(confirmWithdrawTransaction)
    {
        if(Utility::performWithdrawDepositTransactionInClientsFile(mainClient , withdrawAmount , mainClientsVector , clientsFilePath , delimiterInFile , TransactionType ::Withdraw_Transaction))   
        {
            TransactionStruct withdrawTransaction{TransactionType::Withdraw_Transaction , withdrawAmount};
            Utility::loadTransactionRecordToFile(withdrawTransaction , mainClient.accountNumber , delimiterInFile);
            cout << "\nTransaction Done Successifuly.\n";
        }

        else
            cout << "\nCan NOT Perform This Transaction\n\n";

        Utility::displayClientBalance(mainClient);
    }
}
void MainMenuFeatures::Deposit()
{
    Utility::displayHeaderScreen("Deposite Screen");

    long double depositAmount =Utility::readTransactionAmount(mainClient , TransactionType::Deposit_Transaction , "\nPlease Enter Deposit Amount");

    bool confirmDepsitTransaction = UserInput::readYesNoAsBool("\nAre You Sure To Perform This Transaction?\n");

    if(confirmDepsitTransaction)
    {
        if(Utility::performWithdrawDepositTransactionInClientsFile(mainClient , depositAmount , mainClientsVector , clientsFilePath , delimiterInFile , TransactionType::Deposit_Transaction))
        {
            TransactionStruct depositTransaction{TransactionType::Deposit_Transaction , depositAmount};
            Utility::loadTransactionRecordToFile(depositTransaction , mainClient.accountNumber , delimiterInFile);            
            cout << "\nTransaction Done Successifuly.\n";
        }   
        else
            cout << "\nCan NOT Perform This Transaction\n\n";

        Utility::displayClientBalance(mainClient);        
    }


}
void MainMenuFeatures::checkBalance()
{
    Utility::displayHeaderScreen("Check Balance Screen");

    Utility::displayClientBalance(mainClient);
}
UpdateOptions updateOption;
void preformUpdateOptoin(const UpdateOptions& updateOption)
{
        
    if(updateOption == UpdateOptions::Go_Back_To_Main_Menu)
        return;
    
    mainClientsVector = Utility::updateClientInVector(mainClientsVector , mainClient , updateOption);

    if(Utility::loadClientsVectorToFile(mainClientsVector , clientsFilePath , delimiterInFile))
        cout << "\nUpdated Successfuly\n";
    else
        cout << "\nSomthing Went Wrong: Can NOT Update This Client\n";

    UserInput::clickOnAnyKey("\n\nClick On Any key To Go Back To Main Menu Screen...");

}
void MainMenuFeatures::updateClientMenu()
{
    bool backToMainMenuConfirm = false;
    do
    {
        Utility::displayHeaderScreen("Update My Informition Screen");

        Utility::displayMenuList("[1] Update PIN\n\n[2] Update Name\n\n[3] Update Address\n\n[4] Update Phone Number\n\n[5] Go Back To Main Menue");

        updateOption = UserInput::readOptionNumber<UpdateOptions>("\nChoose What Do You Want To Do? [1 to 5]? ");

        UserInput::clearTerminalScreen();

        preformUpdateOptoin(updateOption);

        UserInput::clearTerminalScreen();

        if(updateOption == UpdateOptions::Go_Back_To_Main_Menu)
        {
            backToMainMenuConfirm = UserInput::readYesNoAsBool("\nAre You Soure You Want To Go Back To Main Menu?\n");
            if(!backToMainMenuConfirm)
                UserInput::clearTerminalScreen();
        }

    } while (!backToMainMenuConfirm);

}
void MainMenuFeatures::payToFriend()
{

    Utility::displayHeaderScreen("Pay To Friend Screen");

    string receiverAccountNumber = Utility::readAccountNumber("Please Enter Your Friend Account Number Here: " , mainClientsVector , false);

    long double amount =  Utility::readTransactionAmount(mainClient , TransactionType::Withdraw_Transaction , "Please Enter Amount To Send Here" ,  "\nError! You Enterd Invalid Send Amount [The Amount Exceeds Your Balance].\n");

    Client receiverClient = Utility::getClientByAccountNumber(receiverAccountNumber , mainClientsVector);

   Utility::displayClientCard("Send [" + to_string(amount) + "] To The Following Client :" , receiverClient , false);

   bool payConfirm = UserInput::readYesNoAsBool("\nAre You Sure You Want To Perform This Pay Transaction??\n");

   if(payConfirm)
   {
        mainClientsVector = Utility::performPayOperationInVector(mainClient , receiverClient , amount , mainClientsVector);

        if(Utility::loadClientsVectorToFile(mainClientsVector , clientsFilePath , delimiterInFile))
        {
            PayOperation payOpertion{mainClient.accountNumber , receiverAccountNumber , amount};
            Utility::loadPayOperationToPaysFiles(payOpertion , delimiterInFile);
            cout << "\nTransaction Done Successfuly\n";
        }
        else
            cout << "\nCan NOT Perform This Transaction\n";
   }

}
void MainMenuFeatures::displayTransactionsHsitory()
{
    Utility::displayHeaderScreen("Transactions History Screen");

    const string transactionFilePath = Utility::getTransactionFilePath(mainClient.accountNumber , MarkInTransactionFileName);

    vector<TransactionStruct> transactions = Utility::loadTransactionsFileToVector(transactionFilePath , delimiterInFile);


    Utility::displayTransactionsTableUsingVector(transactions);

}
void performDisplayPaysTypesOption(const DisplayPaysTypes& displayPaysTypesOption , const vector<PayOperation>& payOperations)
{
    switch (displayPaysTypesOption)
    {
    case DisplayPaysTypes::Display_Sended_Pays_Operations :
        Utility::displayPaysOperationsFromVector(payOperations , mainClient.accountNumber , displayPaysTypesOption);
        break;
    case DisplayPaysTypes::Display_Received_Pays_Opertion :
        Utility::displayPaysOperationsFromVector(payOperations , mainClient.accountNumber , displayPaysTypesOption);
        break;
    case DisplayPaysTypes::Display_All_Pays_Operation :
        Utility::displayPaysOperationsFromVector(payOperations , mainClient.accountNumber , displayPaysTypesOption);
        break;
    
    default:
        break;
    }
    if(displayPaysTypesOption != DisplayPaysTypes::Back_To_Main_Menu)
        UserInput::clickOnAnyKey("\n\nClick On Any key To Go Back To Main Menu Screen...");
}
void MainMenuFeatures::displayPaysHistory()
{
    DisplayPaysTypes displayPaysTypesOption;

    const string paysFilePath = Utility::getClientPaysFilePath(mainClient.accountNumber , markInPaysFileName);

    vector<PayOperation> payOperations = Utility::loadPaysFileToVector(paysFilePath , delimiterInFile); 

    bool backToMainMenueConfirm = false;
    do
    {
        Utility::displayHeaderScreen("Pays History Screen");

        Utility::displayMenuList("[1] Display All Pays History\n\n[2] Display Sended Pays Operation \n\n[3] Display Received Pays Operation\n\n[4] Back To Main Menu");

        displayPaysTypesOption = UserInput::readOptionNumber<DisplayPaysTypes>("\nChoose What Do You Want To Do? [1 to 4]? ");

        UserInput::clearTerminalScreen();

        performDisplayPaysTypesOption(displayPaysTypesOption , payOperations);

        if(displayPaysTypesOption == DisplayPaysTypes::Back_To_Main_Menu)
            backToMainMenueConfirm = UserInput::readYesNoAsBool("\nAre You Sure You Want To Back To Main Menu?\n");

        UserInput::clearTerminalScreen();

    } while (!backToMainMenueConfirm);
    
}
bool logout()
{
    return (mainOption == MainMenuOptions::Logout);
}


void performMainOption(const MainMenuOptions& mainOption)
{

    switch (mainOption)
    {
        case MainMenuOptions::Quick_Withdraw          : MainMenuFeatures::quickWithdraw(); break;
        case MainMenuOptions::Normal_Withdraw         : MainMenuFeatures::normalWithdraw(); break;
        case MainMenuOptions::Deposit                 : MainMenuFeatures::Deposit(); break;
        case MainMenuOptions::Check_Balance           : MainMenuFeatures::checkBalance(); break;
        case MainMenuOptions::Update_My_Information   : MainMenuFeatures::updateClientMenu(); break;
        case MainMenuOptions::Pay_To_Friend           : MainMenuFeatures::payToFriend(); break;
        case MainMenuOptions::Display_Transactions_History   : MainMenuFeatures::displayTransactionsHsitory(); break;
        case MainMenuOptions::Display_Pays_History           : MainMenuFeatures::displayPaysHistory(); break;

        default: break;
        
    }
    if(mainOption != MainMenuOptions::Logout && mainOption != MainMenuOptions::Update_My_Information && mainOption != MainMenuOptions::Display_Pays_History)
        UserInput::clickOnAnyKey("\n\nClick On Any key To Go Back To Main Menu Screen...");
}



void mainMenu()
{

    bool logoutConfirm = false;
    do
    {
        Utility::displayHeaderScreen("ATM Main Menu");

        Utility::displayMenuList("[1] Quick Withdraw\n\n[2] Normal Withdraw\n\n[3] Deposit\n\n[4] Check Balance\n\n[5] Update My Information\n\n[6] Pay To Friend\n\n[7] Display Transactions History\n\n[8] Display Pays History\n\n[9] Logout");

        mainOption = UserInput::readOptionNumber<MainMenuOptions>("\nChoose What Do You Want To Do? [1 to 8]? ");

        UserInput::clearTerminalScreen();

        performMainOption(mainOption);

        if(logout())
            logoutConfirm = UserInput::readYesNoAsBool("\nAre You Sure You Want To Logout?\n");
  

        UserInput::clearTerminalScreen();

    } while (!logoutConfirm);
    
}



bool login()
{
    Utility::displayHeaderScreen("Login Screen");

    bool loginFailed;

    do
    {
        string accountNumber = Utility::readAccountNumber("Please Enter Your Account Number Here : " , mainClientsVector);

        string pinCode = Utility::readPIN("Please Enter PIN Code Here            : ");

        loginFailed = !(Utility::findClientByAccountNumberAndPinCode(accountNumber , pinCode , mainClientsVector , mainClient));

        if(loginFailed)
            Utility::displayFailLoginErrorMessage();

    } while (loginFailed);

    return true;
}



void Run_ATM_System()
{
    UserInput::clearTerminalScreen();

    while(login())
    {
        UserInput::clearTerminalScreen();
        mainMenu();
    }
}



int main()
{
    Run_ATM_System();
    
    return 0;
}


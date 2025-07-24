#include"Utility.h"
#include"UserInput.cpp"
#include <fstream>
#include <iomanip>
using namespace std;

vector<string> Utility::splitEachWordInVector(const string& baseString, const string& delimiter)
{
    vector<string> words;
    string wordTemporary = "";
    short delimiterPosition = 0;
    string baseStringCopy = baseString;
    while ((delimiterPosition = baseStringCopy.find(delimiter)) != string::npos)
    {
        wordTemporary = baseStringCopy.substr(0, delimiterPosition);

        if (!wordTemporary.empty())
            words.push_back(wordTemporary);

        baseStringCopy.erase(0, delimiterPosition + delimiter.length());
    }

    if (!baseStringCopy.empty())
        words.push_back(baseStringCopy);

    return words;
}

Client Utility::convertLineOfDataToClientRecord(const string &lineofData, const string &delimiterInFile)
{
    Client client;

    vector<string> clientData = splitEachWordInVector(lineofData, delimiterInFile);

    client.accountNumber = clientData[0];
    client.name          = clientData[1];
    client.pinCode       = clientData[2];
    client.address       = clientData[3];
    client.phoneNumber   = clientData[4];
    client.balance       = stod(clientData[5]);

    return client;
}
vector<Client> Utility::loadClientsFileToVector(const string &filePath, const string &delimiterInFile)
{
    vector<Client> Clients;
    ifstream myFile(filePath);
    if (myFile.is_open())
    {
        Client clientTemporary;
        string lineOfData = "";
        while (getline(myFile, lineOfData))
        {

            clientTemporary = convertLineOfDataToClientRecord(lineOfData, delimiterInFile);

            Clients.push_back(clientTemporary);
        }
        myFile.close();
    }
    return Clients;
}
void Utility::displayHeaderScreen(const string &title)
{
    cout << "\n_________________________________________________________________________________________________________________\n\n";
    cout << right << setw(60) << title;
    cout << "\n_________________________________________________________________________________________________________________\n\n";
}
bool Utility::isReservedAccountNumber(const string &accountNumberToCheack , const vector<Client> & clientsVectorToCheak)
{
    
    for (const Client &client : clientsVectorToCheak)
    {
        if (client.accountNumber == accountNumberToCheack)
            return true;
    }
    return false;
}
string Utility::readAccountNumber(const string &msg , const vector<Client> & clientsVectorToReadFrom , bool newAccountNumber)
{
    string accountNumber;

    cout << msg;

    getline(cin >> ws, accountNumber);


    if (newAccountNumber)
    {
        while (isReservedAccountNumber(accountNumber, clientsVectorToReadFrom))
        {
            cout << "Client With Account Number [" << accountNumber << "] Already Exist , Please Enter Another Account Number??\n";
            getline(cin >> ws, accountNumber); 
        }
    }

    return accountNumber;
}
void Utility::displayWrongPinErrorMessage()
{
    cout << "\nWrong PIN Formate Please Try Again!!\n";
}
bool Utility::isCorrectPIN(const string &pinCode, const Client &client)
{
    return client.pinCode == pinCode;
}
bool Utility::isValidPinFormate(const string& pinCodeTpCheck)
{
    return (pinCodeTpCheck.length() == 6);
}
string Utility::readPIN(const string &msg, bool pinCodeForNewClient)
{
    string pinCode;
    cout << msg;
    getline(cin >> ws, pinCode);

    if(pinCodeForNewClient)
    {
        while(!isValidPinFormate(pinCode))
        {
            displayWrongPinErrorMessage();
            cout << msg;
            getline(cin >> ws, pinCode);
        }
            
    }


    return pinCode;
}
bool Utility::findClientByAccountNumberAndPinCode(const string& accountNumberToCheck , const string& pinCodeToCheck , const vector<Client>& clientsToCheck , Client& clientToFill)
{
    for(const Client& client : clientsToCheck)
    {
        if(client.accountNumber == accountNumberToCheck && client.pinCode == pinCodeToCheck)
        {
            clientToFill = client;
            return true;
        }
    }
    return false;
}   
void Utility::displayFailLoginErrorMessage()
{
    cout << "\nLogin Fail!! Please Check The Account Number And PIN Code.\n";
}
void Utility::displayMenuList(const string &menueList)
{
    cout << menueList;

    cout << "\n_________________________________________________________________________________________________________________\n";
}
Client Utility::decreaseClientBalance(const Client& client , const long double& amount)
{
    Client clientAfterDecreaseBalance = client;

    if(client.balance >= amount)
       clientAfterDecreaseBalance.balance -= amount;

    return clientAfterDecreaseBalance;
}
Client Utility::increaseClientBalance(const Client& client , const long double& amount)
{
    Client clientAfterDecreaseBalance = client;

    clientAfterDecreaseBalance.balance += amount;

    return clientAfterDecreaseBalance;
}
vector<Client> Utility::performTransactionInVector(Client& clientToTransaction , const long double& amount , const vector<Client>& clients , const TransactionType& type )
{

    vector<Client> clientsAfterTransaction = clients;

    bool isTransactionEnd = false;
  
    for(Client& client : clientsAfterTransaction)
    {
        if(client.accountNumber == clientToTransaction.accountNumber)
        {
            isTransactionEnd = true;
            switch (type)
            {
                case TransactionType::Withdraw_Transaction :
                {
                    client = decreaseClientBalance(client , amount);
                    clientToTransaction = decreaseClientBalance(clientToTransaction , amount);
                    break;
                }
                case TransactionType::Deposit_Transaction :
                {
                    client = increaseClientBalance(client , amount);
                    clientToTransaction = increaseClientBalance(clientToTransaction , amount);
                    break;
                }
                
                default:
                    break;
            }
        }
        if(isTransactionEnd)
            break;
    }

    return clientsAfterTransaction;
}
string Utility::convertClientRecordToLine(const Client &client, const string &delimiter)
{
    string lineOfData = "";
    lineOfData += client.accountNumber + delimiter;
    lineOfData += client.name + delimiter;
    lineOfData += client.pinCode + delimiter;
    lineOfData += client.address + delimiter;
    lineOfData += client.phoneNumber + delimiter;
    lineOfData += to_string(client.balance);
    return lineOfData;
}
bool Utility::addClientToFile(const Client &client, const string &filePath, const string &delimiter)
{
    string lineOfClientData = convertClientRecordToLine(client, delimiter);

    ofstream myFile;
    myFile.open(filePath, ios::app);

    if (myFile.is_open())
    {
        myFile << lineOfClientData << endl;

        myFile.close();

        return true;
    }
    else
        return false;

}
bool Utility::loadClientsVectorToFile(const vector<Client>& clients , const string& filePath, const string& delimiterInFile)
{
    ofstream myFile(filePath, ios::out);

    if (myFile.is_open())
    {
        for (const Client &client : clients)
            addClientToFile(client, filePath, delimiterInFile);

        myFile.close();
        return true;
    }
    else
        return false;

}
long double Utility::getClientBalance(const Client &client)
{
    return client.balance;
}
void Utility::displayClientBalance(const Client &client)
{
    cout << "\nYour Balance Is (" << Utility::getClientBalance(client) << ")\n";
}
void Utility::withdrawValidation(const Client &client , long int& amount , const string& errorMessage , const string& readMessage)
{
    while (client.balance < amount)
    {
        cout << errorMessage;
        amount = UserInput::readNumberMultipleTo(readMessage , 5);
    }
}
bool Utility::performWithdrawDepositTransactionInClientsFile(Client& clientToTransaction , const long double& amount ,  vector<Client>& clients , const string&filePath, const string& delimiterInFile , const TransactionType& type)
{
    clients = performTransactionInVector(clientToTransaction , amount , clients , type);

    return (loadClientsVectorToFile(clients , filePath , delimiterInFile));
}
long double Utility::readTransactionAmount(const Client &client , const TransactionType& type , const string& msg , const string& errorMessage)
{
    long int amount = 0;

    switch (type)
    {
        case TransactionType::Withdraw_Transaction :
        {
            amount = UserInput::readNumberMultipleTo(msg , 5);
            withdrawValidation(client , amount , errorMessage , msg);
            break;
        }
        case TransactionType::Deposit_Transaction :
        {
            amount = UserInput::readPositiveNumber(msg);
            break;
        }

        
        default:
            break;
    }

    

    return amount;
}
vector<Client> Utility::updateClientInVector(const vector<Client>& clients ,  Client &clientToUpdate , const UpdateOptions& updateOption)
{
    vector<Client> clientsAfterUpdate = clients;
    for(Client& client : clientsAfterUpdate)
    {
        if(client.accountNumber == clientToUpdate.accountNumber)
        {
            switch (updateOption)
            {
                case UpdateOptions::Update_PIN  :
                {
                    string NewPIN = readPIN("Please Enter The NEW PIN Here: " , true);
                    client.pinCode = NewPIN;
                    clientToUpdate.pinCode = NewPIN;
                    break;
                }   
                case UpdateOptions::Update_Name :
                {
                    string NewName = UserInput::readStringFromUser("Please Enter The NEW Name Here" , 4 , 50);
                    client.name = NewName;
                    clientToUpdate.name = NewName;
                    break;
                }   
                case UpdateOptions::Update_Address :
                {
                    string NewAddress = UserInput::readStringFromUser("Please Enter The NEW Address Here" , 4 , 30);
                    client.address = NewAddress;
                    clientToUpdate.address = NewAddress;
                    break;                    
                }  
                case UpdateOptions::Update_Phone_Number :
                {
                    string NewPhoneNumber = UserInput::readStringFromUser("Please Enter The NEW Phone Number Here" , 10 , 15);
                    client.phoneNumber = NewPhoneNumber;
                    clientToUpdate.phoneNumber = NewPhoneNumber;
                    break;                    
                }
                default: break;
                
            }
            return clientsAfterUpdate;
        }
    }
    return clientsAfterUpdate;
}
Client Utility::getClientByAccountNumber(const std::string &accountNumber , const std::vector<Client>& clients)
{
    Client clientToGet;
    for(const Client& client : clients)
    {
        if(accountNumber == client.accountNumber)
        {
            clientToGet = client;
        }
    }
    return clientToGet;
}
void Utility::displayClientCard(const string& msg , const Client& client , bool fullAccess)
{
    cout << "\n------------------------------------------------------\n";
    cout << msg;
    cout << "\n------------------------------------------------------\n";
    cout << "Account Number : " << client.accountNumber << endl;
    cout << "Name           : " << client.name          << endl;
    if(fullAccess)
    {
        cout << "Address         : " << client.address          << endl;
        cout << "PIN             : " << client.pinCode          << endl;
        cout << "Phone Number    : " << client.phoneNumber      << endl;
        cout << "Balance         : " << client.balance          << endl;
    }
    cout << "\n------------------------------------------------------\n";
}
vector<Client> Utility::performPayOperationInVector(Client& sender , Client& receiver , const long double& amount , const vector<Client>& clients)
{
    vector<Client> clientsAfterPerformPayTransaction = clients;

    clientsAfterPerformPayTransaction = performTransactionInVector(sender , amount , clientsAfterPerformPayTransaction , TransactionType::Withdraw_Transaction);

    clientsAfterPerformPayTransaction = performTransactionInVector(receiver , amount , clientsAfterPerformPayTransaction , TransactionType::Deposit_Transaction);

    return clientsAfterPerformPayTransaction;
}
bool Utility::loadTransactionRecordToFile(const TransactionStruct& transaction , const string& accountNumber , const string& delimiter)
{
    string transactionFilePath = getTransactionFilePath(accountNumber , MarkInTransactionFileName);
    ofstream transactionFile(transactionFilePath , ios::app);
    if(transactionFile.is_open())
    {
        string TransactionLine = convertTransactionRecordToLine(transaction , delimiter);
        transactionFile << TransactionLine << endl;
        transactionFile.close();
        return true;
    }
    else
        return false;
}
string Utility::convertTransactionRecordToLine(const TransactionStruct& transaction , const string& delimiter)
{
    string line = "";
    line += to_string(transaction.type);
    line += delimiter;
    line += to_string(transaction.amount);
    return line;
}
string Utility::getTransactionFilePath(const string& accountNumbe , const string& MarkInTransactionFileName)
{
    string transactionFilePath = "";

    transactionFilePath += accountNumbe;
    transactionFilePath += MarkInTransactionFileName;
    transactionFilePath += ".txt";

    return transactionFilePath;
}
vector<TransactionStruct> Utility::loadTransactionsFileToVector(const string& filePath, const string& delimiterInFile)
{   
    vector<TransactionStruct> transactions;
    ifstream transactionFile(filePath);
    if(transactionFile.is_open())
    {
        string lineTemporary;
        TransactionStruct transactionTemorary;
        while(getline(transactionFile , lineTemporary))
        {
            transactionTemorary = convertLineOfTransactionToRecord(lineTemporary , delimiterInFile);
            transactions.push_back(transactionTemorary);
        }
    }
    return transactions;
}
TransactionStruct Utility::convertLineOfTransactionToRecord(const string& line , const string& delimiterInFile)
{
    vector<string> words = splitEachWordInVector(line , delimiterInFile);

    TransactionStruct transaction;

    transaction.type = TransactionType(stoi(words[0]));
    transaction.amount =  double(stod(words[1]));

    return transaction;
}
void Utility::displayTransactionsTableUsingVector(const vector<TransactionStruct>& transactions)
{
    displayTransactionTableHeader();

    for(const TransactionStruct& transaction : transactions)
    {
        displayTransactionRowUsingRecord(transaction);
    }
        
}
void Utility::displayTransactionTableHeader()
{
    
    cout << left << setw(12) << "  Type";
    cout << " | ";
    cout << right << setw(12) << " Amount";
    cout << "\n----------------------------\n";
}
void Utility::displayTransactionRowUsingRecord(const TransactionStruct& transaction)
{
    cout << left << setw(12) << getTransactionName(transaction.type);
    cout << " | ";
    cout << right << setw(12) << to_string(transaction.amount);
    cout << "\n";
}
string Utility::getTransactionName(const TransactionType& type)
{
    string transactionNames[] = {"Withdraw" , "Deposite"};
    switch (type)
    {
        case TransactionType::Withdraw_Transaction : return transactionNames[0];
        case TransactionType::Deposit_Transaction : return transactionNames[1];

        
        default: return "";
    }
}
char Utility::getTransactionSign(const TransactionType& type)
{
    switch (type)
    {
        case TransactionType::Withdraw_Transaction : return '-';
        case TransactionType::Deposit_Transaction : return '+';

        default: return '+';
    }
    return '+';
}
bool Utility::loadPayOperationToPaysFiles(const PayOperation& payOperation , const string& delimiterInFile)
{
    string senderPaysFilePath   = getClientPaysFilePath(payOperation.senderAccountNumber , markInPaysFileName);
    string receiverPaysFilePath = getClientPaysFilePath(payOperation.receiverAccountNumber , markInPaysFileName);

    ofstream senderPaysFile(senderPaysFilePath , ios::app);
    ofstream receiverPaysFile(receiverPaysFilePath , ios::app);

    if(senderPaysFile.is_open() && receiverPaysFile.is_open())
    {
        string line = convertPayOpertionRecordToLine(payOperation , delimiterInFile);

        senderPaysFile << line << endl;
        receiverPaysFile << line << endl;
        
        senderPaysFile.close();
        receiverPaysFile.close();

        return true;
    }
    else
        return false;
}
string Utility::convertPayOpertionRecordToLine(const PayOperation& payOperation , const string& delimiterInFile)
{
    string line = "";
    line += payOperation.senderAccountNumber + delimiterInFile;
    line += payOperation.receiverAccountNumber + delimiterInFile;
    line += to_string(payOperation.amount);
    return line;
}
string Utility::getClientPaysFilePath(const string& accountNumber , const string& markInPaysFileName)
{
    string paysFilePath = "";
    paysFilePath += accountNumber;
    paysFilePath += markInPaysFileName;
    return paysFilePath;
}
vector<PayOperation> Utility::loadPaysFileToVector(const string& filePath, const string& delimiterInFile)
{
    vector<PayOperation> payOperations;
    ifstream paysFile(filePath);
    if(paysFile.is_open())
    {
        string line;
        PayOperation payOperationTemporary;
        while (getline(paysFile , line))
        {
            payOperationTemporary = convertLineOfPayOperationToRecord(line , delimiterInFile);
            payOperations.push_back(payOperationTemporary);
        }
    }
    return payOperations;
}
PayOperation Utility::convertLineOfPayOperationToRecord(const string& line , const string& delimiterInFile)
{
    vector<string> words = splitEachWordInVector(line , delimiterInFile);

    PayOperation payOperation;

    payOperation.senderAccountNumber = words[0];
    payOperation.receiverAccountNumber = words[1];
    payOperation.amount = stod(words[2]);

    return payOperation;
}
void Utility::displayPaysOperationsFromVector(const vector<PayOperation>& payOperations , const string& accountNumber , const DisplayPaysTypes& displayPaysTypesOption)
{
    for(const PayOperation& payOperation : payOperations)
    {
        if(displayPaysTypesOption == DisplayPaysTypes::Display_All_Pays_Operation)
        {
            displayPayOperationInFormat(payOperation);
        }
        else if(displayPaysTypesOption == DisplayPaysTypes::Display_Sended_Pays_Operations && accountNumber == payOperation.senderAccountNumber)
        {
            displayPayOperationInFormat(payOperation);
        }
        else if(displayPaysTypesOption == DisplayPaysTypes::Display_Received_Pays_Opertion && accountNumber == payOperation.receiverAccountNumber)
        {
            displayPayOperationInFormat(payOperation);
        }
    }
}
void Utility::displayPayOperationInFormat(const PayOperation& payOperation)
{
    cout << "\n------------------------\n";
    cout << "Sended From : " << payOperation.senderAccountNumber << endl;
    cout << "Sended To   : " << payOperation.receiverAccountNumber << endl;
    cout << "The Amount  : " << payOperation.amount;
    cout << "\n------------------------\n";
}

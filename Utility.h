#pragma once

#include<iostream>
#include<vector>
#include <iomanip>

struct Client
{
    std::string accountNumber = "";
    std::string name = "";
    std::string pinCode = "";
    std::string address = "";
    std::string phoneNumber = "";
    long double balance = 0;
};



enum UpdateOptions {Update_PIN = 1 , Update_Name = 2 , Update_Address = 3 , Update_Phone_Number = 4 , Go_Back_To_Main_Menu = 5};
enum TransactionType {Withdraw_Transaction = 1 , Deposit_Transaction = 2};

struct TransactionStruct 
{
    TransactionType type;
    long double amount = 0;
};

struct PayOperation
{
    std::string senderAccountNumber = "";
    std::string receiverAccountNumber = "";
    long double amount = 0;
};
enum DisplayPaysTypes
{
    Display_All_Pays_Operation     = 1 ,
    Display_Sended_Pays_Operations     ,
    Display_Received_Pays_Opertion     ,
    Back_To_Main_Menu
};

const std::string MarkInTransactionFileName = "TR";
const std::string markInPaysFileName = "PAYS";

namespace Utility
{
    std::vector<std::string> splitEachWordInVector(const std::string& baseString, const std::string& delimiter);
    Client convertLineOfDataToClientRecord(const std::string& lineofData, const std::string& delimiterInFile);
    std::vector<Client> loadClientsFileToVector(const std::string& filePath, const std::string& delimiterInFile);
    void displayHeaderScreen(const std::string& title);
    bool isReservedAccountNumber(const std::string& accountNumberToCheack , const std::vector<Client>&  clients);
    std::string readAccountNumber(const std::string& msg , const std::vector<Client>& clientsVectorToReadFrom , bool newAccountNumber = false);
    bool isCorrectPIN(const std::string& password, const Client& client);
    void displayWrongPinErrorMessage();
    bool isValidPinFormate(const std::string& pinCodeToCheck);
    std::string readPIN(const std::string& msg, bool pinCodeForNewClient = false);
    bool findClientByAccountNumberAndPinCode(const std::string& accountNumberToCheck , const std::string& pinCodeToCheck , const std::vector<Client>& clientsToCheck , Client& clientToFill);
    void displayFailLoginErrorMessage();
    void displayMenuList(const std::string &menueList);
    Client decreaseClientBalance(const Client& client , const long double& amount);
    std::vector<Client> performTransactionInVector(Client& clientToTransaction , const long double& amount , const std::vector<Client>& clients , const TransactionType& type );
    bool addClientToFile(const Client &client, const std::string &filePath, const std::string &delimiter);
    std::string convertClientRecordToLine(const Client &client, const std::string &delimiter);
    bool loadClientsVectorToFile(const std::vector<Client>& clients , const std::string& filePath, const std::string& delimiterInFile);
    long double getClientBalance(const Client &client);
    void displayClientBalance(const Client &client);
    void withdrawValidation(const Client &client , long int& amount , const std::string& errorMessage , const std::string& readMessage);
    bool performWithdrawDepositTransactionInClientsFile(Client& clientToTransaction , const long double& amount ,  std::vector<Client>& clients , const std::string& filePath, const std::string& delimiterInFile , const TransactionType& type );
    long double readTransactionAmount(const Client &client , const TransactionType& type , const std::string& msg , const std::string& errorMessage = "");
    Client increaseClientBalance(const Client& client , const long double& amount);
    std::vector<Client> updateClientInVector(const std::vector<Client>& clients ,  Client &clientToUpdate , const UpdateOptions& updateOption);
    Client getClientByAccountNumber(const std::string &accountNumber , const std::vector<Client>& clients);
    void displayClientCard(const std::string& msg , const Client& client , bool fullAccess);
    std::vector<Client> performPayOperationInVector(Client& sender , Client& receiver , const long double& amount , const std::vector<Client>& clients);
    bool loadTransactionRecordToFile(const TransactionStruct& transaction , const std::string& accountNumber , const std::string& delimiter);
    std::string convertTransactionRecordToLine(const TransactionStruct& transaction , const std::string& delimiter);
    std::string getTransactionFilePath(const std::string& accountNumbe , const std::string& MarkInTransactionFileName);
    std::vector<TransactionStruct> loadTransactionsFileToVector(const std::string& filePath, const std::string& delimiterInFile);
    TransactionStruct convertLineOfTransactionToRecord(const std::string& line , const std::string& delimiterInFile);
    void displayTransactionsTableUsingVector(const std::vector<TransactionStruct>& transactions);
    void displayTransactionRowUsingRecord(const TransactionStruct& transaction);
    std::string getTransactionName(const TransactionType& type);
    char getTransactionSign(const TransactionType& type);
    void displayTransactionTableHeader();
    bool loadPayOperationToPaysFiles(const PayOperation& payOperation , const std::string& delimiterInFile);
    std::string convertPayOpertionRecordToLine(const PayOperation& payOperation , const std::string& delimiterInFile);
    std::string getClientPaysFilePath(const std::string& accountNumber , const std::string& markInPaysFileName);
    std::vector<PayOperation> loadPaysFileToVector(const std::string& filePath, const std::string& delimiterInFile);
    PayOperation convertLineOfPayOperationToRecord(const std::string& line , const std::string& delimiterInFile);
    void displayPaysOperationsFromVector(const std::vector<PayOperation>& payOperations , const std::string& accountNumber , const DisplayPaysTypes& displayPaysTypesOption);
    void displayPayOperationInFormat(const PayOperation& payOperation);
}












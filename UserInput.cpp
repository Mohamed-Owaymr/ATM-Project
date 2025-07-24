#include <limits>
#include <cctype>
#include <string>
#include <conio.h>
#include "magic_enum.hpp"
#include "UserInput.h"
using namespace std;


bool UserInput::isNegative(float value)
{
    return value < 0;
}
bool UserInput::isPositive(float value)
{
    return value > 0;
}
bool UserInput::isZero(float value)
{
    return value == 0;
}
void UserInput::cleanCin()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
bool UserInput::isLetter(char value)
{
    return isupper(value) || islower(value);
}
void UserInput::printInvalidValueErrorMessage()
{
    cout << "Error! You Entered Invalid Value\n";
}
float UserInput::readPositiveNumber(const string& msg)
{
    float number;
    cout << msg << ": ";
    cin >> number;
    while(cin.fail() || isNegative(number) || isZero(number))
    {
        cleanCin();
        printInvalidValueErrorMessage();
        cout << msg << " Again: ";
        cin >> number;
    }
    return number;
}
float UserInput::readNegativeNumber(const string& msg)
{
    float number;
    cout << msg << ": ";
    cin >> number;
    while(cin.fail() || isPositive(number) || isZero(number))
    {
        cleanCin();
        printInvalidValueErrorMessage();
        cout << msg << " Again: ";
        cin >> number;
    }
    return number;
}
float UserInput::readNaturalNumber(const string& msg)
{
    float number;
    cout << msg << ": ";
    cin >> number;
    while(cin.fail())
    {
        cleanCin();
        printInvalidValueErrorMessage();
        cout << msg << " Again: ";
        cin >> number;
    }
    return number;
}
char UserInput::readLetterFromUser(const std::string& msg)
{
    char input;
    cout << msg <<": ";
    cin >> input;
    while(cin.fail() || !isLetter(input))
    {
        cleanCin();
        printInvalidValueErrorMessage();
        cout << msg << " Again: ";
        cin >> input;
    }
    return input;
}
bool UserInput::isFalseLetterCharacter(char letter)
{
    return letter == 'n' || letter == 'N';
}
bool UserInput::isTrueLetterCharacter(char letter)
{
    return letter == 'y' || letter == 'Y';
}
bool UserInput::readYesNoAsBool(const string& msg)
{
    char letter = readLetterFromUser(msg);
    while(!(isFalseLetterCharacter(letter) || isTrueLetterCharacter(letter)))
    {
        cleanCin();
        printInvalidValueErrorMessage();
        letter = readLetterFromUser(msg);
    }
    if(isFalseLetterCharacter(letter))
        return false;
    return true;
}
bool UserInput::isInRange(float from , float to , float number , bool inclusive)
{
    if(inclusive)
        return number >= from && number <= to;
    else
        return number > from && number < to;
}
float UserInput::readNumberInRange(const std::string& msg , float from , float to , bool inclusive)
{
    float number;
    cout << msg << ": ";
    cin >> number;
    while(cin.fail() || !isInRange(from , to , number , inclusive))
    {
        cleanCin();
        printInvalidValueErrorMessage();
        cout << msg << " Again: ";
        cin >> number;
    }
    return number;
}
void UserInput::displayUserOptionsList(const string& options)
{
    cout << "\n****************************\n";
    cout << "Your Options: \n";
    cout << options << endl;
    cout << "****************************\n";
}
float UserInput::readNumberFromUser(const string& msg , enNumberInputTypes inputType)
{
    float inputNumber = 0;
    switch (inputType)
    {
    case enNumberInputTypes::NaturalNum:
        inputNumber = readNaturalNumber(msg);
        break;
    case enNumberInputTypes::PositiveNum:
        inputNumber = readPositiveNumber(msg);
        break;
    case enNumberInputTypes::NegativeNum:
        inputNumber = readNegativeNumber(msg);
        break;

    
    default:
        inputNumber = readPositiveNumber(msg);
        break;
    }
    return inputNumber;
}
string UserInput::readStringFromUser(const string& msg , short minLength , short maxLength , bool inclusive)
{
    string input;
    cout << msg << ": ";
    getline(cin >> ws , input);
    short length = input.length();
    while(input.empty() || !isInRange(minLength , maxLength , length , inclusive))
    {
        cout << msg << " Again: ";
        getline(cin >> ws , input);
        length = input.length();
    }
    
    return input;
}
void UserInput::clearTerminalScreen()
{
    std::cout << "\033[2J\033[1;1H";
}
bool UserInput::clickOnCharacter(const char Character)
{
    if( _kbhit() )
    {
        char key = _getch();
        if(key == Character)
        {
            return true;
        }
    }
    return false;
}

bool UserInput::clickOnAnyKey(const string& msg)
{
    cout << msg;
    return getch();
}
long int UserInput::readNumberMultipleTo(const string& msg , int number)
{
    long int numberToRead = readNaturalNumber(msg);

    while (numberToRead % number)
    {
        cout << "\nError! [" << numberToRead << "] Is NOT Multiple To " << number << endl;
        numberToRead = readNaturalNumber(msg);
    }
    
    return numberToRead;
}

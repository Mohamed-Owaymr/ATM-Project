#pragma once

#include <iostream>




namespace UserInput
{
    bool isNegative(float value);
    bool isPositive(float value);
    bool isZero(float value);
    void cleanCin();
    bool isLetter(char value);
    void printInvalidValueErrorMessage();
    float  readPositiveNumber(const std::string& msg);
    float  readNegativeNumber(const std::string& msg);
    float  readNaturalNumber(const std::string& msg);
    long int    readNumberMultipleTo(const std::string& msg , int number);
    char readLetterFromUser(const std::string& msg);
    bool isFalseLetterCharacter(char letter);
    bool isTrueLetterCharacter(char letter);
    bool readYesNoAsBool(const std::string& msg);
    bool isInRange(float from , float to , float number , bool inclusive  = true);
    float  readNumberInRange(const std::string& msg , float from , float to , bool inclusive  = true);
    void displayUserOptionsList(const std::string& options);

    template <typename EnumType>
    size_t getEnumSizeUsingMagicEnumCount()
    {
        static_assert(std::is_enum<EnumType>::value, "Error: The parameter must be an enum!");
        return magic_enum::enum_count<EnumType>();
    }

    template<typename EnumType>
    bool isValidOptionNumber(short opNumber)
    {
        size_t enumSize = getEnumSizeUsingMagicEnumCount<EnumType>();
        return opNumber <= enumSize && !isNegative(opNumber);
    }

    template<typename EnumType>
    EnumType readOptionNumber(const std::string& msg, const std::string& optionsList)
    {
        short optionNumber;
        displayUserOptionsList(optionsList);
        optionNumber = readPositiveNumber(msg);
        while (!isValidOptionNumber<EnumType>(optionNumber))
        {
            printInvalidValueErrorMessage();
            optionNumber = readPositiveNumber(msg);
        }
        return static_cast<EnumType>(optionNumber);
    }
    template<typename EnumType>
    EnumType readOptionNumber(const std::string& msg)
    {
        short optionNumber;
        optionNumber = readPositiveNumber(msg);
        while (!isValidOptionNumber<EnumType>(optionNumber))
        {
            printInvalidValueErrorMessage();
            optionNumber = readPositiveNumber(msg);
        }
        return static_cast<EnumType>(optionNumber);
    }

    enum enNumberInputTypes{NaturalNum = 1 , PositiveNum = 2 , NegativeNum = 3};

    float readNumberFromUser(const std::string& msg , enNumberInputTypes inputType);

    std::string readStringFromUser(const std::string& msg , short minLength , short maxLength , bool inclusive = true);

    void clearTerminalScreen();

    bool clickOnCharacter(const char Character);

    bool clickOnAnyKey(const std::string& msg);


} 

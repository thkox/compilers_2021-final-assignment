#include <iostream>
using namespace std;

//The string that we are gonna use in production.
string characters = "<E>";
//We set a char with all the available symbols.
const char* listOfSymbols[10] = { "<E>","<Y>","<A>","<B>","v","-","+","^","(",")" };
//It's a pointer for the string characters
int symbolPointer = 0;
//Store pointer's location after a symbol change.
int storePointer = 0;
//counter of Y, to make the production finite
int counterY = 0;

//this method is gonna be used, when the production method has found a non-terminal symbol and it's position.
string changeSymbols(string toChangeSymbols, string delimiter, string newSymbol, int ruleNumber)
{
    cout << "The <" << delimiter << "> is a non-terminal character. Using the " << ruleNumber << ". Grammar Rule" << endl;
    string leftString;
    string rightString;
    //we separate the left and right string from the terminal symbol.
    leftString = toChangeSymbols.substr(0, symbolPointer - 1);
    toChangeSymbols.erase(0, symbolPointer + 1 + delimiter.length());
    rightString = toChangeSymbols;
    toChangeSymbols = leftString + newSymbol + rightString;
    //characters = toChangeSymbols;
    cout << "=> " << characters << endl << endl;
    //save pointer location
    storePointer = symbolPointer - 1;
    //to make the program finite
    if (delimiter == "Y" && counterY != 0)
    {
        counterY--;
    }
    return toChangeSymbols;
}
//this method is gonna be used when the production method has found a non-terminal symbol.
int rules(int ruleNumber)
{
    switch (ruleNumber) {
    case 1:
        characters = changeSymbols(characters, "E", "(<Y>)", 1); //1.<E>::=(<Y>)
        break;
    case 2:
        characters = changeSymbols(characters, "Y", "<A><B>", 2); //2.<Y>::=<A><B>
        break;
    case 3:
        characters = changeSymbols(characters, "A", "v", 3); //3.<A>::=v
        break;
    case 4:
        characters = changeSymbols(characters, "A", "<E>", 4); //4.<A>::=<E>
        break;
    case 5:
        characters = changeSymbols(characters, "B", "-<Y>", 5); //5.<B>::=-<Y>
        break;
    case 6:
        characters = changeSymbols(characters, "B", "+<Y>", 6); //6.<B>::=+<Y>
        break;
    case 7:
        characters = changeSymbols(characters, "B", "^", 7); //7.<B>::=^
        break;
    }

    ruleNumber = 0;
    symbolPointer = storePointer; //to skip the already terminal character that exists on the left side of the pointer
    return 0;
}
int chooseA;
int chooseB;
//it's starts the production of the symbols sequence.
int production(string sequenceOfSymbols)
{
    srand(time(0));
    while (symbolPointer != characters.length())
    {
        //in order to stop the program from being infinite, we created the following "if" to stop some grammatics rule from repeating.
        if (counterY == 0)
        {
            chooseA = 3;
            chooseB = 7;
        }
        else
        {
            chooseA = 3 + (rand() % (4 - 3 + 1));
            chooseB = 5 + (rand() % (7 - 5 + 1));
        }
        switch (characters[symbolPointer]) {
        case 'E':
            rules(1);
            break;
        case 'Y':
            rules(2);
            break;
        case 'A':
            rules(chooseA);
            break;
        case 'B':
            rules(chooseB);
            break;
        }
        symbolPointer++;
    }
    cout << "---- Now all the characters are terminals. ----" << endl << endl;
    cout << "The final symbol string is: " << characters << endl << endl;
    cout << "To close the program, press Enter:" << endl;
    cin.get();
    return 0;
}

int main()
{
    cout << "First Exercise: \n" << "RANDOM SYMBOL STRING GENERATOR\n" << endl;
    cout << "Symbol's string format: BNF (Backus-Naur Form)\n" << endl;
    cout << "Grammar:\n 1.<E>::=(<Y>)\n 2.<Y>::=<A><B>\n 3.<A>::=v\n 4.<A>::=<E>\n 5.<B>::=-<Y>\n 6.<B>::=+<Y> \n 7.<B>::=^" << endl;
    cout << "~-~-~-~-~" << endl;
    cout << "Non-terminal Characters: E, Y, A, B\n" << "Terminal Characters: (, ), v, -, +, ^" << endl;
    cout << "~-~-~-~-~" << endl;
    cout << "When you are ready press ENTER:" << endl;
    cin.get();
    //chooses a random length for the string.
    srand(time(0)); //it's choose random numbers based on the current time.
    //the random times the rules A and B are gonna be non-terminal.  FIX EXPLANATION.
    counterY = rand() % 40; // range [0 - 39]
    //stringCharactersGenerator(lengthOfSymbols);
    cout << "The starting symbol is: " << characters << "\n" << endl;
    production(characters);
    return 0;
}
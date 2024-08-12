#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

string listOfSymbols = "SXYZab*+-^()";
//symbol strign that the user is going to input
string symbolString = "";
//output string
string stringTree = "S";
//list to print the tree
list<string> tree;
//the stack
string stack = "$";
//tableElement
string tableElement;
//SyntaxRule
string syntaxRule;
//we count how many times a symbol of the input is different with every single character in listOfSymbols.
int counterCorrectSymbols = 0;
//table M
string M[5][9] = { {"", "(", ")", "a", "b", "*", "+", "-", "$"},
				   {"S", "(X)", "", "", "", "", "", "", ""},
				   {"X", "YZ", "", "YZ", "YZ", "", "", "", ""},
				   {"Y", "S", "", "a", "b", "", "", "", ""},
				   {"Z", "", "^", "", "", "*X", "+X", "-X", ""} };

char separator = ' ';
int stackW = 15;
int inputW = 0; 
int tableEW = 13;
int syntaxRW = 10;

//teplate for the table
template<typename T> void printElement(T t, const int& width)
{
	cout << left << setw(width) << setfill(separator) << t << "|| ";
}

bool validateString(string toBeCheckedString);

//print the tree
void print(list<string> const& list)
{
	for (auto const& i : list) {
		cout << i << endl;
	}
}


string printTree(string changeSymbols, char delimiter, string newSymbol)
{
	int symbolPointer = changeSymbols.find(delimiter);
	string leftString;
	string rightString;
	//we separate the left and right string from the non-terminal symbol.
	leftString = changeSymbols.substr(0, symbolPointer);
	changeSymbols.erase(0, symbolPointer + 1);
	rightString = changeSymbols;
	changeSymbols = leftString + newSymbol + rightString;
	tree.push_back(changeSymbols);
	//to make the program finite
	return changeSymbols;
}

//we search M table to find the proper syntax rule
int findProperRule(int nonTC, int tC, char lastSymbol, char firstSymbol)
{
	if (M[nonTC][tC] != "")
	{
		tableElement.push_back('M');
		tableElement.push_back('(');
		tableElement.push_back(lastSymbol);
		tableElement.push_back(',');
		tableElement.push_back(firstSymbol);
		tableElement.push_back(')');

		syntaxRule.push_back(lastSymbol);
		syntaxRule.push_back('-');
		syntaxRule.push_back('-');
		syntaxRule.push_back('>');
		syntaxRule.append(M[nonTC][tC]);


		stack.pop_back();
		//add symbols in stack
		if (M[nonTC][tC] != "^")
		{
			for (int i = M[nonTC][tC].length() - 1; i >= 0; i--)
			{
				stack.push_back(M[nonTC][tC][i]);
			}
		}
		printElement(tableElement, tableEW);
		printElement(syntaxRule, syntaxRW);
		cout << endl;
		stringTree = printTree(stringTree, lastSymbol, M[nonTC][tC]);
		tableElement.erase(0, tableElement.length());
		syntaxRule.erase(0, syntaxRule.length());
		return 0;
	}
	else
	{
		return -1;
	}
}

//delete the proper symbols
void removeSymbols()
{
	stack.pop_back();
	symbolString.erase(0, 1);
}

//compare the last symbol from the stack with the first symbol of the input.
int findProperSymbols(char lastSymbol, char firstSymbol)
{
	int nonTCIndex;
	switch (lastSymbol) {
	case 'S':
		nonTCIndex = 1;
		break;
	case 'X':
		nonTCIndex = 2;
		break;
	case 'Y':
		nonTCIndex = 3;
		break;
	case 'Z':
		nonTCIndex = 4;
		break;
	default:
		nonTCIndex = 0;
	}

	int tCIndex;
	switch (firstSymbol) {
	case '(':
		tCIndex = 1;
		break;
	case ')':
		tCIndex = 2;
		break;
	case 'a':
		tCIndex = 3;
		break;
	case 'b':
		tCIndex = 4;
		break;
	case '*':
		tCIndex = 5;
		break;
	case '+':
		tCIndex = 6;
		break;
	case '-':
		tCIndex = 7;
		break;
	case '$':
		tCIndex = 8;
		break;
	default:
		tCIndex = 0;
	}
	if (nonTCIndex == 0)
	{
		removeSymbols();
		cout << endl;
		return 0;
	}
	else
	{

		if (findProperRule(nonTCIndex, tCIndex, lastSymbol, firstSymbol) != -1)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
}

bool parchingTable()
{
	stack.push_back('S');
	if (symbolString[symbolString.length() - 1] != '$')
	{
		symbolString.push_back('$');
	}

	printElement("STACK", stackW);
	printElement("INPUT", inputW);
	printElement("TABLE ELEMENT", tableEW);
	printElement("PRODUCTION", syntaxRW);
	cout << endl;
	while (symbolString != "$" && stack != "$")
	{
		printElement(stack, stackW);
		printElement(symbolString, inputW);

		//we take the last symbol from the stack
		if (findProperSymbols(stack.back(), symbolString.front()) == -1)
		{
			break;
		}
	}

	if (symbolString == "$" && stack == "$")
	{
		printElement(stack, stackW);
		printElement(symbolString, inputW);
		cout << endl;
		cout << "\nThe symbol string is accepted, successfully!" << endl;

		cout << "\nHere is the tree:\n";
		print(tree);
	}
	else
	{
		cout << "\n\nThe symbol syntax is not correct." << endl;
	}
	return true;
}

bool stringVocabularyResult(string notCheckedString)
{
	if (validateString(notCheckedString) != true)
	{
		cout << "\nThe symbol string does not have the right vocabulary." << endl;
		cout << "Accepted Symbols: a, b, *, +, -, ^, (, ), $" << endl;
		cout << "\nPlease try again:" << endl;
		counterCorrectSymbols = 0;
		cin >> symbolString;
		return stringVocabularyResult(symbolString);
	}
	else
	{
		cout << "Let's move to our next step:\n" << endl;
		tree.push_back(stringTree);
		inputW = symbolString.length() + 5;
		stackW = symbolString.length() + 5;
		return true;
	}

}

int stringIncludeDollar = 0;

bool validateString(string toBeCheckedString)
{
	//we add automatically the dollar at the end of the string in case the user forgets it
	if (toBeCheckedString[toBeCheckedString.length() - 1] == '$')
	{
		stringIncludeDollar = toBeCheckedString.length() - 1;
	}
	else
	{
		stringIncludeDollar = toBeCheckedString.length();
	}
	for (int i = 0; unsigned(i) < stringIncludeDollar; i++)
	{
		for (int j = 4; j < 12; j++)
		{
			if (toBeCheckedString[i] == listOfSymbols[j])
			{
				counterCorrectSymbols++;
			}
		}
	}
	if (counterCorrectSymbols == stringIncludeDollar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	cout << "Second Exercise:\n" << "TOP-DOWN PARCHER\n" << endl;
	cout << "Grammar's format: Context-free" << endl;
	cout << "\nGrammar:" << endl;
	cout << " 1. S --> (X)\n" << " 2. X --> YZ\n" << " 3. Y --> a\n" << " 4. Y --> b\n" << " 5. Y --> S\n" << " 6. Z --> *X\n" << " 7. Z --> -X\n" << " 8. Z --> +X\n" << " 9. Z --> ^\n" << endl;
	cout << "~-~-~-~-~" << endl;
	cout << "Non-terminal Characters: S, X, Y, Z\n" << "Terminal Characters: a, b, *, +, -, ^, (, )" << endl;
	cout << "~-~-~-~-~" << endl;
	cout << "Please write the symbol string that you want to validate\n(if you do not add $ at the end of the string, it will be added automatically): ";
	//we store the user's symbol string.
	cin >> symbolString;
	cout << "The symbol string that you typed is: " << symbolString << endl;
	if (stringVocabularyResult(symbolString) != false)
	{
		parchingTable();
	}
	cout << "To close the program, press Enter:" << endl;
	cin.get();
	cin.ignore();
}

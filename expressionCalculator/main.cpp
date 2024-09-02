#include <iostream>
#include <string>
#include <vector>

#include "parse.h"
#include "Validation.h"
#include "evaliuation.h"

using namespace std;

vector<string> ValidTokensList = {
  "+",
  "-",
  "*",
  "/", 
  "(",
  ")"
};



int main() {
  
	cout << "Welcome to the expression Calculator by Prodigg. \nPlease enter expression to calculate: ";
	string input = "";
	getline(cin, input);
	cout << "\n";

	//tokens tokenList = tokeniseStr(input, " ");
	tokens tokenList = tokeniseStr(input, ValidTokensList);
	//dumpTokens(&cout, tokenList);
	tokensParsed tokensListParsed = parseTokens(tokenList);
	//dumpParsedTokens(&cout, tokensListParsed);

	// check expression before evaluation
	checkExpression(tokensListParsed);

	cout << "The result is: " << evalToken(tokensListParsed) << "\n";
	waitKeyPress();
	exit(EXIT_SUCCESS);
}
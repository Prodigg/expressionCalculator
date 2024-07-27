#include <iostream>
#include <string>
#include <vector>

#include "parse.h"

using namespace std;

vector<string> ValidTokensList = {
  "+",
  "-",
  "*",
  "/"
};



int main() {
  
	cout << "Welcome to the expression Calculator by Raphael Sauer. \nPlease enter expression to calculate: ";
	string input = "";
  getline(cin, input);
  cout << "\n";

  //tokens tokenList = tokeniseStr(input, " ");
  tokens tokenList = tokeniseStr(input, ValidTokensList);
  //dumpTokens(&cout, tokenList);
  tokensParsed tokensListParsed = parseTokens(tokenList);
  dumpParsedTokens(&cout, tokensListParsed);

  exit(EXIT_SUCCESS);
}
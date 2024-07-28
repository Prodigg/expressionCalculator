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

// returns -1 if non operator found
static int searchFirstLestValOp(tokensParsed tokens) {
	int retVal = -1;
	for (int i = 0; i < tokens.size(); i++) {
		switch (tokens.at(i).type) {
		case TOKEN_PLUS:
			return i;
		case TOKEN_MINUS:
			return i;
		case TOKEN_MULTIPLY:
			if (retVal > i) break;
			retVal = i;
			break;
		case TOKEN_DIVIDE:
			if (retVal > i) break;
			retVal = i;
			break;
		default:
			// do nothing
			break;
		}
	}
	return retVal;

}

//TODO: support bracets

// eval token doesn't support bracets
// in case of no tokens given returns 0
double evalToken(tokensParsed tokens, uint16_t level = 0) {
	tokensParsed rhs; // right hand side
	tokensParsed lhs; // left hand side

	singleParsedToken operatorToken;

	tokens.shrink_to_fit();

	// check if token list is valid 
	if (tokens.size() <= 0) {
		// no tokens given 
		cout << errorMsg "EROR: no tokens given at level: " << level;
	}

	// return number
	if (tokens.size() == 1 && tokens.at(0).type == TOKEN_NUMBER) {
		return tokens.at(0).as.number;
	}

	// find operator position
	int operatorPos = searchFirstLestValOp(tokens);

	if (operatorPos == -1) { 
		cout << errorMsg << "ERROR: no operator token found at level: " << level << "\n";
		cout << "given tokens: \n";
		dumpParsedTokens(&cout, tokens);
		exit(EXIT_FAILURE);
	}
	
	// resolve operator, rhs and lhs
	operatorToken = tokens.at(operatorPos);
	
	for (size_t i = 0; i < operatorPos; i++) {
		lhs.push_back(tokens.at(i));
	}

	for (size_t i = operatorPos + 1; i < tokens.size(); i++) {
		rhs.push_back(tokens.at(i));
	}

	switch (operatorToken.type) {
	case TOKEN_PLUS:
		return evalToken(lhs, level + 1) + evalToken(rhs, level + 1);
	case TOKEN_MINUS:
		return evalToken(lhs, level + 1) - evalToken(rhs, level + 1);
	case TOKEN_MULTIPLY:
		return evalToken(lhs, level + 1) * evalToken(rhs, level + 1);
	case TOKEN_DIVIDE:
		return evalToken(lhs, level + 1) / evalToken(rhs, level + 1);
	default:
		cout << errorMsg << "ERROR: invalid token or number detected at level: " << level;
		exit(EXIT_FAILURE);
	}
}

int main() {
  
	cout << "Welcome to the expression Calculator by Raphael Sauer. \nPlease enter expression to calculate: ";
	string input = "";
	getline(cin, input);
	cout << "\n";

	//tokens tokenList = tokeniseStr(input, " ");
	tokens tokenList = tokeniseStr(input, ValidTokensList);
	//dumpTokens(&cout, tokenList);
	tokensParsed tokensListParsed = parseTokens(tokenList);
	//dumpParsedTokens(&cout, tokensListParsed);

	cout << "The result is: " << evalToken(tokensListParsed);

	exit(EXIT_SUCCESS);
}
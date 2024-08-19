#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "parse.h"

/// <summary>
/// searches First least prioraty operator
/// </summary>
/// <param name="tokens"></param>
/// <returns>-1 if no operator found</returns>
static int searchFirstLestValOp(tokensParsed tokens) {
	int retVal = -1;
	size_t bracetsOpen = 0;
	for (int i = 0; i < tokens.size(); i++) {
		switch (tokens.at(i).type) {
		case TOKEN_PLUS:
			if (bracetsOpen > 0) break;
			return i;
		case TOKEN_MINUS:
			if (bracetsOpen > 0) break;
			return i;
		case TOKEN_MULTIPLY:
			if (retVal > i) break;
			if (bracetsOpen > 0) break;
			retVal = i;
			break;
		case TOKEN_DIVIDE:
			if (retVal > i) break;
			if (bracetsOpen > 0) break;
			retVal = i;
			break;
		case TOKEN_BRACET_OPEN:
			bracetsOpen++;
			break;
		case TOKEN_BRACET_CLOSE:
			bracetsOpen--;
			if (bracetsOpen < 0) {
				cout << errorMsg << "ERROR: closing bracet not valid. \n";
				exit(EXIT_FAILURE);
			}
		default:
			// do nothing
			break;
		}
	}
	return retVal;

}

/// <summary>
/// evaluate expression Tokens
/// </summary>
/// <param name="tokens"></param>
/// <param name="level"></param>
/// <returns>number calculatet</returns>
static double evalToken(tokensParsed tokens, uint16_t level = 0) {
	tokensParsed rhs; // right hand side
	tokensParsed lhs; // left hand side

	singleParsedToken operatorToken;

	// check if token list is valid 
	if (tokens.size() <= 0) {
		// no tokens given 
		cout << errorMsg "EROR: no tokens given at level: " << level << "\n";
		exit(EXIT_FAILURE);
	}

	if (tokens.at(0).type == TOKEN_BRACET_OPEN && tokens.at(tokens.size() - 1).type == TOKEN_BRACET_CLOSE) {
		// not needed bracets detected (removing)
		tokens.erase(tokens.begin());
		tokens.erase(--tokens.end());
	}

	tokens.shrink_to_fit();

	// check if token list is valid 
	if (tokens.size() <= 0) {
		// no tokens given 
		cout << errorMsg "EROR: no tokens given at level: " << level << "\n";
		exit(EXIT_FAILURE);
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

	for (size_t i = static_cast<size_t>(operatorPos) + 1; i < tokens.size(); i++) {
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
		cout << errorMsg << "ERROR: invalid token or number detected at level: " << level << "\n";
		exit(EXIT_FAILURE);
	}
}
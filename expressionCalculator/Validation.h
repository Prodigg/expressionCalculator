#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "parse.h"

/// <summary>
/// calculates str length from tokens
/// </summary>
/// <param name="tokens"></param>
/// <param name="tokenIndex"></param>
/// <returns>string length</returns>
uint32_t mapTokenToStrLentgth(tokensParsed tokens, uint16_t tokenIndex) {
	if (tokenIndex > tokens.size()) {
		return 0;
	}
	uint32_t strLength = 0;
	for (size_t i = 0; i < tokenIndex; i++) {
		strLength += tokens.at(i).str.length();
	}
	return strLength;
}

/// <summary>
/// generates a string from tokens
/// </summary>
/// <param name="tokens"></param>
/// <returns></returns>
string tokensToString(tokensParsed tokens) {
	string str = "";
	for (size_t i = 0; i < tokens.size(); i++) {
		str += tokens.at(i).str;
	}
	return str;
}

/// <summary>
/// checks if a token is an operator
/// </summary>
/// <param name="tokenType">of token</param>
/// <returns></returns>
bool isTokenOperator(TokenType tokenType) {
	switch (tokenType) {
	case TOKEN_PLUS:
		return true;
	case TOKEN_MINUS:
		return true;
	case TOKEN_MULTIPLY:
		return true;
	case TOKEN_DIVIDE:
		return true;
	}
	return false;
}

void waitKeyPress() {
	system("pause");
	return;
}

/// <summary>
/// Validates if expression has errors
/// </summary>
/// <param name="tokens"></param>
void checkExpression(tokensParsed tokens) {
	if (tokens.size() == 0) {
		cout << "ERROR: no expression given \n";
		waitKeyPress();
		exit(EXIT_FAILURE);
	}

	string TmpErrorMsg = "";

	// check if brackets are ok
	int32_t bracketCount = 0;
	for (size_t i = 0; i < tokens.size(); i++) {
		if (tokens.at(i).type == TOKEN_BRACET_OPEN) {
			bracketCount++;
		}
		else if (tokens.at(i).type == TOKEN_BRACET_CLOSE) {
			bracketCount--;
		}

		if (bracketCount < 0) {
			TmpErrorMsg.insert(TmpErrorMsg.begin(), mapTokenToStrLentgth(tokens, i), ' ');
			cout << "ERROR: bracket closing unexpected\n";
			cout << tokensToString(tokens) << "\n";
			cout << TmpErrorMsg << "^\n";
			waitKeyPress();
			exit(EXIT_FAILURE);
		}
	}

	if (bracketCount > 0) {
		TmpErrorMsg.insert(TmpErrorMsg.begin(), mapTokenToStrLentgth(tokens, tokens.size()), ' ');
		cout << "ERROR: brackets not closed\n";
		cout << tokensToString(tokens) << "\n";
		cout << TmpErrorMsg << "^\n";
		waitKeyPress();
		exit(EXIT_FAILURE);
	}

	// check if nums are valid
	TokenType lastTokenType = tokens.at(0).type;

	// check first token
	if (isTokenOperator(lastTokenType)) {
		TmpErrorMsg.insert(TmpErrorMsg.begin(), mapTokenToStrLentgth(tokens, 0), ' ');
		cout << "ERROR: unexpected operator\n";
		cout << tokensToString(tokens) << "\n";
		cout << TmpErrorMsg << "^\n";
		waitKeyPress();
		exit(EXIT_FAILURE);
	}

	for (size_t i = 1; i < tokens.size(); i++) {
		lastTokenType = tokens.at(i - 1).type;
		TokenType currentToken = tokens.at(i).type;
		switch (currentToken) {
		case TOKEN_NUMBER:
			if (lastTokenType == TOKEN_NUMBER) {
				//ERROR
				TmpErrorMsg.insert(TmpErrorMsg.begin(), mapTokenToStrLentgth(tokens, i), ' ');
				cout << "ERROR: unexpected number\n";
				cout << tokensToString(tokens) << "\n";
				cout << TmpErrorMsg << "^\n";
				waitKeyPress();
				exit(EXIT_FAILURE);
			}
			break;
		case TOKEN_PLUS:
			if (isTokenOperator(lastTokenType)) {
				// ERROR
				TmpErrorMsg.insert(TmpErrorMsg.begin(), mapTokenToStrLentgth(tokens, i), ' ');
				cout << "ERROR: unexpected operator\n";
				cout << tokensToString(tokens) << "\n";
				cout << TmpErrorMsg << "^\n";
				waitKeyPress();
				exit(EXIT_FAILURE);
			}
			break;
		case TOKEN_MINUS:
			if (isTokenOperator(lastTokenType)) {
				// ERROR
				TmpErrorMsg.insert(TmpErrorMsg.begin(), mapTokenToStrLentgth(tokens, i), ' ');
				cout << "ERROR: unexpected operator\n";
				cout << tokensToString(tokens) << "\n";
				cout << TmpErrorMsg << "^\n";
				waitKeyPress();
				exit(EXIT_FAILURE);
			}
			break;
		case TOKEN_MULTIPLY:
			if (isTokenOperator(lastTokenType)) {
				// ERROR
				TmpErrorMsg.insert(TmpErrorMsg.begin(), mapTokenToStrLentgth(tokens, i), ' ');
				cout << "ERROR: unexpected operator\n";
				cout << tokensToString(tokens) << "\n";
				cout << TmpErrorMsg << "^\n";
				waitKeyPress();
				exit(EXIT_FAILURE);
			}
			break;
		case TOKEN_DIVIDE:
			if (isTokenOperator(lastTokenType)) {
				// ERROR
				TmpErrorMsg.insert(TmpErrorMsg.begin(), mapTokenToStrLentgth(tokens, i), ' ');
				cout << "ERROR: unexpected operator\n";
				cout << tokensToString(tokens) << "\n";
				cout << TmpErrorMsg << "^\n";
				waitKeyPress();
				exit(EXIT_FAILURE);
			}
			break;
		case TOKEN_BRACET_OPEN:
			if (lastTokenType == TOKEN_NUMBER) {
				// ERROR
				TmpErrorMsg.insert(TmpErrorMsg.begin(), mapTokenToStrLentgth(tokens, i), ' ');
				cout << "ERROR: unexpected opening of bracket\n";
				cout << tokensToString(tokens) << "\n";
				cout << TmpErrorMsg << "^\n";
				waitKeyPress();
				exit(EXIT_FAILURE);
			}
			break;
		case TOKEN_BRACET_CLOSE:
			if (isTokenOperator(lastTokenType)) {
				// ERROR
				TmpErrorMsg.insert(TmpErrorMsg.begin(), mapTokenToStrLentgth(tokens, i), ' ');
				cout << "ERROR: unexpected operator\n";
				cout << tokensToString(tokens) << "\n";
				cout << TmpErrorMsg << "^\n";
				waitKeyPress();
				exit(EXIT_FAILURE);
			}
			if (lastTokenType == TOKEN_BRACET_OPEN) {
				// ERROR
				TmpErrorMsg.insert(TmpErrorMsg.begin(), mapTokenToStrLentgth(tokens, i), ' ');
				cout << "ERROR: expected number or expression\n";
				cout << tokensToString(tokens) << "\n";
				cout << TmpErrorMsg << "^\n";
				waitKeyPress();
				exit(EXIT_FAILURE);
			}
			break;
		default:
			cout << errorMsg << "ERROR: unknown token\n";
			waitKeyPress();
			exit(EXIT_FAILURE);
			break;
		}
	}
	// check last token
	if (isTokenOperator(tokens.at(tokens.size() - 1).type)) {
		TmpErrorMsg.insert(TmpErrorMsg.begin(), mapTokenToStrLentgth(tokens, tokens.size() - 1), ' ');
		cout << "ERROR: unexpected operator\n";
		cout << tokensToString(tokens) << "\n";
		cout << TmpErrorMsg << "^\n";
		waitKeyPress();
		exit(EXIT_FAILURE);
	}

	return;
}
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "tokenise.h"

using namespace std;

enum TokenType {
  TOKEN_NUMBER = 0,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_MULTIPLY,
  TOKEN_DIVIDE,
  TOKEN_BRACET_OPEN,
  TOKEN_BRACET_CLOSE
};

struct ParsedTokenAs {
  double number = 0;
  string expression = "";
};

struct singleParsedToken {
  TokenType type = TOKEN_NUMBER;
  string str = "";
  ParsedTokenAs as;
};

typedef std::vector<singleParsedToken> tokensParsed;

/// <summary>
/// check if string is an number
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
bool isStrNum(string str);

/// <summary>
/// parses TokenList and resolves types of tokens
/// </summary>
/// <param name="tokenList"></param>
/// <returns></returns>
tokensParsed parseTokens(tokens tokenList);

string tokenTypeToStr(TokenType tokenType);

void dumpParsedTokens(ostream* outstream, tokensParsed tokensParsedList);
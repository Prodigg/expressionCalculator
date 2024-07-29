#include "parse.h"

/// <summary>
/// check if string is an number
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
bool isStrNum(string str) {
  for (size_t i = 0; i < str.length(); i++) {
    if (!(isdigit(str.at(i)) || (str.at(i) == '.'))) return false;
  }
  return true;
}

/// <summary>
/// parses TokenList and resolves types of tokens
/// </summary>
/// <param name="tokenList"></param>
/// <returns></returns>
tokensParsed parseTokens(tokens tokenList) {
  tokensParsed returnTokenParsed;
  singleParsedToken currentParsedToken;
  for (size_t i = 0; i < tokenList.size(); i++) {
    currentParsedToken.str = tokenList.at(i);

    if (isStrNum(tokenList.at(i))) {
      currentParsedToken.type = TOKEN_NUMBER;
      currentParsedToken.as.number = atof(tokenList.at(i).c_str());
    }
    else if (tokenList.at(i) == "+") {
      currentParsedToken.type = TOKEN_PLUS;
      currentParsedToken.as.expression = "+";
    }
    else if (tokenList.at(i) == "-") {
      currentParsedToken.type = TOKEN_MINUS;
      currentParsedToken.as.expression = "-";
    }
    else if (tokenList.at(i) == "*") {
      currentParsedToken.type = TOKEN_MULTIPLY;
      currentParsedToken.as.expression = "*";
    }
    else if (tokenList.at(i) == "/") {
      currentParsedToken.type = TOKEN_DIVIDE;
      currentParsedToken.as.expression = "/";
    }
    else if (tokenList.at(i) == "(") {
        currentParsedToken.type = TOKEN_BRACET_OPEN;
        currentParsedToken.as.expression = "(";
    }
    else if (tokenList.at(i) == ")") {
        currentParsedToken.type = TOKEN_BRACET_CLOSE;
        currentParsedToken.as.expression = ")";
    }
    else {
      cout << errorMsg << "ERROR: tokenType not valid for token\"" << tokenList.at(i) << "\"\n";
      exit(EXIT_FAILURE);
    }
    returnTokenParsed.push_back(currentParsedToken);
  }
  return returnTokenParsed;
}

string tokenTypeToStr(TokenType tokenType) {
  switch (tokenType) {
  case TOKEN_NUMBER:
    return "TOKEN_NUMBER";
  case TOKEN_PLUS:
    return "TOKEN_PLUS";
  case TOKEN_MINUS:
    return "TOKEN_MINUS";
  case TOKEN_MULTIPLY:
    return "TOKEN_MULTIPLY";
  case TOKEN_DIVIDE:
    return "TOKEN_DIVIDE";
  case TOKEN_BRACET_OPEN:
      return "TOKEN_BRACET_OPEN";
  case TOKEN_BRACET_CLOSE:
      return "TOKEN_BRACET_OPEN";
  default:
    cout << "ERROR: valid TokenType not found, could not resole string\n";
  }
}

void dumpParsedTokens(ostream* outstream, tokensParsed tokensParsedList) {
  for (size_t i = 0; i < tokensParsedList.size(); i++) {
    cout << tokensParsedList.at(i).str << ": " << tokenTypeToStr(tokensParsedList.at(i).type) << "\n";
  }
  return;
}
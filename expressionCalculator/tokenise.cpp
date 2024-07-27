#include"tokenise.h"

/// <summary>
/// tokenises a string by delimitor
/// </summary>
/// <param name="str"></param>
/// <param name="delimitor"></param>
/// <returns>tokenList</returns>
tokens tokeniseStr(string str, string delimitor) {
  tokens tokenList;

  char* token;
  char* rest = _strdup(str.c_str());

  while ((token = strtok_s(rest, delimitor.c_str(), &rest))) {
    tokenList.push_back(token);
  }

  return tokenList;
}

/// <summary>
/// checks if a string is at the beginning of another string
/// </summary>
/// <param name="str"></param>
/// <param name="strToCheck"></param>
/// <returns></returns>
bool isStrAtBeginning(string str, string strToCheck) {
  // check bounds
  if (str.length() < strToCheck.length()) return false;

  // check if caracters DON'T match
  for (size_t i = 0; i < strToCheck.length(); i++) {
    if (str.at(i) != strToCheck.at(i)) return false;
  }

  // string is at beginning
  return true;
}

/// <summary>
/// Matches an beginning of an String to strings in an List (Warning: start of an string in the List must be exclusive)
/// </summary>
/// <param name="str"></param>
/// <param name="strList"></param>
/// <returns>matched String</returns>
string MatchStrAtBeginningList(string str, vector<string> strList) {
  for (size_t i = 0; i < strList.size(); i++) {
    if (isStrAtBeginning(str, strList.at(i))) {
      return strList.at(i);
    }
  }

  cout << errorMsg << "ERROR: no match for string\"" << str << "\". ";
  exit(EXIT_FAILURE);
}

/// <summary>
/// returns number string if an number is found at beginning of an given string
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
string MatchStrNumber(string str) {
  int i = 0;
  while (isdigit(str.at(i)) || str.at(i) == '.') {
    if (i >= str.length() - 1) {
      i++;
      break;
    }
    i++;
  }
  return str.substr(0, i);
}

/// <summary>
/// tokenises an String by an given ValidTokenList
/// </summary>
/// <param name="str"></param>
/// <param name="ValidtokenList"></param>
/// <returns>tokenList</returns>
tokens tokeniseStr(string str, vector<string> ValidtokenList) {
  tokens ReturnTokens;
  while (str.length() > 0) {
    // check if string beginning is an number
    string matchedStr = MatchStrNumber(str);

    if (matchedStr == "") {
      // try token list
      matchedStr = MatchStrAtBeginningList(str, ValidtokenList);
    }

    // consume stringMatched
    str.erase(0, matchedStr.size());

    ReturnTokens.push_back(matchedStr);
  }
  return ReturnTokens;
}

void dumpTokens(ostream* stream, tokens tokenList) {
  for (size_t i = 0; i < tokenList.size(); i++) {
    *stream << tokenList.at(i) << "\n";
  }
  return;
}
#pragma once
#include <iostream>
#include <string>
#include <vector>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define errorMsg __FILENAME__ << ":" << __LINE__ << ": "

typedef std::vector<std::string> tokens;

using namespace std;

/// <summary>
/// tokenises a string by delimitor
/// </summary>
/// <param name="str"></param>
/// <param name="delimitor"></param>
/// <returns>tokenList</returns>
tokens tokeniseStr(string str, string delimitor);

/// <summary>
/// checks if a string is at the beginning of another string
/// </summary>
/// <param name="str"></param>
/// <param name="strToCheck"></param>
/// <returns></returns>
bool isStrAtBeginning(string str, string strToCheck);

/// <summary>
/// Matches an beginning of an String to strings in an List (Warning: start of an string in the List must be exclusive)
/// </summary>
/// <param name="str"></param>
/// <param name="strList"></param>
/// <returns>matched String</returns>
string MatchStrAtBeginningList(string str, vector<string> strList);

/// <summary>
/// returns number string if an number is found at beginning of an given string
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
string MatchStrNumber(string str);

/// <summary>
/// tokenises an String by an given ValidTokenList
/// </summary>
/// <param name="str"></param>
/// <param name="ValidtokenList"></param>
/// <returns>tokenList</returns>
tokens tokeniseStr(string str, vector<string> ValidtokenList);

void dumpTokens(ostream* stream, tokens tokenList);

/// <summary>
/// strips spaces from given string 
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
string stripSpace(string str);
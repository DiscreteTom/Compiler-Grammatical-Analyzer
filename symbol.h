#pragma once

#include <vector>
#include <string>

using namespace std;

class SymbolTable
{
private:
	vector<string> symbols;

public:
	int getIndex(const string &str); // if str not exist, push it into symbols
	string getStr(int i);						 // return blank string if i is invalid
}

struct Symbol
{
	enum SymbolType
	{
		T, // terminator
		NT // non-terminator
	};
	SymbolType type;
	int index; // index in SymbolTable

	bool operator=(const Symbol &ano) { return ano.type == type && ano.index == index; }
}

const Symbol EPSILON = {Symbol::SymbolType::T, 0};

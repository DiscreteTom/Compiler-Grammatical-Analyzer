#pragma once

#include <vector>
#include <string>

using namespace std;

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
};

template <bool isTerminatorTable>
class SymbolTable
{
private:
	Symbol::SymbolType type;
	vector<string> symbols;

public:
	SymbolTable();
	int getIndex(const string &str); // if str not exist, push it into symbols
	string getStr(int i)const;						 // return blank string if i is invalid
};

const Symbol EPSILON = {Symbol::SymbolType::T, 0};

typedef SymbolTable<true> T_Table;
typedef SymbolTable<false> NT_Table;
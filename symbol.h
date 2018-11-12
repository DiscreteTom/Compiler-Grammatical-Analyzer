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

	bool operator==(const Symbol &ano) const { return ano.type == type && ano.index == index; }
	bool operator!=(const Symbol &ano) const { return !(*this == ano); }
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
	string getStr(int i) const;			 // return blank string if i is invalid
};

const Symbol EPSILON = {Symbol::SymbolType::T, 0};

typedef SymbolTable<true> T_Table;
typedef SymbolTable<false> NT_Table;

template <>
inline SymbolTable<true>::SymbolTable()
{
	getIndex("~"); // insert EPSILON to terminatorTable
}

template <bool b>
SymbolTable<b>::SymbolTable() {}

template <bool b>
int SymbolTable<b>::getIndex(const string &str)
{
	for (int i = 0; i < symbols.size(); ++i)
	{
		if (symbols[i] == str) // str exist
			return i;
	}
	// str does NOT exist, add it to table
	symbols.push_back(str);
	return symbols.size() - 1;
}

template <bool b>
string SymbolTable<b>::getStr(int i) const
{
	if (i >= 0 && i < symbols.size())
		return symbols[i];
	else
		return "";
}
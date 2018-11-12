#include "symbol.h"

using namespace std;

template <>
SymbolTable<true>::SymbolTable()
{
	getIndex("~"); // insert EPSILON to terminatorTable
}

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
string SymbolTable<b>::getStr(int i)const
{
	if (i >= 0 && i < symbols.size())
		return symbols[i];
	else
		return "";
}
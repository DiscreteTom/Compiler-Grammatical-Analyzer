#include "gramma.h"

#include <iostream>

using namespace std;

bool operator==(const Candidate &c1, const Candidate &c2)
{
	if (c1.size() != c2.size())
		return false;
	for (int i = 0; i < c1.size(); ++i)
	{
		if (c1[i] != c2[i])
			return false;
	}
	return true;
}

string GrammaTable::format(const string &str)
{
	string result;
	for (auto c : str)
	{
		if (c != ' ' && c != '\t')
			result += c;
	}
	//check format
	int i = str.find('-');
	if (str[i + 1] != '>')
		result = "";
	return result;
}

void GrammaTable::killDuplicated(int index)
{
	if (index == -1)
	{
		// eliminate same candidate for all gramma
		for (int i = 0; i < grammas.size(); ++i)
		{
			killDuplicated(i);
		}
	}
	else
	{
		// eliminate same candidate for grammas[index]
		for (int i = 0; i < grammas[index].size(); ++i)
		{
			for (int j = i + 1; j < grammas[index].size(); ++j)
			{
				if (grammas[index][i] == grammas[index][j]){
					// eliminate grammas[index][j]
					grammas[index].erase(grammas[index].begin() + j);
					--j;
				}
			}
		}
	}
}

int GrammaTable::insert(const string &grammaLine)
{
	if (error)
		return lineCount;
	++lineCount;
	string str = format(grammaLine);
	if (!str.length())
	{
		error = true;
		return lineCount; // ERROR
	}

	// get left Symbol string
	string left;
	left += str[0];
	int i = 1; // index of str
	while (i < str.length() && str[i] == '\'')
	{
		left += str[i];
		++i;
	}

	// check left Symbol
	int grammaIndex = ntTable.getIndex(left);
	if (grammaIndex == grammas.size()) //new symbol
	{
		grammas.push_back(Gramma());
	}

	// get right
	i += 2; // read "->"
	Candidate candidate;
	string sym; // current symbol string
	while (i < str.length())
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			sym += str[i];
			while (i + 1 < str.length() && str[i + 1] == '\'')
			{
				++i;
				sym += str[i];
			}
			//find this NT
			int index = ntTable.getIndex(sym);
			if (index == grammas.size()) // new NT
			{
				grammas.push_back(Gramma());
			}
			candidate.push_back({Symbol::SymbolType::NT, index});
			sym = "";
		}
		else if (str[i] == '$')
		{
			++i;
			while (i < str.length() && str[i] != '$')
			{
				sym += str[i];
				++i;
			}
			if (str[i] != '$')
			{
				// no matched $
				error = true;
				return lineCount;
			}
			else
			{
				// $ matched
				if (sym.length() < 2)
				{
					error = true;
					return lineCount;
				}
				else
				{
					// got a terminator
					int index = tTable.getIndex(sym);
					candidate.push_back({Symbol::SymbolType::T, index});
					sym = "";
				}
			}
		}
		else if (str[i] == '|')
		{
			if (candidate.size())
			{
				grammas[grammaIndex].push_back(candidate);
				candidate.clear();
			}
		}
		else
		{
			//other characters, inlcude '~', see them as terminator
			sym = str[i];
			while (i + 1 < str.length() && str[i + 1] == '\'')
			{
				sym += str[i + 1];
				++i;
			}
			int index = tTable.getIndex(sym);
			candidate.push_back({Symbol::SymbolType::T, index});
			sym = "";
		}
		++i;
	}
	if (candidate.size())
	{
		grammas[grammaIndex].push_back(candidate);
	}
	killDuplicated(grammaIndex);
	return 0;
}

void GrammaTable::output() const
{
	for (int i = 0; i < grammas.size(); ++i)
	{
		if (grammas[i].size())
			cout << ntTable.getStr(i) << " -> ";
		for (int j = 0; j < grammas[i].size(); ++j)
		{
			// each candidate
			for (int k = 0; k < grammas[i][j].size(); ++k)
			{
				// each symbol
				if (grammas[i][j][k].type == Symbol::SymbolType::NT)
				{
					cout << ntTable.getStr(grammas[i][j][k].index);
				}
				else // type == T
				{
					cout << tTable.getStr(grammas[i][j][k].index);
				}
			}
			if (j != grammas[i].size() - 1)
				cout << " | ";
		}
		if (grammas[i].size())
			cout << endl;
	}
	cout << endl;
}

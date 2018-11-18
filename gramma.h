#pragma once

#include "symbol.h"
#include <vector>
#include <set>
#include <map>

using namespace std;

using Candidate = vector<Symbol>;
using Gramma = vector<Candidate>;
using First = set<Symbol>;
using Follow = set<Symbol>;

bool operator==(const Candidate &c1, const Candidate &c2);

struct TableItem // item in predict analysis table M
{
	int ntIndex;				// non-terminator index in grammas
	int candidateIndex; // candidate index in grammas[ntIndex]
};

struct MapKey
{
	int ntIndex;
	int tIndex;
};

class GrammaTable
{
private:
	// input
	vector<Gramma> grammas;
	T_Table tTable;
	NT_Table ntTable;

	// error handling
	int lineCount;
	bool error;

	// process
	vector<First> firsts;
	vector<Follow> follows;
	map<MapKey, TableItem> M; // predict analysis table

	string format(const string &str); // discard blank chars, return blank string if format is wrong
	/**
	 * killDuplicated:
	 * eliminate same Candidate in grammas[index] if index != -1
	 * eliminate same Candidate in each Gramma when index == -1
	 */
	void killDuplicated(int index = -1);
	void killExplicitLeftRecursion(int index);
	void killEpsilon();
	void killLeftRecursion();
	void getFirsts();
	void getFollows();
	void getM();

public:
	GrammaTable() : lineCount(0), error(false){};

	int insert(const string &grammaLine); // return 0 if ok, otherwise return lineCount
	bool start();													// return false if error
	void output() const;

	bool ok() const { return !error; }
	int currentLineCount() const { return lineCount; }
};

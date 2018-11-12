#pragma once

#include "symbol.h"
#include <vector>

typedef vector<Symbol> Candidate;
typedef vector<Candidate> Gramma;

bool operator==(const Candidate &c1, const Candidate &c2);

class GrammaTable
{
private:
	vector<Gramma> grammas;
	T_Table tTable;
	NT_Table ntTable;

	// error handling
	int lineCount;
	bool error;

	string format(const string &str); // discard blank chars, return blank string if format is wrong
	/**
	 * killDuplicated:
	 * eliminate same Candidate in grammas[index] if index != -1
	 * eliminate same Candidate in each Gramma when index == -1
	 */
	void killDuplicated(int index = -1);

public:
	GrammaTable() : lineCount(0), error(false){};

	int insert(const string &grammaLine); // return 0 if ok, otherwise return lineCount
	bool start();													// return false if error
	void output() const;

	bool ok() const { return !error; }
	int currentLineCount() const { return lineCount; }
};

#include "gramma.h"
#include <iostream>

using namespace std;

void showDeveloper();

int main()
{
	showDeveloper();

	GrammaTable gt;
	string t;

	cout << "Please input grammas.\n";
	cout << "Input blank line to stop input.\n";

	getline(cin, t);
	bool flag = true;
	while (t.length() && flag)
	{
		if (gt.insert(t))
		{
			flag = false;
			cout << "Invalid input at line: " << gt.currentLineCount() << ".\n";
		}
		else
		{
			getline(cin, t);
		}
	}
	gt.generate();
	cout << "Output:\n";
	gt.output();

	flag = true;
	while (flag)
	{
		cout << "\nInput a line to parse, input blank line to stop.\n";
		getline(cin, t);
		if (t.length())
		{
			gt.parse(t);
		}
		else
		{
			flag = false;
		}
	}
	system("pause");
}

void showDeveloper()
{
	cout << "*************************************************************\n"
			 << "           Compiler-Grammatical-Analyzer(CGA)\n"
			 << "                 Written By DiscreteTom\n"
			 << "             See source code and report BUG at\n"
			 << "https://github.com/DiscreteTom/Compiler-Grammatical-Analyzer\n"
			 << "*************************************************************\n\n";
}
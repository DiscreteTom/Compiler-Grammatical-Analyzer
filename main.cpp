#include "gramma.h"
#include <iostream>

using namespace std;

int main()
{
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
	cout << "Output:\n";
	gt.output();
	system("pause");
}
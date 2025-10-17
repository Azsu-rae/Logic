#include "Logic.hpp"

#include <iostream>

int main() {

	string s;
	getline(cin, s);

	cout << "\n";

	Logic l(s);
	l.printTable();

	return 0;
}
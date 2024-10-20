#include "../include/Logic.hpp"

int main () {

	cout << endl;

	string s;
	getline(cin, s);

	cout << endl;

	Logic p(s);
	p.printTable();

	cout << endl;

	return 0;
}

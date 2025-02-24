#ifndef LOGIC_HPP
#define LOGIC_HPP

#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <string>
#include <unordered_map>

#include "Var.hpp"

using namespace std;

class Logic {
public:
	Var V;

	Logic() {}

	Logic(string s) {

		inputFormula(s);
	}

	static bool not_(bool p);
	static bool and_(bool p, bool q);
	static bool or_(bool p, bool q);
	static bool cond(bool p, bool q);
	
	void inputFormula(string s);
	void printTable();

	string implication(string var1, string var2);
	string conjunction(string var1, string var2);
	string disjunction(string var1, string var2);
	string negation(string var1);

private:
	vector<vector<bool>> T;

	// inputFormula's Helper methods
	Var createChild();
	void truthTable();
	bool getVar(string s);
	string postfixFormula(string s);

	// computeFormula's Helper methods
	bool lessPrio(string op, string var);
	string scratchWork(string op, string var1, string var2);
	pair<string,int> createFormula(char op, string var1, string var2);

	// operations helper method
	string computeFormula(char op, string var1, string var2);
};
#endif

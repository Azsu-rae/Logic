#include "Var.hpp"

int Var::sizeVar() {

	return var.size();
}

int Var::sizeFormula() {

	return formula.size();
}


void Var::insert(pair<string, int> s) {

	if (s.first.size() > 1 && formulaNum.find(s.first) == formulaNum.end()) {
		formulaNum.emplace(s.first, formula.size());
		formula.push_back(s);
	}
	else if (s.first.size() == 1) {
		insert(s.first[0]);
	}
}

void Var::insert(char c) {

	if (varNum.find(c) == varNum.end()) {
		varNum.emplace(c, var.size());
		var.push_back(c);
	}
}

int Var::get(string s) {

	if (s.size() > 1 && formulaNum.find(s) != formulaNum.end()) {
		return var.size() + formulaNum[s];
	}
	else if (s.size() == 1) {
		return get(s[0]);
	}
	else {
		return -1;
	}
}

int Var::get(char c) {

	if (varNum.find(c) != varNum.end()) {
		return varNum[c];
	}
	else {
		return -1;
	}
}

string Var::get(int i) {

	if (i < var.size()) {
		return string(1, var[i]);
	}
	else if (i < formula.size() + var.size()) {
		return formula[i - var.size()].first;
	}
	else {
		return "";
	}
}

int Var::getPrio(string s) {

	if (get(s) != -1 && s.size() > 1) {
		return formula[formulaNum[s]].second;
	}
	else {
		return -1;
	}
}
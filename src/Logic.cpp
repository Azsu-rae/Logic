#include "../include/Logic.hpp"

int exp(int a, int n) {

	if (!n) {
		return 1;
	} else {
		return a*exp(a, n-1);
	}
}

bool Logic::not_(bool p) {

	return !p;
}

bool Logic::and_(bool p, bool q) {

	return p && q;
}

bool Logic::or_(bool p, bool q) {

	return p || q;
}

bool Logic::cond(bool p, bool q) {

	return !p || q;
}

bool Logic::getVar(string s) {

	int n = V.sizeVar();

	for (char c : s) {
		if (c >= 97 && c <= 122) {
			V.insert(c);
		}
	} 

	return V.sizeVar() > n;
}

string Logic::postfixFormula(string s) {

	unordered_map<char,int> prio = {{'~', 1},{'A', 2},{'O', 3},{'-', 4}};
	stack<pair<char,int>> op;
	string ans;
	int p = 0;
	for (char c : s) {
		int temp = c;
		if (temp >= 97 && temp <= 122) {
			ans.push_back(c);
		} else if (c == '~' || c == 'O' || c == 'A' || c == '-') {
			while (!op.empty() && (p==op.top().second ? prio.at(op.top().first)<=prio.at(c) : p<op.top().second)) {
				ans.push_back(op.top().first);
				op.pop();
			} 
			op.push(make_pair(c, p));
		} else if (c == '(') {
			p++;
		} else if (c == ')') {
			p--;
		}
	} 
	while (!op.empty()) {
		ans.push_back(op.top().first);
		op.pop();
	} 

	return ans;
}

Var Logic::createChild() {

	Var newV;
	int n = V.sizeVar();
	for (int i=0;i<n;i++) {
		newV.insert(V.get(i)[0]);
	} 

	return newV;
}

void Logic::truthTable() {

	int n = V.sizeVar();
	int rows = exp(2, n);
	int half = rows;
	bool value = true;
	vector<vector<bool>> T(n, vector<bool>(exp(2,n)));
	for (int i=0;i<n;i++) {
		half /= 2;
		for (int j=0;j<rows;j++) {
			if (!(j%half)) {
				value = !value;
			} T[i][j] = value;
		}
	} 
	this->T = T;

	Var oldV = V;
	V = createChild();
	int m = V.sizeFormula();
	for (int i=0;i<m;i++) {
		inputFormula(oldV.get(n+i));
	} 
}

void Logic::inputFormula(string s) {

	if (getVar(s)) {
		truthTable();
	} 

	if (V.get(s) != -1 || s.size() <= 1) {
		return;
	} 

	string postfix = postfixFormula(s);
	stack<string> v;
	for (char c : postfix) {
		int temp = c;
		if (temp >= 97 && temp <= 122) {
			v.push(string(1, c));
		} else {
			string v1, v2, f;
			v1 = v.top(); v.pop(); 
			if (c != '~') {
				v2 = v.top(); v.pop();
			} 
			switch (c) {
				case '~':
					f = negation(v1);
					break;
				case 'A':
					f = conjunction(v2, v1);
					break;
				case 'O':
					f = disjunction(v2, v1);
					break;
				case '-':
					f = implication(v2, v1);
					break;
				default: 
					cout << "postfix is messed up!" << endl;
					cout << c << endl;
			} 
			v.push(f);
		}
	}
}

bool Logic::lessPrio(string op, string var) {

	unordered_map<string,int> opPrio = {{"~",1},{" AND ",2},{" OR ",3},{" -> ",4}};
	if (var.size() <= 1) {
		return false;
	} else {
		return V.getPrio(var) > opPrio.at(op); 
	}
}

string Logic::scratchWork(string op, string var1, string var2) {

	if (lessPrio(op, var1)) {
		var1 = "("+var1+")";
	} 
	if (lessPrio(op, var2)) {
		var2 = "("+var2+")";
	} 

	return  var1 + op + var2;
}

pair<string,int> Logic::createFormula(char op, string var1, string var2) {

	string newFormula;
	int prio;
	switch (op) {
		case 'i': 
			newFormula = scratchWork(" -> ", var1, var2);
			prio = 4;
			break;
		case 'c':
			newFormula = scratchWork(" AND ", var1, var2);
			prio = 2;
			break;
		case 'd':
			newFormula = scratchWork(" OR ", var1, var2);
			prio = 3;
			break;
		case 'n':
			newFormula = scratchWork("~", var1, var2);
			prio = 1;
			break;
		default: 
			cout << "ERROR" << endl;
		break;
	} 

	return make_pair(newFormula, prio);
}

string Logic::computeFormula(char op, string var1, string var2) {

	pair<string,int> newFormula = createFormula(op, var1, var2);
	if (V.get(newFormula.first) != -1) {
		return newFormula.first;
	} 

	inputFormula(var1);
	inputFormula(var2);

	int rows = exp(2,V.sizeVar()), s = T.size(), column1 = V.get(var1), column2 = V.get(var2);
	T.push_back(vector<bool>(rows));
	for (int i=0;i<rows;i++) {
		bool ans;
		switch (op) {
			case 'n': 
				ans = not_(T[column2][i]);
				break;
			case 'c': 
				ans = and_(T[column1][i], T[column2][i]);
				break;
			case 'd':
				ans = or_(T[column1][i], T[column2][i]);
				break;
			case 'i': 
				ans = cond(T[column1][i], T[column2][i]);
				break;
			default:
				cout << "ERROR" << endl;
			break;
		} 
		T[s][i] = ans;
	} 

	V.insert(newFormula);
	return newFormula.first;
}

string Logic::implication(string var1, string var2) {

	return computeFormula('i', var1, var2);
}

string Logic::conjunction(string var1, string var2) {

	return computeFormula('c', var1, var2);
}

string Logic::disjunction(string var1, string var2) {

	return computeFormula('d', var1, var2);
}

string Logic::negation(string var1) {

	return computeFormula('n', "", var1);
}

void Logic::printTable() {

	int columns = T.size(), rows = exp(2,V.sizeVar()), residue = 0, length = 0;
	vector<int> pos;
	for (int i=0;i<rows+2;i++) {
		for (int j=0;j<columns;j++) {
			if (!i) {
				cout << V.get(j) << "|";
				length += V.get(j).size() + 1;
				pos.push_back(length-1);
			} else if (i == 1) {
				int p = 0;
				for (int i=0;i<length;i++) {
					if (i != pos[p]) {
						cout << "-";
					} else {
						cout << "+";
						p++;
					}
				} 
				break;
			} else {
				cout << T[j][i-2];
				while (residue--) {
					cout << " ";
				} 
				cout << "|";
				if (j+1>=V.sizeVar() && V.sizeFormula() && j != columns-1) {
					int numSpaces = V.get(j+1).size();
					int half = numSpaces/2;
					while (half--) {
						cout << " ";
					} 
					residue = numSpaces/2-!(numSpaces%2);
				} else {
					residue = 0;
				}
			} 
		} 
		cout << endl;
	}
}

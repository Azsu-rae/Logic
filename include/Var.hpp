#ifndef VAR_HPP
#define VAR_HPP

#include <vector>
#include <utility>
#include <string>
#include <unordered_map>

using namespace std;

class Var {
public:
	int sizeVar();
	int sizeFormula();

	void insert(pair<string, int> s);
	void insert(char c);

	string get(int i);
	int get(string s);
	int get(char c);

	int getPrio(string s);
private:
	unordered_map<char, int> varNum; // var -> order of input to use in the below vector
	vector<char> var;

	unordered_map<string, int> formulaNum; // formula -> order of input to use in the below vector
	vector<pair<string, int>> formula;
};
#endif
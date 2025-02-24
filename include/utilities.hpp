#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <iostream>

using namespace std;

int exp(int a, int n) {

	if (!n) {
		return 1;
	} else {
		return a*exp(a, n-1);
	}
}

#endif

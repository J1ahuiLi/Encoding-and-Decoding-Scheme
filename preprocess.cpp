#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include "defns.h"

using namespace std;

int preprocessAlgorithm(symbol Symbols[]) {
	//Initialize Symbols
	for (int i = 0; i < NSYMBOLS; i++) {
		Symbols[i].symbol = '\0';
		Symbols[i].freq = 0;
		Symbols[i].parent = NULL;
		Symbols[i].left = NULL;
		Symbols[i].right = NULL;
		for (int i = 0; i < E_LEN; i++) {
			Symbols[i].encoding[i] = '\0';
		}
	}

    Symbols[10].freq = 1;
	Symbols[10].symbol = '\n';

	char s;
	while (cin.get(s)) {
		Symbols[(int)s].symbol = s;
		Symbols[(int)s].freq++;
	}

	for (int i = 0; i < NSYMBOLS; i++) {
		if (Symbols[i].freq != 0) {
			cout << i << '\t' << Symbols[i].freq << '\n';
		}

	}
	
}

int main()
{
	//The Preprocessing Algorithm
	symbol Symbols[NSYMBOLS];
	preprocessAlgorithm(Symbols);

	return 0;
}


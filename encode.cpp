#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include "defns.h"
#include "insertion.h"
#include "merge.h"

#define	NALPHA  52
#define	NNONALPHA   76

using namespace std;

void encodeAlgorithm(symbol Symbols[], tree Alpha[], tree NonAlpha[]) {
    int alpha_count = 0;
    int nonAlpha_count = 0;

    //initialization
    for (int i = 0; i < 2 * NALPHA - 1; i++) {
        Alpha[i].freq = 0;
        Alpha[i].symbol = '\0';
        Alpha[i].index = i;
        Alpha[alpha_count].root = NULL;
    }
    for (int i = 0; i < 2 * NNONALPHA - 1; i++) {
        NonAlpha[i].freq = 0;
        NonAlpha[i].symbol = '\0';
        NonAlpha[i].index = i;
        NonAlpha[nonAlpha_count].root = NULL;
    }

    //Build tree-structured array
    for (int m = 0; m < NSYMBOLS; m++) {
        if ((m >= 65 && m <= 90) || (m >= 97 && m <= 122)) {
            if (Symbols[m].freq != 0) {
                Alpha[alpha_count].freq = Symbols[m].freq;
                Alpha[alpha_count].index = m;
                Alpha[alpha_count].symbol = Symbols[m].symbol;
                Alpha[alpha_count].root = &Symbols[m];
                alpha_count++;
            }
        }
        else {
            if (Symbols[m].freq != 0) {
                NonAlpha[nonAlpha_count].freq = Symbols[m].freq;
                NonAlpha[nonAlpha_count].index = m;
                NonAlpha[nonAlpha_count].symbol = Symbols[m].symbol;
                NonAlpha[nonAlpha_count].root = &Symbols[m];
                nonAlpha_count++;
            }
        }
    }
}

//count tree number
int cTNum(tree arrAy[], int Num) {
    int numArray = 0;
    for (int i = 0; i < 2 * Num - 1; i++) {
        if (arrAy[i].freq > 0) {
            numArray++;
        }
    }
    return numArray;
}

//count symbol number
int cSNum(symbol arrAy[]) {
    int numArray = 0;
    for (int i = 0; i < 52; i++) {
        if (arrAy[i].freq > 0) {
            numArray++;
        }
    }
    return numArray;
}


//find the two a and b with the smallest freq
void Select(tree HuffTree[], int* a, int* b, int n) {
    int i;
    int weight = 0;
    for (i = 0; i < n; i++) {
        if (HuffTree[i].root->parent != NULL) {
            continue;
        }
        else {
            if (weight == 0) {
                weight = HuffTree[i].freq;
                *a = i;
            }
            else {
                if (HuffTree[i].freq < weight)
                {
                    weight = HuffTree[i].freq;
                    *a = i;
                }
            }
        }
    }
    weight = 0;
    for (i = 0; i < n; i++) {
        if (HuffTree[i].root->parent != NULL || (i == *a)) {
            continue;
        }
        else {
            if (weight == 0) {
                weight = HuffTree[i].freq;
                *b = i;
            }
            else {
                if (HuffTree[i].freq < weight) {
                    weight = HuffTree[i].freq;
                    *b = i;
                }
            }
        }
    }
    int temp;
    if ((HuffTree[*a].root->left < HuffTree[*b].root->left) && ((char)HuffTree[*a].symbol < (char)HuffTree[*b].symbol)) {
        temp = *a;
        *a = *b;
        *b = temp;
    }
}

//build binary tree
void huffTree(tree bTree[],symbol t[], int eNum) {
    for (int i = 0; i <= NSYMBOLS - 1; i++) {
        t[i].symbol = '\0';
        t[i].freq = 0;
        t[i].parent = NULL;
        t[i].left = NULL;
        t[i].right = NULL;
        for (int a = 0; a < E_LEN; a++) {
            t[i].encoding[a] = '\0';
        }
    }

    int i = 0;
    for (int addNode = eNum; addNode < 2 * eNum - 1; addNode++) {
        int i1 = 0;
        int i2 = 0;

        Select(bTree, &i1, &i2, addNode);
        t[i].freq = bTree[i1].freq + bTree[i2].freq;
        bTree[i1].root->parent = &t[i];
        bTree[i2].root->parent = &t[i];
        t[i].left = bTree[i1].root;
        t[i].right = bTree[i2].root;
        bTree[addNode].root = &t[i];
        bTree[addNode].freq = t[i].freq;

        i++;
    }

}

//ebcode
void Huff_Code(tree Alpha[], int numberA) {
    for (int i = 0; i < numberA; i++) {
        string encodeNum = "";
        int l = 0;
        symbol* t;
        t = Alpha[i].root;

        while (t->parent != NULL) {
            symbol* k;
            k = t->parent;
            if (k->left == t) {
                encodeNum = encodeNum + "0";
            }
            else {
                encodeNum = encodeNum + "1";
            }
            l++;
            t = t->parent;
        }

        for (int l = 0; l <= encodeNum.size() - 1; l++) {
            Alpha[i].root->encoding[l] = (char)encodeNum[l];
        }
    }
}



int main(int argc, char *argv[])
{
    symbol Symbols[NSYMBOLS];
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

    ifstream file;
    file.open(argv[1], ios::in);
    if (file.fail()) {
        cout << "error" << endl;
        file.close();
    }
    else {
        int i = 0;
        while (!file.eof()) {
            int a;
            file >> a;
            Symbols[a].symbol = char(a);
            file >> Symbols[a].freq;

        }
        file.close();
    }

    //Build symbol-structured array
    tree Alpha[2 * NALPHA - 1];
    tree NonAlpha[2 * NNONALPHA - 1];
    encodeAlgorithm(Symbols, Alpha, NonAlpha);

    int numberA = cTNum(Alpha, NALPHA);
    int numberB = cTNum(NonAlpha, NNONALPHA);

    if (argv[2] == "insertion") {
        insertionSort(Alpha, cTNum(Alpha, NALPHA));
        insertionSort(NonAlpha, cTNum(NonAlpha, NNONALPHA));
    }
    else if (argv[2] == "merge") {
		mergeSort(Alpha, 0, cTNum(Alpha, NALPHA) - 1);
		mergeSort(NonAlpha, 0, cTNum(NonAlpha, NNONALPHA) - 1);
    }

    symbol tAlpha[NSYMBOLS];
    symbol tNonAlpha[NSYMBOLS];

    huffTree(Alpha, tAlpha, cTNum(Alpha, NALPHA));
    huffTree(NonAlpha, tNonAlpha, cTNum(NonAlpha, NNONALPHA));

    symbol Root;
    Root.freq = Alpha[cTNum(Alpha, NALPHA) - 1].freq + NonAlpha[cTNum(NonAlpha, NNONALPHA) - 1].freq;
    Alpha[cTNum(Alpha, NALPHA) - 1].root->parent = &Root;
    NonAlpha[cTNum(NonAlpha, NNONALPHA) - 1].root->parent = &Root;
    Root.left = Alpha[cTNum(Alpha, NALPHA) - 1].root;
    Root.right = NonAlpha[cTNum(NonAlpha, NNONALPHA) - 1].root;
    Root.parent = NULL;

    Huff_Code(Alpha, numberA);
    Huff_Code(NonAlpha, numberB);

    //print
    cout << numberA + numberB << '\n';
    for (int i = 0; i < NSYMBOLS; i++) {
        if (Symbols[i].freq > 0) {
            cout << i << '\t' << Symbols[i].symbol << '\t';
            for (int m = E_LEN - 1; m >= 0; m--) {
                if (Symbols[i].encoding[m] >= 0 && Symbols[i].encoding[m] != '\0') {
                    cout << Symbols[i].encoding[m];
                }
            }
            cout << '\n';
        }
    }
    cout << '\n';

    char s;
    while (cin.get(s)) {
        for (int i = 0; i < NSYMBOLS; i++) {
            if (s == Symbols[i].symbol) {
                for (int m = E_LEN - 1; m >= 0; m--) {
                    if (Symbols[i].encoding[m] >= 0 && Symbols[i].encoding[m] != '\0') {
                        cout << Symbols[i].encoding[m];
                    }
                }
            }
        }
    }  
    for (int m = E_LEN - 1; m >= 0; m--) {
                    if (Symbols[10].encoding[m] >= 0 && Symbols[10].encoding[m] != '\0') {
                        cout << Symbols[10].encoding[m];
                    }
                }

    return 0;
}

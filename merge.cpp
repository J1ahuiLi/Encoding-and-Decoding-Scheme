#include<iostream>
#include "defns.h"
#include "merge.h"

using namespace std;

void merge(tree a[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int i, j, k;
    tree* L = new tree[n1 + 1];
    tree* R = new tree[n2 + 1];
    for (i = 0; i < n1; i++)
        L[i] = a[p + i];
    for (j = 0; j < n2; j++)
        R[j] = a[q + j + 1];
    L[n1].freq = 11111111;
    R[n2].freq = 11111111;

    for (i = 0, j = 0, k = p; k <= r; k++) {
        if (L[i].freq <= R[j].freq)
            a[k] = L[i++];
        else
            a[k] = R[j++];
    }

    delete[]L;
    delete[]R;
}

void mergeSort(tree a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

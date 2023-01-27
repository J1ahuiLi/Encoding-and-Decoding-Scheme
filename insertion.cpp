#include "insertion.h"
#include "defns.h"

void insertionSort(struct tree a[], int len)
{
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (a[i].freq >= 1) {
            count++;
        }
    }

    tree key;
    key.freq = 0;
    key.symbol = '\0';
    key.index = -1;

    for (int j = 1; j < count; j++) {
        key = a[j];
        int i = j - 1;
        while (i >= 0 && a[i].freq > key.freq) {
            a[i + 1] = a[i];
            i--;
        }
        a[i + 1] = key;
    }
}
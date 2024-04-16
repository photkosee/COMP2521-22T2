// Phot Koseekrainiramon (z5387411)
// on 15/08/2022

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List flas(List l) {
    if (l == NULL) {
        return NULL;
    }
    List curr = l;
    int countLen = 1;
    int totalLen = 1;
    int currIndex = 0;
    int index = 0;
    while (curr->next != NULL) {
        currIndex++;
        if (curr->value < curr->next->value) {
            countLen++;
        } else {
            if (countLen > totalLen) {
                totalLen = countLen;
                index = currIndex - countLen;
            }
            countLen = 1;
        }
        curr = curr->next;
    }
    if (totalLen < 2) {
        return NULL;
    }

    List curr2 = l;
    for (int i = 0; i <= index - 1; i++) {
        curr2 = curr2->next;
    }

    return curr2;
}


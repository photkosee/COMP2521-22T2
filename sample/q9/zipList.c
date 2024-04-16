// Phot Koseekrainiramon (z5387411)
// on 11/08/2022

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

// Worst case time complexity of this solution: O(n + m)
List zipList(List l1, int x, List l2, int y) {
    List l = ListNew();
    if ((l1->first == NULL && l2->first == NULL) || (x == 0 && y == 0) ||
        (l1->first == NULL && y == 0) || (l2->first == NULL && x == 0)) {
        return l;
    }
    if (y == 0) {
        Node currL1 = l1->first;
        Node n = newNode(currL1->value);
        l->first = n;
        l->last = n;
        currL1 = currL1->next;
        Node currL = l->first;
        for (int i = 1; i < x && currL1 != NULL; i++) {
            Node n = newNode(currL1->value);
            currL->next = n;
            currL = currL->next;
            l->last = n;
            currL1 = currL1->next;
        }

        while (currL1 != NULL) {
            for (int i = 0; i < x && currL1 != NULL; i++) {
                Node n = newNode(currL1->value);
                currL->next = n;
                currL = currL->next;
                l->last = n;
                currL1 = currL1->next;
            }
        }
    } else if (x == 0) {
        Node currL2 = l2->first;
        Node n = newNode(currL2->value);
        l->first = n;
        l->last = n;
        currL2 = currL2->next;
        Node currL = l->first;
        for (int i = 1; i < y && currL2 != NULL; i++) {
            Node n = newNode(currL2->value);
            currL->next = n;
            currL = currL->next;
            l->last = n;
            currL2 = currL2->next;
        }

        while (currL2 != NULL) {
            for (int i = 0; i < y && currL2 != NULL; i++) {
                Node n = newNode(currL2->value);
                currL->next = n;
                currL = currL->next;
                l->last = n;
                currL2 = currL2->next;
            }
        }
    } else if (l1->first != NULL) {
        Node currL1 = l1->first;
        Node n = newNode(currL1->value);
        l->first = n;
        l->last = n;
        currL1 = currL1->next;
        Node currL2 = l2->first;
        Node currL = l->first;
        for (int i = 1; i < x && currL1 != NULL; i++) {
            Node n = newNode(currL1->value);
            currL->next = n;
            currL = currL->next;
            l->last = n;
            currL1 = currL1->next;
        }

        while (currL1 != NULL || currL2 != NULL) {
            for (int i = 0; i < y && currL2 != NULL; i++) {
                Node n = newNode(currL2->value);
                currL->next = n;
                currL = currL->next;
                l->last = n;
                currL2 = currL2->next;
            }
            for (int i = 0; i < x && currL1 != NULL; i++) {
                Node n = newNode(currL1->value);
                currL->next = n;
                currL = currL->next;
                l->last = n;
                currL1 = currL1->next;
            }
        }
    } else {
        Node currL2 = l2->first;
        Node n = newNode(currL2->value);
        l->first = n;
        l->last = n;
        currL2 = currL2->next;
        Node currL1 = l1->first;
        Node currL = l->first;
        for (int i = 1; i < y && currL2 != NULL; i++) {
            Node n = newNode(currL2->value);
            currL->next = n;
            currL = currL->next;
            l->last = n;
            currL2 = currL2->next;
        }

        while (currL1 != NULL || currL2 != NULL) {
            for (int i = 0; i < x && currL1 != NULL; i++) {
                Node n = newNode(currL1->value);
                currL->next = n;
                currL = currL->next;
                l->last = n;
                currL1 = currL1->next;
            }
            for (int i = 0; i < y && currL2 != NULL; i++) {
                Node n = newNode(currL2->value);
                currL->next = n;
                currL = currL->next;
                l->last = n;
                currL2 = currL2->next;
            }
        }
    }

    return l;
}


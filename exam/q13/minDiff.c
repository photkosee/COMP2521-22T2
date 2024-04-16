// Phot Koseekrainiramon (z5387411)
// on 15/08/2022

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

typedef struct list *List;

struct list {
    int value;
    List next;
};

List newNode2(int value);
List ListNew(void);
void ListFree(List l);
List ListInsert(List l, int value);
void getKey(BSTree t, int l, List new);

int minDiff(BSTree t, int l) {
    if (l == 0) {
        return 0;
    }
    List new = ListNew();
    getKey(t, l, new);
    if (new == NULL || new->next == NULL) {
        ListFree(new);
        return 0;
    }
    List curr = new;
    int minimum = abs(curr->value - curr->next->value);
    curr = curr->next;
    while (curr->next != NULL) {
        int tmp = abs(curr->next->value - curr->value);
        if (tmp < minimum) {
            minimum = tmp;
        }
    }
    ListFree(new);
    return minimum;
}

void getKey(BSTree t, int l, List new) {
    if (t == NULL) {
        return;
    }
    if (l == 0) {
        new = ListInsert(new, t->key);
    } else {
        getKey(t->left, l - 1, new);
        getKey(t->right, l - 1, new);
    }
}

// Creates a new empty list
List ListNew(void) {
    return NULL;
}

// Frees all memory associated with the given list
void ListFree(List l) {
    List curr = l;
    while (curr != NULL) {
        List temp = curr;
        curr = curr->next;
        free(temp);
    }
}

// Inserts a value at the end of the given list
// Returns the beginning of the updated list
List ListInsert(List l, int value) {
    List n = newNode2(value);
    if (l == NULL) {
        return n;
    }
    List curr = l;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = n;
    return l;
}

// Creates a new list node
List newNode2(int value) {
    List n = malloc(sizeof(*n));
    assert(n != NULL);
    n->value = value;
    n->next = NULL;
    return n;
}

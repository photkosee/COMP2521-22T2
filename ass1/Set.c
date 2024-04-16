// Implementation of the Set ADT using a balanced BST
// COMP2521 22T2 Assignment 1
// Phot Koseekrainiramon (z5387411)
// on 22/06/2022 - 30/06/2022

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Set.h"
#include "SetStructs.h"

#define EMPTY 0

typedef struct node *Tree;

// Group 1
static void TreeFree(Tree t);
static Tree TreeInsert(Set s, Tree t, int item, Tree parent);
static int max(int a, int b);
static int height (Tree t);
static int updateHeight(Tree t);
static int getBalance(Tree t);
static Tree RotateLeft(Tree current);
static Tree RotateRight(Tree current);
static Tree newTree(Set s, int item, Tree parent);
static void setTreePointer(Tree new, Tree parent, int item);
static bool TreeContains(Tree t, int item);
static void PrintTree(Tree t);
// Group 2
static Tree TreeInsertUnion(Set s, Tree t);
static Tree TreeInsertIntersection(Set s, Tree t1, Tree t2);
static Tree TreeInsertDifference(Set s, Tree t1, Tree t2);
static bool TreeSubset(Tree t1, Tree t2);
static int TreeFloor(Tree t, int item);
static int TreeCeiling(Tree t, int item);

////////////////////////////////////////////////////////////////////////
// Basic Operations

/**
 * Creates a new empty set
 */
Set SetNew(void) {
	Set new = malloc(sizeof(*new));
	if (new == NULL) {
		fprintf(stderr, "ERROR");
		exit(EXIT_FAILURE);
	}
	new->size = EMPTY;
	new->max = NULL;
	new->min = NULL;
	new->tree = NULL;
	return new;
}

/**
 * Frees all memory associated with the given set
 */
void SetFree(Set s) {
	if (s == NULL) {
		return;
	}
	TreeFree(s->tree);
	free(s);
}

/**
 * Inserts an item into the set
 */
void SetInsert(Set s, int item) {
	s->tree = TreeInsert(s, s->tree, item, s->tree);
	return;
}

/**
 * Returns the number of elements in the set
 */
int SetSize(Set s) {
	return s->size;
}

/**
 * Returns true if the set contains the given item, and false otherwise
 */
bool SetContains(Set s, int item) {
	if (item == s->max->item || item == s->min->item) {
		return true;
	}
	return TreeContains(s->tree, item);
}

/**
 * Prints the given set in the format
 * {elem1, elem2, elem3}
 */
void SetShow(Set s) {
	printf("{");
	PrintTree(s->tree);
	printf("}");
}

////////////////////////////////////////////////////////////////////////
// Further Operations

/**
 * Returns a new set representing the union of the two sets
 */
Set SetUnion(Set s1, Set s2) {
	Set new = SetNew();
	new->tree = TreeInsertUnion(new, s1->tree);
	new->tree = TreeInsertUnion(new, s2->tree);
	return new;
}

/**
 * Returns a new set representing the intersection of the two sets
 */
Set SetIntersection(Set s1, Set s2) {
	Set new = SetNew();
	new->tree = TreeInsertIntersection(new, s1->tree, s2->tree);
	return new;
}

/**
 * Returns a new set representing the set difference s1 - s2
 */
Set SetDifference(Set s1, Set s2) {
	Set new = SetNew();
	new->tree = TreeInsertDifference(new, s1->tree, s2->tree);
	return new;
}

/**
 * Returns true if the two sets are equal, and false otherwise
 */
bool SetEquals(Set s1, Set s2) {
	if (s1->size != s2->size) {
		return false;
	} else if (s1->size == EMPTY && s2->size == EMPTY) {
		return true;
	} else if (s1->min->item != s2->min->item || 
	s1->max->item != s2->max->item) {
		return false;
	}
	return TreeSubset(s1->tree, s2->tree);
}

/**
 * Returns true if set s1 is a subset of set s2, and false otherwise
 */
bool SetSubset(Set s1, Set s2) {
	if (s1->size == EMPTY) {
		return true;
	} else if (s1->size > s2->size || s2->size == EMPTY) {
		return false;
	}
	return TreeSubset(s1->tree, s2->tree);
}

/**
 * Finds the floor of a given item in a set
 */
int SetFloor(Set s, int item) {
	if (s->size == EMPTY || s->min->item > item) {
		return UNDEFINED;
	} else if (s->min->item == item) {
		return item;
	} else if (s->max->item <= item) {
		return s->max->item;
	} else {
		return TreeFloor(s->tree, item);
	}
}

/** 
 * Returns the ceiling of a given item in a set
 */
int SetCeiling(Set s, int item) {
	if (s->size == EMPTY || s->max->item < item) {
		return UNDEFINED;
	} else if (s->min->item >= item) {
		return s->min->item;
	} else if (s->max->item == item) {
		return item;
	} else {
		return TreeCeiling(s->tree, item);
	}
}

////////////////////////////////////////////////////////////////////////
// Cursor Operations

/**
 * Creates a new cursor positioned at the smallest element of the set
 */
SetCursor SetCursorNew(Set s) {
	SetCursor new = malloc(sizeof(*new));
	if (new == NULL) {
		fprintf(stderr, "ERROR");
		exit(EXIT_FAILURE);
	}
	new->tree = s->min;
	new->s = s;
	return new;
}

/**
 * Frees all memory associated with the given cursor
 */
void SetCursorFree(SetCursor cur) {
	free(cur);
	return;
}

/**
 * Returns the element at the cursor's current position, and then moves
 * the cursor to the next greatest element. If there is no next greatest
 * element, then all subsequent calls to SetCursorNext on this cursor
 * should return UNDEFINED.
 */
int SetCursorNext(SetCursor cur) {
	if (cur->tree == NULL) {
		return UNDEFINED;
	}
	int item = cur->tree->item;
	cur->tree = cur->tree->next;
	return item;
}

////////////////////////////////////////////////////////////////////////
// Helper functions

// Group 1

// Free all Trees
static void TreeFree(Tree t) {
	if (t == NULL) {
		return;
	}
	TreeFree(t->left);
	TreeFree(t->right);
	free(t);
}

// Inserts an item into the tree and rebalancing itself
static Tree TreeInsert(Set s, Tree t, int item, Tree parent) {
	if (t == NULL) {
		return newTree(s, item, parent);
	} else if (item < t->item) {
		t->left = TreeInsert(s, t->left, item, t);
	} else if (item > t->item) {
		t->right = TreeInsert(s, t->right, item, t);
	} else { // (item == t->item)
		return t;
	}

	t->height = updateHeight(t);
	int balance = getBalance(t);

	if (balance > 1 && item < t->left->item) {
		return RotateRight(t);
	}
	if (balance < - 1 && item > t->right->item) {
		return RotateLeft(t);
	}
	if (balance > 1 && item > t->left->item) {
		t->left = RotateLeft(t->left);
		return RotateRight(t);
	}
	if (balance < -1 && item < t->right->item) {
		t->right = RotateRight(t->right);
		return RotateLeft(t);
	}
	return t;
}

// Return the bigger integer
static int max(int a, int b) {
	if (a >= b) {
		return a;
	}
	return b;
}

// Return height of the tree
static int height(Tree t) {
	if (t == NULL) {
		return EMPTY;
	}
	return t->height;
}

// Updating height of the tree
static int updateHeight(Tree t) {
	return max(height(t->left), height(t->right)) + 1;
}

// Get balance of the tree
static int getBalance(Tree t) {
	if (t == NULL) {
		return EMPTY;
	} else {
		return height(t->left) - height(t->right);
	}
}

// Left rotating subtree rooted
static Tree RotateLeft(Tree current) {
	Tree new = current->right;
	Tree T2 = new->left;
	new->left = current;
	current->right = T2;

	current->height = updateHeight(current);
	new->height = updateHeight(new);

	return new;
}

// Right rotating subtree rooted
static Tree RotateRight(Tree current) {
	Tree new = current->left;
	Tree T2 = new->right;
	new->right = current;
	current->left = T2;

	current->height = updateHeight(current);
	new->height = updateHeight(new);

	return new;
}

// Creates a new Tree containing the given value
static Tree newTree(Set s, int item, Tree parent) {
	Tree new = malloc(sizeof(*new));
	if (new == NULL) {
		fprintf(stderr, "ERROR");
		exit(EXIT_FAILURE);
	}
	s->size++;
	new->item = item;
	new->left = NULL;
	new->right = NULL;
	new->height = 1;

	setTreePointer(new, parent, item);

	if (s->min == NULL || item < s->min->item) {
		s->min = new;
	}
	if (s->max == NULL || item > s->max->item) {
		s->max = new;
	}
	return new;
}

// Setting pointer pre and next of the new tree Tree
static void setTreePointer(Tree new, Tree parent, int item) {
	// if new tree is a left child
	if (parent && parent->item > item) {
		new->next = parent;
		new->pre = parent->pre;
		if (parent->pre != NULL) {
			parent->pre->next = new;
		}
		parent->pre = new;
	// if new tree is a right child
	} else if (parent && parent->item < item) {
		new->pre = parent;
		new->next = parent->next;
		if (parent->next != NULL) {
			parent->next->pre = new;
		}
		parent->next = new;
	} else {
		new->next = NULL;
		new->pre = NULL;
	}
}

// Returns true if the tree contains the given item, and false otherwise
static bool TreeContains(Tree t, int item) {
	if (t == NULL) {
		return false;
	} else if (item < t->item) {
		return TreeContains(t->left, item);
	} else if (item > t->item) {
		return TreeContains(t->right, item);
	} else { // (item == t->item)
		return true;
	}
	return false;
}

// Print each element in the tree in ascending separted by a comma and space
static void PrintTree(Tree t) {
	if (t == NULL) {
		return;
	}
	if (t->left) {
		PrintTree(t->left);
		printf(", ");
	}
	printf("%d", t->item);
	if (t->right) {
		printf(", ");
		PrintTree(t->right);
	}
}

// Group 2

// insert any elements in the tree to the set
static Tree TreeInsertUnion(Set s, Tree t) {
	if (t->left) {
		TreeInsertUnion(s, t->left);
	}
	s->tree = TreeInsert(s, s->tree, t->item, s->tree);
	if (t->right) {
		TreeInsertUnion(s, t->right);
	}
	return s->tree;
}

// Insert only the intersected item to the tree
static Tree TreeInsertIntersection(Set s, Tree t1, Tree t2) {
	if (t1->left) {
		TreeInsertIntersection(s, t1->left, t2);
	}
	if (TreeContains(t2, t1->item)) {
		s->tree = TreeInsert(s, s->tree, t1->item, s->tree);
	}
	if (t1->right) {
		TreeInsertIntersection(s, t1->right, t2);
	}
	return s->tree;
}

// Insert only item from Tree t1 that's not existing in Tree t2 to the tree
static Tree TreeInsertDifference(Set s, Tree t1, Tree t2) {
	if (t1->left) {
		TreeInsertDifference(s, t1->left, t2);
	}
	if (!(TreeContains(t2, t1->item))) {
		s->tree = TreeInsert(s, s->tree, t1->item, s->tree);
	}
	if (t1->right) {
		TreeInsertDifference(s, t1->right, t2);
	}
	return s->tree;
}

// Return true if Tree t2 contains all items of Tree t1
static bool TreeSubset(Tree t1, Tree t2) {
	if (t1 == NULL) {
		return true;
	}
	if (!(TreeContains(t2, t1->item))) {
		return false;
	}
	return TreeSubset(t1->left, t2) && TreeSubset(t1->right, t2);
}

// Finds the floor of a given item in a tree
static int TreeFloor(Tree t, int item) {
	if (t->item == item) {
		return t->item;
	} else if (t->left && item < t->item) {
		return TreeFloor(t->left, item);
	} else if (t->right && item > t->item && item >= t->right->item) {
		return TreeFloor(t->right, item);
	} else {
		return t->item;
	}
}

// Returns the ceiling of a given item in a tree
static int TreeCeiling(Tree t, int item) {
	if (t->item == item) {
		return t->item;
	} else if (t->left && item < t->item) {
		// has to be TreeCeiling
		return TreeFloor(t->left, item);
	} else if (t->right && item > t->item && item <= t->right->item) {
		return TreeFloor(t->right, item);
	} else {
		return t->item;
	}
}

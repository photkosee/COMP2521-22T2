// Phot Koseekrainiramon
// COMP2521 lab04
// on 18/06/2022

// Implementation of the binary search tree ADT

#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "BSTree.h"
#include "Queue.h"

typedef struct BSTNode {
	int value;
	BSTree left;
	BSTree right;
	int height;
} BSTNode;

////////////////////////////////////////////////////////////////////////

static BSTree newBSTree(int v);
static void showBSTreeBSTree(BSTree t);
static void doPrintBSTree(BSTree t, FILE *out);
BSTree RotateRight(BSTree t);
BSTree RotateLeft(BSTree t);
int Balance(BSTree t);
static int max(int a, int b);
static int height (BSTree t);
////////////////////////////////////////////////////////////////////////
static int max(int a, int b) {
    if (a >= b) {
        return a;
    }
    return b;
}

// Return height of the tree
static int height (BSTree t) {
    if (t == NULL) {
        return 0;
    } else if (t->left && t->right) {
        return 1 + max(t->left->height, t->right->height);
    } else if (t->left) {
        return 1 + t->left->height;
    } else if (t->right) {
        return 1 + t->right->height;
    } else {
        return 1;
    }
}

// Creates a new empty BSTree
BSTree BSTreeNew(void) {
	return NULL;
}

// Frees all the memory associated with the given BSTree
void BSTreeFree(BSTree t) {
	if (t == NULL) {
		return;
	}
	
	BSTreeFree(t->left);
	BSTreeFree(t->right);
	free(t);
}

// Inserts a new value into the given BSTree and returns the root of the
// updated BSTree. Does not insert duplicate values.
BSTree BSTreeInsert(BSTree t, int v) {
	if (t == NULL) {
        return newBSTree(v);
    } else if (v < t->value) {
        t->left = BSTreeInsert(t->left, v);
    } else if (v > t->value) {
        t->right = BSTreeInsert(t->right, v);
    } else {
        return t;
    }

    t->height = height(t);
    int balance = Balance(t);
    if (balance > 1 && v < t->left->value) {
        return RotateRight(t);
    }
    if (balance < - 1 && v > t->right->value) {
        return RotateLeft(t);
    }
    if (balance > 1 && v > t->left->value) {
        t->left = RotateLeft(t->left);
        return RotateRight(t);
    }
    if (balance < -1 && v < t->right->value) {
        t->right = RotateRight(t->right);
        return RotateLeft(t);
    }
    return t;
}

// Return the differences of height 
int Balance(BSTree t) {
    if (t == NULL) {
        return 0;
    }
    return height(t->left) - height(t->right);
}

// Left rotating subtree rooted and adjusting their parent pointers
BSTree RotateLeft(BSTree t) {
    BSTree pre_right = t->right;
    BSTree pre_left = pre_right->left;
    pre_right->left = t;
    t->right = pre_left;

    t->height = height(t);
    pre_right->height = height(pre_right);

    return pre_right;
}

// Right rotating subtree rooted and adjusting their parent pointers
BSTree RotateRight(BSTree t) {
    BSTree pre_left = t->left;
    BSTree pre_right = pre_left->right;
    pre_left->right = t;
    t->left = pre_right;

    t->height = height(t);
    pre_left->height = height(pre_left);

    return pre_left;
}

// Creates a new BSTree containing the given value
static BSTree newBSTree(int v) {
	BSTree new = malloc(sizeof(*new));
	if (new == NULL) {
		err(EX_OSERR, "couldn't allocate BST BSTree");
	}
	
	new->value = v;
	new->left = NULL;
	new->right = NULL;
	new->height = 0;
	return new;
}

// Checks whether a value is in the given BSTree
bool BSTreeFind(BSTree t, int v) {
	if (t == NULL) {
		return false;
	} else if (v < t->value) {
		return BSTreeFind(t->left, v);
	} else if (v > t->value) {
		return BSTreeFind(t->right, v);
	} else { // (v == t->value)
		return true;
	}
}

// Prints a BSTree to the given file.
// Assumes that the file is open for writing.
void BSTreePrint(BSTree t, FILE *out) {
	doPrintBSTree(t, out);
}

// Prints a BSTree to stdout.
void BSTreeShow(BSTree t) {
	BSTreePrint(t, stdout);
}

////////////////////////////////////////////////////////////////////////

// Counts the number of BSTrees in the given BSTree
int BSTreeNumNodes(BSTree t) {
	if (t == NULL) {
		return 0;
	} else {
		return 1 + BSTreeNumNodes(t->left) + BSTreeNumNodes(t->right);
	}
}

// Counts the number of leaves in the given BSTree
int BSTreeNumLeaves(BSTree t) {
	if (t == NULL) {
		return 0;
	} 
	if (t->left == NULL && t->right == NULL) {
		return 1;
	} else {
		return BSTreeNumLeaves(t->left) + BSTreeNumLeaves(t->right);
	}
}

// Deletes all of the leaves in the given BSTree and returns the root of
// the updated BSTree
BSTree BSTreeDeleteLeaves(BSTree t) {
	if (t == NULL) {
		return NULL;
	}
	if (t->left == NULL && t->right == NULL) {
		free(t);
		return NULL;
	}
	t->left = BSTreeDeleteLeaves(t->left);
	t->right = BSTreeDeleteLeaves(t->right);
	return t;
}

////////////////////////////////////////////////////////////////////////

// Prints the value in the given BSTree
static void showBSTreeBSTree(BSTree t) {
	if (t == NULL) return;
	printf("%d ", t->value);
}

// Prints the in-order traversal of the given BSTree
void BSTreeInOrder(BSTree t) {
	if (t == NULL) return;

	BSTreeInOrder(t->left);
	showBSTreeBSTree(t);
	BSTreeInOrder(t->right);
}

// Prints the pre-order traversal of the given BSTree
void BSTreePreOrder(BSTree t) {
	if (t == NULL) return;

	showBSTreeBSTree(t);
	BSTreePreOrder(t->left);
	BSTreePreOrder(t->right);
}

// Prints the post-order traversal of the given BSTree
void BSTreePostOrder(BSTree t) {
	if (t == NULL) return;

	BSTreePostOrder(t->left);
	BSTreePostOrder(t->right);
	showBSTreeBSTree(t);
}

// Prints the level-order traversal of the given BSTree
void BSTreeLevelOrder(BSTree t) {
	if (t == NULL) return;
	Queue q = QueueNew();
	QueueEnqueue(q, t);
	while (QueueSize(q) > 0) {
		BSTree t = QueueDequeue(q);
		printf("%d ", t->value);
		if (t->left != NULL) {
			QueueEnqueue(q, t->left);
		}
		if (t->right != NULL) {
			QueueEnqueue(q, t->right);
		}
	}
	QueueFree(q);
}

////////////////////////////////////////////////////////////////////////
// ASCII tree printer
// Courtesy: ponnada
// Via: http://www.openasthra.com/c-tidbits/printing-binary-trees-in-ascii/

// data structures
typedef struct asciiBSTree_struct asciiBSTree;
struct asciiBSTree_struct {
	asciiBSTree *left, *right;
	// length of the edge from this BSTree to its children
	int edge_length;
	int height;
	int lablen;
	// -1=I am left, 0=I am root, 1=I am right
	int parent_dir;
	// max supported unit32 in dec, 10 digits max
	char label[11];
};

// functions
static void print_level(asciiBSTree *BSTree, int x, int level, FILE *out);
static void compute_edge_lengths(asciiBSTree *BSTree);
static void compute_lprofile(asciiBSTree *BSTree, int x, int y);
static void compute_rprofile(asciiBSTree *BSTree, int x, int y);
static asciiBSTree *build_ascii_tree(BSTree t);
static void free_ascii_tree(asciiBSTree *BSTree);

#define MAX_HEIGHT 1000
static int lprofile[MAX_HEIGHT];
static int rprofile[MAX_HEIGHT];
#define INFINITY (1 << 20)

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

static int gap = 3; // gap between left and right BSTrees

// used for printing next BSTree in the same level,
// this is the x coordinate of the next char printed
static int print_next;

// prints ascii tree for given Tree structure
static void doPrintBSTree(BSTree t, FILE *out)
{
	asciiBSTree *proot;
	int xmin, i;
	if (t == NULL)
		return;
	proot = build_ascii_tree(t);
	compute_edge_lengths(proot);
	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
		lprofile[i] = INFINITY;
	compute_lprofile(proot, 0, 0);
	xmin = 0;
	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
		xmin = MIN(xmin, lprofile[i]);
	for (i = 0; i < proot->height; i++) {
		print_next = 0;
		print_level(proot, -xmin, i, out);
		fprintf(out, "\n");
	}
	if (proot->height >= MAX_HEIGHT) {
		fprintf(out,
			"(Tree is taller than %d; may be drawn incorrectly.)\n",
			MAX_HEIGHT);
	}
	free_ascii_tree(proot);
}

// This function prints the given level of the given tree, assuming
// that the BSTree has the given x cordinate.
static void print_level(asciiBSTree *BSTree, int x, int level, FILE *out)
{
	int i, isleft;
	if (BSTree == NULL)
		return;
	isleft = (BSTree->parent_dir == -1);
	if (level == 0) {
		for (i = 0;
			 i < (x - print_next - ((BSTree->lablen - isleft) / 2));
			 i++)
			fprintf(out, " ");
		print_next += i;
		fprintf(out, "%s", BSTree->label);
		print_next += BSTree->lablen;
	} else if (BSTree->edge_length >= level) {
		if (BSTree->left != NULL) {
			for (i = 0; i < (x - print_next - (level)); i++) {
				fprintf(out, " ");
			}
			print_next += i;
			fprintf(out, "/");
			print_next++;
		}
		if (BSTree->right != NULL) {
			for (i = 0; i < (x - print_next + (level)); i++) {
				printf(" ");
			}
			print_next += i;
			fprintf(out, "\\");
			print_next++;
		}
	} else {
		print_level(
			BSTree->left,
			x - BSTree->edge_length - 1,
			level - BSTree->edge_length - 1,
			out);
		print_level(
			BSTree->right,
			x + BSTree->edge_length + 1,
			level - BSTree->edge_length - 1,
			out);
	}
}

// This function fills in the edge_length and
// height fields of the specified tree
static void compute_edge_lengths(asciiBSTree *BSTree)
{
	int h, hmin, i, delta;
	if (BSTree == NULL)
		return;
	compute_edge_lengths(BSTree->left);
	compute_edge_lengths(BSTree->right);

	/* first fill in the edge_length of BSTree */
	if (BSTree->right == NULL && BSTree->left == NULL)
		BSTree->edge_length = 0;
	else {
		if (BSTree->left == NULL)
			hmin = 0;
		else {
			for (i = 0; i < BSTree->left->height && i < MAX_HEIGHT; i++)
				rprofile[i] = -INFINITY;
			compute_rprofile(BSTree->left, 0, 0);
			hmin = BSTree->left->height;
		}
		if (BSTree->right == NULL)
			hmin = 0;
		else {
			for (i = 0; i < BSTree->right->height && i < MAX_HEIGHT; i++)
				lprofile[i] = INFINITY;
			compute_lprofile(BSTree->right, 0, 0);
			hmin = MIN(BSTree->right->height, hmin);
		}
		delta = 4;
		for (i = 0; i < hmin; i++) {
			int w = gap + 1 + rprofile[i] - lprofile[i];
			delta = (delta > w) ? delta : w;
		}

		// If the BSTree has two children of height 1, then we allow the
		// two leaves to be within 1, instead of 2
		if (((BSTree->left != NULL && BSTree->left->height == 1) ||
			(BSTree->right != NULL && BSTree->right->height == 1)) &&
			delta > 4)
			delta--;
		BSTree->edge_length = ((delta + 1) / 2) - 1;
	}

	// now fill in the height of BSTree
	h = 1;
	if (BSTree->left != NULL)
		h = MAX(BSTree->left->height + BSTree->edge_length + 1, h);
	if (BSTree->right != NULL)
		h = MAX(BSTree->right->height + BSTree->edge_length + 1, h);
	BSTree->height = h;
}

static asciiBSTree *build_ascii_tree_recursive(BSTree t)
{
	asciiBSTree *BSTree;

	if (t == NULL)
		return NULL;
	BSTree = malloc(sizeof(asciiBSTree));
	BSTree->left = build_ascii_tree_recursive(t->left);
	BSTree->right = build_ascii_tree_recursive(t->right);
	if (BSTree->left != NULL)
		BSTree->left->parent_dir = -1;
	if (BSTree->right != NULL)
		BSTree->right->parent_dir = 1;
	sprintf(BSTree->label, "%d", t->value);
	BSTree->lablen = (int) strlen(BSTree->label);

	return BSTree;
}

// Copy the tree into the ascii BSTree structre
static asciiBSTree *build_ascii_tree(BSTree t)
{
	asciiBSTree *BSTree;
	if (t == NULL)
		return NULL;
	BSTree = build_ascii_tree_recursive(t);
	BSTree->parent_dir = 0;
	return BSTree;
}

// Free all the BSTrees of the given tree
static void free_ascii_tree(asciiBSTree *BSTree)
{
	if (BSTree == NULL)
		return;
	free_ascii_tree(BSTree->left);
	free_ascii_tree(BSTree->right);
	free(BSTree);
}

// The following function fills in the lprofile array for the given
// tree. It assumes that the center of the label of the root of this tree
// is located at a position(x,y).  It assumes that the edge_length
// fields have been computed for this tree.
static void compute_lprofile(asciiBSTree *BSTree, int x, int y)
{
	int i, isleft;
	if (BSTree == NULL)
		return;
	isleft = (BSTree->parent_dir == -1);
	lprofile[y] = MIN(lprofile[y], x - ((BSTree->lablen - isleft) / 2));
	if (BSTree->left != NULL) {
		for (i = 1; i <= BSTree->edge_length && y + i < MAX_HEIGHT; i++)
			lprofile[y + i] = MIN(lprofile[y + i], x - i);
	}
	compute_lprofile(
		BSTree->left,
		x - BSTree->edge_length - 1,
		y + BSTree->edge_length + 1);
	compute_lprofile(
		BSTree->right,
		x + BSTree->edge_length + 1,
		y + BSTree->edge_length + 1);
}

static void compute_rprofile(asciiBSTree *BSTree, int x, int y)
{
	int i, notleft;
	if (BSTree == NULL)
		return;
	notleft = (BSTree->parent_dir != -1);
	rprofile[y] = MAX(rprofile[y], x + ((BSTree->lablen - notleft) / 2));
	if (BSTree->right != NULL) {
		for (i = 1; i <= BSTree->edge_length && y + i < MAX_HEIGHT; i++)
			rprofile[y + i] = MAX(rprofile[y + i], x + i);
	}
	compute_rprofile(
		BSTree->left,
		x - BSTree->edge_length - 1,
		y + BSTree->edge_length + 1);
	compute_rprofile(
		BSTree->right,
		x + BSTree->edge_length + 1,
		y + BSTree->edge_length + 1);
}


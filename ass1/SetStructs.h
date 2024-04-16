// COMP2521 22T2 Assignment 1
// Phot Koseekrainiramon (z5387411)
// on 30/06/2022

// DO NOT CHANGE THE NAME OF THIS STRUCT
struct node {
    int item;           // DO NOT CHANGE/REMOVE THIS FIELD
    struct node *left;  // DO NOT CHANGE/REMOVE THIS FIELD
    struct node *right; // DO NOT CHANGE/REMOVE THIS FIELD
    int height;				// Storing it's height in integer
    struct node *next;		// A pointer pointing to it's smallest item that
                            // is greater than the current item
    struct node *pre;       // A pointer pointing to it's largest item that is
                            // smaller than the current item 
};

// DO NOT CHANGE THE NAME OF THIS STRUCT
struct set {
    struct node *tree;  // DO NOT CHANGE/REMOVE THIS FIELD
    int size;           // Storing the number of nodes in the tree in integer
    struct node *max;   // A pointer pointing to the node in the tree that 
                        // stores greatest item
    struct node *min;   // A pointer pointing to the node in the tree that 
                        // stores smallest item
};

// You may define more structs here if needed 

////////////////////////////////////////////////////////////////////////
// Cursors

struct cursor {
    struct node *tree;  // a pointer pointing to a node in a tree
    struct set *s;      // a pointer pointing to a set
};

////////////////////////////////////////////////////////////////////////


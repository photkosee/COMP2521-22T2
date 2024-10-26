// Phot Koseekrainiramon (z5387411)
// COMP2521 lab02
// on 08/06/2022
// Implementation of the Queue ADT using a circular array

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

#define DEFAULT_SIZE 16 // DO NOT change this line

// DO NOT modify this struct
struct queue {
	Item *items;
	int size;
	int capacity;
	int frontIndex;
};

/**
 * Creates a new empty queue
 */
Queue QueueNew(void) {
	Queue q = malloc(sizeof(*q));
	if (q == NULL) {
		fprintf(stderr, "couldn't allocate Queue");
		exit(EXIT_FAILURE);
	}

	q->items = malloc(DEFAULT_SIZE * sizeof(Item));
	if (q->items == NULL) {
		fprintf(stderr, "couldn't allocate Queue");
		exit(EXIT_FAILURE);
	}

	q->size = 0;
	q->capacity = DEFAULT_SIZE;
	q->frontIndex = 0;
	return q;
}

/**
 * Frees all resources associated with the given queue
 */
void QueueFree(Queue q) {
	free(q->items);
	free(q);
}

/**
 * Adds an item to the end of the queue
 */
void QueueEnqueue(Queue q, Item it) {
	
	Queue current = q;
	// in case the array is full
	if (current->size >= current->capacity) {
		current->capacity *= 2;
		q->items = realloc(q->items, current->capacity * sizeof(Item));
		// move all the back part of arrays to the back of first part of arrays
		for (int i = 0; i < current->frontIndex; i++) {
			current->items[i + ((current->capacity) / 2)] = current->items[i];
		} 
		/*	
		// move all the first part to the end of arrays
		for (int i = current->frontIndex; i < (current->capacity / 2); i++) {
			current->items[i + ((current->capacity) / 2)] = current->items[i];
		}	
		*/
	}
	// add the item to the back of arrays
	int last = (current->frontIndex + current->size) % current->capacity;
	/*
	if (last >= current->capacity) {
	    last -= current->capacity;
	}
	*/
	current->items[last] = it;
	current->size += 1;
	
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q) {
	
	Queue current = q;
	Item item = current->items[current->frontIndex];
	// move front index by one
	current->frontIndex += 1;
	if (current->frontIndex >= current->capacity) {
	    current->frontIndex -= current->capacity;
	}
	current->size -= 1;
	
	return item;
}

/**
 * Gets the item at the front of the queue without removing it
 * Assumes that the queue is not empty
 */
Item QueueFront(Queue q) {
	assert(q->size > 0);

	return q->items[q->frontIndex];
}

/**
 * Gets the size of the given queue
 */
int QueueSize(Queue q) {
	return q->size;
}

/**
 * Returns true if the queue is empty, and false otherwise
 */
bool QueueIsEmpty(Queue q) {
	return q->size == 0;
}

/**
 * Prints the items in the queue to the given file with items space-separated
 */
void QueueDump(Queue q, FILE *fp) {
	for (int i = q->frontIndex, j = 0; j < q->size; i = (i + 1) % q->capacity, j++) {
		fprintf(fp, "%d ", q->items[i]);
	}
	fprintf(fp, "\n");
}

/**
 * Prints out information for debugging
 */
void QueueDebugPrint(Queue q) {

}


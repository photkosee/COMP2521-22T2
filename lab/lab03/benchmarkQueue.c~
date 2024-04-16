// Phot Koseekrainiramon (z5387411)
// on 10/06/2022
// performing a series of queue operations to check the perfomances of
// array and circularArray

#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

// Because the only difference in time complexity between these two files is 
// the worst case when array has to dequeue that is O(n) but it is O(1) for
// circularArray. That means if you want to see the differences you have to run
// a lot of dequeueing.

int main(void) {
	Queue q = QueueNew();
    
    for (int i = 0; i < 10000; i++) {
        QueueEnqueue(q, i);
    }
	for (int i = 0; i < 10000; i++) {
        QueueDequeue(q);
    }
    
	QueueFree(q);
}


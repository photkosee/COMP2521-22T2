// COMP2521 22T2 Assignment 1

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "SetStructs.h"

#include "Set.h"

void testSetInsert(void);
void testSetSize(void);
void testSetContains(void);
void testSetShow(void);

void testSetUnion(void);
void testSetIntersection(void);
void testSetDifference(void);
void testSetEquals(void);
void testSetSubset(void);

void testSetFloor(void);
void testSetCeiling(void);

void testSetCursor(void);

int main(int argc, char *argv[]) {
	
	testSetInsert();
	testSetSize();
	testSetContains();
	
	testSetShow();

	testSetUnion();
	testSetIntersection();
	testSetDifference();
	testSetEquals();
	testSetSubset();
	testSetFloor();
	testSetCeiling();

	testSetCursor();

}

void testSetInsert(void) {
	// NOTE: SetInsert can't be tested on its own unless we have direct
	//       access to the internal representation of the ADT, so you
	//       may want to #include "SetStructs.h" and then access
	//       s->tree

	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);
	assert(SetSize(s) == 4);
	SetInsert(s, 8);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);
	assert(SetSize(s) == 4);

	SetFree(s);
	
}

void testSetSize(void) {
	
	Set s = SetNew();
	assert(SetSize(s) == 0);
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);
	assert(SetSize(s) == 4);
	SetInsert(s, 7);
	SetInsert(s, 2);
	assert(SetSize(s) == 5);

	SetFree(s);
	
}

void testSetContains(void) {
	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);
	assert(SetContains(s, 2));
	assert(SetContains(s, 4));
	assert(SetContains(s, 5));
	assert(SetContains(s, 8));
	assert(!SetContains(s, 3));
	assert(SetContains(s, 2));

	SetFree(s);
}

void testSetShow(void) {
	// SetShow can't be tested with assert, since it prints to stdout.
	// Therefore, it must be manually checked.

	Set s = SetNew();
	SetShow(s);
	printf("\n");
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);
	SetShow(s);
	printf("\n");
	SetFree(s);
}

void testSetUnion(void) {
	Set a = SetNew();
	SetInsert(a, 5);
	SetInsert(a, 2);
	SetInsert(a, 8);
	SetInsert(a, 4);

	Set b = SetNew();
	SetInsert(b, 3);
	SetInsert(b, 8);
	SetInsert(b, 7);
	SetInsert(b, 5);

	Set c = SetUnion(a, b);
	assert(SetContains(c, 2));
	assert(SetContains(c, 3));
	assert(SetContains(c, 4));
	assert(SetContains(c, 5));
	assert(SetContains(c, 7));
	assert(SetContains(c, 8));
	assert(SetSize(c) == 6);

	Set d = SetUnion(a, c);
	assert(SetContains(d, 2));
	assert(SetContains(d, 3));
	assert(SetContains(d, 4));
	assert(SetContains(d, 5));
	assert(SetContains(d, 7));
	assert(SetContains(d, 8));
	assert(SetSize(d) == 6);
	SetInsert(d, 5);
	SetInsert(d, -3);
	assert(SetSize(d) == 7);

	SetFree(a);
	SetFree(b);
	SetFree(c);
	SetFree(d);
}

void testSetIntersection(void) {
	Set a = SetNew();
	SetInsert(a, 5);
	SetInsert(a, 2);
	SetInsert(a, 8);
	SetInsert(a, 4);

	Set b = SetNew();
	SetInsert(b, 3);
	SetInsert(b, 8);
	SetInsert(b, 7);
	SetInsert(b, 5);

	Set c = SetIntersection(a, b);
	assert(SetContains(c, 5));
	assert(SetContains(c, 8));
	assert(!SetContains(c, 2));
	assert(!SetContains(c, 3));
	assert(!SetContains(c, 4));
	assert(!SetContains(c, 7));
	assert(SetSize(c) == 2);

	Set d = SetNew();
	SetInsert(d, 15);

	Set e = SetIntersection(a, d);
	assert(SetSize(e) == 0);

	SetFree(a);
	SetFree(b);
	SetFree(c);
	SetFree(d);
	SetFree(e);
}

void testSetDifference(void) {
	Set a = SetNew();
	SetInsert(a, 5);
	SetInsert(a, 2);
	SetInsert(a, 8);
	SetInsert(a, 4);

	Set b = SetNew();
	SetInsert(b, 3);
	SetInsert(b, 8);
	SetInsert(b, 7);
	SetInsert(b, 5);

	Set c = SetDifference(a, b);
	assert(SetContains(c, 2));
	assert(SetContains(c, 4));
	assert(!SetContains(c, 3));
	assert(!SetContains(c, 5));
	assert(!SetContains(c, 7));
	assert(!SetContains(c, 8));
	assert(SetSize(c) == 2);

	SetFree(a);
	SetFree(b);
	SetFree(c);
}

void testSetEquals(void) {
	Set a = SetNew();
	SetInsert(a, 4);
	SetInsert(a, 2);
	SetInsert(a, 7);
	SetInsert(a, 1);

	Set b = SetNew();
	SetInsert(b, 2);
	SetInsert(b, 4);
	SetInsert(b, 1);
	SetInsert(b, 7);

	Set c = SetNew();
	SetInsert(c, 4);
	SetInsert(c, 2);
	SetInsert(c, 7);
	SetInsert(c, 3);

	assert(SetEquals(a, b));
	assert(!SetEquals(a, c));

	SetFree(a);
	SetFree(b);
	SetFree(c);
}


void testSetSubset(void) {
	Set a = SetNew();
	SetInsert(a, 5);
	SetInsert(a, 3);
	SetInsert(a, 6);

	Set b = SetNew();
	SetInsert(b, 3);
	SetInsert(b, 9);
	SetInsert(b, 5);
	SetInsert(b, 6);

	Set c = SetNew();
	SetInsert(c, 4);
	SetInsert(c, 6);
	SetInsert(c, 3);
	SetInsert(c, 7);

	assert(SetSubset(a, b));
	assert(!SetSubset(a, c));

	SetFree(a);
	SetFree(b);
	SetFree(c);
}

void testSetFloor(void) {
	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);

	assert(SetFloor(s, 7) == 5);
	assert(SetFloor(s, 4) == 4);
	assert(SetFloor(s, 1) == UNDEFINED);

	Set a = SetNew();
	assert(SetFloor(a, 10) == UNDEFINED);

	SetFree(s);
	SetFree(a);
}

void testSetCeiling(void) {
	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);

	assert(SetCeiling(s, 2) == 2);
	assert(SetCeiling(s, 6) == 8);
	assert(SetCeiling(s, 9) == UNDEFINED);

	Set a = SetNew();
	assert(SetFloor(a, 10) == UNDEFINED);

	SetFree(s);
	SetFree(a);
}

void testSetCursor(void) {
	Set s = SetNew();
	SetInsert(s, 5);
	SetInsert(s, 2);
	SetInsert(s, 8);
	SetInsert(s, 4);
	
	SetCursor cur = SetCursorNew(s);
	assert(SetCursorNext(cur) == 2);
	assert(SetCursorNext(cur) == 4);
	SetInsert(s, 5);
	assert(SetCeiling(s, 6) == 8);
	SetInsert(s, 7);
	SetInsert(s, 3);
	SetInsert(s, 1);
	assert(SetCursorNext(cur) == 5);
	assert(SetCursorNext(cur) == 7);
	assert(SetFloor(s, 2) == 2);
	assert(SetCursorNext(cur) == 8);
	assert(SetFloor(s, 6) == 5);
	assert(SetCursorNext(cur) == UNDEFINED);
	assert(SetCeiling(s, 0) == 1);
	assert(SetCeiling(s, 2) == 2);
	assert(SetCeiling(s, 6) == 7);
	assert(SetCursorNext(cur) == UNDEFINED);

	Set a = SetNew();
	SetInsert(a, 15);
	SetInsert(a, 21);
	SetInsert(a, 17);
	SetInsert(a, 18);
	SetInsert(a, 40);
	SetInsert(a, 10);
	SetInsert(a, 19);
	SetInsert(a, 20);
	SetInsert(a, 13);
	SetInsert(a, 14);
	SetInsert(a, 12);
	SetInsert(a, 11);
	SetInsert(a, 5);

	SetCursor aa = SetCursorNew(a);
	assert(SetCursorNext(aa) == 5);
	assert(SetCursorNext(aa) == 10);
	assert(SetCursorNext(aa) == 11);
	assert(SetCursorNext(aa) == 12);
	assert(SetCursorNext(aa) == 13);
	assert(SetCursorNext(aa) == 14);
	assert(SetCursorNext(aa) == 15);
	SetInsert(a, 1);
	SetInsert(a, 2);
	SetInsert(a, 6);
	SetInsert(a, 7);
	SetInsert(a, 16);
	SetInsert(a, 22);
	SetInsert(a, -5);
	SetInsert(a, -8);
	SetInsert(a, -10);
	SetInsert(a, -20);
	assert(SetCursorNext(aa) == 17);
	assert(SetCursorNext(aa) == 18);
	assert(SetCursorNext(aa) == 19);
	assert(SetCursorNext(aa) == 20);
	assert(SetCursorNext(aa) == 21);
	assert(SetCursorNext(aa) == 22);
	assert(SetCursorNext(aa) == 40);
	assert(SetCursorNext(aa) == UNDEFINED);
	
	Set b = SetNew();
	SetCursor bb = SetCursorNew(b);
	assert(SetCursorNext(bb) == UNDEFINED);
	assert(SetCursorNext(bb) == UNDEFINED);

	SetFree(s);
	SetCursorFree(cur);
	SetFree(a);
	SetCursorFree(aa);
	SetFree(b);
	SetCursorFree(bb);

}

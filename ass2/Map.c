// Phot Koseekrainiramon (z5387411)
// COMP2521 assignment2
// on 21/07/2022
// Implementation of the Map ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Map.h"

#define ENOUGH 10000     // maximum number of edges

struct map { 
	Road  *roads;    // array of edges
	char **names;    // array of citiy's names
	int    city;     // #vertices
	int    numEdges; // #edges
	int    road;     // index of roads
	int    n;        // size of edge array
};

// Helper functions
static bool citiesAreConnected(Road r1, Road r2);
static char *myStrdup(char *s);

////////////////////////////////////////////////////////////////////////
// Basic Operations

/**
 * Creates a new map with the given number of cities
 * Assumes that numCities is positive
 */
Map MapNew(int numCities) {
	Map new = malloc(sizeof(*new));
	if (new == NULL) {
		fprintf(stderr, "ERROR");
		exit(EXIT_FAILURE);
	}

	new->city = numCities;
	new->road = 0;
	new->numEdges = 0;
	new->n = ENOUGH;
	new->roads = malloc(new->n * sizeof(Road));
	if (new->roads == NULL) {
		fprintf(stderr, "ERROR");
		exit(EXIT_FAILURE);
	}

	new->names = malloc(numCities * sizeof(char *));
	if (new->names == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}

	return new;
}

/**
 * Frees all memory associated with the given map
 */
void MapFree(Map m) {
	if (m == NULL) {
		fprintf(stderr, "ERROR");
		exit(EXIT_FAILURE);
	}
	
	free(m->roads);
	for (int i = 0; i < m->city; i++) {
		free(m->names[i]);
	}
	free(m->names);
	free(m);
	return;
}

/**
 * Returns the number of cities on the given map
 */
int MapNumCities(Map m) {
	return m->city;
}

/**
 * Returns the number of roads on the given map
 */
int MapNumRoads(Map m) {
	return m->numEdges;
}

/**
 * Inserts a road between two cities with the given length
 * Does nothing if there is already a road between the two cities
 * Assumes that the cities are valid and are not the same
 * Assumes that the length of the road is positive
 */
void MapInsertRoad(Map m, int city1, int city2, int length) {
	if (m == NULL || m->road >= m->n) {
		fprintf(stderr, "ERROR");
		exit(EXIT_FAILURE);
	}
	// current index of roads array
	int i = 0;
	while (i < m->road && !citiesAreConnected((Road){city1, city2, length},
	                                          m->roads[i])) {
		i++;
	}
	if (i == m->road) {
		m->roads[m->road++] = (Road){city1, city2, length};
		m->roads[m->road++] = (Road){city2, city1, length};
		m->numEdges++;
	}
	return;
}

/**
 * Sets the name of the given city
 */
void MapSetName(Map m, int city, char *name) {
	m->names[city] = myStrdup(name);
	return;
}

/**
 * Returns the name of the given city
 */
char *MapGetName(Map m, int city) {
	return m->names[city];
}

/**
 * Checks if there is a road between the two given cities
 * Returns the length of the road if there is a road, and 0 otherwise
 */
int MapContainsRoad(Map m, int city1, int city2) {
	if (m == NULL || m->road >= m->n) {
		fprintf(stderr, "ERROR");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < m->road; i++) {
		if (citiesAreConnected((Road){city1, city2, 0}, m->roads[i])) {
			return m->roads[i].length;
		}
	}
	return 0;
}

/**
 * Returns the number of roads connected to the given city and stores
 * them in the given roads array. The `from` field should be equal to
 * `city` for all the roads in the array.
 * Assumes that the roads array is large enough to store all the roads
 */
int MapGetRoadsFrom(Map m, int city, Road roads[]) {
	int numRoad = 0;
	for (int i = 0; i < m->road; i++) {
		if (city == m->roads[i].from) {
			roads[numRoad++] = m->roads[i];
		}
	}
	// sort roads in asending order in term of destinated city id
	for (int i = 0; i < numRoad; i++) {
		for (int j = i + 1; j < numRoad; j++) {
			if (roads[i].to > roads[j].to) {
				Road r = roads[i];
				roads[i] = roads[j];
				roads[j] = r;
			}
		}
	}
	return numRoad;
}

/**
 * Displays the map
 * !!! DO NOT EDIT THIS FUNCTION !!!
 * This function will work once the other functions are working
 */
void MapShow(Map m) {
	printf("Number of cities: %d\n", MapNumCities(m));
	printf("Number of roads: %d\n", MapNumRoads(m));
	
	Road *roads = malloc(MapNumRoads(m) * sizeof(Road));
	if (roads == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);    
	}
	
	for (int i = 0; i < MapNumCities(m); i++) {
		printf("[%d] %s has roads to:", i, MapGetName(m, i));
		int numRoads = MapGetRoadsFrom(m, i, roads);
		for (int j = 0; j < numRoads; j++) {
			if (j > 0) {
				printf(",");
			}
			printf(" [%d] %s (%d)", roads[j].to, MapGetName(m, roads[j].to),
					 roads[j].length);
		}
		printf("\n");
	}
	
	free(roads);
}

////////////////////////////////////////////////////////////////////////
// Helper function

// check if two cities are connected
static bool citiesAreConnected(Road r1, Road r2) {
	return ((r1.from == r2.from && r1.to == r2.to) ||
	(r1.to == r2.from && r1.from == r2.to));
}

// copy char
static char *myStrdup(char *s) {
	char *copy = malloc((strlen(s) + 1) * sizeof(char));
	if (copy == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}
	return strcpy(copy, s);
}

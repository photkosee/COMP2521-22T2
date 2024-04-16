// Phot Koseekrainiramon (z5387411)
// on 23/07/2022
// Algorithms to design electrical grids

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Place.h"
#include "PQ.h"

////////////////////////////////////////////////////////////////////////
// Your task

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * from a power plant to all the given cities. Power lines must be built
 * between cities or between a city and a power plant.  Cost is directly
 * proportional to the total length of power lines used.
 * Assumes  that  numCities  is at least 1 (numCities is the size of the
 * cities array).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */
int planGrid1(Place cities[], int numCities, Place powerPlant,
              PowerLine powerLines[]) {

    Graph g = GraphNew(numCities + 1);
    Edge e;
    for (int i = 0; i < numCities; i++) {
        int x = cities[i].x - powerPlant.x;
        int y = cities[i].y - powerPlant.y;
        double length = sqrt((x * x) + (y * y));
        e.v = i;
        e.w = numCities;
        e.weight = length;
        GraphInsertEdge(g, e);

        for (int j = i + 1; j < numCities; j++) {
            x = cities[i].x - cities[j].x;
            y = cities[i].y - cities[j].x;
            length = sqrt((x * x) + (y * y));
            e.v = i;
            e.w = j;
            e.weight = length;
            GraphInsertEdge(g, e);
        }
    }

    Graph mst = GraphMST(g);
    PowerLine p;
    int index = 0;
    for (int i = 0; i < numCities; i++) {
        if (GraphIsAdjacent(mst, i, numCities)) {
            p.p1 = cities[i];
            p.p2 = powerPlant;
            powerLines[index] = p;
            index++;
        }

        for (int j = i + 1; j < numCities; j++) {
            if (GraphIsAdjacent(mst, i, j) != 0) {
                p.p1 = cities[i];
                p.p2 = cities[j];
                powerLines[index] = p;
                index++;
            }
        }
    }

    GraphFree(mst);
    GraphFree(g);
    return index;
}

////////////////////////////////////////////////////////////////////////
// Optional task

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * to all the given cities.  Power lines must be built between cities or
 * between a city and a power plant.  Cost is directly  proportional  to
 * the  total  length of power lines used.  Assume that each power plant
 * generates enough electricity to supply all cities, so not  all  power
 * plants need to be used.
 * Assumes  that  numCities and numPowerPlants are at least 1 (numCities
 * and numPowerPlants are the sizes of the cities and powerPlants arrays
 * respectively).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */
int planGrid2(Place cities[], int numCities,
              Place powerPlants[], int numPowerPlants,
              PowerLine powerLines[]) {
    // TODO: Complete this function
    return 0;
}

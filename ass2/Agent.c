// Phot Koseekrainiramon (z5387411)
// COMP2521 assignment 2
// on 31/07/2022
// Implementation of the Agent ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Agent.h"
#include "Map.h"

typedef int Item;
typedef struct queue *Queue;
typedef struct node  *Node;

// struct node storing item for queue
struct node {
	Item item;  // storing city id as an item
	Node next;
};

// struct queue to store the path when getting an information
struct queue {
	Node head;
	int  size;
};

// This struct stores information about an individual agent and can be
// used to store information that the agent needs to remember.
struct agent {
	char  *name;
	int    startLocation;
	int    location;
	int    maxStamina;      // max stamina
	int    stamina;         // current stamina
	int    strategy;
	Map    map;
	int   *numVisit;        // tracking a number of time visitting a city
							// using each city id as an index
	int   *prev;            // tracking the previous city visited before
							// coming to the index (current location)
	int   *visited;         // tracking whether if the index
							// (current location) is visited using
							// 0 as unvisited and 1 as visited
	Queue  q;               // tracking the path following the information
};

static Move chooseRandomMove(Agent agent, Map m);
static int filterRoads(Agent agent, Road roads[], int numRoads,
					   Road legalRoads[]);
static Move chooseCheapestLeastVisitedMove(Agent agent, Map m);
static int filterCheapestLeastVisted(Agent agent, Road legalRoads[],
									 int numLegalRoads,
									 Road leastVisitedRoads[]);
static Move chooseDFSMove(Agent agent, Map m);

// Helper functions
static void setVisited(Agent agent, Map m);
static Move followInfo(Agent agent);
static int getLength(Agent agent, int location, int dest);
static void dijkstra(Agent agent, int V, int map[][V],
					 int location, int dest);
static void findPath(Queue vSet, int V, int visited[], int length[][V],
					 int stamina[], int turn[], int pred[], Agent agent, int dest);
static Queue QueueNew(void);
static void QueueFree(Queue q);
static void QueueEnqueue(Queue q, Item it);
static Item QueueDequeue(Queue q);
static bool QueueIsEmpty(Queue q);
static Item QueueFront(Queue q);
static int maximumFilterRoads(Agent agent, Road roads[], int numRoads,
							  Road legalRoads[]);

////////////////////////////////////////////////////////////////////////
// Basic operation

/**
 * Creates a new agent
 */
Agent AgentNew(int start, int stamina, int strategy, Map m, char *name) {
	if (start >= MapNumCities(m)) {
		fprintf(stderr, "error: starting city (%d) is invalid\n", start);
		exit(EXIT_FAILURE);
	}
	
	Agent agent = malloc(sizeof(struct agent));
	if (agent == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}
	
	agent->startLocation = start;
	agent->location = start;
	agent->maxStamina = stamina;
	agent->stamina = stamina;
	agent->strategy = strategy;
	agent->map = m;
	agent->name = strdup(name);
	
	agent->numVisit = malloc(MapNumCities(m) * sizeof(int *));
	if (agent->numVisit == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}
	agent->visited = calloc(MapNumCities(m), sizeof(int *));
	if (agent->visited == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}
	agent->prev = calloc(MapNumCities(m), sizeof(int *));
	if (agent->prev == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}
	agent->q = QueueNew();
	for (int i = 0; i < MapNumCities(m); i++) {
		agent->numVisit[i] = 0;
		agent->visited[i] = 0;
	}
	agent->numVisit[start]++;
	return agent;
}

/**
 * Frees all memory associated with the agent
 * NOTE: You should not free the map because the map is owned by the
 *       main program, and the main program will free it
 */
void AgentFree(Agent agent) {
	free(agent->name);
	free(agent->numVisit);
	free(agent->prev);
	free(agent->visited);
	QueueFree(agent->q);
	free(agent);
}

////////////////////////////////////////////////////////////////////////
// Making moves

/**
 * Calculates the agent's next move
 */
Move AgentGetNextMove(Agent agent, Map m) {
	switch (agent->strategy) {
		case STATIONARY:                return (Move){agent->location, 0};
		case RANDOM:                    return chooseRandomMove(agent, m);
		case CHEAPEST_LEAST_VISITED:
			return chooseCheapestLeastVisitedMove(agent, m);
		case DFS:                       return chooseDFSMove(agent, m);
		default:
			printf("error: strategy not implemented yet\n");
			exit(EXIT_FAILURE);
	}
}

// Move to next city randomly
static Move chooseRandomMove(Agent agent, Map m) {
	// check if an agent has an information path to follow or not
	if (!QueueIsEmpty(agent->q)) {
		return followInfo(agent);
	}
	// back to old strat if have no information paths
	Road *roads = malloc(MapNumCities(m) * sizeof(Road));
	Road *legalRoads = malloc(MapNumCities(m) * sizeof(Road));

	// Get all roads to adjacent cities
	int numRoads = MapGetRoadsFrom(m, agent->location, roads);

	// Filter out roads that the agent does not have enough stamina for
	int numLegalRoads = filterRoads(agent, roads, numRoads, legalRoads);

	Move move;
	if (numLegalRoads > 0) {
		// Sort the roads using insertion sort
		for (int i = 1; i < numLegalRoads; i++) {
			Road r = legalRoads[i];
			int j = i;
			while (j > 0 && r.to < legalRoads[j - 1].to) {
				legalRoads[j] = legalRoads[j - 1];
				j--;
			}
			legalRoads[j] = r;
		}
		
		// nextMove is randomly chosen from the legal roads
		int k = rand() % numLegalRoads;
		move = (Move){legalRoads[k].to, legalRoads[k].length};
		agent->numVisit[legalRoads[k].to]++;
	} else {
		// The agent must stay in the same location
		move = (Move){agent->location, 0};
		agent->numVisit[agent->location]++;
	}
	
	free(legalRoads);
	free(roads);
	return move;
}

// Move to next least visited city, choose the cheapest if there are cities
// with same numVisited, choose the one with lowest id if there are cites
// with same numVisited with smae costs.
static Move chooseCheapestLeastVisitedMove(Agent agent, Map m) {
	// check if an agent has an information path to follow or not
	if (!QueueIsEmpty(agent->q)) {
		return followInfo(agent);
	}
	// back to old strat if have no information paths
	Road *roads = malloc(MapNumCities(m) * sizeof(Road));
	Road *legalRoads = malloc(MapNumCities(m) * sizeof(Road));
	Road *leastVisitedRoads = malloc(MapNumCities(m) * sizeof(Road));

	// Get all roads to adjacent cities
	int numRoads = MapGetRoadsFrom(m, agent->location, roads);

	// Filter out roads that the agent does not have enough stamina for
	int numLegalRoads = filterRoads(agent, roads, numRoads, legalRoads);

	Move move;
	if (numLegalRoads > 0) {
		// Filter least visited cities to an array and return index of the
		// cheapest city among those and use that city as a move
		int cheapestIndex = filterCheapestLeastVisted(agent, legalRoads,
													  numLegalRoads,
													  leastVisitedRoads);
		// nextMove is the cheapest city with lowest id from
		// the least visited roads
		move = (Move){leastVisitedRoads[cheapestIndex].to,
					  leastVisitedRoads[cheapestIndex].length};
		agent->numVisit[leastVisitedRoads[cheapestIndex].to]++;
	} else {
		// The agent must stay in the same location
		move = (Move){agent->location, 0};
		agent->numVisit[agent->location]++;
	}
	
	free(leastVisitedRoads);
	free(legalRoads);
	free(roads);
	return move;
}

// Taking the agent through every city on the map using the DFS algorithm.
// If the DFS has a choice between multiple cities,
// it must prioritise the city with the lowest ID.
static Move chooseDFSMove(Agent agent, Map m) {
	// check if an agent has an information path to follow or not
	if (!QueueIsEmpty(agent->q)) {
		return followInfo(agent);
	}
	// back to old strat if have no information paths
	// set the pointer prev and visited of an agent when start over the strat
	setVisited(agent, m);
	// mark current city as visited and finding the next supposed city
	// to be visitted that never been visited (dfs) into dest
	agent->visited[agent->location] = 1;
	Road *roads = malloc(MapNumCities(m) * sizeof(Road));
	int numRoads = MapGetRoadsFrom(m, agent->location, roads);
	int dest = MapNumCities(m);
	int length;
	for (int i = 0; i < numRoads; i++) {
		if (!agent->visited[roads[i].to]) {
			dest = roads[i].to;
			length = roads[i].length;
			break;
		}
	}

	Move move;
	// for the case that there's no next cities not ever been visited 
	if (dest == MapNumCities(m)) {
		// finding the index of the previous city using pointer prev
		for (int i = 0; i < numRoads; i++) {
			if (roads[i].to == agent->prev[agent->location]) {
				dest = roads[i].to;
				length = roads[i].length;
				break;
			}
		}
		// nextMove is the previous city
		if (agent->stamina >= length) {
			move = (Move){dest, length};
			agent->numVisit[dest]++;
		} else {
			// The agent must stay in the same location
			move = (Move){agent->location, 0};
			agent->numVisit[agent->location]++;
		}
	} else if (agent->stamina >= length) {
		// nextMove is the lowest id of unvisited city chosen by using dfs
		move = (Move){dest, length};
		agent->prev[dest] = agent->location;
		agent->numVisit[dest]++;
	} else {
		// The agent must stay in the same location
		move = (Move){agent->location, 0};
		agent->numVisit[agent->location]++;
	}
	free(roads);
	return move;
}

// Takes an array with all the possible roads and puts the ones the agent
// has enough stamina for into the legalRoads array
// Returns the number of legal roads
static int filterRoads(Agent agent, Road roads[], int numRoads,
					   Road legalRoads[]) {
	int numLegalRoads = 0;
	for (int i = 0; i < numRoads; i++) {
		if (roads[i].length <= agent->stamina) {
			legalRoads[numLegalRoads++] = roads[i];
		}
	}
	return numLegalRoads;
}

// Takes an array with all the possible roads and puts the least visited ones
// the agent has enough stamina for into the leastVisitedRoads array
// Returns index of cheapest leastVisitedRoads
static int filterCheapestLeastVisted(Agent agent, Road legalRoads[],
									 int numLegalRoads,
									 Road leastVisitedRoads[]) {
	// finding the least amount of time a city is ever visited 
	int leastVisitedCity = agent->numVisit[legalRoads[0].to];
	for (int i = 1; i < numLegalRoads; i++) {
		if (agent->numVisit[legalRoads[i].to] < leastVisitedCity) {
			leastVisitedCity = agent->numVisit[legalRoads[i].to];
		}
	}
	// fill an array leastVisitedRoads with cities' getting visited the least
	int numleastVisited = 0;
	for (int i = 0; i < numLegalRoads; i++) {
		if (agent->numVisit[legalRoads[i].to] == leastVisitedCity) {
			leastVisitedRoads[numleastVisited++] = legalRoads[i];
		}
	}
	// the cheapest index is 0 when there's only 1 least visited city
	if (numleastVisited == 1) {
		return 0;
	}
	// if there're more than 1 least visited city, finding the index of
	// the cheapest one among them, always return the cheapest index of all
	int cheapestIndex = numleastVisited - 1;
	int cheapestLength = leastVisitedRoads[numleastVisited - 1].length;
	for (int i = numleastVisited - 2; i >= 0; i--) {
		if (leastVisitedRoads[i].length <= cheapestLength) {
			cheapestIndex = i;
			cheapestLength = leastVisitedRoads[i].length;
		}
	}
	return cheapestIndex;
}

/**
 * Executes a given move by updating the agent's internal state
 */
void AgentMakeNextMove(Agent agent, Move move) {
	if (move.to == agent->location) {
		agent->stamina = agent->maxStamina;
	} else {
		agent->stamina -= move.staminaCost;
	}
	agent->location = move.to;    
}

////////////////////////////////////////////////////////////////////////
// Gets information about the agent
// NOTE: It is expected that these functions do not need to be modified

/**
 * Gets the name of the agent
 */
char *AgentName(Agent agent) {
	return agent->name;
}

/**
 * Gets the current location of the agent
 */
int AgentLocation(Agent agent) {
	return agent->location;
}

/**
 * Gets the amount of stamina the agent currently has
 */
int AgentStamina(Agent agent) {
	return agent->stamina;
}

////////////////////////////////////////////////////////////////////////
// Learning information

/**
 * Tells the agent where the thief is
 */
void AgentGainInfo(Agent agent, int thiefLocation) {
	// reset visited and prev pointer for dfs strat to restrat the strat
	// when done following least turns path
	for (int i = 0; i < MapNumCities(agent->map); i++) {
		agent->visited[i] = 0;
		agent->prev[i] = -1;
	}
	int v = MapNumCities(agent->map);
	// setting a map using length of index x and y
	int map[v][v];
	for (int i = 0; i < v; i++) {
		Road *roads = malloc(v * sizeof(Road));
		Road *legalRoads = malloc(v * sizeof(Road));
		int numRoads = MapGetRoadsFrom(agent->map, i, roads);
		int numLegalRoads = maximumFilterRoads(agent, roads,
											   numRoads, legalRoads);
		for (int j = 0; j < v; j++) {
			map[i][j] = 0;
		}
		for (int k = 0; k < numLegalRoads; k++) {
			map[i][legalRoads[k].to] = legalRoads[k].length;
			map[legalRoads[k].to][i] = legalRoads[k].length;
		}
		free(legalRoads);
		free(roads);
	}
	// assigning a path to the agent
	dijkstra(agent, v, map, agent->location, thiefLocation);
	return;
}

////////////////////////////////////////////////////////////////////////
// Displaying state

/**
 * Prints information about the agent (for debugging purposes)
 */
void AgentShow(Agent agent) {
	return;
}

////////////////////////////////////////////////////////////////////////
// Helper functions

// Setting prev and visited pointer of the agent,
// reset if all cities has been visited
static void setVisited(Agent agent, Map m) {
	for (int i = 0; i < MapNumCities(m); i++) {
		// do nothing if some cities haven't been visited
		if (!agent->visited[i]) {
			return;
		}
	}
	// Set all visited back to 0
	for (int i = 0; i < MapNumCities(m); i++) {
		agent->visited[i] = 0;
		agent->prev[i] = -1;
	}
	return;
}

// if an agent have still got an information of the thief, he then continuing
// his path heading to the location of the thief when he first got it
static Move followInfo(Agent agent) {
	Move move;
	int dest = QueueFront(agent->q);
	int length = getLength(agent, agent->location, dest);
	if (agent->stamina < length) {
		// make a move following the info
		move = (Move){agent->location, 0};
		agent->numVisit[agent->location]++;
	} else {
		// The agent must stay in the same location
		dest = QueueDequeue(agent->q);
		move = (Move){dest, length};
		agent->numVisit[dest]++;
	}
	return move;
}

// letting the agent know the least turns path heading to the thief's location
// storing the path as a queue using pointer q of the agent
static void dijkstra(Agent agent, int V, int length[][V],
					 int location, int dest) {
	// tracking how many turn to the city index
	int *turn = calloc(V, sizeof(int *));
	// tracking how much stamina is left at the city index
	int *stamina = calloc(V, sizeof(int *));
	// tracking predecessor of the least turns path from city index
	int *pred = calloc(V, sizeof(int *));
	// checking if the city index has been visited (1) or not (0)
	int *visited = calloc(V, sizeof(int *));
	for (int i = 0; i < V; i++) {
		turn[i] = V * V;
		stamina[i] = agent->stamina;
		pred[i] = -1;
		visited[i] = 0;
	}
	turn[location] = 0;
	// vertices with unknown least turns path
	Queue vSet = QueueNew();
	QueueEnqueue(vSet, location);
	// getting the path
	findPath(vSet, V, visited, length, stamina, turn, pred, agent, dest);
	// storing the path into a queue
	Queue q = QueueNew();
	int curr = dest;
	while (pred[curr] != -1) {
		QueueEnqueue(q, curr);
		curr = pred[curr];
	}
	QueueFree(agent->q);
	QueueFree(vSet);
	free(visited);
	free(pred);
	free(stamina);
	free(turn);
	// setting pointer q of the agent to track the path
	agent->q = q;
	return;
}

// finding the least turns path by tracking pred
static void findPath(Queue vSet, int V, int visited[], int length[][V],
					 int stamina[], int turn[], int pred[], Agent agent, int dest) {
	int lastStemina = 0;
	while (!QueueIsEmpty(vSet)) {
		// current city index
		int curr = QueueDequeue(vSet);
		visited[curr] = 1;
		// for all cities
		for (int i = 0; i < V; i++) {
			// consider only the unvisited one
			if (length[curr][i] != 0 && !visited[i]) {
				// relaxation
				int numTurns = 0;
				// tracking current stamina
				stamina[i] = stamina[curr];
				// add turn and refill stamina if the agent has to stop
				if (stamina[i] < length[curr][i]) {
					stamina[i] = agent->maxStamina;
					numTurns++;
				}
				// an agent crossing a road (take turn and lose stamina)
				numTurns++;
				stamina[i] -= length[curr][i];
				// update data for city index i
				if (turn[curr] + numTurns < turn[i]) {
					turn[i] = turn[curr] + numTurns;
					pred[i] = curr;
					QueueEnqueue(vSet, i);
				}
				if (turn[curr] + numTurns == turn[i] &&
					stamina[i] > lastStemina) {
					// in case it takes the same turn, we will have the one
					// with more stamina left
					pred[i] = curr;
					lastStemina = stamina[i];
				}
			}
		}
	}
}

// returning length between location and destination,
// return 0 is they are not connected
static int getLength(Agent agent, int location, int dest) {
	Road *roads = malloc(MapNumCities(agent->map) * sizeof(Road));
	int numRoads = MapGetRoadsFrom(agent->map, location, roads);
		for (int i = 0; i < numRoads; i++) {
			if (roads[i].to == dest) {
				int length = roads[i].length;
				free(roads);
				return length;
			}
		}
	free(roads);
	return 0;
}

/**
 * Creates a new empty queue
 */
static Queue QueueNew(void) {
	Queue q = malloc(sizeof(*q));
	if (q == NULL) {
		fprintf(stderr, "couldn't allocate Queue\n");
		exit(EXIT_FAILURE);
	}

	q->head = NULL;
	q->size = 0;
	return q;
}

/**
 * Frees all resources associated with the given queue
 */
static void QueueFree(Queue q) {
	Node curr = q->head;
	while (curr != NULL) {
		Node temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(q);
}

/**
 * Adds an item to the front of the queue
 */
static void QueueEnqueue(Queue q, Item it) {
	Node n = malloc(sizeof(*n));
	if (n == NULL) {
		fprintf(stderr, "couldn't allocate Queue\n");
		exit(EXIT_FAILURE);
	}
	n->item = it;
	q->size++;
	if (QueueIsEmpty(q)) {
		n->next = NULL;
		q->head = n;
		return;
	}
	n->next = q->head;
	q->head = n;
	return;
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
static Item QueueDequeue(Queue q) {
	if (q->head == NULL) {
		return -1;
	}
	Node current = q->head;
	Item item = current->item;
	q->head = current->next;
	free(current);
	q->size -= 1;

	return item;
}

/**
 * Returns true if the queue is empty, and false otherwise
 */
static bool QueueIsEmpty(Queue q) {
	return q->size == 0;
}

/**
 * Gets the item at the front of the queue without removing it
 * Assumes that the queue is not empty
 */
static Item QueueFront(Queue q) {
	assert(q->size > 0);

	return q->head->item;
}

// Takes an array with all the possible roads and puts the ones the agent
// has enough maximum stamina for into the legalRoads array
// Returns the number of legal roads
static int maximumFilterRoads(Agent agent, Road roads[], int numRoads,
							  Road legalRoads[]) {
	int numLegalRoads = 0;
	for (int i = 0; i < numRoads; i++) {
		if (roads[i].length <= agent->maxStamina) {
			legalRoads[numLegalRoads++] = roads[i];
		}
	}
	return numLegalRoads;
}

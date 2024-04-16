// Phot Koseekrainiramon (z5387411)
// on 17/07/2022
// DFS maze solver

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Stack.h"

bool solve(Maze m) {
    int height = MazeHeight(m);
    int width = MazeWidth(m);
    bool **visited = createBoolMatrix(height, width);
    Cell **pred = createCellMatrix(height, width);

    Stack s = StackNew();
    Cell start = MazeGetStart(m);
    StackPush(s, start);
    // DFS
    bool found = false;
    while (!found && !StackIsEmpty(s)) {
        Cell v = StackPop(s);
        visited[v.row][v.col] = true;
        if (MazeVisit(m, v)) {
            found = true;
            // Make way back to the starting point
            Cell current = v;
            while (current.col != start.col || current.row != start.row) {
                MazeMarkPath(m, current);
                current = pred[current.row][current.col];
            }
            MazeMarkPath(m, start);

        } else {
            // Check adjecent areas
            Cell adj[4] = {
                { .row = v.row - 1, .col = v.col },
                { .row = v.row + 1, .col = v.col },
                { .row = v.row, .col = v.col - 1 },
                { .row = v.row, .col = v.col + 1 },
            };
            for (int i = 0; i < 4; i++) {
                Cell w = adj[i];
                // Check wall and have visited cases and is in the maze
                if (w.row >= 0 && w.row < height && w.col >= 0 && w.col < width) {
                    if (!MazeIsWall(m, w) && !visited[w.row][w.col]) {
                        StackPush(s, w);
                        pred[w.row][w.col] = v;
                    }
                }
            }
        }
    }

    StackFree(s);
    freeCellMatrix(pred);
    freeBoolMatrix(visited);

    return found;
}


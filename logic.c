#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"

// Global variables
Cell maze[3][10][25];

Player players[3] = {   {0, 'A', NORTH, 0, 6, 12, false, 0, false, 0},
                        {1, 'B', WEST,  0, 9,  8, false, 0, false, 0},
                        {2, 'C', EAST,  0, 9, 16, false, 0, false, 0}   };

// Function definitions
void printPlayer(int value) {
    if (value == 0) {
        printf("Player A");
    }
    else if (value == 1) {
        printf("Player B");
    }
    else {
        printf("Player C");
    }
}

void initializeMaze() {
    for (int f = 0; f < 3; f++) {
        for (int w = 0; w < 10; w++) {
            for (int l = 0; l < 25; l++) {
                maze[f][w][l].floor = f;
                maze[f][w][l].width = w;
                maze[f][w][l].length = l;
                maze[f][w][l].isEmpty = true;
                maze[f][w][l].isWall = false;
                maze[f][w][l].isStartingArea = false;
                maze[f][w][l].isStairsStart = false;
                maze[f][w][l].isStairsEnd = false;
                maze[f][w][l].isPoleStart = false;
                maze[f][w][l].isPoleEnd = false;
                maze[f][w][l].isGoal = false;
            }
        }
    }

    // Adding the starting area
    for (int w = 6; w < 10; w++)
        for (int l = 8; l < 17; l++) {
            maze[0][w][l].isStartingArea = true;
            maze[0][w][l].isWall = true;
            maze[0][w][l].isEmpty = false;
        }

    // Adding the second floor walls
    for (int w = 0; w < 6; w++)
        for (int l = 8; l < 17; l++) {
            maze[1][w][l].isWall = true;
            maze[1][w][l].isEmpty = false;
        }

    // Adding the third floor walls
    for (int w = 0; w < 10; w++)
        for (int l = 0; l < 8; l++) {
            maze[2][w][l].isWall = true;
            maze[2][w][l].isEmpty = false;
        }

    // Adding the third floor walls
    for (int w = 0; w < 10; w++)
        for (int l = 17; l < 25; l++) {
            maze[2][w][l].isWall = true;
            maze[2][w][l].isEmpty = false;
        }

    // Stairs
    maze[0][4][5].isStairsStart = true;
    maze[2][0][10].isStairsEnd = true;

    // Poles
    maze[0][5][24].isPoleStart = true;
    maze[2][5][24].isPoleEnd = true;

    // Goal
    maze[2][0][16].isGoal = true;
}

// Rolling the movement dice
int rollMovementDice() { 
    return rand() % 6 + 1; 
}

// Rolling the direction dice
int rollDirectionDice() { 
    return rand() % 6 + 1; 
}

// Check the eligibility to roll the direction dice
bool isEligibleForDirectionRoll(int value) { 
    return (players[value].steps % 4 == 3); 
}

void updateDirection(int value, int directionDice) {
    if (directionDice == 2) {
        players[value].dir = NORTH;
    } else if (directionDice == 3) {
        players[value].dir = EAST;
    } else if (directionDice == 4) {
        players[value].dir = SOUTH;
    } else if (directionDice == 5) {
        players[value].dir = WEST;
    }
}

bool canPlayerMove(int value, int movementDice) {
    int f = players[value].floor;
    int w = players[value].width;
    int l = players[value].length;

    if (players[value].dir == NORTH) {
        if (w - movementDice < 0) {
            return true;
        } else {
            for (int i = movementDice; i >= 1; i--) {
                if (!maze[f][w - i][l].isWall) {
                    return true;
                }   
            }
            return false;
        }
    } else if (players[value].dir == EAST) {
        if (l + movementDice > 24) {
            return true;
        } else {
            for (int i = movementDice; i >= 1; i--) {
                if (!maze[f][w][l + i].isWall) {
                    return true;
                }
            }
            return false;
        }   
    } else if (players[value].dir == SOUTH) {
        if (w + movementDice > 9) {
            return true;
        } else {
            for (int i = movementDice; i >= 1; i--) {
                if (!maze[f][w + i][l].isWall) {
                    return true;
                }
            }
            return false;
        }
    } else {
        if (l - movementDice < 0) {
            return true;
        } else {
            for (int i = movementDice; i >= 1; i--) {
                if (!maze[f][w][l - i].isWall) {
                    return true;
                }
            }
            return false;
        }
    }
}

void checkStairsAndPoles(int value) {
    int f = players[value].floor;
    int w = players[value].width;
    int l = players[value].length;

    // cheking for the stairs
    if (maze[f][w][l].isStairsStart) {
        players[value].floor = 2; players[value].width = 0; players[value].length = 10;
    } else if (maze[f][w][l].isStairsEnd) {
        players[value].floor = 0; players[value].width = 4; players[value].length = 5;
    }

    // cheking for the poles
    if (maze[f][w][l].isPoleEnd) {
        players[value].floor = 0; players[value].width = 5; players[value].length = 24;
    }
}

void movePlayer(int value, int movementDice) {
    int f = players[value].floor;
    int w = players[value].width;
    int l = players[value].length;

    maze[f][w][l].isEmpty = true;

    for (int i = 1; i <= movementDice; i++) {
        if (players[value].dir == NORTH) {
            w--;
        } else if (players[value].dir == EAST) {
            l++;
        } else if (players[value].dir == SOUTH) {
            w++;
        } else {
            l--;
        }

        if (w < 0) {
            w = 0;
        }
        if (w > 9) {
            w = 9;
        }
        if (l < 0) {
            l = 0;
        }
        if (l > 24) {
            l = 24;
        }

        players[value].floor = f;
        players[value].width = w;
        players[value].length = l;

        checkStairsAndPoles(value);

        f = players[value].floor;
        w = players[value].width;
        l = players[value].length;
    }
    maze[f][w][l].isEmpty = false;
}

void capturePlayer(int value) {
    for (int i = 0; i < 3; i++) {
        if (i != value &&
            players[i].floor == players[value].floor &&
            players[i].width == players[value].width &&
            players[i].length == players[value].length &&
            !players[i].hasWon) {
            players[i].isEntered = false;

            if (i == 0) { 
                players[i].floor = 0; players[i].width = 6; players[i].length = 12; 
            } else if (i == 1) { 
                players[i].floor = 0; players[i].width = 9; players[i].length = 8; 
            } else { 
                players[i].floor = 0; players[i].width = 9; players[i].length = 16; 
            }

            printf("\n");
            printPlayer(value);
            printf(": captured ");
            printPlayer(i);
        }
    }
}

bool hasPlayerWon(int value) {
    return maze[players[value].floor][players[value].width][players[value].length].isGoal;
}

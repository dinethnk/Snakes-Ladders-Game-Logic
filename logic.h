#ifndef LOGIC_H
#define LOGIC_H

#include <stdbool.h>

// Data types
typedef struct {
    int floor;
    int width;
    int length;
    bool isEmpty;
    bool isWall;
    bool isStartingArea;
    bool isStairsStart;
    bool isStairsEnd;
    bool isPoleStart;
    bool isPoleEnd;
    bool isGoal;
} Cell;

typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
} Direction;

typedef struct {
    int value;
    char name;
    Direction dir;
    int floor;
    int width;
    int length;
    bool isEntered;
    int steps;
    bool hasWon;
    int placeWon;
} Player;

// External variables
extern Cell maze[3][10][25];
extern Player players[3];

// Function prototypes
void printPlayer(int value);
void initializeMaze();
int rollMovementDice();
int rollDirectionDice();
bool isEligibleForDirectionRoll(int value);
void updateDirection(int value, int directionDice);
bool canPlayerMove(int value, int movementDice);
void checkStairsAndPoles(int value);
void movePlayer(int value, int movementDice);
void capturePlayer(int value);
bool hasPlayerWon(int value);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"

int main() {
    srand(time(NULL));
    initializeMaze();
    printf("\nWelcome to Maze to Savor!\nPlayers: A, B, C\n");
    printf("\n\n==============================================================================================================");
    int winner = -1;
    int round = 0;
    bool gameOver = false;

    while (!gameOver) {
        for (int i = 0; i < 3; i++) {
            if (!players[i].isEntered) {
                int movementDice = rollMovementDice();
                printf("\n\n");
                printPlayer(i);
                printf(": movement dice = %d", movementDice);

                if (movementDice == 6) {
                    players[i].isEntered = true;
                    if (i == 0) { 
                        players[i].floor = 0;
                        players[i].width = 5; 
                        players[i].length = 12; 
                    } else if (i == 1) { 
                        players[i].floor = 0; 
                        players[i].width = 9; 
                        players[i].length = 7; 
                    } else { 
                        players[i].floor = 0; 
                        players[i].width = 9; 
                        players[i].length = 17; 
                    }

                    printf(" -> entered maze at [%d,%d,%d]", players[i].floor, players[i].width, players[i].length);
                    maze[players[i].floor][players[i].width][players[i].length].isEmpty = false;
                } else {
                    printf(" -> waiting at starting area");
                }
            } else if (!players[i].hasWon) {
                int movementDice = rollMovementDice();
                printf("\n\n");
                printPlayer(i);
                printf(": movement dice = %d", movementDice);

                if (isEligibleForDirectionRoll(i)) {
                    int directionDice = rollDirectionDice();
                    updateDirection(i, directionDice);
                    printf(" | direction dice = %d | new direction: ", directionDice);

                    if (players[i].dir == NORTH) {
                        printf("NORTH");
                    } else if (players[i].dir == EAST) {
                        printf("EAST");
                    } else if (players[i].dir == SOUTH) {
                        printf("SOUTH");
                    } else {
                        printf("WEST");
                    }
                }

                if (canPlayerMove(i, movementDice)) {
                    movePlayer(i, movementDice);
                    printf(" -> moved to [%d,%d,%d]", players[i].floor, players[i].width, players[i].length);
                    capturePlayer(i);

                    if (hasPlayerWon(i)) {
                        players[i].hasWon = true;
                        winner = i;
                        printf(" *** Captured the flag! ***");
                        gameOver = true;
                        break;
                    }
                } else {
                    printf(" -> blocked, stayed at [%d,%d,%d]", players[i].floor, players[i].width, players[i].length);
                }
            }
            players[i].steps++;
        }
        round++;
        printf("\n\n\t--- End of round %d ---\n", round);
        printf("\n==============================================================================================================");
    }
    printf("\n\n\tGAME FINISHED\n");
    printf("\tWINNER: ");
    printPlayer(winner);
    printf("\n\n");
    return 0;
}
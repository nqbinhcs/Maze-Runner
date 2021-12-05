#include "TileMap.h"
#include "stdafx.h"

#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <stack>
#include <fstream>
#include <stack>
using namespace std;

void Cell::initialize(Cell gameMap[SIZE_ROW][SIZE_COL]) {
    for (int i = 1; i < SIZE_ROW - 1; i++) {
        for (int j = 1; j < SIZE_COL - 1; j++) {

            gameMap[1][j].top_wall = false;
            gameMap[SIZE_ROW - 2][j].bot_wall = false;
            gameMap[i][1].left_wall = false;
            gameMap[i][SIZE_COL - 2].right_wall = false;
        }
    }
}
void Cell::GenerateMaze(Cell Level[SIZE_ROW][SIZE_COL], int& posX, int& posY, int& goalX, int& goalY) {
    srand((unsigned)time(NULL));                                            // Pick random start cell
    int random = 0;
    int randomX = ((2 * rand()) + 1) % (SIZE_COL - 1);                      // Generate a random odd number between 1 and SIZE
    int randomY = ((2 * rand()) + 1) % (SIZE_ROW - 1);                      // Generate a random odd number between 1 and SIZE
    posX = randomX;                                             // Save player's initial X position
    posY = randomY;                                             // Save player's initial Y position
    int visitedCells = 1;
    int totalCells = ((SIZE_ROW - 1) / 2) * ((SIZE_COL - 1) / 2);
    int percent = 0;
    stack<int> back_trackX, back_trackY;                        // Stack is used to trace the reverse path

    Level[randomY][randomX].display = ' ';                      // Set S as the start cell
    Level[randomY][randomX].visited = true;                     // Set start cell as visited;

    while (visitedCells < totalCells)
    {
        if (((Level[randomY - 2][randomX].visited == false) && (Level[randomY][randomX].top_wall == true && Level[randomY - 2][randomX].bot_wall == true)) ||
            ((Level[randomY + 2][randomX].visited == false) && (Level[randomY][randomX].bot_wall == true && Level[randomY + 2][randomX].top_wall == true)) ||
            ((Level[randomY][randomX - 2].visited == false) && (Level[randomY][randomX].left_wall == true && Level[randomY][randomX - 2].right_wall == true)) ||
            ((Level[randomY][randomX + 2].visited == false) && (Level[randomY][randomX].right_wall == true && Level[randomY][randomX + 2].left_wall == true)))
        {
            random = (rand() % 4) + 1;      // Pick a random wall 1-4 to knock down

             // GO UP
            if ((random == 1) && (randomY > 1)) {
                if (Level[randomY - 2][randomX].visited == false) {    // If not visited
                    Level[randomY - 1][randomX].display = ' ';    // Delete display
                    Level[randomY - 1][randomX].visited = true;   // Mark cell as visited
                    Level[randomY][randomX].top_wall = false;   // Knock down wall

                    back_trackX.push(randomX);          // Push X for back track
                    back_trackY.push(randomY);          // Push Y for back track

                    randomY -= 2;                   // Move to next cell
                    Level[randomY][randomX].visited = true;     // Mark cell moved to as visited
                    Level[randomY][randomX].display = ' ';      // Update path
                    Level[randomY][randomX].bot_wall = false;   // Knock down wall
                    visitedCells++;                 // Increase visitedCells counter
                }
                else
                    continue;
            }

            // GO DOWN
            else if ((random == 2) && (randomY < SIZE_ROW - 2)) {
                if (Level[randomY + 2][randomX].visited == false) {    // If not visited
                    Level[randomY + 1][randomX].display = ' ';    // Delete display
                    Level[randomY + 1][randomX].visited = true;   // Mark cell as visited
                    Level[randomY][randomX].bot_wall = false;   // Knock down wall

                    back_trackX.push(randomX);          // Push X for back track
                    back_trackY.push(randomY);          // Push Y for back track

                    randomY += 2;                   // Move to next cell
                    Level[randomY][randomX].visited = true;     // Mark cell moved to as visited
                    Level[randomY][randomX].display = ' ';      // Update path
                    Level[randomY][randomX].top_wall = false;   // Knock down wall
                    visitedCells++;                 // Increase visitedCells counter
                }
                else
                    continue;
            }

            // GO LEFT
            else if ((random == 3) && (randomX > 1)) {
                if (Level[randomY][randomX - 2].visited == false) {    // If not visited
                    Level[randomY][randomX - 1].display = ' ';    // Delete display
                    Level[randomY][randomX - 1].visited = true;   // Mark cell as visited
                    Level[randomY][randomX].left_wall = false;  // Knock down wall

                    back_trackX.push(randomX);          // Push X for back track
                    back_trackY.push(randomY);          // Push Y for back track

                    randomX -= 2;                   // Move to next cell
                    Level[randomY][randomX].visited = true;     // Mark cell moved to as visited
                    Level[randomY][randomX].display = ' ';      // Update path
                    Level[randomY][randomX].right_wall = false; // Knock down wall
                    visitedCells++;                 // Increase visitedCells counter
                }
                else
                    continue;
            }

            // GO RIGHT
            else if ((random == 4) && (randomX < SIZE_COL - 2)) {
                if (Level[randomY][randomX + 2].visited == false) {    // If not visited
                    Level[randomY][randomX + 1].display = ' ';    // Delete display
                    Level[randomY][randomX + 1].visited = true;   // Mark cell as visited
                    Level[randomY][randomX].right_wall = false; // Knock down wall

                    back_trackX.push(randomX);          // Push X for back track
                    back_trackY.push(randomY);          // Push Y for back track

                    randomX += 2;                   // Move to next cell
                    Level[randomY][randomX].visited = true;     // Mark cell moved to as visited
                    Level[randomY][randomX].display = ' ';      // Update path
                    Level[randomY][randomX].left_wall = false;  // Knock down wall
                    visitedCells++;                 // Increase visitedCells counter
                }
                else
                    continue;
            }

            percent = (visitedCells * 100 / totalCells * 100) / 100;        // Progress in percentage
            //cout << endl << "   Generating a Random Maze... " << percent << "%" << endl;
        }
        else {
            randomX = back_trackX.top();
            back_trackX.pop();

            randomY = back_trackY.top();
            back_trackY.pop();
        }

        /*ClearScreen();
        Redraw(Level);*/
    }

    goalX = randomX;
    goalY = randomY;
    Level[goalY][goalX].display = ' ';

    //system("cls");
    //ClearScreen();
    //Redraw(Level);
    cout << endl << "Complete!" << endl;
}
void Cell::pointStartEnd(Cell Level[SIZE_ROW][SIZE_COL], int& posX, int& posY, int& goalX, int& goalY) {
    srand((unsigned)time(NULL));
    int random = (rand() % 2) + 1;

    /* Level[posY][posX].display == ' ';
     Level[goalY][goalX].display == ' ';*/

     //column one is start and column last is end.
    if (random == 1) {
        posX = 1;
        goalX = SIZE_COL - 2;
        do {
            posY = (rand() % (SIZE_ROW - 2)) + 1;
        } while (Level[posY][posX].display == '*');
        do {
            goalY = (rand() % (SIZE_ROW - 2)) + 1;
        } while (Level[goalY][goalX].display == '*');
    }
    //row one is start and row last is end.
    else {
        posY = 1;
        goalY = SIZE_ROW - 2;
        do {
            posX = (rand() % (SIZE_COL - 2)) + 1;
        } while (Level[posY][posX].display == '*');
        do {
            goalX = (rand() % (SIZE_COL - 2)) + 1;
        } while (Level[goalY][goalX].display == '*');
    }
    Level[posY][posX].display = 'S';
    Level[goalY][goalX].display = 'E';
}


bool TileMap::creatGameMap() {
    Cell::initialize(gameMap);
    Cell::GenerateMaze(gameMap, posX, posY, goalX, goalY);
    Cell::pointStartEnd(gameMap, posX, posY, goalX, goalY);
    return true;
}
bool TileMap::setdisplayMap() {
    for (int i = 0; i < SIZE_COL; i++) {
        for (int j = 0; j < SIZE_ROW; j++) {
            if (gameMap[j][i].getDisplay() == ' ') {
                displayRects[i + j * SIZE_COL].setPosition((i)*SIZE_CELL, (j)*SIZE_CELL);
                displayRects[i + j * SIZE_COL].setSize(SIZE_CELL, SIZE_CELL);
                displayRects[i + j * SIZE_COL].setOutLine(1.f, sf::Color(0, 0, 0));
                displayRects[i + j * SIZE_COL].setColor(sf::Color(10, 84, 100));
            }
            else if (gameMap[j][i].getDisplay() == 'E') {
                displayRects[i + j * SIZE_COL].setPosition((i)*SIZE_CELL, (j)*SIZE_CELL);
                displayRects[i + j * SIZE_COL].setSize(SIZE_CELL, SIZE_CELL);
                displayRects[i + j * SIZE_COL].setOutLine(1.f, sf::Color(0, 0, 0));
                displayRects[i + j * SIZE_COL].setColor(sf::Color(112, 110, 209));
            }
            else if (gameMap[j][i].getDisplay() == 'S') {
                displayRects[i + j * SIZE_COL].setPosition((i)*SIZE_CELL, (j)*SIZE_CELL);
                displayRects[i + j * SIZE_COL].setSize(SIZE_CELL, SIZE_CELL);
                displayRects[i + j * SIZE_COL].setOutLine(1.f, sf::Color(0, 0, 0));
                displayRects[i + j * SIZE_COL].setColor(sf::Color(255, 0, 0));
            }
            else {

                displayRects[i + j * SIZE_COL].setPosition((i)*SIZE_CELL, (j)*SIZE_CELL);
                displayRects[i + j * SIZE_COL].setSize(SIZE_CELL, SIZE_CELL);
                displayRects[i + j * SIZE_COL].setOutLine(1.f, sf::Color(0, 0, 0));
                displayRects[i + j * SIZE_COL].setColor(sf::Color(255, 181, 0));
            }
            //TAOJ CAC DIEM CHO NHIEU DUONG DI
            if (std::rand() / (float)RAND_MAX < 0.25f) {
                if (i != 0 && j != 0 && i < SIZE_COL - 1 && j < SIZE_ROW - 1 && gameMap[j][i].getDisplay() != 'S' && gameMap[j][i].getDisplay() != 'E') {
                    displayRects[i + j * SIZE_COL].setColor(sf::Color(10, 84, 100));
                }
            }
        }
    }
    return true;
}
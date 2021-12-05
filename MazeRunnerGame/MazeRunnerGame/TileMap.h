#pragma warning
#pragma once
#include "DefinedVariables.hpp"
#include "Square.hpp"
#include "Player.hpp"

class Cell {
private:
    bool visited;
    bool top_wall;
    bool bot_wall;
    bool left_wall;
    bool right_wall;
    char display;
public:
    Cell() {
        display = '*';
        visited = false;
        top_wall = true;
        bot_wall = true;
        left_wall = true;
        right_wall = true;
    }
    ~Cell() {

    }
    char getDisplay() {
        return display;
    }


    //Các hàm thao tác với mảng 2 chiều cell.
    static void initialize(Cell gameMap[SIZE_ROW][SIZE_COL]);
    static void GenerateMaze(Cell Level[SIZE_ROW][SIZE_COL], int& posX, int& posY, int& goalX, int& goalY);
    static void pointStartEnd(Cell Level[SIZE_ROW][SIZE_COL], int& posX, int& posY, int& goalX, int& goalY);

};


class TileMap
{
private:
    int posX, posY;
    int goalX, goalY;
    Cell gameMap[SIZE_ROW][SIZE_COL];
    Square displayRects[SIZE_ROW * SIZE_COL];

public:
    TileMap() {
        posX = posY = 0;
        goalX = goalY = 0;
    }
    ~TileMap() {
    }

    int getRowStart() {
        return posY;
    }
    int getColStart() {
        return posX;
    }
    int getRowEnd() {
        return goalY;
    }
    int getColEnd() {
        return goalX;
    }
    bool creatGameMap();
    bool setdisplayMap();

    void drawMap(sf::RenderTarget* target, Player player) {
        for (int i = 0; i < SIZE_ROW * SIZE_COL; i++) {
            this->displayRects[i].render(target);
        }
        player.update(target);
        player.render(target);
    }
};


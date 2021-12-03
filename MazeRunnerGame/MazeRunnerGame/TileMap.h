#pragma warning
#pragma once
#include "DefinedVariables.hpp"
#include "Square.hpp"
#include "Player.hpp"

class TileMap
{
private:
    int* gameMap;
    Square* displayRects;

public:
    TileMap() {
        gameMap = new int[12 * 20];
        displayRects = new Square[12 * 20];
    }
    ~TileMap() {
        delete[] gameMap;
        delete[] displayRects;
    }

    bool  getMap() {
        /*int gameMap[12 * 20];
        Square displayRects[12 * 20];*/
        std::srand(std::sin(std::time(nullptr)) * 1000);
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 12; j++) {
                this->displayRects[i + j * 20].setPosition(i * 50, j * 50);
                this->displayRects[i + j * 20].setSize(OBJECT_WIDTH, OBJECT_HEIGHT);
                this->displayRects[i + j * 20].setOutLine(1.f, sf::Color(0, 0, 0));

                if (std::rand() / (float)RAND_MAX < 0.22f || i == 0 || j == 0 || i == 19 || j == 11) {
                    this->gameMap[i + j * 20] = 1;
                    this->displayRects[i + j * 20].setColor(sf::Color(0, 0, 0));
                }
            }
        }
        return true;
	}

    void drawMap(sf::RenderTarget* target, Player player) {
        for (int i = 0; i < 12 * 20; i++) {
            this->displayRects[i].render(target);
        }
        player.update(target);
        player.render(target);
    }
};


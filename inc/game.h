#ifndef GameH
#define GameH
#include "map.h"
#include "snake.h"

struct GameLoopArgs{
    Snake* snake;
    Map* map;
    bool* gameOver;
    char* direction;
    int score;
};

struct TakeSnakeDirectionArgs{
    bool* gameOver;
    char* direction;
};

class Game{
private:
    static void* takeSnakeDirection(void* args);
    static void* gameLoop(void* args);
    void mainPage();
    static void createFood(Map*);
    int startGame();
    static bool isDirectionChanged(char* direction, Snake* snake, Map* map);
    void gameOverScreen(int);
public:
    void open();
};



#endif

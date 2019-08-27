#include "../inc/game.h"


int main(){
    Game* game = new Game();
    game->open();
    delete game;
    return 0;
}

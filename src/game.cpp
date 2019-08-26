#include "../inc/game.h"
#include "../inc/getch.h"
#include "../inc/location.h"
#include "../inc/cellstates.h"
#include "../inc/map.h"
#include "../inc/snake.h"
#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

using namespace std;


void Game::open(){
    mainPage();
}

void Game::mainPage(){
    char selection = '\0';
    int score;

    while(selection != '2'){
        selection = '\0';
        system("clear");

        cout<<"1. Start to play"<<endl;
        cout<<"2. Quit the game"<<endl;
        while(selection != '1' && selection != '2'){
            cout<<"\033[3;1H";
            cout<<"Select only 1 or 2: ";
            cin>>selection;
        }

        if(selection == '1'){
            score = startGame();
            gameOverScreen(score);
        }
    }
}

void Game::gameOverScreen(int score){
    cout<<"\033[1;31m"; // red color
    cout<<"\033[6;15H";

    //drawing a red frame with '#'
    for(int i =0; i < 30; i++){
        cout<<"#";
    }
    cout<<"\033[7;15H";
    for(int i = 0; i < 7; i++){
        cout<<"#";
        for(int k = 0; k < 28; k++){
            cout<<" ";
        }
        cout<<"#";
        cout<<"\033["<<8+i<<";"<<"15H";
    }
    for(int i =0; i < 30; i++){
        cout<<"#";
    }

    //showing the text
    cout<<"\033[8;26H";
    cout<<"GAME OVER";
    cout<<"\033[10;28HSCORE";
    cout<<"\033[12;30H"<<score;
    cout<<"\033[0;37m"; // white color
    fflush(stdout);
    getch();
}



void* Game::gameLoop(void* _args){
    //setting the arguments out of void struct pointer
    struct GameLoopArgs *args = (GameLoopArgs*)_args;
    Snake *snake = args->snake;
    Map *map = args->map;
    char * direction = args->direction;
    bool * gameOver = args->gameOver;
    bool isThereFood = false;
    int* score = &(args->score);
    //game loop
    while(! *gameOver){

        //food creation
        if(!isThereFood){
            Game::createFood(map);
            isThereFood = true;
            (*score)++;
            cout<<"\033[9;60HSCORE: "<<*score;
        }
        usleep(100000);
        //checks for direction changes every loop
        if(Game::isDirectionChanged(direction,snake,map)){
            if(*direction == 'w'){
                map->setCellStatus(snake->headLocation, UP_CORNER);
            }
            else if(*direction == 'a'){
                map->setCellStatus(snake->headLocation, LEFT_CORNER);
            }
            else if(*direction == 's'){
                map->setCellStatus(snake->headLocation, DOWN_CORNER);
            }
            else if(*direction == 'd'){
                map->setCellStatus(snake->headLocation, RIGHT_CORNER);
            }
        }
        *gameOver = ! snake->move(&isThereFood);
        fflush(stdout);
    }

}

void Game::createFood(Map *map){
/*
    This method can create some problems in the late game because random
    function might not found an empty location for food,
    so game can freeze.

    For solution, this method should run in a different thread
    or empty cell locations should be stored in a different list or array.
*/
    srand(time(NULL));
    Location* temp;

    //location's x axis value should be in [1-50]
    //           y axis value should be in [1-20]
    //otherwise we get segmentation fault
    while(map->getCellStatus(temp = new Location(rand() % 50 + 1, rand() % 20 + 1)) != EMPTY){
        delete temp;
    }
    map->setCellStatus(temp, FOOD); //putting the food on the map
    cout<<"\033["<<temp->y + 1<<";"<<temp->x + 1<<"HF"; // putting the food on screen.

    delete temp;
}


bool Game::isDirectionChanged(char* direction, Snake* snake, Map* map){
    //previous cell state of the snake's head
    CellStates cellState = map->getCellStatus(snake->headLocation);

    //demand for changing the direction in the same axis is not allowed.
    //it should be orthogonal
    if( (cellState == RIGHT_CONTD || cellState == LEFT_CONTD)  && (*direction == 'd'  || *direction == 'a')){
        return false;
    }
    else if((cellState == UP_CONTD || cellState == DOWN_CONTD ) && (*direction == 'w'  || *direction == 's')){
        return false;
    }
    else{
        true;
    }
}


void* Game::takeSnakeDirection(void* _args){
    //setting the arguments out of void struct pointer
    struct TakeSnakeDirectionArgs *args = (TakeSnakeDirectionArgs*) _args;
    char * direction = args->direction;
    bool * gameOver = args->gameOver;

    //takes new direction for snake from user untill the game ends
    while(! *gameOver){
        *direction = getch();
    }
}



int Game::startGame(){
    Map *map = new Map();
    Snake *snake = new Snake(map);
    char* direction = new char;
    bool* gameOver = new bool;

    //setting the starting direction of the snake as right
    *direction = 'd';
    *gameOver = false;

    //setting the struct for gameLoop method arguments
    struct GameLoopArgs args1;
    args1.snake = snake;
    args1.map = map;
    args1.gameOver = gameOver;
    args1.direction = direction;
    args1.score = -1;

    //setting the struct for takeSnakeDirection method arguments
    struct TakeSnakeDirectionArgs args2;
    args2.gameOver = gameOver;
    args2.direction = direction;

    //creating the threads
    pthread_t gameLooperThread, snakeDirectionTakerThread;
    pthread_create(&gameLooperThread, NULL, &(Game::gameLoop), (void*)&args1);
    pthread_create(&snakeDirectionTakerThread, NULL, &(Game::takeSnakeDirection),(void*)&args2);

    //thread joining
    pthread_join(gameLooperThread, NULL);
    pthread_join(snakeDirectionTakerThread, NULL);

    delete map;
    delete snake;
    delete direction;
    delete gameOver;

    return args1.score;
}

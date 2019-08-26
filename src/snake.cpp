#include "../inc/snake.h"
#include "../inc/location.h"
#include "../inc/map.h"
#include "../inc/cellstates.h"
#include <iostream>

using namespace std;

Snake::Snake(Map* map){
    this->map = map;
    this->headLocation = new Location(27,9);
    this->tailLocation = new Location(26,9);
    this->map->setCellStatus(this->headLocation, RIGHT_CONTD);
    this->map->setCellStatus(this->tailLocation, RIGHT_CONTD);
    cout<<"\033[10;27Ho";
    cout<<"\033[10;28Ho";

}
Snake::~Snake(){
    delete headLocation;
    delete tailLocation;
}

bool Snake::move(bool* isThereFood){
    bool foodEaten = false;
    if(moveTheHead(&foodEaten, isThereFood)){
        moveTheTail(foodEaten);
        return true;
    }
    else{
        return false;
    }
}

bool Snake::moveTheHead(bool* foodEaten, bool* isThereFood){
    CellStates headStatus = map->getCellStatus(headLocation);
    Location* tempLocation; // this variable is for preventing
                            //memoryleaks while sending a new Location instance as argument

    //move the head
    if(headStatus == RIGHT_CONTD || headStatus == RIGHT_CORNER){
        if(headLocation->x + 1 > 50){
            return false;
        }
        else if((map->getCellStatus(tempLocation = new Location(headLocation->x + 1, headLocation->y)) != EMPTY)
                &&(map->getCellStatus(tempLocation) != FOOD)){
            return false;
        }
        else{
            if(map->getCellStatus(tempLocation) == FOOD){
                *foodEaten = true;
                *isThereFood = false;
            }
            headLocation->x += 1;
            map->setCellStatus(headLocation, RIGHT_CONTD);
        }
    }

    else if(headStatus == LEFT_CONTD || headStatus == LEFT_CORNER){
        if(headLocation->x - 1 < 1){
            return false;
        }
        else if((map->getCellStatus(tempLocation = new Location(headLocation->x - 1, headLocation->y)) != EMPTY)
                && (map->getCellStatus(tempLocation) != FOOD)){
            return false;
        }
        else{
            if(map->getCellStatus(tempLocation) == FOOD){
                *foodEaten = true;
                *isThereFood = false;
            }
            headLocation->x -= 1;
            map->setCellStatus(headLocation, LEFT_CONTD);
        }
    }
    else if(headStatus == DOWN_CONTD || headStatus == DOWN_CORNER){
        if(headLocation->y + 1 > 20){
            return false;
        }
        else if((map->getCellStatus(tempLocation = new Location(headLocation->x, headLocation->y + 1)) != EMPTY)
                &&(map->getCellStatus(tempLocation) != FOOD)){
            return false;
        }
        else{
            if(map->getCellStatus(tempLocation) == FOOD){
                *foodEaten = true;
                *isThereFood = false;
            }
            headLocation->y += 1;
            map->setCellStatus(headLocation, DOWN_CONTD);
        }
    }
    else if (headStatus == UP_CONTD || headStatus == UP_CORNER){
        if(headLocation->y - 1 < 1){
            return false;
        }
        else if((map->getCellStatus(tempLocation = new Location(headLocation->x , headLocation->y - 1)) != EMPTY)
        &&(map->getCellStatus(tempLocation) != FOOD)){
            return false;
        }
        else{
            if(map->getCellStatus(tempLocation) == FOOD){
                *foodEaten = true;
                *isThereFood = false;
            }
            headLocation->y -= 1;
            map->setCellStatus(headLocation, UP_CONTD);
        }
    }

    //put the head on screen.
    cout<<"\033["<<headLocation->y + 1<<";"<<headLocation->x + 1<<"Ho";

    if(tempLocation != NULL){
        delete tempLocation;
    }

    return true;
}
void Snake::moveTheTail(bool foodEaten){

    if(!foodEaten){
        //move the tail
        CellStates tailStatus = map->getCellStatus(tailLocation);

        map->setCellStatus(tailLocation, EMPTY);
        cout<<"\033["<<tailLocation->y + 1<<";"<<tailLocation->x + 1<<"H ";
        if(tailStatus == RIGHT_CONTD || tailStatus == RIGHT_CORNER){
            tailLocation->x += 1;
        }

        else if(tailStatus == LEFT_CONTD || tailStatus == LEFT_CORNER){
            tailLocation->x -= 1;
        }
        else if(tailStatus == DOWN_CONTD || tailStatus == DOWN_CORNER){
            tailLocation->y += 1;
        }
        else if (tailStatus == UP_CONTD || tailStatus == UP_CORNER){
            tailLocation->y -= 1;
        }
    }
}

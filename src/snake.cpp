#include "../inc/snake.h"
#include "../inc/location.h"
#include "../inc/map.h"
#include "../inc/cellstates.h"
#include <iostream>

using namespace std;

Snake::Snake(Map* map){
    this->map = map;
    this->headLocation = new Location(HORIZONTAL_LENGTH / 2 + 2,  VERTICAL_LENGTH / 2 - 1);
    this->tailLocation = new Location(HORIZONTAL_LENGTH / 2 + 1,  VERTICAL_LENGTH / 2 - 1);
    this->map->setCellStatus(this->headLocation, RIGHT_CONTD);
    this->map->setCellStatus(this->tailLocation, RIGHT_CONTD);
    cout<<"\033["<< VERTICAL_LENGTH / 2 <<";"<< HORIZONTAL_LENGTH / 2 + 2<<"Ho";
    cout<<"\033[" << VERTICAL_LENGTH / 2 << ";"<< HORIZONTAL_LENGTH / 2 + 3 << "Ho";

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

bool Snake::checkMapBorderCollision(CellStates &headStatus, Location* headLocation){

    if(headStatus == RIGHT_CONTD || headStatus == RIGHT_CORNER){
        if(headLocation->x + 1 > HORIZONTAL_LENGTH){
            return false;
        }
        headLocation->x += 1;
        headStatus = RIGHT_CONTD;
    }
    else if(headStatus == LEFT_CONTD || headStatus == LEFT_CORNER){
        if(headLocation->x - 1 < 1){
            return false;
        }
        headLocation->x -=1;
        headStatus = LEFT_CONTD;
    }
    else if(headStatus == DOWN_CONTD || headStatus == DOWN_CORNER){
        if(headLocation->y + 1 > VERTICAL_LENGTH){
            return false;
        }
        headLocation->y += 1;
        headStatus = DOWN_CONTD;
    }
    else if (headStatus == UP_CONTD || headStatus == UP_CORNER){
        if(headLocation->y - 1 < 1){
            return false;
        }
        headLocation->y -=1;
        headStatus = UP_CONTD;
    }
    return true;
}

bool Snake::checkSnakeCollision(Location* headLocation, Map* map, bool* foodEaten, bool* isThereFood){
    if(map->getCellStatus(headLocation) == EMPTY){
        return true;
    }
    else if(map->getCellStatus(headLocation) == FOOD){
        *foodEaten = true;
        *isThereFood = false;
        return true;
    }
    else{
        return false;
    }
}

bool Snake::moveTheHead(bool* foodEaten, bool* isThereFood){
    CellStates headStatus = map->getCellStatus(headLocation);

    //move the head
    if(checkMapBorderCollision(headStatus, headLocation)){
        if(checkSnakeCollision(headLocation, map, foodEaten, isThereFood)){
            //there is no collision so move demand is approved
            //set the map
            map->setCellStatus(headLocation, headStatus);
            //put the head on screen.
            cout<<"\033["<<headLocation->y + 1<<";"<<headLocation->x + 1<<"Ho";
            return true;
        }
    }
    return false;

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

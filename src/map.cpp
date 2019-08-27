#include "../inc/map.h"
#include "../inc/cellstates.h"
#include "../inc/location.h"
#include <stdlib.h>
#include <iostream>

using namespace std;


int HORIZONTAL_LENGTH = 50;
int VERTICAL_LENGTH = 20;

Map::Map(){

    cells = new CellStates*[HORIZONTAL_LENGTH];
    for(int i = 0; i < HORIZONTAL_LENGTH; i++){
        cells[i] = new CellStates[VERTICAL_LENGTH];
        for(int k = 0; k < VERTICAL_LENGTH; k++){
            cells[i][k] = EMPTY;
        }
    }

    drawMap();
}

CellStates Map::getCellStatus(Location *location){
    return cells[location->x - 1][location->y - 1];
}

void Map::setCellStatus(Location *location, CellStates state){
    cells[location->x - 1][location->y - 1] = state;
}

void Map::drawMap(){
    system("clear");
    cout<<"\033[1;1H";

    for(int i = 0; i < HORIZONTAL_LENGTH + 2; i++){
        cout<<"#";
    }
    cout<<endl;
    for(int i = 0; i < VERTICAL_LENGTH; i++){
        cout<<"#";
        for(int k = 0; k < HORIZONTAL_LENGTH; k++){
            cout<<" ";
        }
        cout<<"#"<<endl;
    }
    for(int i = 0; i < HORIZONTAL_LENGTH + 2; i++){
        cout<<"#";
    }
}

Map::~Map(){
    for(int i = 0; i < HORIZONTAL_LENGTH; i++){
        delete [] cells[i];
    }

    delete [] cells;
}

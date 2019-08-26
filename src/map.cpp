#include "../inc/map.h"
#include "../inc/cellstates.h"
#include "../inc/location.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

Map::Map(){
    cells = new CellStates*[50];
    for(int i = 0; i < 50; i++){
        cells[i] = new CellStates[20];
        for(int k = 0; k < 20; k++){
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

    for(int i = 0; i < 52; i++){
        cout<<"#";
    }
    cout<<endl;
    for(int i = 0; i < 20; i++){
        cout<<"#";
        for(int k = 0; k < 50; k++){
            cout<<" ";
        }
        cout<<"#"<<endl;
    }
    for(int i = 0; i < 52; i++){
        cout<<"#";
    }
}

Map::~Map(){
    for(int i = 0; i < 50; i++){
        delete [] cells[i];
    }

    delete [] cells;
}

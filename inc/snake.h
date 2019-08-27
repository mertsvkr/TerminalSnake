#ifndef SnakeH
#define SnakeH

#include "location.h"
#include "map.h"
class Snake{
    Map* map;
    bool moveTheHead(bool*, bool*);
    bool checkSnakeCollision(Location*, Map*, bool*, bool*);
    bool checkMapBorderCollision(CellStates &, Location*);
    void moveTheTail(bool);

public:
    Snake(Map* map);
    Location *headLocation, *tailLocation;
    bool move(bool* isThereFood);
    ~Snake();
};


#endif

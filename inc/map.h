#ifndef MapH
#define MapH
#include "cellstates.h"
#include "location.h"

class Map{
    CellStates **cells;
    void drawMap();
public:
    Map();
    CellStates getCellStatus(Location *location);
    void setCellStatus(Location *location, CellStates state);
    ~Map();
};

#endif
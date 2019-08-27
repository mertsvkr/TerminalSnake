#ifndef MapH
#define MapH
#include "cellstates.h"
#include "location.h"

//lengths for map size
extern int HORIZONTAL_LENGTH ;
extern int VERTICAL_LENGTH;

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

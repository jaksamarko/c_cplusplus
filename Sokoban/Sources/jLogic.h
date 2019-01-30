#ifndef J_LOGIC_H
#define J_LOGIC_H
#include"jInit.h"
#include<stdbool.h>
bool checkWin(staticObjects *box, staticObjects *goal);

struct staticObjects* boxIsThere(staticObjects *first, int x, int y);

bool placeFree(int x, int y);
bool playerCollide(movingObjects player, staticObjects *boxes);

#endif // J_LOGIC_H

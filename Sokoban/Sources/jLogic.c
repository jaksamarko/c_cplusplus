#include"jLogic.h"
bool checkWin(staticObjects *box, staticObjects *goal)
{
    bool done;
    staticObjects *goalFirst=goal;
    while(box!=NULL)
    {
        done=false;
        goal=goalFirst;
        while(goal!=NULL)
        {
            if(box->x==goal->x && box->y==goal->y)
            {
                done=true;
                break;
            }
            goal=goal->next;
        }
        if(!done)
        {
            return false;
        }
        box=box->next;
    }
    return true;
}

struct staticObjects* boxIsThere(staticObjects *first, int x, int y)
{
    while(first!=NULL)
    {
        if(first->x==x && first->y==y)
        {
            return first;
        }
        first=first->next;
    }
    return NULL;
}

bool placeFree(int x, int y)
{
    return (gameMap[x][y]!=cols[0]);
}

bool playerCollide(movingObjects player, staticObjects *boxes)
{
    int xdir,ydir;
    struct staticObjects *bColl;
    bColl=boxIsThere(boxes,player.x,player.y);
    if(bColl!=NULL)
    {
        xdir=player.x-player.prevx;
        ydir=player.y-player.prevy;

        if(!placeFree(bColl->x+xdir,bColl->y+ydir)||
                boxIsThere(boxes,bColl->x+xdir,bColl->y+ydir)!=NULL)
        {
            return true;
        }
        bColl->x+=xdir;
        bColl->y+=ydir;
        return false;
    }
    if(!placeFree(player.x,player.y))
    {
        return true;
    }
    return false;
}

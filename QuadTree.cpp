#include "precomp.h"
#include "QuadTree.h"

//void BattleSim::QuadTree::insert(QNode node)
//{
//    if (&node == nullptr) return;
//    if (!inBoundary(node.pos)) return;
//
//    if (abs(topLeftBorder.x + botRightBorder.x) <= 1 &&
//        abs(topLeftBorder.y - botRightBorder.y) <= 1)
//    {
//        if (n == nullptr)
//            n = &node;
//        return;
//    }
//    //defines North Tree or South Tree
//    if ((topLeftBorder.x + botRightBorder.x) / 2 >= node.pos.x)
//    {
//        //defines West or East;
//        if ((topLeftBorder.x + botRightBorder.x) / 2 >= node.pos.y)
//        {
//
//            if (NWTree == NULL)
//                NWTree = new QuadTree(
//                    vec2(topLeftBorder.x, topLeftBorder.y),
//                    vec2((topLeftBorder.x + botRightBorder.x) / 2,
//                         (topLeftBorder.y + botRightBorder.y) / 2));
//            NWTree->insert(node);
//        }
//        else
//        {
//            //indicates NE Tree
//            if (NETree == NULL)
//                NETree = new QuadTree(
//                    vec2(topLeftBorder.x, (topLeftBorder.y + botRightBorder.y) / 2),
//                    vec2((topLeftBorder.x + botRightBorder.x) / 2, botRightBorder.y));
//            NETree->insert(node);
//        }
//    }
//    else //south tree
//    {
//        //defines West or East;
//        if ((topLeftBorder.y + botRightBorder.y) / 2 >= node.pos.y)
//        {
//            if (SWTree == nullptr)
//            {
//                SWTree = new QuadTree(
//                    vec2((topLeftBorder.x + botRightBorder.x) / 2, topLeftBorder.y),
//                    vec2( botRightBorder.x, (topLeftBorder.y + botRightBorder.y) / 2));
//            }
//            SWTree->insert(node);
//        }
//        else
//        {
//            if (SETree == nullptr)
//            {
//                SETree = new QuadTree(
//                    vec2((topLeftBorder.x + botRightBorder.x) / 2, (topLeftBorder.y + botRightBorder.y) / 2),
//                    vec2( botRightBorder.x, botRightBorder.y));
//            }
//            SETree->insert(node);
//        }
//    }
//}

bool BattleSim::QuadTree::insertNode(QNode node)
{
    if (&node == nullptr) return false;
    if (!inBoundary(node.pos)) return false;
    if (points.size() < this->capacity && NWTree == NULL) {
        points.push_back(&node);
        count++;
        float k = 5;
        node.test = k;
       /* node.NWBorder = abs(topLeftBorder.x - node.pos.x);
        node.NEBorder = abs(topLeftBorder.y - node.pos.y);
        node.SWBorder = abs(botRightBorder.x - node.pos.x);
        node.SEBorder = abs(botRightBorder.x - node.pos.x);*/
        this->points;
        return true;
  
   }
    this->points;
    if (NWTree == NULL) {
        subdivide();
    }
    if (NWTree->insertNode(node)) return true;    
    if (NETree->insertNode(node)) return true;
    if (SWTree->insertNode(node)) return true;
    if (SETree->insertNode(node)) return true;

    return false;
}

void BattleSim::QuadTree::subdivide()
{
    NWTree = new QuadTree(
        vec2(topLeftBorder.x, topLeftBorder.y),
        vec2((topLeftBorder.x + botRightBorder.x) / 2,
                (topLeftBorder.y + botRightBorder.y) / 2));

    NETree = new QuadTree(
        vec2(topLeftBorder.x, (topLeftBorder.y + botRightBorder.y) / 2),
        vec2((topLeftBorder.x + botRightBorder.x) / 2, botRightBorder.y));

    SWTree = new QuadTree(
        vec2((topLeftBorder.x + botRightBorder.x) / 2, topLeftBorder.y),
        vec2( botRightBorder.x, (topLeftBorder.y + botRightBorder.y) / 2));

    SETree = new QuadTree(
        vec2((topLeftBorder.x + botRightBorder.x) / 2, (topLeftBorder.y + botRightBorder.y) / 2),
        vec2( botRightBorder.x, botRightBorder.y));
    for (auto node : points) {
        this->NETree->insertNode(*node);
        this->NWTree->insertNode(*node);
        this->SETree->insertNode(*node); 
        this->SWTree->insertNode(*node);
        
    }
    points.clear();

}

QNode BattleSim::QuadTree::FindClosest(vec2 tankpos, QNode closestnode)
{
    //go to the quadrent tankpos
    //check if it has more quadtree's
    //
    return QNode();
}

bool BattleSim::QuadTree::inBoundary(vec2 point)
{
   return(point.x <= topLeftBorder.x &&
        point.x >= botRightBorder.x &&
        point.y <= topLeftBorder.y &&
        point.y >= botRightBorder.y)
        ;
}


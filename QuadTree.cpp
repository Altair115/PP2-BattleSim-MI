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

bool BattleSim::QuadTree::insertNode(QNode *node)
{
    if (&node == nullptr) return false;
    if (!inBoundary(node->pos)) return false;
    if (points.size() < this->capacity && NWTree == NULL) {
        points.push_back(node);
        count++;

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
                (topLeftBorder.y + botRightBorder.y) / 2),this);

    NETree = new QuadTree(
        vec2(topLeftBorder.x, (topLeftBorder.y + botRightBorder.y) / 2),
        vec2((topLeftBorder.x + botRightBorder.x) / 2, botRightBorder.y),this);

    SWTree = new QuadTree(
        vec2((topLeftBorder.x + botRightBorder.x) / 2, topLeftBorder.y),
        vec2( botRightBorder.x, (topLeftBorder.y + botRightBorder.y) / 2),this);

    SETree = new QuadTree(
        vec2((topLeftBorder.x + botRightBorder.x) / 2, (topLeftBorder.y + botRightBorder.y) / 2),
        vec2( botRightBorder.x, botRightBorder.y),this);
    for (auto node : points) {
        this->NETree->insertNode(node);
        this->NWTree->insertNode(node);
        this->SETree->insertNode(node); 
        this->SWTree->insertNode(node);
        
    }
    points.clear();

}

QNode* BattleSim::QuadTree::FindClosest(vec2 tankpos, QNode* closestnode = nullptr, float closestdistance = numeric_limits<float>::infinity())
{
    if(this->NETree->count > 0 && this->NETree->rectangle->intersectsCircle(tankpos, closestdistance)) {
        if (this->NETree->points.size() == 0 && this->NETree->count==4) {
           closestnode = this->NETree->FindClosest(tankpos, closestnode, closestdistance);
        }
        else if (this->NETree->points.size() > 0)
        {
            auto tupleNodeDistantce = this->NETree->closestDistanceinPoints(tankpos, closestdistance);
            closestnode = get<0>(tupleNodeDistantce);
            closestdistance = get<1>(tupleNodeDistantce);
            auto x = get<0>(tupleNodeDistantce);
            auto d = get<1>(tupleNodeDistantce);
            
        }
        //if no points go in deeper
    }  
    if (this->NWTree->count >0 && this->NWTree->rectangle->intersectsCircle(tankpos, closestdistance))
    {
        if (this->NWTree->points.size() == 0 && this->NWTree->count==4)
        {
            closestnode = this->NWTree->FindClosest(tankpos, closestnode, closestdistance);
        }
        else if (this->NWTree->points.size() > 0)
        {
            auto tupleNodeDistantce = this->NWTree->closestDistanceinPoints(tankpos, closestdistance);
            closestnode = get<0>(tupleNodeDistantce);
            closestdistance = get<1>(tupleNodeDistantce);
        }
    }   
    if (this->SETree->count >0 && this->SETree->rectangle->intersectsCircle(tankpos, closestdistance))
    {
        if (this->SETree->points.size() == 0 && this->SETree->count == 4)
        {
            closestnode =this->SETree->FindClosest(tankpos, closestnode, closestdistance);
        }
        else if (this->SETree->points.size()>0)
        {
            auto tupleNodeDistantce = this->SETree->closestDistanceinPoints(tankpos, closestdistance);
            closestnode = get<0>(tupleNodeDistantce);
            closestdistance = get<1>(tupleNodeDistantce);
        }
    }   
    if (this->SWTree->count >0 && this->SWTree->rectangle->intersectsCircle(tankpos, closestdistance))
    {
        if (this->SWTree->points.size() == 0 && this->SWTree->count == 4)
        {
            closestnode = this->SWTree->FindClosest(tankpos, closestnode, closestdistance);
        }
        else if (this->SWTree->points.size()>0)
        {
            auto tupleNodeDistantce = this->SWTree->closestDistanceinPoints(tankpos, closestdistance);
            closestnode = get<0>(tupleNodeDistantce);
            closestdistance = get<1>(tupleNodeDistantce);
        }
    }

    return closestnode;
}

bool BattleSim::QuadTree::inBoundary(vec2 point)
{
   return(point.x <= topLeftBorder.x &&
        point.x >= botRightBorder.x &&
        point.y <= topLeftBorder.y &&
        point.y >= botRightBorder.y)
        ;
}

tuple<QNode*,float> BattleSim::QuadTree::closestDistanceinPoints(vec2 tankpos,float closestdistance)
{
    QNode *closestNode = new QNode();
    for (int i = 0; i < points.size(); i++)
    {
        float distance = sqrt((tankpos.x - points[i]->pos.x) + (tankpos.y - points[i]->pos.y));
        if (distance < closestdistance)
        {
            closestNode = points[i];
            closestdistance = distance;
        }
    }
    return make_tuple(closestNode,closestdistance);
}


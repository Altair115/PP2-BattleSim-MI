#pragma once
namespace BattleSim
{
class QNode
{
  private:

  public:
    QNode(vec2 _pos, Tank _tank)
    {
        tank = &_tank;
        pos = _pos;
        NWBorder = numeric_limits<float>::infinity();
        NEBorder = numeric_limits<float>::infinity();
        SWBorder = numeric_limits<float>::infinity();
        SEBorder = numeric_limits<float>::infinity();
    }
    QNode()
    {
        tank = nullptr;
    }

    float NWBorder;
    float NEBorder;
    float SWBorder;
    float SEBorder;
    vec2 pos = (0, 0);
    Tank* tank = nullptr;
};
class QuadTree
{
    int capacity = 4;
    int count;
    vector<QNode*> points;
    QuadTree* NETree;
    QuadTree* NWTree;
    QuadTree* SETree;
    QuadTree* SWTree;

  public:
    vec2 topLeftBorder;
    vec2 botRightBorder;
    QuadTree()
    {
        count = 0;

        topLeftBorder = (0, 0);
        botRightBorder = (0, 0);
        NETree = nullptr;
        NWTree = nullptr;
        SETree = nullptr;
        SWTree = nullptr;
    }
    QuadTree(vec2 topL, vec2 botR)
    {

        count = 0;
        NETree = nullptr;
        NWTree = nullptr;
        SETree = nullptr;
        SWTree = nullptr;
        topLeftBorder = topL;
        botRightBorder = botR;
    }
    bool insertNode(QNode);
    void subdivide();
    QNode FindClosest(vec2, QNode);
    bool inBoundary(vec2);
};
} // namespace BattleSim

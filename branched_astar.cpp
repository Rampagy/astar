#include "branched_astar.hpp"


vector<Position> astar_search(  const vector<vector<int>> &weighted_map,
                                const Position start, const Position goal )
{
    int mapWidth = weighted_map.front().size();
    int mapHeight = weighted_map.size();

    vector<Position> path = {};
    if (start.x < 0 || start.y < 0 || goal.x >= mapWidth || goal.y >= mapHeight ||
        start == goal )
    {
        return path;
    }


    unordered_set<Position> close_set;
    unordered_map<Position, Position> came_from;
    unordered_map<Position, float> gscore;
    unordered_map<Position, float> fscore;
    priority_queue<score_T, vector<score_T>, greater<score_T>> oheap;
    unordered_set<Position> oheap_copy;



    path.push_back( Position(0,0) );
    path.push_back( Position(0,0) );
    return path;
}
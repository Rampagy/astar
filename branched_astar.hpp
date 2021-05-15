#ifndef BRANCHED_ASTAR_HPP
#define BRANCHED_ASTAR_HPP


#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <iostream>
#include "position.hpp"


using namespace std;


typedef pair<float, Position> score_T;


vector<Position> astar_search(  const vector<vector<int>> &weighted_map,
                                const Position start, const Position goal );


#endif
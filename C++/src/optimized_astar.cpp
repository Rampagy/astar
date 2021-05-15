#include "optimized_astar.hpp"

/** References:
 *      https://www.geeksforgeeks.org/a-search-algorithm/
 *
 */


float optimized_heuristic(Position a, Position b)
{
    return (float)abs( (a.x - b.x) + (a.y - b.y) );
}


vector<Position> optimized_astar_search(  const vector<vector<int>> &weighted_map,
                                          const Position start, const Position goal )
{
    int mapWidth = weighted_map.front().size();
    int mapHeight = weighted_map.size();

    vector<Position> path = {};
    if (start.x < 0 || start.y < 0 || goal.x >= mapWidth || goal.y >= mapHeight ||
        start == goal || mapWidth < 2 || mapHeight < 2 )
    {
        return path;
    }

    unordered_set<Position> close_set;
    unordered_map<Position, Position> came_from;
    unordered_map<Position, float> gscore;
    unordered_map<Position, float> fscore;
    priority_queue<score_T, vector<score_T>, greater<score_T>> oheap;

    Position current;
    array<Position, 4> neighbors;
    std::unordered_map<Position, float>::iterator neighbor_iter;
    float tentative_gscore;
    float current_gscore;

    // add initial position to the search list
    gscore[start] = 0;
    fscore[start] = optimized_heuristic(start, goal);
    oheap.emplace(fscore[start], start);


    while ( !oheap.empty() )
    {
        current = oheap.top().second;
        oheap.pop();

        if (current == goal)
        {
            // path found!
            while (came_from.find(current) != came_from.end())
            {
                path.push_back(current);
                current = came_from[current];
            }

            reverse(path.begin(), path.end());

            return path;
        }

        // add current position to the already searched list
        close_set.insert(current);
        neighbors = current.get_surrounding_positions();

        // search surrounding neighbors
        for (Position neighbor : neighbors)
        {
            // if the neighbor is a valid position
            if (neighbor.x >= 0 && neighbor.y >= 0 &&
                neighbor.y < mapHeight && neighbor.x < mapWidth &&
                weighted_map[neighbor.y][neighbor.x] < 255)
            {
                tentative_gscore = gscore[current];
                neighbor_iter = gscore.find(neighbor);

                if (neighbor_iter == gscore.end())
                {
                    current_gscore = 0;
                }
                else
                {
                    current_gscore = neighbor_iter->second;
                }

                // if the neighbor is not in the closed set or
                // it's gscore is better than the current
                if ((close_set.find(neighbor) == close_set.end()) ||
                    (tentative_gscore < current_gscore))
                {
                    came_from[neighbor] = current;

                    // gscore = cost to get from start to the current position
                    gscore[neighbor] = tentative_gscore;

                    // hscore = estimated cost to get from the current position to the goal
                    // fscore = gscore +  hscore
                    fscore[neighbor] = tentative_gscore + optimized_heuristic(neighbor, goal);
                    oheap.emplace(fscore[neighbor], neighbor);
                }
            }
        }
    }

    return path;
}
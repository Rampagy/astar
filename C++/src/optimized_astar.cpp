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
    unordered_set<Position> oheap_copy;

    Position current;
    array<Position, 4> neighbors;
    std::unordered_map<Position, float>::iterator neighbor_iter;
    float tentative_gscore;
    float current_gscore;

    // add initial position to the search list
    gscore[start] = 0;
    fscore[start] = optimized_heuristic(start, goal);
    oheap.emplace(fscore[start], start);
    oheap_copy.insert(start);

    while ( !oheap.empty() )
    {
        current = oheap.top().second;
        oheap.pop();
        oheap_copy.erase(current);

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
                tentative_gscore = gscore[current] + (float)weighted_map[neighbor.y][neighbor.x];
                neighbor_iter = gscore.find(neighbor);

                if (neighbor_iter == gscore.end())
                {
                    current_gscore = 0;
                }
                else
                {
                    current_gscore = neighbor_iter->second;
                }

                if ((tentative_gscore >= current_gscore) &&
                    (close_set.find(neighbor) != close_set.end()))
                {
                    continue;
                }

                if ((tentative_gscore < current_gscore) ||
                    (oheap_copy.find(neighbor) == oheap_copy.end()))
                {
                    // track the node's parent
                    came_from[neighbor] = current;

                    // gscore = cost to get from start to the current position
                    // hscore = estimated cost to get from the current position to the goal
                    // fscore = gscore +  hscore
                    gscore[neighbor] = tentative_gscore;
                    fscore[neighbor] = tentative_gscore + optimized_heuristic(neighbor, goal);

                    // Add to the open list
                    oheap.emplace(fscore[neighbor], neighbor);
                    if (oheap_copy.find(neighbor) == oheap_copy.end())
                    {
                        // don't add twice (keys must be unique)
                        oheap_copy.insert(neighbor);
                    }
                }
            }
        }
    }

    return path;
}
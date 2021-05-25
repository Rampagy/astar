#include "optimized_astar.hpp"


/** References:
 *      https://www.geeksforgeeks.org/a-search-algorithm/
 *
 */


float optimized_heuristic(Position a, Position b)
{
    return (float)abs( (a.x - b.x) + (a.y - b.y) );
}

bool greater_comp(const score_T a, const score_T b)
{
    return a.first > b.first;
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
    deque<score_T> oheap;
    unordered_map<Position, float> oheap_copy;

    Position current;
    array<Position, 4> neighbors;
    std::unordered_map<Position, float>::iterator neighbor_iter;
    std::unordered_map<Position, float>::iterator open_iter;

    // add initial position to the search list
    gscore[start] = 0;
    fscore[start] = optimized_heuristic(start, goal);
    oheap.emplace_back(fscore[start], start);
    push_heap(oheap.begin(), oheap.end(), greater_comp);
    oheap_copy.emplace(start, fscore[start]);

    while ( !oheap.empty() )
    {
        pop_heap(oheap.begin(), oheap.end());
        oheap.pop_back();
        current = oheap.front().second;
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

        neighbors = current.get_surrounding_positions();

        // search surrounding neighbors
        for (Position neighbor : neighbors)
        {
            // if the neighbor is a valid position
            if (neighbor.x >= 0 && neighbor.y >= 0 &&
                neighbor.y < mapHeight && neighbor.x < mapWidth &&
                weighted_map[neighbor.y][neighbor.x] < 255)
            {
                float neighbor_gscore = gscore[current] + (float)weighted_map[neighbor.y][neighbor.x] +
                                optimized_heuristic(neighbor, current);
                float neighbor_fscore = neighbor_gscore + optimized_heuristic(neighbor, goal);

                // if this neighbor is already on the open list with a smaller fscore, skip it
                open_iter = oheap_copy.find(neighbor);
                if (open_iter != oheap_copy.end())
                {
                    if (open_iter->second <= neighbor_fscore)
                    {
                        continue;
                    }
                }
                // check if it is on the closed list
                else if (close_set.find(neighbor) != close_set.end())
                {
                    if (fscore.find(neighbor)->second <= neighbor_fscore)
                    {
                        continue;
                    }
                }
                // Add to the open list
                else
                {
                    // track the node's parent
                    came_from[neighbor] = current;

                    // gscore = cost to get from start to the current position
                    // hscore = estimated cost to get from the current position to the goal (heuristic)
                    // fscore = gscore +  hscore
                    gscore[neighbor] = neighbor_gscore;
                    fscore[neighbor] = neighbor_fscore;

                    // Add to the open list
                    oheap_copy.emplace(neighbor, fscore[neighbor]);
                    oheap.emplace_back(fscore[neighbor], neighbor);
                    push_heap(oheap.begin(), oheap.end(), greater_comp);
                }
            }
        }

        // add current position to the already searched list
        close_set.insert(current);
    }

    return path;
}

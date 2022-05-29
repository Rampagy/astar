#include "optimized_astar.hpp"
#include "main.hpp"

/** References:
 *      https://www.geeksforgeeks.org/a-search-algorithm/
 *      https://medium.com/@nicholas.w.swift/easy-a-star-pathfinding-7e6689c7f7b2
 *      http://theory.stanford.edu/~amitp/GameProgramming/ImplementationNotes.html
 * 
 */


inline float optimized_heuristic(Position a, Position b)
{
    return (float)abs( (a.x - b.x) + (a.y - b.y) );
}

inline bool greater_comp(const score_T a, const score_T b)
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
    vector<score_T> oheap;
    unordered_map<Position, float> oheap_copy;

    Position current;
    array<Position, 4> neighbors;
    std::unordered_map<Position, float>::iterator neighbor_iter;
    std::unordered_map<Position, float>::iterator open_iter;

    // Memory preallocation
    oheap.reserve(mapWidth + mapHeight);
    oheap_copy.reserve(mapWidth * mapHeight);
    close_set.reserve(mapWidth * mapHeight);
    came_from.reserve(mapWidth * mapHeight);
    gscore.reserve(mapWidth * mapHeight);
    fscore.reserve(mapWidth * mapHeight);
    path.reserve(mapWidth + mapHeight);

    // add initial position to the search list
    gscore[start] = 0;
    fscore[start] = 0;
    oheap.emplace_back(fscore[start], start);
    push_heap(oheap.begin(), oheap.end(), greater_comp);
    oheap_copy.emplace(start, fscore[start]);

    int count = 0;
    while ( !oheap.empty() )
    {
        count++;
        pop_heap(oheap.begin(), oheap.end(), greater_comp);
        oheap.pop_back();
        current = oheap.front().second;
        oheap_copy.erase(current);
        close_set.insert(current);

        #if defined(TEST_ASTAR)
        cout << current << endl;
        #endif

        if (current == goal)
        {
            // path found!
            while (came_from.find(current) != came_from.end())
            {
                path.push_back(current);
                current = came_from[current];
            }
            
            reverse(path.begin(), path.end());
            cout << "count: " << count << endl;
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


                // if the neighbor is already on the open list check to see if the neighbor is better before updating it
                open_iter = oheap_copy.find(neighbor);
                if (open_iter != oheap_copy.end() && neighbor_gscore < gscore[neighbor])
                {
                    // track the node's parent
                    came_from[neighbor] = current;

                    // gscore = cost to get from start to the current position
                    // hscore = estimated cost to get from the current position to the goal (heuristic)
                    // fscore = gscore +  hscore
                    gscore[neighbor] = neighbor_gscore;
                    fscore[neighbor] = neighbor_fscore;

                    // update the neighbors values
                    oheap_copy[neighbor] = neighbor_fscore;

                    // remove the old fscore
                    for (int i = 0; i < oheap.size(); i++)
                    {
                        if (oheap[i].second == neighbor)
                        {
                            oheap.erase(oheap.begin() + i);
                            break;
                        }
                    }

                    // add the new fscore and sort
                    oheap.emplace_back(neighbor_fscore, neighbor);
                    make_heap(oheap.begin(), oheap.end(), greater_comp);
                }

                if (close_set.find(neighbor) != close_set.end() && neighbor_gscore < gscore[neighbor])
                {
                    // remove neighbor from closed list
                    close_set.erase(neighbor);
                }
                
                // it's not on the oheap or close set, so add it
                if (close_set.find(neighbor) == close_set.end() && open_iter == oheap_copy.end()) 
                {
                    // track the node's parent
                    came_from[neighbor] = current;

                    // gscore = cost to get from start to the current position
                    // hscore = estimated cost to get from the current position to the goal (heuristic)
                    // fscore = gscore +  hscore
                    gscore[neighbor] = neighbor_gscore;
                    fscore[neighbor] = neighbor_fscore;

                    // Add to the open list
                    oheap_copy.emplace(neighbor, neighbor_fscore);
                    oheap.emplace_back(neighbor_fscore, neighbor);
                    push_heap(oheap.begin(), oheap.end(), greater_comp);
                }
            }
        }
    }

    return path;
}

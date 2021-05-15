#include "branched_astar.hpp"


#define ABS_MACRO(x) (x) < 0 ? (x)*-1 : (x)


/** References:
 *      https://www.geeksforgeeks.org/a-search-algorithm/
 *
 */


float branched_heuristic(Position a, Position b)
{
    return ABS_MACRO( (a.x - b.x) + (a.y - b.y) );
}


vector<Position> branched_astar_search(  const vector<vector<int>> &weighted_map,
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

    // add initial position to the search list
    gscore[start] = 0;
    fscore[start] = branched_heuristic(start, goal);
    oheap.push(make_pair(fscore[start], start));
    oheap_copy.insert(start);


    while ( !oheap.empty() )
    {
        Position current = oheap.top().second;
        oheap.pop();
        oheap_copy.erase(current);

        if (current == goal)
        {
            while (came_from.find(current) != came_from.end())
            {
                path.push_back(current);
                current = came_from[current];
            }

            reverse(path.begin(), path.end());

            // path found!
            return path;
        }

        // add current position to the already searched list
        close_set.insert(current);
        array<Position, 4> neighbors = current.get_surrounding_positions();

        // search surrounding neighbors
        for (Position neighbor : neighbors)
        {
            if (neighbor.x < 0 || neighbor.y < 0 ||
                neighbor.y >= mapHeight || neighbor.x >= mapWidth ||
                weighted_map[neighbor.y][neighbor.x] >= 255)
            {
                // this position is an invalid position OR it is unwalkable
                continue;
            }

            float tentative_gscore = gscore[current];
            float current_gscore;
            if (gscore.find(neighbor) == gscore.end())
            {
                current_gscore = 0;
            }
            else
            {
                current_gscore = gscore.find(neighbor)->second;
            }

            // if the neighbor has already been searched
            // only replace if the new score is better than the previous
            if ((close_set.find(neighbor) != close_set.end()) &&
                (tentative_gscore >= current_gscore))
            {
                continue;
            }

            // if the new gscore (path) is better than the existing path
            // and the position has already been searched update the position
            if ( (tentative_gscore < current_gscore) ||
                 (oheap_copy.find(neighbor) == oheap_copy.end()) )
            {
                came_from[neighbor] = current;

                // gscore = cost to get from start to the current position
                gscore[neighbor] = tentative_gscore;

                // hscore = estimated cost to get from the current position to the goal
                // fscore = gscore +  hscore
                fscore[neighbor] = tentative_gscore + branched_heuristic(neighbor, goal);
                oheap.push(make_pair(fscore[neighbor], neighbor));

                // if neighbor is not already in the open list add it
                if (oheap_copy.find(neighbor) == oheap_copy.end())
                {
                    // don't add twice (keys must be unique)
                    oheap_copy.insert(neighbor);
                }
            }
        }
    }

    return path;
}
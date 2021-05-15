#include "main.hpp"


int main ()
{
    Position start = Position(0, 0);
    Position goal = Position(4, 4);

    vector<vector<int>> map = {
        {0, 255, 0,   0, 0},
        {0, 255, 0, 255, 0},
        {0, 255, 0, 255, 0},
        {0, 255, 0, 255, 0},
        {0,   0, 0, 255, 0},
    };

    vector<Position> path = astar_search(map, start, goal);

    for (const auto pos : path)
    {
        cout << pos.to_string() << "\n";
    }
}
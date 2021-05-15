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

    auto start_time = chrono::high_resolution_clock::now();

    vector<Position> path = astar_search(map, start, goal);

    auto end_time = chrono::high_resolution_clock::now();
    double duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

    cout << "Path found in " << duration << " microseconds, path = ";

    for (const auto pos : path)
    {
        cout << pos.to_string() << " ";
    }
    cout << endl;


}
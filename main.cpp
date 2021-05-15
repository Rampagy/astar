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

    // list of function pointers
    vector<vector<Position> (*)(const vector<vector<int>> &, const Position, const Position)> astar_functions;
    astar_functions.push_back( branched_astar_search );
    astar_functions.push_back( optimized_astar_search );


    for (const auto astar_algo : astar_functions)
    {
        double fastest_time = numeric_limits<double>::infinity();
        vector<Position> path;

        for (int i = 0; i < 25; i++)
        {
            chrono::high_resolution_clock::time_point start_time, end_time;
            double duration;

            start_time = chrono::high_resolution_clock::now();

            path = (*astar_algo)(map, start, goal);

            end_time = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

            if (duration < fastest_time)
            {
                fastest_time = duration;
            }
        }

        cout << "Path found in " << fastest_time << " microseconds, path = ";

        for (const auto pos : path)
        {
            cout << pos.to_string() << " ";
        }
        cout << endl;
    }

    /*
    // branched A*
    start_time = chrono::high_resolution_clock::now();

    path = branched_astar_search(map, start, goal);

    end_time = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

    cout << "Path found in " << duration << " microseconds, path = ";

    for (const auto pos : path)
    {
        cout << pos.to_string() << " ";
    }
    cout << endl;


    // branchless A*
    start_time = chrono::high_resolution_clock::now();

    path = optimized_astar_search(map, start, goal);

    end_time = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

    cout << "Path found in " << duration << " microseconds, path = ";

    for (const auto pos : path)
    {
        cout << pos.to_string() << " ";
    }
    cout << endl;*/
}
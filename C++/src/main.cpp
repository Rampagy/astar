#include "main.hpp"




void generate_maze(vector<vector<int>> &maze)
{
    cout << "Generating maze..." << endl;

    // height
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        vector<int> maze_row;
        // width
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            maze_row.push_back(rand() % 256);
        }

        maze.push_back(maze_row);
    }
}


int main ()
{
    Position start = Position(0, 0);
    Position goal = Position(MAP_WIDTH-1, MAP_HEIGHT-1);
    vector<vector<int>> maze;

    // generate the maze
    generate_maze(maze);

    // make sure start and end are walkable
    maze[start.y][start.x] = 0;
    maze[goal.y][goal.x] = 0;

    // list of function pointers
    vector<vector<Position> (*)(const vector<vector<int>> &, const Position, const Position)> astar_functions;
    astar_functions.push_back( branched_astar_search );
    astar_functions.push_back( optimized_astar_search );

    cout << "Starting search..." << endl;

    // for each astar algorithm run 25 iterations and report the fastest time
    for (const auto astar_algo : astar_functions)
    {
        double total_time = 0;
        vector<Position> path;

        for (int i = 0; i < SEARCH_ITERATIONS; i++)
        {
            chrono::high_resolution_clock::time_point start_time, end_time;
            double duration;

            start_time = chrono::high_resolution_clock::now();

            path = (*astar_algo)(maze, start, goal);

            end_time = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

            total_time += duration;
        }

        cout << "Path found in " << total_time/1000/1000 << " seconds" << endl;
    }
}
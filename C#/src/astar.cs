using System;
using System.Collections;
using System.Collections.Generic;

namespace astar
{
    public partial class main
    {
        static Random rnd = new Random();
        const int MAP_WIDTH = 500;
        const int MAP_HEIGHT = 500;
        const int SEARCH_ITERATIONS = 100;
        static List<List<int>> maze = new List<List<int>>();
        static double total_time = 0;


        public static void Main(string[] args)
        {
            Position start = new Position(0, 0);
            Position goal = new Position(MAP_WIDTH - 1, MAP_HEIGHT - 1);
            List<Position> path = new List<Position>();

            // generate the maze
            generateMaze();

            // make sure the start and end are walkable
            maze[start.y][start.x] = 0;
            maze[goal.y][goal.x] = 0;

            Console.WriteLine(maze.Count);
            Console.WriteLine(maze[0].Count);
        }

        static void generateMaze()
        {
            // height
            for (int i = 0; i < MAP_HEIGHT; i++)
            {
                List<int> maze_row = new List<int>();
                // width
                for (int j = 0; j < MAP_WIDTH; j++)
                {
                    maze_row.Add(rnd.Next(0, 255));
                }
                maze.Add(maze_row);
            }
        }
    }
}
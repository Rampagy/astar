using System;
using System.Diagnostics;
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

            for (int i = 0; i < SEARCH_ITERATIONS; i++)
            {
                Stopwatch stopwatch = new Stopwatch();
                stopwatch.Start();

                AStarSearch(maze, start, goal);

                stopwatch.Stop();
                total_time += stopwatch.Elapsed.TotalSeconds;
            }

            Console.WriteLine("C++ path found in " + total_time + " seconds");
        }

        private static void generateMaze()
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

        private static List<Position> AStarSearch(  in List<List<int>> weightedMap,
                                                    in Position start, in Position goal)
        {
            int mapWidth = weightedMap[0].Count;
            int mapHeight = weightedMap.Count;

            List<Position> path = new List<Position>();
            if (start.x < 0 || start.y < 0 || goal.x >= mapWidth || goal.y >= mapHeight ||
                start == goal || mapWidth < 2 || mapHeight < 2 )
            {
                return path;
            }


            Console.WriteLine("Fooled You!");

            return path;
        }
    }
}
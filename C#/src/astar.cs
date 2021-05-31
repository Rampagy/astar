using System;
using System.Diagnostics;
using System.Collections;
using System.Collections.Generic;
using Priority_Queue;

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

                // regenerate the map
                maze.Clear();
                generateMaze();
            }

            Console.WriteLine("C# path found in " + total_time + " seconds");
        }

        private static void generateMaze()
        {
            // height
            for (int i = 0; i < MAP_HEIGHT; i++)
            {
                List<int> maze_row = new List<int>(MAP_WIDTH);
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

            List<Position> path = new List<Position>((mapWidth + mapHeight) << 2);
            if (start.x < 0 || start.y < 0 || goal.x >= mapWidth || goal.y >= mapHeight ||
                start == goal || mapWidth < 2 || mapHeight < 2 )
            {
                return path;
            }

            // create a* variables and preallcoate memory at the same time
            HashSet<Position> close_set = new HashSet<Position>((mapWidth * mapHeight) >> 2);
            Dictionary<Position, Position> came_from = new Dictionary<Position, Position>((mapWidth * mapHeight) >> 2);
            Dictionary<Position, float> gscore = new Dictionary<Position, float>((mapWidth * mapHeight) >> 2);
            Dictionary<Position, float> fscore = new Dictionary<Position, float>((mapWidth * mapHeight) >> 2);
            Dictionary<Position, float> oheap_copy = new Dictionary<Position, float>((mapWidth * mapHeight) >> 2);
            // must allocate absolute max that can be in priority_queue because it will not reallocate if it hits max
            FastPriorityQueue<Position> oheap = new FastPriorityQueue<Position>(mapWidth * mapHeight + 1);

            Position current;
            List<Position> neighbors = new List<Position>();

            // add initial position to the search list
            gscore[start] = 0;
            fscore[start] = heuristic(start, goal);
            oheap.Enqueue(start, fscore[start]);
            oheap_copy.Add(start, fscore[start]);

            while ( oheap.Count > 0 )
            {
                // dequeue retrieves and removes
                current = oheap.Dequeue();
                oheap_copy.Remove(current);

                if (current.Equals(goal))
                {
                    // path found!
                    Position new_current;
                    while (came_from.TryGetValue(current, out new_current))
                    {
                        path.Add(new_current);
                        current = new_current;
                    }

                    path.Reverse();

                    return path;
                }

                neighbors = current.GetSurroundingPositions();

                foreach (Position neighbor in neighbors)
                {
                    // if the neighbor is a valid position
                    if (neighbor.x >= 0 && neighbor.y >= 0 &&
                        neighbor.y < mapHeight && neighbor.x < mapWidth &&
                        weightedMap[neighbor.y][neighbor.x] < 255)
                    {
                        float neighbor_gscore = gscore[current] + (float)weightedMap[neighbor.y][neighbor.x] +
                                    heuristic(neighbor, current);
                        float neighbor_fscore = neighbor_gscore + heuristic(neighbor, goal);

                        // if this neighbor is already on the open list with a smaller fscore, skip it
                        float existing_neighbor_fscore = 0F;
                        if (oheap_copy.TryGetValue(neighbor, out existing_neighbor_fscore))
                        {
                            if (existing_neighbor_fscore <= neighbor_fscore)
                            {
                                continue;
                            }
                        }
                        // check if it is on the closed list
                        else if (close_set.Contains(neighbor))
                        {
                            if (fscore[neighbor] <= neighbor_fscore)
                            {
                                continue;
                            }
                        }
                        // add to the open list
                        else
                        {
                            // track the node's parent
                            came_from[neighbor] = current;

                            // gscore = cost to get from the start to the current position
                            // hscore = estimated cost to get from the current position to the goal (heuristic)
                            // fscore = gscore + hscore
                            gscore[neighbor] = neighbor_gscore;
                            fscore[neighbor] = neighbor_fscore;

                            // Add to the open list
                            oheap_copy.Add(neighbor, neighbor_fscore);
                            oheap.Enqueue(neighbor, neighbor_fscore);
                        }

                    }
                }

                // add current position to the already searched list
                close_set.Add(current);
            }

            return path;
        }

        static float heuristic(in Position a, in Position b)
        {
            return (float)Math.Abs( (a.x - b.x) + (a.y - b.y) );
        }
    }
}
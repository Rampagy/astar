package astar;

import java.util.ArrayList;
import java.util.Random;
import java.util.HashMap;
import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.Collections;

public class Main {
    static Random random = new Random();
    final static int MAP_WIDTH = 500;
    final static int MAP_HEIGHT = 500;
    final static int SEARCH_ITERATIONS = 100;
    static ArrayList<ArrayList<Integer>> maze = new ArrayList<ArrayList<Integer>>();
    static double total_time = 0;


    static void GenerateMaze()
    {
        //height
        for (int i = 0; i < MAP_HEIGHT; i++)
        {
            ArrayList<Integer> maze_row = new ArrayList<Integer>();
            //width
            for (int j = 0; j < MAP_WIDTH; j++)
            {
                maze_row.add(Math.abs(random.nextInt()) % 255);
            }
            maze.add(maze_row);
        }
    }


    public static void main(String[] args)
    {
        Position start = new Position(0, 0);
        Position goal = new Position(MAP_WIDTH - 1, MAP_HEIGHT - 1);
        ArrayList<Position> path = new ArrayList<Position>();

        // generate the maze
        GenerateMaze();

        // make sure start and end are walkable
        maze.get(start.y).set(start.x, 0);
        maze.get(goal.y).set(goal.x, 0);

        // loop through maze multiple times and report total time
        for (int i  = 0; i < SEARCH_ITERATIONS; i++)
        {
            long start_time, end_time;

            start_time = System.nanoTime();

            path = AStarSearch(maze, start, goal);

            end_time = System.nanoTime();

            // track total execution time
            total_time += end_time - start_time;

            // generate new maze
            maze.clear();
            GenerateMaze();
        }

        System.out.println("Java path found in " + total_time/1000/1000/1000 + " seconds");
    }


    static ArrayList<Position> AStarSearch( final ArrayList<ArrayList<Integer>> weightedMap,
                                                     final Position start, final Position goal)
    {
        int mapWidth = weightedMap.get(0).size();
        int mapHeight = weightedMap.size();

        ArrayList<Position> path = new ArrayList<Position>();
        if((start.x < 0 )|| (start.y < 0) || (goal.x >= mapWidth) || (goal.y >= mapHeight) ||
                (start == goal) || (mapWidth < 2) || (mapHeight < 2))
        {
            return path;
        }

        HashSet<Position> close_set = new HashSet<>();
        HashMap<Position, Position> came_from = new HashMap<>();
        HashMap<Position, Float> gscore = new HashMap<>();
        HashMap<Position, Float> fscore = new HashMap<>();
        PriorityQueue<Pair> oheap = new PriorityQueue<>();
        HashMap<Position, Float> oheap_copy = new HashMap<>();

        Position current;
        ArrayList<Position> neighbors = new ArrayList<Position>();

        // add initial position to the search list
        gscore.put(start, (float)0);
        fscore.put(start, Heuristic(start, goal));
        oheap.add(new Pair(fscore.get(start), start));
        oheap_copy.put(start, fscore.get(start));

        while ( !oheap.isEmpty() )
        {
            // poll retrieves and removes
            current = oheap.poll().position;
            oheap_copy.remove(current);

            if (current.equals(goal))
            {
                //path found!
                while (came_from.get(current) != null)
                {
                    path.add(current);
                    current = came_from.get(current);
                }

                Collections.reverse(path);

                return path;
            }

            neighbors = current.GetSurroundingPositions();

            // search surrounding neighbors
            for (Position neighbor : neighbors)
            {
                // if the neighbor is a valid position
                if (neighbor.x >= 0 && neighbor.y >= 0 &&
                    neighbor.y < mapHeight && neighbor.x < mapWidth &&
                    weightedMap.get(neighbor.y).get(neighbor.x) < 255)
                {
                    float neighbor_gscore = gscore.get(current) + (float)weightedMap.get(neighbor.y).get(neighbor.x) +
                                    Heuristic(neighbor, current);
                    float neighbor_fscore = neighbor_gscore + Heuristic(neighbor, goal);

                    // if this neighbor is already on the open list with a smaller fscore, skip it
                    Object existing_neighbor_fscore = oheap_copy.get(neighbor);
                    if (existing_neighbor_fscore != null)
                    {
                        if ((float)existing_neighbor_fscore <= neighbor_fscore)
                        {
                            continue;
                        }
                    }
                    // check if it is on the closed list
                    else if (close_set.contains(neighbor))
                    {
                        if (fscore.get(neighbor) <= neighbor_fscore)
                        {
                            continue;
                        }
                    }
                    // add to the open list
                    else
                    {
                        //track the node's parent
                        came_from.put(neighbor, current);

                        // gscore = cost to get from start to the current position
                        // hscore = estimated cost to get from the current position to the goal (heuristic)
                        // fscore = gscore +  hscore
                        gscore.put(neighbor, neighbor_gscore);
                        fscore.put(neighbor, neighbor_fscore);

                        // Add to the open list
                        oheap_copy.put(neighbor, neighbor_fscore);
                        oheap.add(new Pair(neighbor_fscore, neighbor));
                    }
                }
            }

            // add current position to the already searched list
            close_set.add(current);
        }

        return path;
    }


    static float Heuristic(final Position a, final Position b)
    {
        return (float)Math.abs( (a.x - b.x) + (a.y - b.y));
    }
}

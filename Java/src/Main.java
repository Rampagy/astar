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
                maze_row.add(Math.abs(random.nextInt()) % 256);
            }
            maze.add(maze_row);
        }
    }


    public static void main(String[] args)
    {
        Position start = new Position(0, 0);
        Position goal = new Position(MAP_WIDTH - 1, MAP_HEIGHT - 1);

        // generate the maze
        GenerateMaze();

        // make sure start and end are walkable
        maze.get(start.y).set(start.x, 0);
        maze.get(goal.y).set(goal.x, 0);

        // loop through maze multiple times and report total time
        for (int ii  = 0; ii < SEARCH_ITERATIONS; ii++)
        {
            long start_time, end_time;

            start_time = System.nanoTime();

            OptimizedAStarSearch(maze, start, goal);

            end_time = System.nanoTime();

            total_time += end_time - start_time;
        }

        System.out.println("Java path found in " + total_time/1000/1000/1000 + " seconds");
    }


    static ArrayList<Position> OptimizedAStarSearch( final ArrayList<ArrayList<Integer>> weightedMap,
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
        HashSet<Position> oheap_copy = new HashSet<>();

        Position current;
        ArrayList<Position> neighbors = new ArrayList<Position>();
        float tentative_gscore;
        float current_gscore;

        // add initial position to the search list
        gscore.put(start, (float)0);
        fscore.put(start, OptimizedHeuristic(start, goal));
        oheap.add(new Pair(fscore.get(start), start));
        oheap_copy.add(start);

        while ( !oheap.isEmpty() )
        {
            // poll retrieves and removes
            current = oheap.poll().position;
            oheap_copy.remove(current);
            //System.out.print(oheap.size()+":");

            if (current == goal)
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

            // add current position to the already searched list
            close_set.add(current);
            neighbors = current.GetSurroundingPositions();

            // search surrounding neighbors
            for (Position neighbor : neighbors)
            {
                // if the neighbor is a valid position
                if (neighbor.x >= 0 && neighbor.y >= 0 &&
                    neighbor.y < mapHeight && neighbor.x < mapWidth &&
                    weightedMap.get(neighbor.y).get(neighbor.x) < 255)
                {
                    tentative_gscore = gscore.get(current) +  (float)weightedMap.get(neighbor.y).get(neighbor.x);

                    if (gscore.get(neighbor) == null)
                    {
                        current_gscore = 0;
                    }
                    else
                    {
                        current_gscore = gscore.get(neighbor);
                    }

                    if ((tentative_gscore >= current_gscore) &&
                        (close_set.contains(neighbor)))
                    {
                        continue;
                    }

                    if ((tentative_gscore < current_gscore) ||
                        (!oheap_copy.contains(neighbor)))
                    {
                        //track the node's parent
                        came_from.put(neighbor, current);

                        // gscore = cost to get from start to the current position
                        // hscore = estimated cost to get from the current position to the goal
                        // fscore = gscore +  hscore
                        gscore.put(neighbor, tentative_gscore);
                        fscore.put(neighbor, tentative_gscore + OptimizedHeuristic(neighbor, goal));

                        // Add to the open list
                        oheap.add(new Pair(fscore.get(neighbor), neighbor));
                        if ( !oheap_copy.contains(neighbor) )
                        {
                            // don't add twice (keys must be unique)
                            oheap_copy.add(neighbor);
                        }
                    }
                }
            }
        }

        return path;
    }


    static float OptimizedHeuristic(Position a, Position b)
    {
        return (float)Math.abs( (a.x - b.x) + (a.y - b.y));
    }
}
